/** 
 * Atyscape Atys viewer - Landscape Manager
 * 2007-02-25 - Zorglub / Ulukyn
 * 
 * Atyscape is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software: if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/big_file.h>
#include <nel/3d/u_landscape.h>
#include <cmath>
#include <map>


#include <nel/misc/types_nl.h>
#include <nel/misc/event_listener.h>
#include <nel/misc/command.h>
#include <nel/misc/log.h>
#include <nel/misc/time_nl.h>
#include <nel/misc/displayer.h>
#include <nel/misc/vector.h>
#include <nel/misc/vectord.h>
#include <nel/misc/time_nl.h>

/*
 * (dyma) 2008-06-24
 * Build only works for me (linux) if progress_callback.h is
 * includet after vector.h and vectord.h
 *
 * FIXME: Needs test under windows!
 */
#include <nel/misc/progress_callback.h>

#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/scene_user.h>
#include <nel/3d/u_material.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/u_skeleton.h>
#include <nel/misc/big_file.h>
#include <nel/3d/u_light.h>

#include <nel/3d/u_visual_collision_manager.h>
#include <nel/3d/u_visual_collision_entity.h>
#include <nel/3d/instance_group_user.h>

#include <nel/pacs/u_move_container.h>
#include <nel/pacs/u_move_primitive.h>
#include <nel/pacs/u_global_retriever.h>
#include <nel/pacs/u_global_position.h>


#include "world.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;
using namespace NLPACS;

class Progressor : public IProgressCallback {
public:
	virtual void progress(float value) {
		//nlinfo("Progress at %f", value);
	}
};

CWorld::CWorld(TSharedComponents share)
{
	_SC = share;
	_UseCollisionSystem = false;
	_UpdateZonesDistance = 500.0f;
	_SkyRotX = 0;
}

void CWorld::loadRegion(const CAtyscapeRegion &region, const string &seasonName)
{
	_Ld = _SC.Scene->createLandscape();

	string season = "_" + seasonName;
	_Ld->loadBankFiles(region.Bank + ".smallbank", region.Bank + season + ".farbank");
	_Ld->postfixTileFilename(season.c_str());
	_Ld->postfixTileVegetableDesc(season.c_str());
	
	Progressor pr;
	_Ld->loadVegetableTexture("microveget_" + region.MVG + season + ".dds");
	_Ld->flushTiles(pr);
	//_Ld->setVegetableDensity(50.0f);
	_Ld->setZonePath(_SC.Config->RyzomDataPath.c_str());
	//_Ld->setVegetableWind(CVector(1.0f, 0.0f, 0.0f), 10.0f, 100.0f, 1.0f);
	_Ld->enableReceiveShadowMap(true);
	_Ld->enableAdditive(true);
	_Ld->enableVegetable(true);
	_Ld->setTileNear(50);
	//_Ld->setThreshold(0.01f);

	CRGBA diffuse(241, 226, 244);
	_Ld->setupStaticLight(diffuse, NLMISC::CRGBA(17, 54, 100), 1.1f);


	setupCollisionSystem(region.Pacs+".rbank", region.Pacs+".gr");
	_SC.Scene->setCoarseMeshManagerTexture(string("nel_coarse_mesh_" + region.Bank + season + ".dds").c_str());

	/* Load the instance groups of this region */
	TTime print = 0;
	vector<string> ig;
	CBigFile::getInstance().list(region.IgBNP, ig);
	
	CInstanceGroup *father = ((CSceneUser*)_SC.Scene)->getScene().getGlobalInstanceGroup();

	_SC.Ui->Text->addTextZone("World.info", 0.50f, 0.45f, CRGBA(100, 100, 255), 18, UTextContext::TopLeft);
	for (uint32 i = 0; i < ig.size (); i++){
		// Progress inf	o
		TTime now = CTime::getLocalTime();
		if (now - print > 50) {
			_SC.Ui->Text->setText("World.info", "Creating instances (%i/%i)", i, ig.size());
			_SC.Ui->Text->update();
			print = CTime::getLocalTime();
		}
		// The real thing
 		UInstanceGroup *inst = UInstanceGroup::createInstanceGroup (ig[i]);
		if (!inst)
		{
			nlinfo("Bad ig file : %s", ig[i].c_str());
			continue; // Bad file, should be handled by filtering on filename
		}
		else
		{
			nlinfo("Good ig : %s", ig[i].c_str());
		}
		inst->createRoot(*_SC.Scene);
		inst->addToScene(*_SC.Scene);
		//inst->setClusterSystemForInstances((UInstanceGroup *)father);
		//_SC.Scene->setToGlobalInstanceGroup(inst);
		//inst->displayDebugClusters(_SC.Driver, _SC.Driver->createTextContext("data/font.pfb"));
		//inst->linkToParentCluster((UInstanceGroup*)father);
	}

	loadSkydome(region, seasonName);

	_SC.Ui->Text->delTextZone("World.info");
}

void CWorld::loadAround(CVector pos)
{
	_Ld->loadAllZonesAround(pos, _UpdateZonesDistance);
	_Ld->invalidateAllTiles();
}

void CWorld::updateAround(CVector pos)
{
	_Ld->refreshZonesAround(pos, _UpdateZonesDistance);
}

void CWorld::setupCollisionSystem(string retrieverBankName, string globalRetrieverName)
{
	// init the global retriever and the retriever bank
	_RetrieverBank = URetrieverBank::createRetrieverBank(retrieverBankName.c_str());
	_GlobalRetriever = UGlobalRetriever::createGlobalRetriever(globalRetrieverName.c_str(), _RetrieverBank);

	// create the move primitive
	_MoveContainer = UMoveContainer::createMoveContainer(_GlobalRetriever, 100, 100, 6.0);

	_VisualCollisionManager = _SC.Scene->createVisualCollisionManager();
	_VisualCollisionManager->setLandscape(_Ld);
	_VisualCollisionManager->setPlayerInside(true); 

	_SC.Scene->setVisualCollisionManagerForShadow(_VisualCollisionManager);

	//_CamCollisionEntity = _VisualCollisionManager->createEntity();
	//_CamCollisionEntity->setCeilMode(true);

	_UseCollisionSystem = true;
}

void  CWorld::evalCollision(double dt, uint8 worldImage)
{
	_MoveContainer->evalCollision(dt, worldImage);
}


void CWorld::createLight() {
	//_Sun = ULight::createLight();
	//_SC.Driver->enableLight(0);
	//_Sun->setMode(ULight::DirectionalLight);
	//CConfigFile::CVar sD = _SC.Config->Conf.getVar("SunDirection");
	//_SunDirection.set(sD.asFloat(0), sD.asFloat(1), sD.asFloat(2));
	//_Sun->setDirection(_SunDirection);
	//_SC.Driver->setLight(0, *_Sun);
	_SC.Scene->setSunAmbient(CRGBA(200, 200, 200));
	_SC.Scene->setSunDiffuse(CRGBA(255,255,255));
	_SC.Scene->setSunSpecular(CRGBA(255,255,255));
	_SC.Scene->setSunDirection(CVector(-2.935f, 0.107f, -1.22f));

	_SC.Scene->enableLightingSystem(true);
	_SC.Scene->enableShadowPolySmooth(true);
	_SC.Scene->setPolygonBalancingMode(UScene::PolygonBalancingOn);
	_SC.Scene->setGroupLoadMaxPolygon("Fx", 1000);
	
	//_SC.Scene->setSunSpecular(CRGBA(255, 155, 0)); // Pour simuler le coucher de soleil

	_SC.Scene->setSunAmbient(CRGBA(55, 55, 55));
	//_SC.Scene->setSunDiffuse(CRGBA(255, 0, 0));
	//_SC.Scene->setSunDirection(CVector(1, 0, 1));
}

// Code below is from Kervala (Thanks :)
bool CWorld::loadSkydome(const CAtyscapeRegion &region, const string &season)
{
	std::string skydome;


	_SkyScene = _SC.Driver->createScene(false);
	_SkyScene->getCam().setTransformMode(UTransformable::DirectMatrix);

	string skyDomePrefix = region.Bank.substr(0, 2);
	if (skyDomePrefix == "pr")
	{
		_HaveSky = false;
		return false;
	}

	//setup fog
	_SC.Driver->enableFog(true);
	_SC.Driver->setupFog(100, 600, CRGBA(200, 200, 200));

	_HaveSky = true;
	
	skydome = /*skyDomePrefix+*/"la_sky_dome.ig";

	vector<string> ig;
	CBigFile::getInstance().list(skydome, ig);
	nlinfo("skydome ig list : %i", ig.size());
	UInstanceGroup *inst = UInstanceGroup::createInstanceGroup(skydome);

	if (inst == NULL)
	{
		nlwarning("Instance group '%s' not found", skydome.c_str());
		return false;
	}
	else
	{
		nlinfo("sky ok !");
	}

	inst->addToScene(*_SkyScene);

	inst->unfreezeHRC();

//	UAnimation *animation = UAnimation::createAnimation("de_sky_dome.anim");

	// get the sky
	UInstance ii = inst->getInstance(0);
	//ii.setScale(2.9f, 2.9f, 2.9f);
	//ii.setPos(0, 0, 50.0f);

/* DOC LA
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(0) in 0 stage have mat stars_dome_map01.TGA 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(0) in 1 stage have mat stars_dome_map02.TGA 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(0) in 2 stage have mat la_su_sky_dome_gradient_fair.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(1) in 0 stage have mat clouds_dome_lightclouds.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(1) in 1 stage have mat clouds_dome_lightclouds_mask.TGA 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(4) in 0 stage have mat clouds_dome_heavyclouds_mask.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(4) in 1 stage have mat clouds_dome_heavyclouds.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(5) in 0 stage have mat clouds_dome_alticlouds.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(7) in 0 stage have mat stars_dome_map01.TGA 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(9) in 0 stage have mat clouds_dome_lightclouds.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(17) in 0 stage have mat clouds_dome_heavyclouds_mask.tga 
2008/05/30 01:52:24 INF 16c4 atyscape_rd.exe world.cpp 260 CWorld::loadSkydome : SKY : instance(18) in 0 stage have mat de_horizon_dome.TGA 
*/

	// Get the material
	uint inum = inst->getNumInstance();

	for (uint i=0; i < inum; i++)
	{
		if (inst->getInstance(i).getNumMaterials() >= 1)
		{
			//inst->getInstance(i).setScale(2.5f, 2.5f, 1.5f);
			for (sint j = 0; j < inst->getInstance(i).getMaterial(0).getLastTextureStage(); j++)
			{
				nlinfo("SKY : instance(%i) in %i stage have mat %s ", i, j, inst->getInstance(i).getMaterial(0).getTextureFileName(j).c_str());
			}
		}
	}

	//inst->getInstance(1).getMaterial(0).setTextureFileName("sky_tryker_day_fair.dds", 0);
	//inst->getInstance(0).getMaterial(0).setTextureFileName("", 1);
	inst->getInstance(0).getMaterial(0).setTextureFileName("la_su_sky_dome_gradient_fair.tga", 2);
	//inst->getInstance(0).getMaterial(0).s
	//inst->getInstance(0).getMaterial(0).setTextureFileName("fog_dome.tga", 1);

	UInstanceMaterial material = ii.getMaterial(0);

	// For each texture
	//string share = material.getTextureFileName(2);

	NL3D::CTextureFile *src = dynamic_cast<NL3D::CTextureFile*>(material.getObjectPtr()->getTexture(2));

	src->setEnlargeCanvasNonPOW2Tex(true);
	src->doGenerate();

	sint hour = 10;

	CBitmap enlargedBitmap;
	enlargedBitmap.resize(1, 128);
	// blit src bitmap
	enlargedBitmap.blit(*src, hour, 0, 1, 128, 0, 0);
	// swap them
//	src->swap(enlargedBitmap);
	src->setEnlargeCanvasNonPOW2Tex(true);
	uint8 *data = new uint8[128*4];
	enlargedBitmap.getData(data);
	material.setTextureMem(2, data, 128*4, false, false, 1, 128);

//	CTextureFile *dst = new CTextureFile(*src);

//	dst->blit(text, sint32 x, sint32 y);

//	blit (const CBitmap &src, sint srcX, sint srcY, sint srcWidth, sint srcHeight, sint destX, sint destY)

	inst->getInstance(1).hide();
	inst->getInstance(3).hide();
	inst->getInstance(4).hide();
	inst->getInstance(7).hide();

	//inst->getInstance(11).hide();
	//inst->getInstance(12).hide();
	//inst->getInstance(13).hide();
	//inst->getInstance(14).hide();

	// hide other layers (trucs qui servent à rien)
	inst->getInstance(2).hide();
	inst->getInstance(5).hide();
	inst->getInstance(6).hide();
	inst->getInstance(8).hide();
	inst->getInstance(9).hide();
	inst->getInstance(10).hide();
	inst->getInstance(17).hide();
	inst->getInstance(18).hide();
	//inst->getInstance(18).getMaterial(0).setTextureFileName("la_horizon_dome.tga");

	return true;
}

//void CWorld::activateClouds(bool clouds)
//{
//	if (_haveClouds)
//	{
//		NL3D::SCloudScapeSetup css;
//
//		if (!_MClouds) m_clouds = m_scene->createCloudScape();
//
//		m_clouds->init(&css);
//		m_clouds->setQuality(160);
//		m_clouds->setNbCloudToUpdateIn80ms(1);
//	}
//	else
//	{
//		if (m_clouds)
//		{
//			m_scene->deleteCloudScape(m_clouds);
//			m_clouds = NULL;
//		}
//	}
//}


void CWorld::updateSky(float dt, CMatrix camView/*double time, double delta*/)
{
	// Before rendre scene
	//if (m_clouds) m_clouds->anim(delta);
	if (_HaveSky)
	{
		_SkyScene->animate(dt);
		CMatrix skyCameraMatrix;
		skyCameraMatrix.identity();

		skyCameraMatrix = camView;

		skyCameraMatrix.setPos(CVector::Null);
		//_SkyRotX += 0.005f;
		//skyCameraMatrix.rotateZ(_SkyRotX);
		_SkyScene->getCam().setMatrix(skyCameraMatrix);
	}
}

void CWorld::renderSky(/*double time, double delta*/)
{

	if (_HaveSky)
	{
		_SkyScene->render();
		_SC.Driver->clearZBuffer();
	}

	// After rendre scene
	//if (m_clouds) m_clouds->render();
}

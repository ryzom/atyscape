/** 
 * Atyscape Atys viewer - Atys Mode
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

#include <vector>
#include <sstream>
#include <string>

#include <nel/misc/types_nl.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/event_mouse_listener.h>

#include "configuration.h"
#include "atys_mode.h"
#include "lg_frame.h"
#include "lg_popup_menu.h"
#include "utils.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

CAtysMode::CAtysMode(TSharedComponents share) : CGameMode(share)
{
	_SC = share;
	
	_SC.Scene->getCam().setTransformMode(UTransformable::DirectMatrix);
	_CamFrustum = _SC.Scene->getCam().getFrustum();
	_CamUIG = (UInstanceGroup*)-1;
	_SC.Scene->getCam().setClusterSystem(_CamUIG);
	_SelectedRegion = "?";
}


void CAtysMode::createLandscape(string region)
{
	World = new CWorld(_SC);
	World->createLight();

	CAtyscapeRegion r = _SC.Config->getRegion(region);
	nlinfo("region : %s, saison : %s", region.c_str(), _SC.Config->Season.c_str());
	World->loadRegion(r, _SC.Config->Season);
	/** Todo **/
	//World->setupCollisionSystem("fyros.rbank", "fyros.gr");
	//World->setupCollisionSystem("tryker.rbank", "tryker.gr");
	/** **/
}

void CAtysMode::setPlayerPosition(CAtyscapePoint p)
{
	CVector pos = CVector(p.x, p.y, p.z);
	World->loadAround(pos);

	CVector snapped = pos, normal;
	//if (World->snapToGround(snapped, normal))
	//{
	//	nlinfo("pos.z = %f, snap.z = %f", pos.z, snapped.z);
	//	pos = snapped;
	//}
	_PlayerPos = pos;
	nlinfo("%f", _PlayerPos.x);

//	_Walker->_Pos = pos;
//	_Cam->_Pos = pos;
}


void CAtysMode::selectRegion()
{
	CFrame* f = new CFrame("/SelectRegion");
	f->create(CWindowManager::getInstance().getWindow("[Root]"));
	f->setTitle("Please Select an Region");
	f->setPos(0.04f, 0.10f);
	f->setSize(0.46f, 0.85f);

	CPopupMenu* mainPopup = new CPopupMenu("/Load/Regions");
	mainPopup->create(f);
	mainPopup->setPos(0.05f, 0.10f);
	mainPopup->setSize(0.44f, 0.55f);

	for (uint i = 0; i < _SC.Config->Regions.size(); i++)
	{
		string regName = _SC.Config->Regions[i].Name;
		mainPopup->addSubMenu("/Load/Regions", "/Load/Regions/"+regName, regName);
		////	_SC.Ui->addMenuItem("/Load/Regions/"+regName, regName, "/Load/Regions");
		CPopupMenu* p = new CPopupMenu("/Load/Regions/"+regName+"/");
		p->create(CWindowManager::getInstance().getWindow("/Load/Regions/"+regName));
		p->setCallback(new CCallback(&CAtysMode::selectRegion, this));
		////	_SC.Ui->addPopupMenu("/Load/Regions/"+regName+"/", "/Load/Regions/"+regName);
	  	ostringstream strI;
		strI << i;

		CAtyscapeRegion selectedRegion = _SC.Config->Regions[i];
		for (uint j = 0; j < selectedRegion.Points.size(); j++)
		{
			string ptName = selectedRegion.Points[j].Name;
	   		ostringstream strJ;
   			strJ << j;
			p->addItem("/Load/Regions/"+regName+"/", "/Load/Points/"+strI.str()+"/"+strJ.str()+"/", ptName);
			///_SC.Ui->addSelectMenuItem("/Load/Points/"+strI.str()+"/"+strJ.str()+"/", ptName, "/Load/Regions/"+regName+"/");
		}

	}
	
	mainPopup->render();
	
	_Select = new CLocationSelect(_SC);
	bool chosen = false;

	while(_SC.Driver->isActive())
	{
	    _SC.Driver->clearBuffers (CRGBA (0, 0, 0));
		_SC.Driver->clearZBuffer();
		_SC.Driver->EventServer.pump();
		_SC.Scene->render();
		_SC.Ui->render();
		_SC.Ui->Text->render();
		if (_SelectedRegion != "?") break;
		_SC.Driver->swapBuffers ();
	}
	//_SC.Ui->clear();
	//_SC.Ui->writeText(0.30f, 0.55f, "AtysScape - Creating landscape");
	//_SC.Ui->update();
	/** **/
	
	vector<string> tokens;
    tokenizer(_SelectedRegion, tokens, "/");

	nlinfo(tokens[2].c_str());
	nlinfo(tokens[3].c_str());
	CAtyscapeRegion selectedRegion = _SC.Config->Regions[atoi(tokens[2].c_str())];

	_SC.Ui->Text->setProps("Main.Info", 0.50f, 0.50f, CRGBA(255, 255, 255), 22, UTextContext::MiddleMiddle);
	_SC.Ui->Text->setText("Main.Info", "Creating landscape");
	_SC.Ui->Text->update();
	////_SC.Ui->clear();
	////_SC.Ui->writeText(0.30f, 0.55f, "AtysScape - Preloading landscape");
	////_SC.Ui->update();

	createLandscape(selectedRegion.Name);
	setPlayerPosition(selectedRegion.Points[atoi(tokens[3].c_str())]);

	_SC.Ui->Text->setEffect("Main.Info", "FadeOut");
	f->destroy();
}

bool CAtysMode::selectRegion(const string &winName)
{
	_SelectedRegion = static_cast<CPopupMenu*>(CWindowManager::getInstance().getWindow(winName))->getSelected();
	return true;
}

void CAtysMode::makeEntities()
{
	_Cam = new CEntity("Camera");
	_Cam->addToWorld(0, World);

	_AnimatedYubo = new CAnimated(_SC, "Yubo");
	_AnimatedHomin = new CHomin(_SC, "Zorglor");
	_AnimatedHomine = new CHomin(_SC, "Nymphea");
	_AnimatedFyrette = new CHomin(_SC, "Elhora");

	_AnimatedsList.push(_AnimatedYubo);
	_AnimatedsList.push(_AnimatedHomin);
	_AnimatedsList.push(_AnimatedHomine);
	_AnimatedsList.push(_AnimatedFyrette);


	_AnimatedYubo->loadAnimsDefinitions("data/anims/fauna/tr_dag.txt");
// 	_AnimatedYubo->loadAnimsDefinitions("data\\anims\\fauna\\tr_dag.txt");
	_AnimatedYubo->init("TR_MO_Dag.skel", "TR_MO_Dag.shape");
	_AnimatedYubo->loadAnimations();
	_AnimatedYubo->setTexture(0, "TR_MO_dag.dds");
	_AnimatedYubo->addToWorld(0, World);

	_AnimatedHomin->loadAnimsDefinitions("data/anims/homins/tryker_hom.txt");
	_AnimatedHomin->init("data/homins/zorglor.cfg");
// 		_AnimatedHomin->loadAnimsDefinitions("data\\anims\\homins\\tryker_hom.txt");
// 	_AnimatedHomin->init("data\\homins\\zorglor.cfg");
	_AnimatedHomin->addToWorld(0, World);

	
	_AnimatedHomine->loadAnimsDefinitions("data/anims/homins/tryker_hom.txt");
	_AnimatedHomine->init("data/homins/nymphea.cfg");
// 	_AnimatedHomine->loadAnimsDefinitions("data\\anims\\homins\\tryker_hom.txt");
// 	_AnimatedHomine->init("data\\homins\\nymphea.cfg");
	_AnimatedHomine->addToWorld(0, World);

	_AnimatedFyrette->loadAnimsDefinitions("data/anims/homins/tryker_hom.txt");
	_AnimatedFyrette->init("data/homins/elhora.cfg");
// 	_AnimatedFyrette->loadAnimsDefinitions("data\\anims\\homins\\tryker_hom.txt");
// 	_AnimatedFyrette->init("data\\homins\\elhora.cfg");
	_AnimatedFyrette->addToWorld(0, World);

	//_AnimatedHomin->setPos(CVector(17244.0f, -32912.0f, -1.4f));


//	bone.getShape().getVisualCollisionMesh();
	
	//_AnimationSet = _SC.Driver->createAnimationSet();
	

//	_AnimatedYubo.loadAnimsDefinitions("data\\anims\\homins\\homin.txt");
	//pl = _PlayListManager->createPlayList(_AnimationSet);
	//_AnimatedYubo->initAnimation(_AnimationSet, pl);
	//nlinfo("Animations count : %i", _AnimationSet->getNumAnimation());
	//pl->registerTransform(skel);

	//skel.bindSkin(bone);
//	yubo = skel;

//	UAnimationSet *animationSet2 = _SC.Driver->createAnimationSet();
////	nyAmn = Homin::fromFile("data\\homins\\zorglor.cfg")->createInstance(_SC.Scene); //makeHomine();
//	nyAmn.setPos(17244.0f, -32912.0f, -1.4f);
//	homin->loadAnimsDefinitions("data\\anims\\homins\\homin.txt");
//	plhom = _PlayListManager->createPlayList(animationSet2);
//	homin->initAnimation(animationSet2, plhom);
//	nlinfo("Animations count : %i", animationSet2->getNumAnimation());
//	homin->playAnimation("IDLE", true);
//	plhom->registerTransform(nyAmn);
//
//	nyAmn2 = Homin::fromFile("data\\homins\\nymphea.cfg")->createInstance(_SC.Scene);
//	nyAmn2.setPos(17244.0f, -32913.0f, -1.4f);
	
	/* Our Fairhaven is much better: it has a third bar ! */
	UInstance bar =  _SC.Scene->createInstance("tr_bar_village_b.shape" );
	bar.setPos(17005.0f, -32858.0f, -1.0f);
	bar.setTransformMode(UTransformable::RotEuler);	
}

void CAtysMode::reset()
{

}

/** 
 * Atyscape Atys viewer - Generic game mode
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

#include <nel/misc/types_nl.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/event_mouse_listener.h>
#include <nel/3d/u_skeleton.h>
#include <nel/3d/u_instance.h>

#include "game_mode.h"
#include "homin.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;
//
CGameMode::CGameMode(TSharedComponents share) /*: _Ui(ui)*/ {
	_State = 0;
//	_SC = share;
//
//	_AnimationSet = NULL;
//	_PlayListManager = NULL;
}

uint CGameMode::getState()
{
	return _State;
}

void CGameMode::renderUI()
{
}

void  CGameMode::finish()
{
}

void CGameMode::pause()
{
}

void CGameMode::resume()
{
}

void CGameMode::reset()
{
}

// 
//
//void CGameMode::createLandScape()
//{
//	World = new CWorld(_SC);
//	World->createLight();
//}
//
//void CGameMode::loadRegion(string region)
//{
//	CAtyscapeRegion r = _SC.Config->getRegion(region);
//	World->loadRegion(r, _SC.Config->Season);
//	World->setupCollisionSystem("tryker.rbank", "tryker.gr");
//}
//
//void CGameMode::loadPosition(CAtyscapePoint p)
//{
//	CVector pos = CVector(p.x, p.y, p.z);
//	_SC.Ui->clear();
//	_SC.Ui->writeText(0.30f, 0.55f, "AtysScape - Preloading landscape");
//	_SC.Ui->update();
//	World->loadAround(pos);
//}
//
//void CGameMode::makeEntities()
//{
//	_AnimatedYubo = new CAnimated(_SC, "Yubo");
//	_AnimatedHomin = new CAnimated(_SC, "Zorglor");
//	_AnimatedHomine = new CAnimated(_SC, "Nymphea");
//
//	_AnimatedsList.push(_AnimatedYubo);
//	_AnimatedsList.push(_AnimatedHomin);
//	_AnimatedsList.push(_AnimatedHomine);
//
//
//	_AnimatedYubo->loadAnimsDefinitions("data\\anims\\fauna\\tr_dag.txt");
//	_AnimatedYubo->init("TR_MO_Dag.skel", "TR_MO_Dag.shape");
//	_AnimatedYubo->setTexture(0, "TR_MO_dag.dds");
//	_AnimatedYubo->playAnimation("IDLE", true);
////	bone.getShape().getVisualCollisionMesh();
//	
//	//_AnimationSet = _SC.Driver->createAnimationSet();
//	
//
////	_AnimatedYubo.loadAnimsDefinitions("data\\anims\\homins\\homin.txt");
//	//pl = _PlayListManager->createPlayList(_AnimationSet);
//	//_AnimatedYubo->initAnimation(_AnimationSet, pl);
//	//nlinfo("Animations count : %i", _AnimationSet->getNumAnimation());
//	//pl->registerTransform(skel);
//
//	//skel.bindSkin(bone);
////	yubo = skel;
//
////	UAnimationSet *animationSet2 = _SC.Driver->createAnimationSet();
//////	nyAmn = Homin::fromFile("data\\homins\\zorglor.cfg")->createInstance(_SC.Scene); //makeHomine();
////	nyAmn.setPos(17244.0f, -32912.0f, -1.4f);
////	homin->loadAnimsDefinitions("data\\anims\\homins\\homin.txt");
////	plhom = _PlayListManager->createPlayList(animationSet2);
////	homin->initAnimation(animationSet2, plhom);
////	nlinfo("Animations count : %i", animationSet2->getNumAnimation());
////	homin->playAnimation("IDLE", true);
////	plhom->registerTransform(nyAmn);
////
////	nyAmn2 = Homin::fromFile("data\\homins\\nymphea.cfg")->createInstance(_SC.Scene);
////	nyAmn2.setPos(17244.0f, -32913.0f, -1.4f);
//	
//	/* Our Fairhaven is much better: it has a third bar ! */
//	UInstance bar =  _SC.Scene->createInstance("tr_bar_village_b.shape" );
//	bar.setPos(17005.0f, -32858.0f, -1.0f);
//	bar.setTransformMode(UTransformable::RotEuler);	
//}
//
//void CGameMode::animate(float curTime)
//{
//	//nlinfo("%s", _AnimatedYubo->getPos().z);
//	_AnimatedYubo->_PlayListManager->animate(curTime);
//	//nlinfo("%s", _AnimatedYubo->getPos().z);
//	_SC.Scene->animate(curTime);
//}

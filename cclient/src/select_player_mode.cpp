/** 
 * Atyscape Atys viewer - Select Player mode
 * Partly based on NEVRAX SNOWBALLS.
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
#include <nel/misc/vectord.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_scene.h>
#include <nel/pacs/u_move_primitive.h>
#include <nel/3d/event_mouse_listener.h>

#include "select_player_mode.h"
#include "entity_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;



CSelPlayerMode::CSelPlayerMode(TSharedComponents share) : CGameMode(share)
{
	_SC = share;
	_MoveSpeed = 1.0f; // Base move speed, user set
	_SelectedPlayer = -1;
	_CurrentPlayer = 0;
	_CamSpeed = 0.1f;
	_CamPos = 0;
	_CanMove= true;
}


void CSelPlayerMode::init()
{
	doRegister();
	_SC.Scene->getCam().setTransformMode(UTransformable::DirectMatrix);

	_World = new CWorld(_SC);
	_World->createLight();

	_Cam = new CEntity("Camera");
	//_Cam->addToWorld(0, _World);

	//_AnimatedYubo = new CAnimated(_SC, "Yubo");
	//_AnimatedHomin = new CHomin(_SC, "Zorglor");

/* TEST */

	CEntityManager *eManager = new CEntityManager();
	eManager->loadShapeDefs("../scripts/shape_datadefs.txt");
	eManager->loadSkelDefs("../scripts/skel_datadefs.txt");
	eManager->loadTexDefs("../scripts/tex_datadefs.txt");
	_AnimatedHomin = eManager->createNewEntity("Zorglor", "../scripts/zorglor.def");
	_AnimatedYubo = eManager->createNewEntity("Yubette", "../scripts/yubette.def");

	//_AnimatedHomin = new CHomin(_SC, "Zorglor");

/* */
	_AnimatedHomine = new CHomin(_SC, "Nymphea");
	_AnimatedFyrette = new CHomin(_SC, "Elhora");

	_AnimatedYubo->loadAnimsDefinitions("data/anims/fauna/tr_dag.txt");
// 	_AnimatedYubo->loadAnimsDefinitions("data\\anims\\fauna\\tr_dag.txt");
	//_AnimatedYubo->init("TR_MO_Dag.skel", "TR_MO_Dag.shape");
	//_AnimatedYubo->setTexture(0, "TR_MO_dag.dds");
	_AnimatedYubo->loadAnimations();
	//_AnimatedYubo->addToWorld(0, World);

	_AnimatedHomin->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
// 	_AnimatedHomin->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
	_AnimatedHomin->loadAnimations();
	
	//_AnimatedHomin->init("data\\homins\\zorglor.cfg");

	//_AnimatedHomin->addToWorld(0, World);
	
	_AnimatedHomine->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
	_AnimatedHomine->init("data/homins/nymphea.cfg");
	//_AnimatedHomine->addToWorld(0, World);

	_AnimatedFyrette->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
	_AnimatedFyrette->init("data/homins/elhora.cfg");

// 		_AnimatedHomine->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
// 	_AnimatedHomine->init("data\\homins\\nymphea.cfg");
// 	//_AnimatedHomine->addToWorld(0, World);
// 
// 	_AnimatedFyrette->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
// 	_AnimatedFyrette->init("data\\homins\\elhora.cfg");

	_Cam->setPos(CVector(0, -2, 1));
	_LastTime = CTime::getLocalTime();

	_AnimatedHomin->setPos(CVector(0, 0, 0));
	_AnimatedHomine->setPos(CVector(1, 0, 0));
	_AnimatedFyrette->setPos(CVector(2, 0, 0));
	_AnimatedYubo->setPos(CVector(3, 0, 0));
	_AnimatedHomin->playAnimation("RUN");
	_Walker = 0;
	_AnimatedHomine->playAnimation("IDLE");
	_AnimatedFyrette->playAnimation("IDLE");
	_AnimatedYubo->playAnimation("IDLE");

	UInstance agora =  _SC.Scene->createInstance("agora_big_palmito.shape" );
	//agora.setPos(70.0f, -100.0f, 10.0f);
	agora.setTransformMode(UTransformable::RotEuler);
	agora.setPos(-10.0f, -10.0f, -10.0f);
	//agora.setRotEuler(0, 0, Pi/2);

	_PopupMenu = new CPopupMenu("/SelectPlayer");
	_PopupMenu->create(CWindowManager::getInstance().getWindow("[Root]"));
	_PopupMenu->setPos(0.04f, 0.10f);
	_PopupMenu->setSize(0.46f, 0.55f);
	_PopupMenu->addItem("/SelectPlayer", "/SelectPlayer/GO", "SELECT");
	_PopupMenu->setCallback(new CCallback(&CSelPlayerMode::go, this));
	_PopupMenu->render();

	farCount[0] = 0;
}

void CSelPlayerMode::operator ()(const CEvent& event)
{
	CEventMouse* mouseEvent=(CEventMouse*)&event;
	
	_SC.Ui->MouseX = mouseEvent->X;
	_SC.Ui->MouseY = mouseEvent->Y;

	if (event == EventMouseUpId)
		updateAnims(true);
	else
		updateAnims(false);
}

void  CSelPlayerMode::updateAnims(bool eventMouseUpId)
{

/*	if (event==EventMouseMoveId)
	{
		if (_CanMove)
		{

			if (mouseEvent->X > 0.60)
			{
				if (_CurrentPlayer < 3)
				{
					_CurrentPlayer++;
					_CamSpeed = abs(_CamSpeed);
				}
			}
			else if (mouseEvent->X < 0.40)
			{
				if (_CurrentPlayer > 0)
				{
					_CurrentPlayer--;
					_CamSpeed = -abs(_CamSpeed);
				}
			}
		}
	} 
	else */
	
	CViewport vp = _SC.Driver->getViewport();
	CAnimated* animateds[4] = {_AnimatedHomin, _AnimatedHomine, _AnimatedFyrette, _AnimatedYubo};

	for (uint i=0; i < 4; i++)
	{
		CVector tpos, tdir;
		vp.getRayWithPoint(_SC.Ui->MouseX, _SC.Ui->MouseY, tpos, tdir, _SC.Scene->getCam().getMatrix(), _SC.Scene->getCam().getFrustum());
	
		float dist2D;
		float distZ;

		bool fi = animateds[i]->_Skeleton.fastIntersect(tpos, tdir, dist2D, distZ, false);
		if (dist2D == 0)
		{
			if (eventMouseUpId)
			{
				animateds[_CurrentPlayer]->playAnimation("IDLE");
				if (i > _CurrentPlayer)
				{
					_CurrentPlayer = i;
					_CamSpeed = abs(_CamSpeed);
				}
				else if (i < _CurrentPlayer)
				{
					_CurrentPlayer = i;
					_CamSpeed = -abs(_CamSpeed);
				}
				else
				{
					
				}
				animateds[_CurrentPlayer]->playAnimation("RUN");
			}
			else
			{
				if (_Walker != i)
				{
					if (i != _CurrentPlayer)
						animateds[i]->playAnimation("WALK");
					_Walker = i;
				}
			}
		}
		else
		{
			if (((i == _Walker) || (farCount[i] > 0))  && (i != _CurrentPlayer))
			{
				farCount[i] ++;
				if (farCount[i] > 50)
				{
					animateds[i]->playAnimation("IDLE");
					farCount[i] = 0;
				}
				_Walker = 32;
			}

		}
	}
}

void CSelPlayerMode::update(float dt)
{
	_LastTime = _NewTime;
	_NewTime = CTime::getLocalTime();
	_DeltaTime = (double)(_NewTime - _LastTime) / 1000.0;
	
	if ((((float)_CurrentPlayer - _CamPos)*(_CamSpeed<0?-1.0f:1.0f)) > 0)
	{
		_CamPos += _CamSpeed;
		_CanMove = false;
	}
	else
	{
		_CamPos = (float)_CurrentPlayer;
		//if (!_CanMove)
		//	_SC.Driver->setMousePos(0.5f, 0.5f);
		_CanMove = true;
		updateAnims(false);
	}

	_AnimatedHomin->updateAnimation();
	_AnimatedHomine->updateAnimation();
	_AnimatedFyrette->updateAnimation();
	_AnimatedYubo->updateAnimation();

	CMatrix camMat = CMatrix::Identity;
	camMat.setPos(CVector(_CamPos, -2, 0.9f));
	_SC.Scene->getCam().setMatrix(camMat);

/*	fr = frustum.unProject(CVector(_MouseEventX, _MouseEventY, 0.5f));
	CLine line;
	line.V0.set(0.5, 0.5, 0);
	line.V1.set(0.5, 1, 0);
	
	CViewport vp = _SC.Driver->getViewport();
	CVector tpos, tdir;
	vp.getRayWithPoint(_MouseEventX, _MouseEventY, tpos, tdir, Cam, frustum);
	tdir.normalize();
	_AnimatedYubo->setEnlighted();*/

}
void CSelPlayerMode::handleEvents()
{
}

bool CSelPlayerMode::go(const string &winName)
{
	////_SelectedPlayer = _CurrentPlayer;
	////	_SC.Ui->removeWindow("/SelectPlayer", "Root");
	////	_SC.Ui->destroy("/SelectPlayer");
	_PopupMenu->destroy();
	_SelectedPlayer = _CurrentPlayer;

	return true;
}

void CSelPlayerMode::render()
{

	_TempCam = _SC.Scene->getCam() ;
	_SC.Driver->setMatrixMode3D( _TempCam );
	CMatrix	mat = _SC.Scene->getCam().getMatrix();
	mat.scale(3.0f);
	mat.setPos(CVector(0.0f, -0.5f, 0.0f));
//	_SC.Ui->writeText3D(mat, "Zorglor");
	mat.setPos(CVector(1.0f, -0.5f, 0.0f));
//	_SC.Ui->writeText3D(mat, "Nymphea");
	mat.setPos(CVector(2.0f, -0.5f, 0.0f));
//	_SC.Ui->writeText3D(mat, "Elhora");
	mat.setPos(CVector(3.0f, -0.5f, 0.0f));
//	_SC.Ui->writeText3D(mat, "Yubette de Mermaidia");
	_SC.Driver->setMatrixMode2D11();

}


void CSelPlayerMode::animate(float curTime)
{
	
	_SC.Scene->animate(curTime);
	_AnimatedHomin->animate(curTime);
	_AnimatedHomine->animate(curTime);
	_AnimatedFyrette->animate(curTime);
	_AnimatedYubo->animate(curTime);
}

uint  CSelPlayerMode::getSelectedPlayer()
{
	return _SelectedPlayer;
}

uint CSelPlayerMode::getState()
{
	if (_SelectedPlayer != -1)
		return 1;
	return 0;
}

void  CSelPlayerMode::finish()
{
	unRegister();
}

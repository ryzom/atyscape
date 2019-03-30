/** 
 * Atyscape Atys viewer - Fly mode input handler
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

#include "walk_mode.h"
#include "entity_manager.h"
#include "utils.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

CWalkMode::CWalkMode(TSharedComponents share) : CAtysMode(share) {
	//_Walker = new CEntity();
	_CamRotation = 0.0f;
	_LastCamRotation = 0.0f;
	_CamWalkerDistance = 7.0f;
	_MouseX = 0.5f;
	_MouseY = 0.5f;
	_HandleMove = false;

	//_OldAnimNorm = 0.0f;

	_MoveSpeed = 1.0f; // Base move speed, user set
	_CamSpeed = 1.0f; // 0.5> ... >1.0

	//_Mat = UMaterial(new CMaterial());
	//_Mat.setColor(CRGBA(0, 255, 0));

	_PlayerOffset = 0.f ;
}

void CWalkMode::setPlayer(uint player)
{
	_Player = player;
}

void CWalkMode::init()
{
	selectRegion();
	doRegister();
	CEntityManager::instance().loadOffsets( "data/defs/offsets.ddf" ) ;
	
	_Cam = new CEntity("Camera");
	_Cam->addToWorld(0, World);
	_Cam->setPos(_PlayerPos);

	CVector translateCam = _Cam->getView().getJ();
	CVector camPos = _PlayerPos - CVector(translateCam .x*5.0f, translateCam .y*5.0f, translateCam .z*5.0f);
	CMatrix camMat = _Cam->getView();
	camMat.setPos(camPos);
	_SC.Scene->getCam().setMatrix(camMat);
	_CamUIG = _SC.Scene->findCameraClusterSystemFromRay(NULL, camPos, camPos);
	_Cam->SnapToGround = false;

	CEntityManager *eManager = &CEntityManager::getInstance();
	string avatarKc = eManager->getKeyCodesOfAvatar(_Player);

	_PlayerOffset = CEntityManager::instance().getOffset(avatarKc) ;
	
	_Walker = eManager->createNewEntity("Player", avatarKc , 2);
	_Walker->addToWorld(0, World);
	_Walker->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
// 	_Walker->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
	_Walker->loadAnimations();
	_Walker->playAnimation("IDLE");
	_Walker->setGlobalPos( CVector(_PlayerPos.x, _PlayerPos.y, _PlayerPos.z + _PlayerOffset) ) ;

	CQuat rotQuat;
	rotQuat=CQuat(CVector(CVector::K), (float)Pi/2.0f);
	_Walker->setQuat(rotQuat*_Walker->getQuat());
	_PosBeforeAnim = _PlayerPos;

	_LastTime = CTime::getLocalTime();

	_GoForward = false;

	_SC.Ui->Text->addTextZone("GameMode.Position", 0.01f, 0.05f, CRGBA(200, 255, 255), 14, UTextContext::TopLeft);
	_SC.Ui->Text->addTextZone("GameMode.View", 0.01f, 0.07f, CRGBA(220, 255, 255), 14, UTextContext::TopLeft);

	//createMap();

	_Map = new CMap("Radar");
	_Map->loadMapsDef("data/defs/maps.ddf");
	string mapName = _Map->getMapNameFromPos(_PlayerPos.x, _PlayerPos.y);
	nlinfo("MAP NAME = %s", mapName.c_str());
	_Map->setCurrentMapName(mapName); 
	_Map->setMapCursorFile("data/custom/map_pos.tga");
	_ShowMap = true;
}

void CWalkMode::applyRot()
{
	CQuat rotQuat;

	if (_GoForward)
	{
		rotQuat=CQuat(CVector(CVector::K), _CamRotation-(float)Pi);
		_LastCamRotation = _CamRotation;
	}
	else
	{
		rotQuat=CQuat(CVector(CVector::K), _LastCamRotation-(float)Pi);
	}

	_Walker->setQuat(rotQuat*_Walker->getQuat());/*_Walker->getQuat());*/
	_Walker->applyQuat();
}

void CWalkMode::handleKeyboard(float speed)
{
	_ShowMap = false;
	CEventListenerAsync al = _SC.Driver->AsyncListener;
	if (al.isKeyDown(KeyLEFT)) {
		_Walker->strafe(speed, false);
	} else if (al.isKeyDown(KeyRIGHT)) {
		_Walker->strafe(speed, true);
	} else if (al.isKeyDown(KeyUP)) {
		_Walker->move(speed);
	}  else if (al.isKeyDown(KeyDOWN)) {
		_Walker->move(speed, true);
	} else if (al.isKeyDown(KeyPRIOR)) {
		_Walker->slew(0, 0, 2);
	} else if (al.isKeyDown(KeyNEXT)) {
		_Walker->slew(0, 0, -2);
	} else if (al.isKeyDown(KeyO)) {
		_MoveSpeed -= 0.005f;
	} else if (al.isKeyDown(KeyP)) {
		_MoveSpeed += 0.005f;
	} else if (al.isKeyDown(KeyM)){
		_ShowMap = true;
	} else if (al.isKeyDown(KeyR)) {
		/* Reset view */
		_Walker->setHeadingAttitude(0.0, 0.0);
		_Cam->setHeadingAttitude(0.0, 0.0);
	}

//	_SC.Scene->setSunDirection(CVector(-3.7f, 0.1f, _MoveSpeed));

	//if (_MoveSpeed < 0.0f) _MoveSpeed = 0.0f;
	//if (_MoveSpeed > 15.0f) _MoveSpeed = 15.0f;

}

void CWalkMode::operator ()(const CEvent& event) {
	CEventMouse* mouseEvent=(CEventMouse*)&event;

	if (event==EventMouseMoveId) {
		if (!_HandleMove) return;

		/* Turn along the Z axis with the X mouse (heading) */
		float angleZ = (float)Pi*2.f*(_MouseX - mouseEvent->X);
		/* Turn along the X axis with the Y mouse (attitude) */
		float angleX = (float)Pi*2.f*(mouseEvent->Y - _MouseY);


		_Cam->saveState();

		_Cam->turn(angleZ, angleX);

		// Test if cam is reversed
		if (_Cam->getView().getK().z <= 0)
		{
			_Cam->restoreState();
			_Cam->turn(angleZ, 0);
		}

		_CamRotation += angleZ;
		if (_CamRotation > 2*(float)Pi)
			_CamRotation -= 2*(float)Pi;

		//_Walker->setHeadingAttitude(0.0, 0.0);
		_Walker->turn(0, 0, angleZ);
		
		// Put the mouse back at the center
		_SC.Driver->setMousePos(0.5f, 0.5f);
		_MouseX = 0.5f;
		_MouseY = 0.5f;

	} else if (event==EventMouseDownId) {
		/* Enable move or move control */
		
		if (mouseEvent->Button == rightButton) {
			_GoForward = true;
			_Walker->playAnimation("RUN", true);

		} else if (mouseEvent->Button == leftButton) {
			/* Set the mouse at the middle so that we don't move too far away next time */
			_SC.Driver->setMousePos(0.5f, 0.5f);
			_HandleMove = true;
		}
	} else if (event == EventMouseUpId) {
		/* Disable move or move control */
		if (mouseEvent->Button == rightButton) {
			_GoForward = false;
			_Walker->playAnimation("IDLE", true);
		} else if (mouseEvent->Button == leftButton) {
			_HandleMove = false;
		}
	} else if (event == EventMouseWheelId)
	{
		CEventMouseWheel* wheelEvent=(CEventMouseWheel*)&event;
		if (wheelEvent->Direction)
		{
			if (_CamWalkerDistance > 1.0f)
				_CamWalkerDistance -= 0.5f;
		}
		else
		{
			if (_CamWalkerDistance < 20.0f)
				_CamWalkerDistance += 0.5f;
		}
	}

}

void CWalkMode::update(float dt)
{
	_LastTime = _NewTime;
	_NewTime = CTime::getLocalTime();
	_DeltaTime = (double)(_NewTime - _LastTime) / 1000.0;
	
	
	//CVector snappedCamPos = _Cam->_Pos;
	CVector walkerPos = _Walker->getPos();

	
	//_Walker->calculateSpeed(_DeltaTime);

	if (_GoForward)
	{
		_Walker->tryMove(dt);
	}

	World->evalCollision(_DeltaTime, 0);
	World->updateSky(dt, _Cam->getView());

	//if (_GoForward)
	_Walker->doMove();
	_Walker->setGlobalPos(CVector(_Walker->getPos().x, _Walker->getPos().y, _Walker->getPos().z + _PlayerOffset)) ;
	//_Walker->_Skeleton.setPos(_Walker->getPos());



	//_Walker->setGlobalPos(walkerPos);
	//_Walker->_Skeleton.setPos(walkerPos);


	//_AnimatedYubo->_MovePrim->getGlobalPosition(pos, 0);



//	_AnimatedYubo->_MovePrim->getGlobalPosition(gPos, 0);
	// convert it in a vector 3d
//	_Walker->_Pos = World->_GlobalRetriever->getGlobalPosition(gPos);
	// get the good z position
//	gPos.LocalPosition.Estimation.z = 0.0f;



	//_Cam->snapToGround();


//	UGlobalPosition	gPos;
//	CVectorD pos = (CVectorD)_Walker->_Pos;

//	_AnimatedYubo->_MovePrim->setGlobalPosition(pos, 0);
	//_AnimatedYubo->_MovePrim->getGlobalPosition(gPos, 0);

	//CVector snappedWalkerPos = World->_GlobalRetriever->getGlobalPosition(gPos);
	//gPos.LocalPosition.Estimation.z = 0.0f;
	//snappedWalkerPos.z = World->_GlobalRetriever->getMeanHeight(gPos);

	//if (!World->_GlobalRetriever->isInterior(gPos))
	//	World->snapToGround(snappedWalkerPos, normal);


	//_Walker->_Pos = snappedWalkerPos;
	//
	CVector translateCam = _Cam->getView().getJ();
	CVector camPos = _Walker->getPos() - CVector(translateCam .x*_CamWalkerDistance, translateCam .y*_CamWalkerDistance, translateCam .z*_CamWalkerDistance-1.5f);
	float camCol = World->_VisualCollisionManager->getCameraCollision(_Walker->getPos(), camPos, 1.0f, true);
//	_SC.Ui->writeText(0.01f, 0.79f, "CamCol - %f", camCol);

	//camPos = _Walker->getPos() - CVector(translateCam .x*5.0f*camCol, translateCam .y*5.0f*camCol, translateCam .z*5.0f*camCol);
	
	CVector endPos;

	//_CamUIG = _SC.Scene->findCameraClusterSystemFromRay(_CamUIG,  _Cam->getView().getPos(), camPos);
	//_Walker->_Skeleton.setClusterSystem(_SC.Scene->getCam().getClusterSystem());
	CMatrix camMat = _Cam->getView();
	camMat.setPos(camPos);
	_SC.Scene->getCam().setMatrix(camMat);

	_Walker->updateAnimation();

	//_AnimatedHomin->updateAnimation();


	//_AnimatedYubo->setPos(_AnimatedYubo->getPos()+CVector(0, 0, _AnimatedYubo->getPos().z));
	//_Walker->setPos(_PosBeforeAnim + CVector(0, 0, _Walker->getPos().z));
	//_AnimatedHomin->setPos(CVector(17244.0f, -32912.0f, -1.4f));


}

void CWalkMode::handleEvents()
{

	handleKeyboard(_MoveSpeed);
	if (_GoForward)
		_Walker->move(_MoveSpeed);

}

void CWalkMode::render() {

	//if (pos2.norm() > _OldAnimNorm)
	//	_MoveSpeed = pos2.norm() - _OldAnimNorm;
	//_OldAnimNorm =  pos2.norm();

	World->updateAround(_Walker->getPos());
	World->renderSky();

	//float speed;




	//if (_ShowMap && (pos.x > 20833.0f) && (pos.x < 30341.0f) && (pos.y < -32993.0f) && (pos.y > -40501.0f))
	//{
		//_SC.Ui->Text->setText("GameMode.View", "[MAP] Cursor at %.4f %.4f", 50+(pos.x*0.2459f)-5123, 600-50-32+(pos.y*0.2472f)+8156);
		//_SC.Driver->setMatrixMode2D(CFrustum(0.0f, 800, 0.0f, 600, 0.0f, 1.0f, false));
	//	_SC.Driver->drawBitmap(50, 600-50-512, 1024, 512, *_Map);
		//_SC.Driver->drawBitmap(50+(pos.x*0.2459f)-5123, 600-50-32-(-pos.y*0.2472f)+8156, 32, 32, *_MapCursor);
	//}
	//else
	//{
	//}

}

void CWalkMode::renderUI()
{
	CVector pos = _Walker->_Skeleton.getPos();
	CVector view = _Walker->getView().getJ();


	uint zoneY = (uint)(-pos.y) / 160 + 1;
	uint zoneX = (uint)pos.x / 160;
	char firstLetter = zoneX / 26 + 'A';
	char secondLetter = zoneX % 26 + 'A';

	_Map->setPosition(pos.x, pos.y);
	if (_ShowMap)
		_Map->render();
	_SC.Ui->Text->setText("GameMode.Position", "AtysScape - X=%.4f Y=%.4f Z=%.4f -> Zone = %d_%c%c", pos.x, pos.y, pos.z,
						   zoneY, firstLetter, secondLetter);
	_SC.Ui->Text->setText("GameMode.View", "View axis %.2f %.2f %.2f - Speed %.2f", view.x, view.y, view.z, _MoveSpeed);
}


void CWalkMode::animate(float curTime)
{

	_SC.Scene->animate(curTime);
	_Walker->animate(curTime);
	applyRot();
	//_AnimatedHomin->_PlayListManager->animate(curTime);
}


void CWalkMode::createMap()
{
	/*_Map = _SC.Driver->createTextureFile("tryker_newbie_map.tga");

	_MapCursor = _SC.Driver->createTextureFile("player_pos.dds");
	_Map->setEnlargeCanvasNonPOW2Tex(true);*/

	//_Map->d
}

void CWalkMode::finish()
{
}

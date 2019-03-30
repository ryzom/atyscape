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

#include "fly_mode.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

CFlyMode::CFlyMode(TSharedComponents share) : CAtysMode(share) {
	_MouseX = 0.5f;
	_MouseY = 0.5f;
	_HandleMove = false;

	_MoveSpeed = 1.0f; // Base move speed, user set

}


void CFlyMode::init()
{
	selectRegion();
	doRegister();
	makeEntities();
	_Cam->setPos(_PlayerPos);
	_LastTime = CTime::getLocalTime();
// 	_AnimatedHomin->setPos(_PlayerPos+CVector(0.5, 0, 0));//CVector(17244.0f, -32912.0f, -1.4f));
// 	_AnimatedHomin->snapToGround();
// 	_AnimatedHomine->setPos(_PlayerPos+CVector(-0.5, 0, 0));//CVector(17244.0f, -32912.0f, -1.4f));
// 	_AnimatedHomine->snapToGround();
// 	_AnimatedHomin->playAnimation("IDLE");
// 	_AnimatedHomine->playAnimation("IDLE");
	_GoForward = false;

	_SC.Ui->Text->addTextZone("GameMode.Position", 0.01f, 0.05f, CRGBA(200, 255, 255), 14, UTextContext::TopLeft);
	_SC.Ui->Text->addTextZone("GameMode.View", 0.01f, 0.07f, CRGBA(220, 255, 255), 14, UTextContext::TopLeft);

}

void CFlyMode::handleKeyboard(float speed) {
	CEventListenerAsync al = _SC.Driver->AsyncListener;
	if (al.isKeyDown(KeyLEFT)) {
		_Cam->strafe(speed, false);
	} else if (al.isKeyDown(KeyRIGHT)) {
		_Cam->strafe(speed, true);
	} else if (al.isKeyDown(KeyUP)) {
		_Cam->move(speed);
	}  else if (al.isKeyDown(KeyDOWN)) {
		_Cam->move(speed, true);
	} else if (al.isKeyDown(KeyPRIOR)) {
		_Cam->slew(0, 0, 2);
	} else if (al.isKeyDown(KeyNEXT)) {
		_Cam->slew(0, 0, -2);
	} else if (al.isKeyDown(KeyP)) {
		_MoveSpeed += 0.005f;
	} else if (al.isKeyDown(KeyM)){
		_MoveSpeed -= 0.005f;
	} else if (al.isKeyDown(KeyR)) {
		/* Reset view */
		_Cam->setHeadingAttitude(0.0, 0.0);

	}

	if (_MoveSpeed < 0.0f) _MoveSpeed = 0.0f;
	if (_MoveSpeed > 15.0f) _MoveSpeed = 15.0f;

}

void CFlyMode::operator ()(const CEvent& event) {
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
		
		// Put the mouse back at the center
		_SC.Driver->setMousePos(0.5f, 0.5f);
		_MouseX = 0.5f;
		_MouseY = 0.5f;

	} else if (event==EventMouseDownId) {
		/* Enable move or move control */
		
		if (mouseEvent->Button == rightButton) {
			_GoForward = true;

		} else if (mouseEvent->Button == leftButton) {
			/* Set the mouse at the middle so that we don't move too far away next time */
			_SC.Driver->setMousePos(0.5f, 0.5f);
			_HandleMove = true;
		}
	} else if (event == EventMouseUpId) {
		/* Disable move or move control */
		if (mouseEvent->Button == rightButton) {
			_GoForward = false;
		} else if (mouseEvent->Button == leftButton) {
			_HandleMove = false;
		}
	}
}

void CFlyMode::update(float dt)
{
	_LastTime = _NewTime;
	_NewTime = CTime::getLocalTime();
	_DeltaTime = (double)(_NewTime - _LastTime) / 1000.0;
	
	CVector walkerPos = _Cam->getPos();

	float camPosz = _Cam->getPos().z;
	_Cam->snapToGround();
	if (camPosz < _Cam->getPos().z)
		_Cam->setPos(CVector(_Cam->getPos().x, _Cam->getPos().y,  _Cam->getPos().z+2.0f));
	else
		_Cam->setPos(CVector(_Cam->getPos().x, _Cam->getPos().y, camPosz));

// 	_AnimatedHomin->updateAnimation();
// 	_AnimatedHomine->updateAnimation();

	CMatrix camMat = _Cam->getView();
	camMat.setPos(_Cam->getPos());
	_SC.Scene->getCam().setMatrix(camMat);
}

void CFlyMode::handleEvents()
{

	handleKeyboard(_MoveSpeed);
	if (_GoForward)
		_Cam->move(_MoveSpeed);

}

void CFlyMode::render() {

	World->updateAround(_Cam->getPos());

	_SC.Scene->render();

	//float speed;
	CVector pos = _Cam->getPos();
	CVector view = _Cam->getView().getJ();

////	_SC.Ui->writeText(0.01f, 0.95f, "View axis %.2f %.2f %.2f - Speed %.2f",
////						   view.x, view.y, view.z, _MoveSpeed);

////	_SC.Ui->writeText(0.90f, 0.99f, "v0.4");

	uint zoneY = (uint)(-pos.y) / 160 + 1;
	uint zoneX = (uint)pos.x / 160;
	char firstLetter = zoneX / 26 + 'A';
	char secondLetter = zoneX % 26 + 'A';

	_SC.Ui->Text->setText("GameMode.Position", "AtysScape - X=%.4f Y=%.4f Z=%.4f -> Zone = %d_%c%c", pos.x, pos.y, pos.z,
						   zoneY, firstLetter, secondLetter);

	_SC.Ui->Text->setText("GameMode.View", "View axis %.2f %.2f %.2f - Speed %.2f", view.x, view.y, view.z, _MoveSpeed);

////	_SC.Ui->writeText(0.01f, 0.89f, "AtysScape - X=%.4f Y=%.4f Z=%.4f -> Zone = %d_%c%c", pos.x, pos.y, pos.z,
////						   zoneY, firstLetter, secondLetter);
}


void CFlyMode::animate(float curTime)
{

	_SC.Scene->animate(curTime);
// 	_AnimatedHomin->animate(curTime);
// 	_AnimatedHomine->animate(curTime);
}

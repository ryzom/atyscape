/** 
 * Atyscape Atys viewer - Make Avatar Mode
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

#include <nel/misc/config_file.h>
#include <nel/3d/event_mouse_listener.h>

#include "make_avatar_mode.h"
#include "entity_manager.h"


using namespace std;
using namespace NLMISC;
using namespace NL3D;


CMakeAvatarMode::CMakeAvatarMode(TSharedComponents share) : CGameMode(share)
{
	_SC = share;
	_IsValidate = false;

	_World = new CWorld(_SC);
	_World->createLight();
	_SC.Scene->getCam().setTransformMode(UTransformable::DirectMatrix);
	_Cam = new CEntity("Camera");
	_EManager = &CEntityManager::getInstance();

	_State = 0;
	_AvatarSpeed = 0;

	_SC.Ui->Text->addTextZone("GameMode.Position", 0.01f, 0.05f, CRGBA(200, 255, 255), 14);
}

void CMakeAvatarMode::init()
{
	doRegister();

	//string keyCodes = _EManager->getKeyCodesOfAvatar(_AvatarId);

	_AvatarConf = new CConfigurator("AvatarConfig");
	_AvatarConf->setDefsFile("data/tmpl/homin.tmpl", "data/i18n/tmpl/homin_tmpl_fr.txt");
	_AvatarConf->create(CWindowManager::getInstance().getWindow("[Root]"));
	_AvatarConf->setPos(5.5f, 5.05f);
	_AvatarConf->setExpand(0.4f, 0.9f);
	//_AvatarConf->initKeyCodes(_Avatar->getKeyCodes());
	_AvatarConf->setRandomKeyCodes();
	_AvatarConf->setCallback("ListBox", new CCallback(&CMakeAvatarMode::setKeyCodes, this));
	_AvatarConf->setCallback("Ok", new CCallback(&CMakeAvatarMode::saveKeyCodes, this));
	_AvatarConf->setCallback("randomEvent", new CCallback(&CMakeAvatarMode::setRandomKeyCodes, this));
	//_AvatarConf->hide();

	_Avatar  = _EManager->createNewEntity("EditedAvatar", _AvatarConf->getKeycodes(), 2);
	_Avatar->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
	_Avatar->loadAnimations();
	_Avatar->playAnimation("IDLE");

	_UnDefAvatar  = _EManager->createNewEntity("EditedAvatar", _EManager->getKeyCodesOfAvatar(5), 2); // AvatarId > 4 = undefined
	_UnDefAvatar->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
	_UnDefAvatar->loadAnimations();
	_UnDefAvatar->playAnimation("IDLE");

	CMatrix camMat = CMatrix::Identity;
	camMat.setPos(CVector(2.5f, -4.0f, 1.0f));
	_SC.Scene->getCam().setMatrix(camMat);
	
	_LastTime = CTime::getLocalTime();

	_AvatarOffset = CEntityManager::instance().getOffset(_AvatarConf->getKeycodes()) + .1f ;

	_Avatar->setPos(CVector(200.0f, -2.0f, _AvatarOffset));
	_UnDefAvatar->setPos(CVector(2.0f, -2.0f, 0));
}

void CMakeAvatarMode::setPlayer(uint player)
{
	_AvatarId = player;
}

void CMakeAvatarMode::operator ()(const CEvent& event)
{
	CEventMouse* mouseEvent=(CEventMouse*)&event;
	
	_SC.Ui->MouseX = mouseEvent->X;
	_SC.Ui->MouseY = mouseEvent->Y;

}

void CMakeAvatarMode::update(float dt)
{

	CQuat q;
	if (_State == 0)
	{
	//	_UnDefAvatar->setQuat(CQuat(CVector::K, _AvatarSpeed)*_UnDefAvatar->getQuat());
	//	_AvatarSpeed += 0.2f;
	//	_SC.Ui->Text->setText("GameMode.Position", "Speed =%.4f", _AvatarSpeed);
	//	if (_AvatarSpeed >= 5.0f)
	//	{
	//		_State = 1;
	//		q = _UnDefAvatar->getQuat();
	//		_UnDefAvatar->setPos(CVector(20.0f, -2.0f, 0));
	//		_Avatar->setPos(CVector(2.0f, -2.0f, 0));
	//		//_EManager->changeEntityShape(_Avatar, _AvatarConf->getKeycodes(), 2);
	//		_Avatar->setQuat(q);
			_UnDefAvatar->setQuat(CQuat(CVector::K, -(float)Pi/2.0f));
			_AvatarConf->setPos(-0.5f, 0.05f);
			_State = 1;
	//	}
	}
	else if (_State == 1)
	{
	//	if (_AvatarSpeed >= 0)
	//	{
	//		_Avatar->setQuat(CQuat(CVector::K, _AvatarSpeed)*_Avatar->getQuat());
	//		_AvatarSpeed -= 0.2f;
	//	//	_AvatarConf->setPos(-0.5f, 0.05f);
	//	//	_State = 2;
	//	}

		_AvatarConf->setPos(_AvatarConf->Pos[0]+0.05f, 0.05f);
		if ((_AvatarConf->Pos[0] > 0.1f) && (_AvatarConf->Pos[0] < 0.3f))
		{
			_UnDefAvatar->setPos(CVector(20.0f, -2.0f, 0));
			_Avatar->setPos(CVector(2.0f, -2.0f, _AvatarOffset));
			_Avatar->setQuat(CQuat(CVector::K, -(float)Pi/2.0f));
			_AvatarSpeed = 0.0f;
		}
		if (_AvatarConf->Pos[0] >= 0.5f)
		{
			_State = 3;
		}
	}
	else if (_State == 2)
	{
	
	}
	else if (_State == 3)
	{
		_State = 3;
		//_AvatarConf->setPos(0.5f, 0.05f);
		//_AvatarConf->show();
	}
	else
	{
		_Avatar->setPos(CVector(2.0f, -2.0f, _AvatarOffset));
	}

	_Avatar->updateAnimation();
	_UnDefAvatar->updateAnimation();

}

void CMakeAvatarMode::handleEvents()
{
	CEventListenerAsync al = _SC.Driver->AsyncListener;
	/*if (al.isKeyDown(KeyLEFT))
	{
		_Pos.x += 0.03f;
	}
	else if (al.isKeyDown(KeyRIGHT))
	{
		_Pos.x -= 0.03f;
	}
	else if (al.isKeyDown(KeyUP))
	{
		_Pos.y -= 0.03f;
	}
	else if (al.isKeyDown(KeyDOWN))
	{
		_Pos.y += 0.03f;
	}
	else if (al.isKeyDown(KeyPRIOR))
	{
		_Pos.z -= 0.03f;
	}
	else if (al.isKeyDown(KeyNEXT))
	{
		_Pos.z += 0.03f;
	}*/
}

void CMakeAvatarMode::render()
{
}


void CMakeAvatarMode::animate(float curTime)
{	
	_SC.Scene->animate(curTime);
	_Avatar->animate(curTime);
	_Avatar->applyQuat();
	_UnDefAvatar->animate(curTime);
	_UnDefAvatar->applyQuat();
}

uint CMakeAvatarMode::getState()
{
	if (_IsValidate)
		return 2;
	else
		return 0;
}

void  CMakeAvatarMode::finish()
{
	unRegister();
	_AvatarConf->destroy();
	_EManager->deleteEntity(_Avatar);
	_EManager->deleteEntity(_UnDefAvatar);
}

bool CMakeAvatarMode::setKeyCodes(const string &keycodes)
{
	_AvatarOffset = CEntityManager::instance().getOffset(keycodes) + .1f ;
	_EManager->changeEntityShape(_Avatar, keycodes, 2);
	_Avatar->setPos( CVector( _Avatar->getPos().x, _Avatar->getPos().y, _AvatarOffset) ) ;
	return true;
}

bool CMakeAvatarMode::saveKeyCodes(const string &keycodes)
{	
	_EManager->saveKeyCodesOfAvatar(_AvatarId, keycodes);
	_IsValidate = true;
	return true;
}

bool CMakeAvatarMode::setRandomKeyCodes(const string &event)
{	
	pause();
	resume();
	_AvatarOffset = CEntityManager::instance().getOffset(_AvatarConf->getKeycodes()) + .1f ;
	nlinfo("event of button");

	return true;
}

void CMakeAvatarMode::pause()
{
	_UnDefAvatar->setPos(CVector(20.0f, -2.0f, 0));
	_UnDefAvatar->animate(0);
	_Avatar->setPos(CVector(20.0f, -2.0f, _AvatarOffset));
	_Avatar->animate(0);
	_AvatarConf->setPos(0.5f, 5.05f);
	unRegister();
}

void CMakeAvatarMode::resume()
{
	_State = 0;
	_AvatarSpeed = 0;
	_IsValidate = false;

	_AvatarConf->setRandomKeyCodes();
	_EManager->changeEntityShape(_UnDefAvatar, _Avatar->getKeyCodes(), 2);
	_EManager->changeEntityShape(_Avatar, _AvatarConf->getKeycodes(), 2);

	_UnDefAvatar->setPos(CVector(2.0f, -2.0f, 0));
	_UnDefAvatar->animate(0);

	_Avatar->playAnimation("IDLE");
	_UnDefAvatar->playAnimation("IDLE");

	CMatrix camMat = CMatrix::Identity;
	camMat.setPos(CVector(2.5f, -4.0f, 1.0f));
	_SC.Scene->getCam().setMatrix(camMat);

}

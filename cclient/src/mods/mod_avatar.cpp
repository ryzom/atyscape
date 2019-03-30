/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Module for Avatar Managment
	____________________________________________________________________

	This file is part of Ryturn Home Crafted MMORPG.

    Ryturn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ryturn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ryturn.  If not, see <http://www.gnu.org/licenses/>.
	____________________________________________________________________

 */

#include "mod_avatar.h"

CModAvatar::CModAvatar()
{
}

void CModAvatar::init(const string &keyCodes)
{
	_Avatar  = CEntityManager::getInstance().createNewEntity("MainAvatar", keyCodes, 2);
	
	// TODO !!
	_Avatar->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
	//
	_Avatar->loadAnimations();
	_Avatar->playAnimation("IDLE");
	_CurrentAnimation = "IDLE";
}

CAnimated* CModAvatar::getAnimated()
{
	return _Avatar;
}

void CModAvatar::setPos(const CVector &newPos)
{
	_Pos = newPos;
	float avatarOffset = CEntityManager::instance().getOffset(_Avatar->getKeyCodes()) + .1f ;
	_Avatar->setPos(newPos+CVector(0, 0, avatarOffset));
	_Avatar->animate(0);
}

uint CModAvatar::update()
{
	_Avatar->updateAnimation();
	return _State;
}

bool CModAvatar::setKeyCodes(const string &keycodes)
{
	CEntityManager::getInstance().changeEntityShape(_Avatar, keycodes, 2);
	setPos(_Pos);
	return true;
}

bool CModAvatar::saveKeyCodes(const string &keycodes)
{	
	//CEntityManager::getInstance()->saveKeyCodesOfAvatar(_AvatarId, keycodes);
	_State = MOD_AVATAR_STATE_VALIDATE;
	return true;
}

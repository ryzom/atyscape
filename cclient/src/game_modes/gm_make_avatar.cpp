/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Make Avatar Game Mode
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

#include "gm_make_avatar.h"

CGmMakeAvatar::CGmMakeAvatar(TSharedComponents share) : CGameMode(share)
{
	_SC = share;
}

void CGmMakeAvatar::init()
{
// Inits
	// Events Resgistration
	doRegister();
	// Views
	// This View First !!!
	_ViewAvatarConfigurator = new CViewAvatarConfigurator();
	_ViewAvatarConfigurator->init();
	



	_ModCam = &CModCam::getInstance();
	_ModCam->init();
	_ModCam->setPos(CVector(2.5f, -4.0f, 1.0f));

	_ViewSceneMakeAvatar = new CViewSceneMakeAvatar();
	_ViewSceneMakeAvatar->init();

	_ViewAvatarShowCase = new CViewAvatarShowCase();
	_ViewAvatarShowCase->init();

	// Mods
	_ModAvatar = &CModAvatar::getInstance(); // Initialised on ViewAvatarConfigurator
	_ModAvatar->setPos(CVector(2.0f, -2.0f, 0));

}

void CGmMakeAvatar::update(float dt)
{
	uint state = _ModAvatar->update();

	if (state == MOD_AVATAR_STATE_VALIDATE)
	{
		_State = GM_MAKE_AVATAR_FINISH;
	}
}

void CGmMakeAvatar::finish()
{
}

void CGmMakeAvatar::pause()
{
}

void CGmMakeAvatar::resume()
{
}

void CGmMakeAvatar::operator()(const CEvent &event)
{
	_ViewAvatarShowCase->handleMouseEvent(event);
}

void CGmMakeAvatar::animate(float curTime)
{
	_CurTime = curTime;
}

void CGmMakeAvatar::render()
{
	_ViewAvatarShowCase->render();
}

void CGmMakeAvatar::handleEvents()
{
}

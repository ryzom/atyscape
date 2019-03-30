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


#ifndef _GM_MAKE_AVATAR_H_
#define _GM_MAKE_AVATAR_H_

#include <nel/misc/singleton.h>
#include <string>
#include "../mods/mod_avatar.h"
#include "../mods/mod_cam.h"
#include "../mods/mod_nel.h"
#include "../mods/mod_avatar_configurator.h"
#include "../game_mode.h"
#include "../views/view_scene_make_avatar.h"
#include "../views/view_avatar_show_case.h"
#include "../views/view_avatar_configurator.h"

using namespace std;

#define GM_MAKE_AVATAR_RUN 0
#define GM_MAKE_AVATAR_FINISH 1

class CGmMakeAvatar : public CGameMode
{

public:
	CGmMakeAvatar(TSharedComponents share);

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void handleEvents();
	virtual void operator ()(const CEvent& event);
	virtual void animate(float curTime);
	virtual void pause();
	virtual void resume();
	void finish();

	void doRegister() {
		CModNel::getInstance().Driver->EventServer.addListener(EventMouseMoveId, this);
		CModNel::getInstance().Driver->EventServer.addListener(EventMouseDownId, this);
		CModNel::getInstance().Driver->EventServer.addListener(EventMouseUpId, this);
	}

	void unRegister() {
		CModNel::getInstance().Driver->EventServer.removeListener(EventMouseMoveId, this);
		CModNel::getInstance().Driver->EventServer.removeListener(EventMouseDownId, this);
		CModNel::getInstance().Driver->EventServer.removeListener(EventMouseUpId, this);
	}


private:
	CModAvatar*					_ModAvatar;
	CModCam*					_ModCam;
	CViewSceneMakeAvatar*		_ViewSceneMakeAvatar;
	CViewAvatarShowCase*		_ViewAvatarShowCase;
	CViewAvatarConfigurator*	_ViewAvatarConfigurator;

	float					_CurTime; // Temporary !!
};

#endif
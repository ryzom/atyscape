/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View for create scene of MakeAvatar
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

#ifndef _VIEW_SCENE_MAKE_AVATAR_H_
#define _VIEW_SCENE_MAKE_AVATAR_H_

#include "../view_base.h"
#include "../mods/mod_cam.h"
#include "../mods/mod_nel.h"

class CViewSceneMakeAvatar : public CViewBase
{

public:
	CViewSceneMakeAvatar();

	void init();
	void render();

private:
	CModCam*	_ModCam;
	CModNel*	_ModNel;
};


#endif
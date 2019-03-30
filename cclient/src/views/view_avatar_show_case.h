/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View of Avatar in ShowCase Mode
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


#ifndef _VIEW_AVATAR_SHOW_CASE_H_
#define _VIEW_AVATAR_SHOW_CASE_H_

#include "../animated.h"
#include "../view_base.h"
#include "../mods/mod_avatar.h"
#include "../mods/mod_time.h"

class CViewAvatarShowCase : public CViewBase
{

public:
	CViewAvatarShowCase();

	void init();
	void handleMouseEvent(const CEvent &event);
	void handleKeyboardEvent(const CEventListenerAsync &event);
	void render();

private:
	CModAvatar*	_ModAvatar;
	CModTime*	_ModTime;
	CAnimated*	_Avatar;

	float		_LastMouseX, _LastMouseY;
	float		_SpeedMove;
	bool		_IsMoving;
};


#endif
/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View of Avatar Configurator
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


#ifndef _VIEW_AVATAR_CONFIGURATOR_H_
#define _VIEW_AVATAR_CONFIGURATOR_H_

#include "../view_base.h"
#include "../lg_ui.h"
#include "../lg_configurator.h"
#include "../mods/mod_avatar.h"

using namespace LG;

class CViewAvatarConfigurator : public CViewBase
{

public:
	CViewAvatarConfigurator();

	void init();
	void render();
	bool setRandomKeyCodes(const string &event);


private:
	CConfigurator*	_Configurator;
	CModAvatar*		_ModAvatar;
};


#endif
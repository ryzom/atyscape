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

#ifndef _MOD_AVATAR_H_
#define _MOD_AVATAR_H_

#include <nel/misc/singleton.h>
#include <string>
#include "../animated.h"
#include "../entity_manager.h"
#include "../mod_base.h"

using namespace std;

#define MOD_AVATAR_STATE_VALIDATE 1

class CModAvatar : public CSingleton<CModAvatar>, CModBase
{

public:
	CModAvatar();

	CAnimated* getAnimated();

	void setPos(const CVector &newpos);
	bool setKeyCodes(const string &keycodes);
	bool saveKeyCodes(const string &keycodes);

	void init(const string &keyCodes);
	uint update();

private:
	CEntityManager	*_EManager;
	CAnimated*		_Avatar;
	string			_CurrentAnimation;
	CVector			_Pos;

};

#endif
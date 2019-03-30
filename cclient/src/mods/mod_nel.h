/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Module for storage of Nel Components
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

#ifndef _MOD_NEL_H_
#define _MOD_NEL_H_

#include <nel/misc/singleton.h>
#include <nel/3d/u_scene.h>
#include <nel/3d/u_driver.h>
#include <string>

#include "../entity.h"
#include "../mod_base.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

class CModNel : public CSingleton<CModNel>, CModBase
{

public:
	CModNel();

	void init(UScene* scene, UDriver* driver);
	uint update();

	UScene	*Scene;
	UDriver	*Driver;

};

#endif
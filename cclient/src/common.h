/** 
 * AtysScape - Common
 * 2007-02-25 - Ulukyn
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



#ifndef _COMMON_H_
#define _COMMON_H_

#include <nel/3d/u_scene.h>
#include <nel/3d/u_driver.h>
#include "lg_ui.h"
#include "lg_window_manager.h"
#include "configuration.h"

#define LOOK "QuadraticLook"


#define callMemberFunction(obj, member) ((obj).*(member))
#define SAFE_DELETE(x) if ((x) != NULL) { delete (x); (x) = NULL; }

using namespace NL3D;
using namespace LG;

struct TSharedComponents
{
	UScene	*Scene;
	UDriver	*Driver;
	CUI		*Ui;
	CAtyscapeConfiguration *Config;
	float DeltaTime;
};

enum
{
	SelfCollisionBit = 1,
	OtherCollisionBit = 2,
	AtysScapeCollisionBit = 4,
	StaticCollisionBit = 8
};

#endif

/** 
 * Atyscape Atys viewer - Landscape
 * 2007-02-24 - Zorglub / Ulukyn 
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

#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/scene_user.h>
#include <nel/misc/progress_callback.h>
#include <nel/misc/big_file.h>
#include <nel/3d/u_landscape.h>


#include "configuration.h"

#define LANDSCAPE_CREATE_INSTANCES "AtysScape - Creating instances (%i/%i)"

using namespace std;
using namespace NL3D;

class CAtysLand
{
public:
	CAtysLand(UScene* scene);

	void load(CAtyscapeRegion region, string season);
	void loadVegetable(string texture);
	void setupCollision();
	bool snapToGround(CVector &pos, CVector &normal);
	void addCollisionMesh(CVisualCollisionMesh);
	ULandscape* Ld;

private:
	UDriver* _Driver;
	UScene* _Scene;
	UTextContext* _TextContext;
	CAtyscapeRegion _Region;
	UVisualCollisionManager* _VisualCollisionManager;
	UVisualCollisionEntity* _CamCollisionEntity;
	bool _UseCollisionSystem;
};

#endif

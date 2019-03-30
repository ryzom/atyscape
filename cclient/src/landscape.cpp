/** 
 * Atyscape Atys viewer - Landscape Manager
 * 2007-02-25 - Zorglub / Ulukyn
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

#include "landscape.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

class Progressor : public IProgressCallback {
public:
	virtual void progress(float value) {
		//nlinfo("Progress at %f", value);
	}
};

CAtysLand::CAtysLand(UScene* scene)
{
	nlinfo("\t\tEntering AtysLand...");
	//_Driver = driver;
	_Scene = scene;
	//_TextContext = textContext;
	Ld = _Scene->createLandscape();
	_UseCollisionSystem = false;
	nlinfo("\t\tLeaving AtysLand...");
}

void CAtysLand::load(CAtyscapeRegion region, string season)
{
	season = "_" + season;
	Ld->loadBankFiles(region.Bank + ".smallbank", region.Bank + season + ".farbank");
	Ld->postfixTileFilename(season.c_str());
	Ld->postfixTileVegetableDesc(season.c_str());
	
	Progressor pr;
	Ld->loadVegetableTexture("microveget_" + region.MVG + season + ".dds");
	Ld->flushTiles(pr);
	Ld->enableVegetable(true);

	_Scene->setCoarseMeshManagerTexture(string("nel_coarse_mesh_" + region.Bank + season + ".dds").c_str());
}

//???
void CAtysLand::loadVegetable(string texture)
{

}

void CAtysLand::setupCollision()
{
	_VisualCollisionManager = _Scene->createVisualCollisionManager();
	_VisualCollisionManager->setLandscape(Ld);

	_CamCollisionEntity = _VisualCollisionManager->createEntity();
	_CamCollisionEntity->setCeilMode(true);

	_UseCollisionSystem = true;
}

bool CAtysLand::snapToGround(CVector &pos, CVector &normal)
{
	return _CamCollisionEntity->snapToGround(pos, normal);
}

void CAtysLand::addCollisionMesh(CVisualCollisionMesh)
{
	//_VisualCollisionManager->addMeshInstanceCollision();
}

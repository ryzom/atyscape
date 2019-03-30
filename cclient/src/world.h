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

#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <nel/pacs/u_retriever_bank.h>
#include <nel/pacs/u_global_retriever.h>
#include <nel/pacs/u_move_container.h>
#include <nel/3d/u_visual_collision_manager.h>
#include <nel/3d/u_visual_collision_entity.h>

#include "configuration.h"
#include "common.h"

using namespace std;
using namespace NL3D;
using namespace NLPACS;

class CWorld
{
public:
	CWorld(TSharedComponents share);

	void loadRegion(const CAtyscapeRegion &region, const string &seasonName);
	void setupCollisionSystem(string retrieverBankName, string globalRetrieverName);
	void evalCollision(double dt, uint8 worldImage);
	void loadAround(CVector pos);
	void updateAround(CVector pos);
	void createLight();
	bool loadSkydome(const CAtyscapeRegion &region, const string &season);
	void updateSky(float dt, CMatrix camView);
	void renderSky();


	UVisualCollisionManager		*_VisualCollisionManager;

protected:
	friend class				CEntity;
	UMoveContainer				*_MoveContainer;
	UGlobalRetriever			*_GlobalRetriever;

private:
	TSharedComponents			_SC;
	CAtyscapeRegion				_Region;
	NL3D::ULandscape*			_Ld;
	NLPACS::URetrieverBank		*_RetrieverBank;
	//UVisualCollisionEntity		*_CamCollisionEntity;
	ULight						*_Sun;
	CVector						_SunDirection;
	bool						_UseCollisionSystem;
	float						_UpdateZonesDistance;
	UScene						*_SkyScene;
	bool						_HaveSky;
	float						_SkyRotX;
};

#endif

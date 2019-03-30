/** 
 * Atyscape Atys viewer - Atys Mode
 * Partly based on NEVRAX SNOWBALLS.
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


#ifndef _ATYS_MODE_H_
#define _ATYS_MODE_H_

#include "world.h"
#include "animated.h"
#include "common.h"
#include "game_mode.h"
#include "select_scene.h"
#include "homin.h"

using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CAtysMode: public CGameMode {
public:
	CAtysMode(TSharedComponents share);
	virtual ~CAtysMode(){}


	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
	virtual void animate(float curTime) = 0;
	void reset();

private:
	void setPlayerPosition(CAtyscapePoint p);
	void createLandscape(string region);
	bool selectRegion(const string &winName);

	CLocationSelect* _Select;

protected:	
	CWorld* World;

	CAnimated *_AnimatedYubo;
	CHomin *_AnimatedHomin;
	CHomin *_AnimatedHomine;
	CHomin *_AnimatedFyrette;

	TSharedComponents	_SC;
	CEntity				*_Cam;
	CVector				_OldCamPos;
	UInstanceGroup		*_CamUIG;
	CVector				_PlayerPos;
	queue <CAnimated*>	_AnimatedsList;
	CFrustum			_CamFrustum;
	string				_SelectedRegion;

	void makeEntities();
	void selectRegion();

};
#endif

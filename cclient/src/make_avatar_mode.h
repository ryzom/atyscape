/** 
 * Atyscape Atys viewer - Make Avatar Mode
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


#ifndef _MAKE_AVATAR_MODE_H_
#define _MAKE_AVATAR_MODE_H_

#include "game_mode.h"
#include "configuration.h"
#include "world.h"
#include "ui.h"
#include "homin.h"
#include "entity.h"
#include "entity_manager.h"
#include "lg_configurator.h"

class CMakeAvatarMode: public CGameMode
{
public:
	CMakeAvatarMode(TSharedComponents share);

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void handleEvents();
	virtual void animate(float curTime);
	virtual void pause();
	virtual void resume();

	void setPlayer(uint player);
	uint getState();
	bool setKeyCodes(const string &keycodes);
	bool saveKeyCodes(const string &keycodes);
	bool setRandomKeyCodes(const string &event);
	void finish();

private:
	void handleKeyboard(float speed);

	void operator ()(const CEvent& event);
	void  updateAnims(bool eventMouseUpId);

	void doRegister() {
		_SC.Driver->EventServer.addListener(EventMouseMoveId, this);
		_SC.Driver->EventServer.addListener(EventMouseDownId, this);
		_SC.Driver->EventServer.addListener(EventMouseUpId, this);
	}

	void unRegister() {
		_SC.Driver->EventServer.removeListener(EventMouseMoveId, this);
		_SC.Driver->EventServer.removeListener(EventMouseDownId, this);
		_SC.Driver->EventServer.removeListener(EventMouseUpId, this);
	}

	void _computeSpeed();
	void turn(float angleZ, float angleX);


private:
	CWorld*				_World;

	CEntity*			_Cam;

	CAnimated*			_Avatar;
	CAnimated*			_UnDefAvatar;
	uint				_AvatarId;
	
	float				_MouseEventX;
	float				_MouseEventY;

	TTime				_NewTime;
	TTime				_LastTime;
	double				_DeltaTime;

	CEntityManager		*_EManager;
	bool				_IsValidate;

	CConfigurator*		_AvatarConf;

	uint				_State;
	float				_AvatarSpeed;
	float				_AvatarOffset ;


};

#endif

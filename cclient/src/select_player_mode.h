#ifndef _SELECT_PLAYER_MODE_H_
#define _SELECT_PLAYER_MODE_H_

#include <vector>
#include <nel/misc/time_nl.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/u_skeleton.h>

#include "game_mode.h"
#include "configuration.h"
#include "world.h"
#include "ui.h"
#include "homin.h"
#include "entity.h"
#include "lg_popup_menu.h"
#include "lg_callback.h"


using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CSelPlayerMode: public CGameMode {
public:
	CSelPlayerMode(TSharedComponents share);
	virtual ~CSelPlayerMode(){}

//	virtual void postInit();

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void handleEvents();
	bool go(const string &winName);
	virtual void animate(float curTime);
	uint  getSelectedPlayer();
	uint getState();
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

	CAnimated*			_AnimatedYubo;
	CAnimated*			_AnimatedHomin;
	CHomin*				_AnimatedHomine;
	CHomin*				_AnimatedFyrette;

	uint				_SelectedPlayer;
	uint				_CurrentPlayer;
	float				_CamPos;
	bool				_CanMove;

	float				_MoveSpeed;
	float				_CamSpeed;
	
	float				_MouseEventX;
	float				_MouseEventY;

	TTime				_NewTime;
	TTime				_LastTime;
	double				_DeltaTime;

	uint				_Walker;
	uint				farCount[4];

	CPopupMenu*			_PopupMenu;

	// test
	UCamera				_TempCam ;

};
#endif

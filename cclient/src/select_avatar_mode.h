#ifndef _SELECT_AVATAR_MODE_H_
#define _SELECT_AVATAR_MODE_H_

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

class CSelAvatarMode: public CGameMode {
public:
	CSelAvatarMode(TSharedComponents share);
	virtual ~CSelAvatarMode(){}

//	virtual void postInit();

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void pause();
	virtual void resume();
	virtual void handleEvents();
	bool go(const string &winName);
	virtual void animate(float curTime);
	void updateAvatars();
	uint  getSelectedPlayer(string &avatarName);
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

	CAnimated*			_Avatars[5];
	CAnimated*			_Idea;
	string				_AvatarNames[5];
	float				_AvatarOffsets[5] ;

	uint				_SelectedAvatar;
	uint				_CurrentAvatar;
	uint				_InTonneauAvatar;
	float				_CamPos;
	bool				_DoMove;

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
	UInstance			_Agora;
	UInstance			_Tonneau;
	UInstance			_TonneauBreak;
	bool				_Run;
	float				_TonneauSpeed;
	float				_IdeaSpeed;

};
#endif


#ifndef _WALK_MODE_H_
#define _WALK_MODE_H_

#include <vector>
#include <nel/misc/time_nl.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_landscape.h>
#include <nel/3d/u_skeleton.h>

#include "walk_mode.h"
#include "atys_mode.h"
#include "configuration.h"
#include "world.h"
#include "ui.h"
#include "homin.h"
#include "lg_map.h"

using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CWalkMode: public CAtysMode {
public:
	CWalkMode(TSharedComponents share);
	virtual ~CWalkMode(){}

//	virtual void postInit();

	void setPlayer(uint player);
	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void finish();
	virtual void renderUI();
	virtual void handleEvents();
	virtual void animate(float curTime);

private:
	void applyRot();
	void handleKeyboard(float speed);

	void operator ()(const CEvent& event);

	void doRegister() {
		_SC.Driver->EventServer.addListener(EventMouseWheelId, this);
		_SC.Driver->EventServer.addListener(EventMouseMoveId, this);
		_SC.Driver->EventServer.addListener(EventMouseDownId, this);
		_SC.Driver->EventServer.addListener(EventMouseUpId, this);
	}

	void _computeSpeed();
	void turn(float angleZ, float angleX);

	void createMap(); // test

	//CVector				fr;
	//CFrustum			frustum;

	//UMaterial			_Mat;
	//CMaterial*			_CMat;
	//float				_OldAnimNorm;
	//bool				_ModePlace;
	//CVector				BuildPos;
	//CMatrix				Cam;	

private:
	CVector				_PosBeforeAnim;
	float				_MoveSpeed;
	float				_AltitudeSpeedBoost;
	CAnimated			*_Walker;
	bool				_GoForward;
	bool				_HandleMove;
	
	float				_CamSpeed;
	float				_LastCamRotation; // Last RotationZ between Cam and Walker
	float				_CamRotation; // RotationZ between Cam and Walker
	float				_CamWalkerDistance;

	float				_MouseX;
	float				_MouseY;
	float				_MouseEventX;
	float				_MouseEventY;

	TTime				_NewTime;
	TTime				_LastTime;
	double				_DeltaTime;
	CQuat				_WalkerQuat;

	uint				_Player;
	float				_PlayerOffset ;

	//UTextureFile		*_Map;
	CMap				*_Map;
	bool				_ShowMap;


};
#endif

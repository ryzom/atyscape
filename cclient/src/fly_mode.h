#ifndef _FLY_MODE_H_
#define _FLY_MODE_H_

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

using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CFlyMode: public CAtysMode {
public:
	CFlyMode(TSharedComponents share);
	virtual ~CFlyMode(){}

//	virtual void postInit();

	virtual void init();
	virtual void update(float dt);
	virtual void render();
	virtual void handleEvents();
	virtual void animate(float curTime);

private:
	void handleKeyboard(float speed);

	void operator ()(const CEvent& event);

	void doRegister() {
		_SC.Driver->EventServer.addListener(EventMouseMoveId, this);
		_SC.Driver->EventServer.addListener(EventMouseDownId, this);
		_SC.Driver->EventServer.addListener(EventMouseUpId, this);
	}

	void _computeSpeed();
	void turn(float angleZ, float angleX);


private:
	CVector				_PosBeforeAnim;
	float				_MoveSpeed;
	float				_AltitudeSpeedBoost;
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


};
#endif

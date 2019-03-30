/** 
 * AtysScape - Entity
 * 2007-03-16 - Ulukyn
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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <nel/misc/vector.h>
#include <nel/misc/vectord.h>
#include <nel/misc/quat.h>
#include <nel/pacs/u_move_primitive.h>
#include <nel/3d/u_visual_collision_entity.h>


#include "world.h"

using namespace std;
using namespace NLMISC;
using namespace NLPACS;

#define BRAKE_FORCE (-0.1)

class CEntity
{

public:
	CEntity(string name); // !!! Entity can no use PACS, so need redefine ctor
	
	void addToWorld(uint8 worldImage, CWorld *world);

	virtual void setPos(CVector pos);
	virtual CVector getPos();
	virtual void setView(CMatrix);
	void setQuat(CQuat quat);
	virtual CQuat getQuat();
	virtual CMatrix getView();

	void setGlobalPos(CVector pos);

	CVector snapToGround();
	void calculateSpeed(float deltaTime);
	/** Try Move Entity with PACS system */
	void tryMove(float dt);

	/** Do Move */
	void doMove();

	/** Make the Entity move in its view direction */
	void move(float speed, bool backwards = false);

	/** Make the Entity strafe in a plane orthogonal to its view direction */
	void strafe(float speed, bool right = false);

	/** Make the Entity move directly, regardless of its view direction */
	void slew(float x, float y, float z);

	/** Directly set Entity heading and attitude */
	void setHeadingAttitude(float heading, float attitude);

	/**
	 * Make the Entity turn
	 * @param zMove between -Pi and Pi to indicate additional Z axis rotation
	 * @param xMove between -Pi and Pi to indicate additional X axis rotation
	 */
	void turn(float angleZ, float angleX);

	/**
	 * Make the Entity turn
	 * @param xMove between -Pi and Pi to indicate additional X axis rotation
	 * @param yMove between -Pi and Pi to indicate additional Y axis rotation
	 * @param zMove between -Pi and Pi to indicate additional Z axis rotation
	 */
	void turn(float angleX, float angleY, float angleZ);

	void saveState();
	void restoreState();

	void updatePosition();

	virtual void show();
	virtual void hide();
	
	virtual void update();
	virtual void render();

	string		Name;
	uint		Id;
	bool		Visible;
	bool		SnapToGround;

protected:
	bool			_TryMove;
	CVector			_Pos;
	CVector			_Speed;
	CMatrix			_View;
	CQuat			_Quat;

	UMovePrimitive			*_MovePrim;
	UVisualCollisionEntity	*_VisualCol;
	uint8					_WorldImage;

	float			_SpeedFactor;

private:
	CWorld			*_World;
//	double			_OldDeltaTime;
	float			_DeltaTime;
	TTime			_NewTime;
	TTime			_LastTime;
	CVector			_OldPos;
	CVector			_SavedPos;
	CVector			_SavedSpeed;
	CMatrix			_SavedView;
	bool			_UseCollisions;



};

#endif

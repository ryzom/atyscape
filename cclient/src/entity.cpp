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

#include "entity.h"

CEntity::CEntity(string name)
{
	Name = name;
	_TryMove = false;
	_Pos = CVector(0, 0, 0);
	_OldPos = _Pos;
	_Speed = CVector(1.0f, 1.0f, 1.0f);
	_UseCollisions = true;
	SnapToGround = true;
}

void CEntity::addToWorld(uint8 worldImage, CWorld *world)
{
	_WorldImage = worldImage;
	_World = world;
	_MovePrim = world->_MoveContainer->addCollisionablePrimitive(_WorldImage, 1);
	_MovePrim->setPrimitiveType(UMovePrimitive::_2DOrientedCylinder);
	_MovePrim->setReactionType(UMovePrimitive::Slide);
	_MovePrim->setTriggerType(UMovePrimitive::NotATrigger);
	_MovePrim->setCollisionMask(/*OtherCollisionBit+AtysScapeCollisionBit+*/StaticCollisionBit);
	_MovePrim->setOcclusionMask(SelfCollisionBit);
	_MovePrim->setObstacle(true);
	_MovePrim->setRadius(0.2f);
	_MovePrim->setHeight(0.8f);
	_MovePrim->insertInWorldImage(_WorldImage);

	_VisualCol = world->_VisualCollisionManager->createEntity();
	_VisualCol->setCeilMode(true);
}

void CEntity::setPos(CVector pos)
{
//	nlinfo("Set Pos (%f, %f ,%f), OLD = (%f, %f ,%f)", pos.x, pos.y, pos.z, _OldPos.x, _OldPos.y, _OldPos.z);
//	_OldPos = _Pos;
	_Pos = pos;
}

void CEntity::calculateSpeed(float deltaTime)
{
	_Speed = (_OldPos-_Pos)/_DeltaTime;
}

void CEntity::setView(CMatrix mat)
{
	_View = mat;
}

void CEntity::setGlobalPos(CVector pos)
{
	_MovePrim->setGlobalPosition(CVectorD(pos.x, pos.y, pos.z), 0);
	setPos(pos);
}

CVector CEntity::getPos()
{
	return _Pos;
}

CMatrix CEntity::getView()
{
	return _View;
}

CVector CEntity::snapToGround()
{
	CVector normal;
	_VisualCol->snapToGround(_Pos, normal);
	return normal;
}

void CEntity::tryMove(float dt)
{
	if (dt < 0.03f)
		dt = 0.03f;
	CVector imediateSpeed = (_Pos - _OldPos)/dt;//CVector((_Pos.x - _OldPos.x)/dt, (_Pos.y - _OldPos.y)/dt, (_Pos.y - _OldPos.y)/dt);
	

	// New speed
	if ( (_MovePrim->getSpeed(_WorldImage).norm()>0.f) || imediateSpeed.norm()>0.f )
	{
		// Brake
		//CVector newSpeed=_Speed;
		//newSpeed.normalize();
		//newSpeed*=BRAKE_FORCE*deltaTime;
		//newSpeed+=_Speed;

		// Stop ?
		//if (_Speed*newSpeed<=0)
		if (imediateSpeed.norm() > 50.0f)
			imediateSpeed=CVector(0,0,0);

		// Set speed
		//_Speed = newSpeed;

		// Try this move
		_MovePrim->move(imediateSpeed * _SpeedFactor, _WorldImage);
		_TryMove=true;
	}
	else
		_TryMove=false;

	//_OldPos = _Pos;

}

void CEntity::doMove()
{
	// New speed
	//setSpeed(_MovePrim->getSpeed(_WorldImage));

	// New position
	UGlobalPosition	gPos;
	_MovePrim->getGlobalPosition(gPos, _WorldImage);
	//_MovePrim->getFinalPosition(gPos);
	if (_UseCollisions)
	{
		_Pos = _World->_GlobalRetriever->getGlobalPosition(gPos);
		gPos.LocalPosition.Estimation.z = 1.0f;
		//snappedWalkerPos.z = World->_GlobalRetriever->getMeanHeight(gPos);

		if (SnapToGround)
		{
			_Pos.z = _World->_GlobalRetriever->getMeanHeight(gPos);

			if (!_World->_GlobalRetriever->isInterior(gPos))
				snapToGround();
		}
	}
	else
	{
		_MovePrim->setGlobalPosition(_Pos, _WorldImage);
	}

}


void CEntity::setHeadingAttitude(float heading, float attitude) {
	/* Reset angles to 0 */
	_View.identity();
	turn(heading, attitude);
}

void CEntity::move(float speed, bool backwards) {
	_OldPos = _Pos;

	//nlinfo("speed : %f", speed);
	_Speed = _View.getJ();// * speed, _View.getJ().y * speed, _View.getJ().y * speed);
	_SpeedFactor = speed;
	if (backwards)
		_Pos -= _Speed;
	else
		_Pos += _Speed;

	//CVector imediateSpeed = (_Pos - _OldPos) ;
}

void CEntity::strafe(float speed, bool right) {
	_Speed = _View.getJ() * speed;

	if (right) {
		_Pos.x += _Speed.y;
		_Pos.y -= _Speed.x;
	} else {
		_Pos.x -= _Speed.y;
		_Pos.y += _Speed.x;
	}
}

void CEntity::slew(float x, float y, float z) {
	_Pos += CVector(x, y, z);
}

void CEntity::turn(float angleZ, float angleX) {
	// Rotate Axis
	CVector axis = _View.getPos();

	// First in the hotSpot
	CMatrix comeFromHotSpot= _View;
	comeFromHotSpot.setPos(axis);
		
	// Axis rotation matrixes
	CMatrix turnZ; turnZ.identity(); turnZ.rotateZ(angleZ);
	CMatrix turnX; turnX.identity(); turnX.rotateX(angleX);

	// Then come back from hotspot
	CMatrix goToHotSpot=comeFromHotSpot;
	goToHotSpot.invert();
	
	// Make the matrix
	CMatrix negPivot, Pivot;
	negPivot.identity();
	negPivot.setPos (-axis);
	Pivot.identity();
	Pivot.setPos (axis);
	
	// Perform base rotation
	//view=Pivot*turnZ*negPivot*comeFromHotSpot*turnX*goToHotSpot*view;
	Pivot*=turnZ;
	Pivot*=negPivot;
	Pivot*=comeFromHotSpot;
	Pivot*=turnX;
	Pivot*=goToHotSpot;
	Pivot*=_View;
	_View = Pivot;

	// Normalize, too much transformation could give an ugly matrix..
	_View.normalize(CMatrix::XYZ);
}

void CEntity::turn(float angleX, float angleY, float angleZ)
{
	_View.rotateX(angleX);
	_View.rotateY(angleY);
	_View.rotateZ(angleZ);
}

void CEntity::saveState()
{
	_SavedPos = _Pos;
	_SavedSpeed = _Speed;
	_SavedView = _View; 
}

void CEntity::restoreState()
{
	_Pos = _SavedPos;
	_Speed = _SavedSpeed;
	_View = _SavedView; 
}

void CEntity::setQuat(CQuat quat)
{
	_Quat = quat;
}

CQuat CEntity::getQuat()
{
	return _Quat;
}

void CEntity::show()
{}

void CEntity::hide()
{}

void CEntity::update()
{}

void CEntity::render()
{}

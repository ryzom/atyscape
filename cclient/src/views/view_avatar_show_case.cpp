/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View of Avatar in ShowCase Mode
	____________________________________________________________________

	This file is part of Ryturn Home Crafted MMORPG.

    Ryturn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ryturn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ryturn.  If not, see <http://www.gnu.org/licenses/>.
	____________________________________________________________________

 */

#include "view_avatar_show_case.h"

#include "../lg_ui.h"

CViewAvatarShowCase::CViewAvatarShowCase()
{
}

void CViewAvatarShowCase::init()
{
	_ModAvatar = &CModAvatar::getInstance();
	_ModTime = &CModTime::getInstance();
	_Avatar = _ModAvatar->getAnimated();
	_IsMoving = false;

	LG::CUI::getInstance().Text->addTextZone("ViewAvatarShowCaseInfos", 0.05f, 0.8f, CRGBA(255, 0, 255), 16);

}

void CViewAvatarShowCase::render()
{
	_Avatar->setQuat(_Avatar->getQuat()*CQuat(CVector(CVector::K), 3*_SpeedMove*(float)Pi));
	_Avatar->animate((float)_ModTime->currentTime());
	// TODO !! No needed in future
	_Avatar->applyQuat();
}

void CViewAvatarShowCase::handleMouseEvent(const CEvent &event)
{
	CEventMouse* mouseEvent=(CEventMouse*)&event;

	if (event == EventMouseMoveId)
	{
		if (_IsMoving)
		{
			// Moving Avatar
			_SpeedMove = mouseEvent->X - _LastMouseX; // -1 < _SpeedMove < 1
			_LastMouseX = mouseEvent->X;
			_LastMouseY = mouseEvent->Y;
		}
		LG::CUI::getInstance().Text->setText("ViewAvatarShowCaseInfos", "SpeedMove = %f", _SpeedMove);
	}
	else if (event == EventMouseUpId)
	{
		_IsMoving = false;
		//_SpeedMove = 0;
		LG::CUI::getInstance().Text->setText("ViewAvatarShowCaseInfos", "");
	}
	else if (event == EventMouseDownId)
	{
		_IsMoving = true;
		_LastMouseX = mouseEvent->X;
		_LastMouseY = mouseEvent->Y;
	}
	// TODO !!!
	//else if (event == EventMouseWheelId)
	//{
	//	CEventMouseWheel* wheelEvent=(CEventMouseWheel*)&event;
	//	if (wheelEvent->Direction)
	//	{
	//		if (_CamWalkerDistance > 1.0f)
	//			_CamWalkerDistance -= 0.5f;
	//	}
	//	else
	//	{
	//		if (_CamWalkerDistance < 20.0f)
	//			_CamWalkerDistance += 0.5f;
	//	}
	//}

	if (!_IsMoving)
	{
		if (_SpeedMove > 0.00001f)
		{
			_SpeedMove -= 0.0001f;
		}
		else
		{
			_SpeedMove = 0;
		}
	}
}

void CViewAvatarShowCase::handleKeyboardEvent(const CEventListenerAsync &event)
{
}
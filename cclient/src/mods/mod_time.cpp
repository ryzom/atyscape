/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Module for Time Managment
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

#include "mod_time.h"
#include <nel/misc/time_nl.h>

CModTime::CModTime()
{
}

void CModTime::init()
{
	_FirstTime = 1;
	_OldTime = 1;
	_Time = 1;
	_DeltaTime = 0;
	_RealDeltaTime = 0;
	_FirstUpdate = true;
	_TimeSpeed = 1.0;
}

void CModTime::speedTime(double dt)
{
	_TimeSpeed = dt;
}

double CModTime::getSpeedTime() const
{
	return _TimeSpeed;
}


uint CModTime::update()
{
	double currentTime = double(CTime::getLocalTime())/1000.0;

	if(_FirstUpdate)
		_FirstTime = currentTime - 1; //-1 for replay 

	//Time = newTime - FirstTime;

	if(_FirstUpdate)
	{
		_DeltaTime = 0;
		_RealDeltaTime = 0;
		_Time = 0;
		_FirstUpdate = false;
	}
	else
	{
		_RealDeltaTime = (currentTime - _OldTime);
		_DeltaTime = _RealDeltaTime * _TimeSpeed;
		_Time += _DeltaTime;
	}

	_OldTime = currentTime;

	_DeltaTimeSmooth.addValue(_RealDeltaTime);

	_CurrentTime = currentTime;//(TTime)CTime::getLocalTime();

	return 0;
}
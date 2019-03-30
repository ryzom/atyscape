/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Module for Time Managment (Code from MtpTarget/time_task
									- Vianney Lecroart - gpl@vialek.com )
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

#ifndef _MOD_TIME_H_
#define _MOD_TIME_H_

#include "../mod_base.h"
#include <nel/misc/singleton.h>
#include <nel/misc/value_smoother.h>

using namespace std;
using namespace NLMISC;

class CModTime : public CSingleton<CModTime>, CModBase
{

public:
	CModTime();

	// Current time in seconds
	double		time() const { return _Time; }

	// Real Current time in seconds
	double		currentTime() const { return _CurrentTime; }

	// Delta time between last and this frame in seconds
	double		deltaTime () const { return _DeltaTime; }
	
	// Delta time between last and this frame in seconds without the slowmotion
	double		realDeltaTime () const { return _RealDeltaTime; }

	// Number of frame render in one second (average)
	double		fps() const { return _DeltaTimeSmooth.getSmoothValue() ? 1.0 / _DeltaTimeSmooth.getSmoothValue() : 0.0; }

	// Number of seconds to render a frame (average)
	double		spf() const { return _DeltaTimeSmooth.getSmoothValue(); }

	void		speedTime(double st);	// 0.0 is stop 1.0 is normal 2.0 is two time faster
	double		getSpeedTime() const;

	void init();
	uint update();

private:
	CValueSmootherTemplate<double> _DeltaTimeSmooth;

	double	_CurrentTime, _Time, _OldTime;
	double	_DeltaTime, _RealDeltaTime;
	double	_FirstTime;
	bool	_FirstUpdate;
	double	_TimeSpeed;
	//TTime	_CurrentTime;



};

#endif
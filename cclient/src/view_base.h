/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View Base for all views
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


#ifndef _VIEW_BASE_H_
#define _VIEW_BASE_H_

#include <nel/3d/event_mouse_listener.h>
#include <nel/misc/events.h>

using namespace NL3D;
using namespace NLMISC;

class CViewBase
{

public:
	CViewBase();

	virtual void init();
	virtual void handleMouseEvent(const CEvent &event);
	virtual void handleKeyboardEvent(const CEventListenerAsync &event);
	virtual void render() = 0;
};


#endif
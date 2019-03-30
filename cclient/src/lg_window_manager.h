/** 
 * AtysScape - Window Manager
 * 2008-05-13 - Ulukyn
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


#ifndef _LG_WINDOW_MANAGER_H_
#define _LG_WINDOW_MANAGER_H_

#include <nel/misc/singleton.h>

#include "lg_window.h"

using namespace std;
using namespace NLMISC;

namespace LG
{

struct WindowProperties 
{
	CWindow *Window;
	string Type;
};



class CWindowManager : public CSingleton<CWindowManager>
{

public:
	CWindowManager();
	CWindow* getWindow(string name);
	CWindow* getRoot();
	string getType(string name);
	void setDriver(UDriver* driver);
	WindowProperties getWindowProps(string name);
	bool addWindow(CWindow* window);
	bool removeWindow(CWindow* window);
	
private:
	map<string, WindowProperties> _Windows;
	UDriver* _Driver;

};

}

#endif

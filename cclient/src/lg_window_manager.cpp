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
#include "lg_window_manager.h"

namespace LG
{

CWindowManager::CWindowManager()
{
}

CWindow* CWindowManager::getWindow(string name)
{
	if (_Windows.find(name) == _Windows.end())
	{
		//nlerror("Widget not found : %s", name.c_str());
		return NULL;
	}
	else
	{
		return _Windows[name].Window;
	}
}

CWindow* CWindowManager::getRoot()
{
	if (_Windows.find("[Root]") == _Windows.end())
	{
		//nlerror("Widget not found : %s", name.c_str());
		return NULL;
	}
	else
	{
		return _Windows["[Root]"].Window;
	}
}

void CWindowManager::setDriver(UDriver* driver)
{
	_Driver = driver;
}

string CWindowManager::getType(string name)
{
	if (_Windows.find(name) == _Windows.end())
	{
		return "not found";
	}
	else
	{
		return _Windows[name].Type;
	}
}

WindowProperties CWindowManager::getWindowProps(string name)
{
	if (_Windows.find(name) == _Windows.end())
	{
		WindowProperties wp;
		wp.Type = "not found";
		wp.Window = NULL;

		return wp;
	}
	else
	{
		return _Windows[name];
	}
}

bool CWindowManager::addWindow(CWindow* window)
{
	window->setDriver(_Driver);

	map<string, WindowProperties>::iterator ite;
	ite = _Windows.find(window->Name);

	if ((ite == _Windows.end()) || (_Windows.empty()))
	{
		WindowProperties wp;
		wp.Type = window->Type;
		wp.Window = window;

		nlinfo("Add Widget %s", window->Name.c_str());

		_Windows.insert(make_pair(window->Name, wp));
		return true;
	}
	else
	{
		nlinfo("Widget %s allready on list", window->Name.c_str());
		for(ite = _Windows.begin(); ite != _Windows.end(); ++ite)
		{
			nlinfo("Item : %s = %s", ite->first.c_str(), ite->second.Window->Name.c_str());
		}
		//nlerror("Widget allready on list");
		return false;
	}
}

bool CWindowManager::removeWindow(CWindow* window)
{
	map<string, WindowProperties>::iterator ite;
	ite = _Windows.find(window->Name);

	if ((ite == _Windows.end()) || (_Windows.empty()))
	{
		return false;
	}
	else
	{
		_Windows.erase(ite);
		nlinfo("Widget %s removed", window->Name.c_str());
		return false;
	}
}


}

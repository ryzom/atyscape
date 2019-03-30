/** 
 * AtysScape - Window
 * 2008-03-16 - Ulukyn
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

#ifndef _LG_WINDOW_H_
#define _LG_WINDOW_H_

#include <nel/3d/u_driver.h>

#include "CEGUI.h"
#include "lg_callback.h"

using namespace std;
using namespace NL3D;

struct TSize
{
	float Height;
	float Width;
};

struct TBorder
{
	float Top;
	float Left;
	float Right;
	float Bottom;
};

struct TExpand
{
	float Vertical;
	float Horizontal;
};

namespace LG
{

typedef bool (Callback)(const CEGUI::EventArgs&) ;
typedef void (TCbFunction)(const string &winName);

class CWindow
{

public:
	CWindow(string name);

	void setDriver(UDriver* driver);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void destroy();
	virtual void update();
	virtual void render();

	void setPos(float x, float y);
	void setSize(float w, float h);
	void setBorder(float top, float right, float bottom, float left);
	void setExpand(float h, float v);

	void addChild(CWindow* win);
	
	void printInfos();

	template<typename T>
	void setCallback(string EventName, bool (T::*function)(const CEGUI::EventArgs&), T* obj)
	{
		Widget->subscribeEvent(_Events[EventName], CEGUI::Event::Subscriber(function, obj));
	}

	void setCallback(const string &name, CCallback* cb);

	CWindow*	Parent;

	float		Pos[2];
	TSize		Size;
	TBorder		Border;
	TExpand		Expand;

	string		Name;
	string		Type;
	string		FullName;
	uint		Id;
	bool		Visible;
	CEGUI::Window* Widget;
	CEGUI::Window* Container;

protected:
	friend class CFrame;
	friend class CVBox;
	friend class CHBox;

	virtual void updateDim();

	float		_Offset[4];
	list<LG::CWindow *>	_Childs;
	CEGUI::WindowManager* _CEGuiWm;
	UDriver* _Driver;
	map<string, /*static const*/ CEGUI::String> _Events;
	uint		_ChildsCount;

	map <string, bool> _ActiveCallbacks;
	map<string, CCallback*> _Callbacks;

};

}

#endif

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

#include "common.h"
#include "lg_window.h"

namespace LG
{

CWindow::CWindow(string name)
{
	Name = name;
	Type = "Window";
	
	Pos[0] = 0;
	Pos[1] = 0;

	Size.Height = 0.0f;
	Size.Width = 0.0f;
	Expand.Horizontal = 1.0f;
	Expand.Vertical = 1.0f;
	Border.Top = 0;
	Border.Bottom = 0;
	Border.Left = 0;
	Border.Right = 0;
	_Offset[0] = 0;
	_Offset[1] = 0;
	_Offset[2] = 0;
	_Offset[3] = 0;

	_Childs.clear();
	_ChildsCount = 0;
	_CEGuiWm = CEGUI::WindowManager::getSingletonPtr();
	Visible = true;
	CWindowManager::getInstance().addWindow(this);
}

void CWindow::setDriver(UDriver* driver)
{
	_Driver = driver;
}

void CWindow::setPos(float x, float y)
{
	Pos[0] = x;
	Pos[1] = y;
	updateDim();
}


void CWindow::setSize(float w, float h)
{
	Size.Height = h;
	Size.Width = w;
	updateDim();
}

void CWindow::setExpand(float h, float v)
{
	Expand.Horizontal = h;
	Expand.Vertical = v;
	updateDim();
}

void CWindow::setBorder(float top, float right, float bottom, float left)
{
	Border.Bottom = bottom;
	Border.Left = left;
	Border.Right = right;
	Border.Top = top;
	updateDim();
}

void CWindow::updateDim()
{
	nlinfo("SetArea %s: ((%f, %f)),((%f, %f)) - ((%f, %f)),((%f, %f))", Name.c_str(),
			Pos[0], Border.Left + _Offset[3],
			Pos[1], Border.Top + _Offset[0],
			Pos[0]+Expand.Horizontal, Size.Width - Border.Left - Border.Right + _Offset[1],
			Pos[1]+Expand.Vertical, Size.Height - Border.Bottom - Border.Top + _Offset[2]);

	Widget->setArea(
		CEGUI::URect(
			CEGUI::UDim(Pos[0], Border.Left + _Offset[3]),
			CEGUI::UDim(Pos[1], Border.Top + _Offset[0]),
			CEGUI::UDim(Pos[0]+Expand.Horizontal, Size.Width - Border.Left - Border.Right + _Offset[1]),
			CEGUI::UDim(Pos[1]+Expand.Vertical, Size.Height - Border.Bottom - Border.Top + _Offset[2])
		)
	);


}


void CWindow::addChild(CWindow* win)
{
	win->FullName = FullName+"."+win->Name;
	nlinfo("%s have new child %s", Name.c_str(), win->Name.c_str());
	_Childs.push_back(win);
	_ChildsCount++;
}

void CWindow::show()
{
	Widget->show();
}

void CWindow::hide()
{
	Widget->hide();
}

void CWindow::update()
{}

void CWindow::render()
{
}

void CWindow::printInfos()
{
	nlinfo("%s (%s) : Pos = %f, %f Size =%fx%f Border = %f, %f, %f, %f Offset = %f, %f, %f, %f, Expand %f, %f",
		Type.c_str(),
		Name.c_str(),
		Pos[0],
		Pos[1],
		Size.Width,
		Size.Height,
		Border.Top,
		Border.Right,
		Border.Bottom,
		Border.Left,
		_Offset[0],
		_Offset[1],
		_Offset[2],
		_Offset[3],
		Expand.Horizontal,
		Expand.Vertical);
}
void CWindow::create(CWindow* parent)
{
	parent->addChild(this);
}
void CWindow::setCallback(const string &name, CCallback* cb)
{
	_Callbacks.insert(make_pair(name, cb));
	_ActiveCallbacks[name] = true;
}


void CWindow::destroy()
{
	_CEGuiWm->destroyWindow(Widget);
	CWindowManager::getInstance().removeWindow(this);
}
};

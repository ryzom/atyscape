/** 
 * AtysScape - ListBox
 * 2008-05-07 - Ulukyn
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
#include "lg_popup_menu.h"

namespace LG
{

CPopupMenu::CPopupMenu(string name) : CWindow(name)
{
	Name = name;
	_IsPopupMenuClicked = false;
	_HaveCb = false;
}

void CPopupMenu::addItem(const string &parent, const string &name, const string &text)
{
	CEGUI::Window* menuItem = _CEGuiWm->createWindow(string(LOOK)+"/MenuItem", name);
    menuItem->setText(text);
	menuItem->subscribeEvent("Clicked", CEGUI::Event::Subscriber(&CPopupMenu::_CB_OnPopupMenuClick, this));
   _CEGuiWm->getWindow(parent)->addChildWindow(menuItem);
   CWindow* win = new CWindow(name);
   win->Widget = menuItem;
   win->Container = win->Widget;
   win->create(CWindowManager::getInstance().getWindow(parent));
}

void CPopupMenu::addSubMenu(const string &parent, const string &name, const string &text)
{
	CEGUI::Window* menuItem = _CEGuiWm->createWindow(string(LOOK)+"/MenuItem", name);
    menuItem->setText(text);	
	_CEGuiWm->getWindow(parent);
	_CEGuiWm->getWindow(parent)->addChildWindow(menuItem);
   CWindow* win = new CWindow(name);
   win->Widget = menuItem;
   win->Container = win->Widget;
   win->create(CWindowManager::getInstance().getWindow(parent));
}

void CPopupMenu::setCallback(CCallback* cb)
{
	_Cb = cb;
	_HaveCb = true;
}

void CPopupMenu::create(CWindow* parent)
{

	Widget = _CEGuiWm->createWindow(string(LOOK)+"/PopupMenu", Name);
    parent->Container->addChildWindow(Widget);
	parent->addChild(this);
}
string  CPopupMenu::getSelected()
{
	return _SelectedItem;
}

void CPopupMenu::show()
{}

void CPopupMenu::hide()
{}

void CPopupMenu::update()
{
}

void CPopupMenu::render()
{
	static_cast<CEGUI::PopupMenu*>(Widget)->openPopupMenu(true);
}

bool CPopupMenu::_CB_OnPopupMenuClick(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs& we = static_cast<const CEGUI::WindowEventArgs&>(e);

	_SelectedItem = string(we.window->getName().c_str());

	if (_HaveCb)
	{
		(*_Cb)(Name);
	}

	_IsPopupMenuClicked = true;

	return true;
}

}

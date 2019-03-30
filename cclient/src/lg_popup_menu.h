/** 
 * AtysScape - Popup Menu
 * 2008-05-15 - Ulukyn
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

#ifndef _LG_POPUP_MENU_H_
#define _LG_POPUP_MENU_H_

#include "lg_window.h"
#include "lg_callback.h"

namespace LG
{

class CPopupMenu : public CWindow
{

public:
	CPopupMenu(string name);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	void addItem(const string &parent, const string &name, const string &text);
	void addSubMenu(const string &parent, const string &name, const string &text);
	void setCallback(CCallback* cb);
	string  getSelected();
	bool _CB_OnPopupMenuClick(const CEGUI::EventArgs& e);

private:
	bool _IsPopupMenuClicked;
	list<CEGUI::Window> _Items;
	bool _HaveCb;
	CCallback* _Cb;
	string _SelectedItem;
};

}

#endif

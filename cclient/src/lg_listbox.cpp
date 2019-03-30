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
#include "lg_listbox.h"

namespace LG
{

CListBox::CListBox(const string &name) : CWindow(name)
{
	Name = name;
	_Events.insert(make_pair("Selected", CEGUI::Combobox::EventListSelectionAccepted));
}

void CListBox::setText(const string &text)
{
	static_cast<CEGUI::Combobox*>(Widget)->getEditbox()->setText(text);
}

CVector CListBox::addItem(const string &id, const string &text)
{
	CEGUI::ListboxTextItem* lbi = new CEGUI::ListboxTextItem(text);
	CEGUI::Combobox* wList = (CEGUI::Combobox*)Widget;
	wList->setReadOnly(true);
	wList->addItem(lbi);
	_Items.push_back(lbi);
	_ItemsId.push_back(id);
	return CVector(lbi->getPixelSize().d_width, lbi->getPixelSize().d_height, 0);
}

void CListBox::getItemsList(vector<string> &items)
{
	items = _ItemsId;
}

void CListBox::create(CWindow* parent)
{
	Type = "Listbox";
	nlinfo(parent->Name.c_str());
	Widget = _CEGuiWm->createWindow(string(LOOK)+"/Combobox", Name);
	parent->Container->addChildWindow(Widget);
	parent->addChild(this);
	
	Size.Height = 27.0f;
	Size.Width = 60.0f;
	Expand.Horizontal = 1.0f;
	Expand.Vertical = 0.0f;
	Border.Top = 1.0f;
	Border.Bottom = 1.0f;
	Border.Left = 3.0f;
	Border.Right = 3.0f;
}

void CListBox::show()
{}

void CListBox::hide()
{}

void CListBox::update()
{
}

void CListBox::render()
{
	Widget->setArea(
		CEGUI::URect(
			CEGUI::UDim(Pos[0], Border.Left + _Offset[3]),
			CEGUI::UDim(Pos[1], Border.Top + _Offset[0]),
			CEGUI::UDim(Pos[0]+Expand.Horizontal, Size.Width - Border.Left - Border.Right + _Offset[1]),
			CEGUI::UDim(1.0f, 0)
		)
	);
}


}

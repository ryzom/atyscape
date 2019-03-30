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
#include "lg_entry.h"

namespace LG
{


CEntry::CEntry(string name) : CWindow(name)
{
	Name = name;
}

const string &CEntry::getText()
{
	_Text = string(static_cast<CEGUI::Editbox *>(Widget)->getValidationString().c_str());
	return _Text;
}

void CEntry::setText(const string &text)
{
	if (text != "")
		static_cast<CEGUI::Editbox *>(Widget)->setText(text);
}


void CEntry::create(CWindow* parent)
{
	Type = "Editbox";
	nlinfo(parent->Name.c_str());
	Widget = _CEGuiWm->createWindow(string(LOOK)+"/Editbox", Name);
	parent->Container->addChildWindow(Widget);
	parent->addChild(this);

	Size.Height = 26.0f;
	Size.Width = 60.0f;
	Expand.Horizontal = 1.0f;
	Expand.Vertical = 0.0f;
	Border.Top = 1.0f;
	Border.Bottom = 1.0f;
	Border.Left = 3.0f;
	Border.Right = 3.0f;
}

void CEntry::show()
{}

void CEntry::hide()
{}

void CEntry::update()
{
}

void CEntry::render()
{
}


}

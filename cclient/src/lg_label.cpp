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
#include "lg_label.h"

namespace LG
{


CLabel::CLabel(string name) : CWindow(name)
{
	Name = name;
}

void CLabel::setText(const string &text)
{
	Widget->setText(text);
	_Text = text;
}



void CLabel::create(CWindow* parent)
{
	Type = "StaticText";
	nlinfo(parent->Name.c_str());
	Widget = _CEGuiWm->createWindow(string(LOOK)+"/StaticText", Name);
	parent->Container->addChildWindow(Widget);
	parent->addChild(this);

	Size.Height = 24.0f;
	Size.Width = 60.0f;
	Expand.Horizontal = 1.0f;
	Expand.Vertical = 0.0f;
}

void CLabel::show()
{}

void CLabel::hide()
{}

void CLabel::update()
{
}

void CLabel::render()
{
}


}

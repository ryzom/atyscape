/** 
 * AtysScape - Button
 * 2008-03-18 - Ulukyn
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
#include "lg_button.h"
#include "lg_window.h"

namespace LG {

CButton::CButton(string name) : CWindow(name)
{
}

void CButton::setText(const string &text)
{
	static_cast<CEGUI::PushButton *>(Widget)->setText(text);
}

void CButton::create(CWindow* parent)
{
	Type = "Button";
	nlinfo(parent->Name.c_str());
	Widget = _CEGuiWm->createWindow(string(LOOK)+"/Button", Name);
	parent->Container->addChildWindow(Widget);
	parent->addChild(this);

	Size.Height = 24.0f;
	Size.Width = 60.0f;
	Expand.Horizontal = 1.0f;
	Expand.Vertical = 0.0f;
	Border.Top = 1.0f;
	Border.Bottom = 1.0f;
	Border.Left = 3.0f;
	Border.Right = 3.0f;
}

void CButton::show()
{}

void CButton::hide()
{}
	
void CButton::update()
{
}

void CButton::render()
{

}

}

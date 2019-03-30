/** 
 * AtysScape - Frame Window
 * 2008-05-01 - Ulukyn
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
#include "lg_frame.h"

namespace LG
{


CFrame::CFrame(string name) : CWindow(name)
{
	Name = name;
	FullName = name;
	nlinfo("created");
}

void CFrame::create(CWindow* parent)
{
	Widget = _CEGuiWm->createWindow(string(LOOK)+"/FrameWindow", Name);
    parent->Container->addChildWindow(Widget);
	parent->addChild(this);

	Container = Widget;
}

void CFrame::setTitle(const string &title)
{
	Widget->setText(title);
}

void CFrame::show()
{}

void CFrame::hide()
{}

void CFrame::update()
{}

void CFrame::render()
{
	list<CWindow*> winList;
	winList = _Childs;
	
	float height = 0;
	float fixedSize = 24; // 24 = Size of Frame Title

	while (!winList.empty())
	{
		CWindow* win = winList.front();

		if (win->Expand.Vertical > 0)
		{
			height ++;
			//= win->Expand.Vertical;
			win->Size.Height = 0;
		}
		else
		{
			fixedSize += win->Size.Height;
		}

		if (win->Expand.Horizontal > 0)
		{
			win->Size.Width = 0;
		}

		winList.pop_front();
	}

	if (height < 1)
		height = 1;

	nlinfo("fixedSize : %f", fixedSize);
	winList = _Childs;

	float posY = 0;
	float offY = 24; 

	while (!winList.empty())
	{
		CWindow* win = winList.front();

		win->setPos(win->Pos[0], win->Pos[1] + posY);

		if (win->Expand.Vertical > 0)
		{
			win->setExpand(win->Expand.Horizontal, win->Expand.Vertical / height);
			win->_Offset[0] = offY + 1;
			win->_Offset[1] = 0;
			nlinfo("offset 2 = %f, %f, %f, %f", offY,  win->Expand.Vertical, fixedSize, height);
			win->_Offset[2] = offY - win->Expand.Vertical*fixedSize;
			win->_Offset[3] = 0;
			win->updateDim();
			posY += win->Expand.Vertical;
			offY -= win->Expand.Vertical*fixedSize;
		}
		else
		{
			win->_Offset[0] = offY + 1;
			win->_Offset[1] = 0;
			win->_Offset[2] = offY - 1;
			win->_Offset[3] = 0;
			win->updateDim();
			offY += win->Size.Height;
		}
		
		win->printInfos();

		nlinfo("OffY = %f", offY);

		win->render();
		winList.pop_front();
	}
}


}

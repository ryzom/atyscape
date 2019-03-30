/** 
 * AtysScape - Vertical Box
 * 2008-04-30 - Ulukyn
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
#include "lg_vbox.h"

namespace LG
{


CVBox::CVBox(string name) : CWindow(name)
{
}

void CVBox::show()
{}

void CVBox::hide()
{}

void CVBox::update()
{}

void CVBox::render()
{
	list<CWindow*> winList;
	winList = _Childs;

	float height = 0;
	float fixedSize = 0;

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

	winList = _Childs;
	float posY = 0;
	float offY = 0;
	
	while (!winList.empty())
	{
		CWindow* win = winList.front();

		win->setPos(Pos[0] + win->Pos[0], Pos[1] + win->Pos[1] + posY);

		win->printInfos();
		if (win->Expand.Vertical > 0)
		{
			win->_Offset[0] = _Offset[0] + offY + 1;
			win->_Offset[1] = _Offset[1];
			nlinfo("vbox offset 2 = %f, %f, %f, %f", offY, Expand.Vertical , fixedSize, height);
			win->_Offset[2] = _Offset[0] + offY - (win->Expand.Vertical*fixedSize + _Offset[0] - _Offset[2]) / height;
			
			if (win->Expand.Horizontal)
				win->_Offset[3] = _Offset[3];
			else
				win->_Offset[3] = _Offset[1];

			offY -= (_Offset[0] - _Offset[2] + win->Expand.Vertical*fixedSize) / height;
			win->setExpand(Expand.Horizontal*win->Expand.Horizontal, (Expand.Vertical*win->Expand.Vertical) / height);
			posY += win->Expand.Vertical;
		}
		else
		{
			win->Expand.Horizontal *= Expand.Horizontal;

			win->_Offset[0] = _Offset[0] + offY + 1;
			win->_Offset[1] = _Offset[1] + 0;
			win->_Offset[2] = _Offset[0] + offY - 1;
			win->_Offset[3] = _Offset[1] + 0;
			win->updateDim();
			offY += win->Size.Height;
	
		}
		
		nlinfo("OffY = %f", offY);

		win->render();
		winList.pop_front();
	}
}

void CVBox::updateDim()
{

}

void CVBox::create(CWindow* parent)
{
	Widget = NULL;
	Container = parent->Container;
	parent->addChild(this);
}


}

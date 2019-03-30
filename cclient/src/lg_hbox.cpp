/** 
 * AtysScape - Horizontal Box
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
#include "lg_hbox.h"

namespace LG
{


CHBox::CHBox(string name) : CWindow(name)
{
}

void CHBox::show()
{}

void CHBox::hide()
{}

void CHBox::update()
{}

void CHBox::render()
{
	//ExpandX = 1;

	//list<CWindow*> winList;
	//winList = _Childs;
	//float width = 0;
	//float offset = 0;
	//while (!winList.empty())
	//{
	//	CWindow* win = winList.front();

	//	if (win->ExpandX != 0)
	//	{
	//		width += (float)win->ExpandX;
	//	}
	//	else
	//	{
	//		offset += win->Off[1];
	//	}

	//	winList.pop_front();
	//}

	//winList = _Childs;
	//float posX = 0;
	//float offX = 0;
	//nlinfo("HBox %s", Name.c_str());
	//
	//while (!winList.empty())
	//{
	//	CWindow* win = winList.front();

	//	win->setPos(posX, win->Pos[1]);

	//	if (win->ExpandX > 0)
	//	{
	//		posX += Size[0]*win->ExpandX / width;
	//		win->setSize(Size[0]*win->ExpandX / width, Size[1]*win->Size[1]);

	//		win->setOffset(Off[0]+win->Off[0], Off[1]+win->Off[1]+offX, Off[2]+win->Off[2], -Off[1]-win->Off[1]+Off[3]+win->Off[3]-((win->ExpandX*offset) / width)+offX);
	//		offX -= (win->ExpandX*offset) / width;
	//	}
	//	else
	//	{
	//		//win->setSize(0, win->Size[1]);

	//		float offXtemp = offX + win->Off[2];
	//		win->setOffset(Off[0]+win->Off[0], Off[1]+win->Off[1]+offX, Off[2]+win->Off[2], win->Off[1]+Off[3]+offX+win->Off[3]);
	//		offX = offXtemp+2;
	//	}
	//	win->render();
	//	winList.pop_front();

	//}
	list<CWindow*> winList;
	winList = _Childs;

	float width = 0;
	float fixedSize = 0;

	while (!winList.empty())
	{
		CWindow* win = winList.front();

		if (win->Expand.Horizontal > 0)
		{
			width ++;
			win->Size.Width = 0;
		}
		else
		{
			fixedSize += win->Size.Width;
		}

		if (win->Expand.Vertical > 0)
		{
			win->Size.Height = 0;
		}

		winList.pop_front();
	}


	winList = _Childs;
	float posX = 0;
	float offX = 0;
	
	while (!winList.empty())
	{
		CWindow* win = winList.front();

		win->setPos(Pos[0] + win->Pos[0] + posX, Pos[1] + win->Pos[1]);

		win->printInfos();
		if (win->Expand.Horizontal > 0)
		{
			win->_Offset[0] = _Offset[0];
			win->_Offset[1] = _Offset[1] + offX + 1;
			nlinfo("hbox offset 2 = %f, %f, %f, %f", offX, Expand.Horizontal , fixedSize, width);
			if (win->Expand.Vertical)
				win->_Offset[2] = _Offset[2];
			else
				win->_Offset[2] = _Offset[0];
			win->_Offset[3] = _Offset[1] + offX - (win->Expand.Horizontal*fixedSize + _Offset[1] - _Offset[3]) / width;
			offX -= (_Offset[1] - _Offset[3] + win->Expand.Horizontal*fixedSize) / width;
			win->setExpand((Expand.Horizontal*win->Expand.Horizontal) / width, Expand.Vertical*win->Expand.Vertical);
			posX += win->Expand.Horizontal;
		}
		else
		{
			win->Expand.Vertical *= Expand.Vertical;

			win->_Offset[0] = _Offset[0];
			win->_Offset[1] = _Offset[1] + offX + 1;
			win->_Offset[2] = _Offset[0];
			win->_Offset[3] = _Offset[1] + offX - 1;
			win->updateDim();
			offX += win->Size.Width;
	
		}
		
		nlinfo("OffX = %f", offX);

		win->render();
		winList.pop_front();
	}

}

void CHBox::updateDim()
{

}

void CHBox::create(CWindow* parent)
{
	Widget = NULL;
	Container = parent->Container;
	parent->addChild(this);
}


}

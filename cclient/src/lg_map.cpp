/** 
 * AtysScape - Map
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
#include "utils.h"
#include "lg_map.h"

namespace LG
{


CMap::CMap(string name) : CWindow(name)
{
	Name = name;

	uint32 width, height;
	_Driver->getWindowSize(width, height);
	_ScreenWidth = (float)width;
	_ScreenHeight = (float)height;

	CImager::getInstance().addImage("map","color_palette.dds", 0.5f, 0.5f, 256, 64);
}

void CMap::loadMapsDef(const string filename)
{
	ifstream mapDefFile(filename.c_str());

	if (mapDefFile.is_open())
	{
		string line;

		while (!mapDefFile.eof())
		{
			getline(mapDefFile, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if ((line == "#") ||(line.empty()))
				continue;

			vector<string> tokens;
			tokenizer(line, tokens, " ");
			
			if (tokens.size() == 13)
			{
				TMapDef mapDef;
				mapDef.Name = tokens[0];
				mapDef.IGMinPosX = string2float(tokens[1]);
				mapDef.IGMaxPosX = string2float(tokens[2]);
				mapDef.IGMinPosY = string2float(tokens[3]);
				mapDef.IGMaxPosY = string2float(tokens[4]);
				mapDef.RatioW = string2float(tokens[5]);
				mapDef.RatioH = string2float(tokens[6]);
				mapDef.OffsetX = string2float(tokens[7]);
				mapDef.OffsetY = string2float(tokens[8]);
				mapDef.Filename = tokens[9];
				mapDef.TexW = string2int(tokens[10]);
				mapDef.TexH = string2int(tokens[11]);
				mapDef.TexRatio = string2float(tokens[12]);
				mapDef.Tex = _Driver->createTextureFile(mapDef.Filename);
				mapDef.Tex->setEnlargeCanvasNonPOW2Tex(true);

				_MapFiles.insert(make_pair(mapDef.Name, mapDef));
				_MapList.push_back(&_MapFiles[mapDef.Name]);

			}

		}
	}
}

void CMap::setMapCursorFile(const string &filename)
{
	_MapCursor = _Driver->createTextureFile(filename);
}

string CMap::getMapNameFromPos(float x, float y)
{

	for (uint i = 0; i < _MapList.size(); i++)
	{
		if (   (x > _MapList[i]->IGMinPosX) && (x <  _MapList[i]->IGMaxPosX)
			&& (y > _MapList[i]->IGMinPosY) && (y <  _MapList[i]->IGMaxPosY))
		{
			return  _MapList[i]->Name;
		}
		
	}
	return "";
}

void CMap::setCurrentMapName(const string &mapName)
{
	if (mapName.empty())
	{
		nlinfo("map ko");
		_Map = NULL;
	}
	else
	{
		nlinfo("map ok");
		_Map = &_MapFiles[mapName];
		CImager::getInstance().changeImage("map", _Map->Filename, (float)_Map->TexW, (float)_Map->TexH);
	}
}

void CMap::setPosition(float x, float y)
{
	_PosX = x;
	_PosY = y;
}


void CMap::create(CWindow* parent)
{

}

void CMap::show()
{}

void CMap::hide()
{}

void CMap::update()
{
}

void CMap::render()
{
	if (_Map != NULL)
	{
		//_Driver->setMatrixMode2D(CFrustum(0.0f, _ScreenWidth, 0.0f, _ScreenHeight, 0.0f, 1.0f, false));
		//_Driver->drawBitmap(5, _ScreenHeight-5-(float)_Map->TexH, (float)_Map->TexW, (float)_Map->TexH, *_Map->Tex);
		CImager::getInstance().setImagePos("map", 5, _ScreenHeight-5-(float)_Map->TexH);
		float posx = 5+(_PosX*_Map->RatioW)-_Map->OffsetX;
		float posy = _ScreenHeight-5+(_PosY*_Map->RatioH)+_Map->OffsetY;
		nlinfo("(%.4f, %.4f)", -_PosY*_Map->RatioH, _ScreenHeight-5+(_PosY*_Map->RatioH)+_Map->OffsetY);
		_Driver->drawBitmap(posx-4,  posy-4, 8, 8, *_MapCursor);
		_Driver->drawLine(posx-2, posy-2, posx+2, posy+2);
		_Driver->drawLine(posx-2, posy+2, posx+2, posy-2);

	}
}


}

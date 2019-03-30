/** 
 * AtysScape - Entry
 * 2008-05-08 - Ulukyn
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

#ifndef _LG_MAP_H_
#define _LG_MAP_H_

#include "lg_window.h"
#include "lg_imager.h"

namespace LG
{

struct TMapDef 
{
	string	Name;
	float	IGMinPosX;
	float	IGMaxPosX;
	float	IGMinPosY;
	float	IGMaxPosY;
	float	RatioW;
	float	RatioH;
	float	OffsetX;
	float	OffsetY;
	string	Filename;
	int		TexW;
	int		TexH;
	float	TexRatio;
	UTextureFile*	Tex;
};

class CMap : public CWindow
{

public:
	CMap(string name);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	void setPosition(float x, float y);
	void loadMapsDef(const string filename);
	string getMapNameFromPos(float x, float y);
	void setCurrentMapName(const string &mapName);
	void setMapCursorFile(const string &filename);

private:
	map<string, TMapDef> _MapFiles;
	vector<TMapDef*>	 _MapList;
	TMapDef				*_Map;
	UTextureFile		*_MapCursor;
	float				_PosX;
	float				_PosY;
	float				_ScreenWidth;
	float				_ScreenHeight;
};

}

#endif

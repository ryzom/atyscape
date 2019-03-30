/** 
	*** LG Image Manager ***
	This file is part of Ryturn Home Crafted MMORPG.

    Ryturn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ryturn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ryturn.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef _LG_IMAGE_H_
#define _LG_IMAGE_H_

#include "lg_window.h"

namespace LG
{

struct CImage
{
	string Name;
	CQuadColorUV QcUv;
	float X;
	float Y;
	float Width;
	float Height;
	UMaterial Mat;
};

class CImager : public CSingleton<CImager>
{

public:
	CImager();
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	void setDriver(UDriver* driver);
	void addImage(const string &imageName, const string &texName, float x, float y, float width, float height);
	void changeImage(const string &imageName, const string &texName, float width, float height);
	void setImagePos(const string &imageName, float x, float y);

private:
	map<string, CImage>	_Images;
	UDriver* _Driver;
};

}

#endif
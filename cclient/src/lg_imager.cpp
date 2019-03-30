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

#include "common.h"
#include "lg_imager.h"

namespace LG
{

CImager::CImager()
{
}

void CImager::setDriver(UDriver* driver)
{
	_Driver = driver;
}

void CImager::create(CWindow* parent)
{

}

void CImager::show()
{}

void CImager::hide()
{}

void CImager::update()
{
}

void CImager::render()
{
	map <string, CImage>::iterator ite;

	for (ite = _Images.begin(); ite != _Images.end(); ite++)
	{
		CImage img = (*ite).second;

		float x0 = img.X;
		float x1 = x0 + img.Width;
		float y0 = img.Y;
		float y1 = y0 + img.Height;
		
		float u0 = 0;
		float u1 = 1;
		float v0 = 0;
		float v1 = 1;
		
		img.QcUv.Uv0.set(u0,v0);
		img.QcUv.Uv1.set(u1,v0);
		img.QcUv.Uv2.set(u1,v1);
		img.QcUv.Uv3.set(u0,v1);
		img.QcUv.V0.set(x0,y0,0);
		img.QcUv.V1.set(x1,y0,0);
		img.QcUv.V2.set(x1,y1,0);
		img.QcUv.V3.set(x0,y1,0);

		_Driver->drawQuad(img.QcUv, img.Mat);
	}
}

void CImager::changeImage(const string &imageName, const string &texName, float width, float height)
{
	_Images[imageName].Height = height;
	_Images[imageName].Width = width;
	string res = CPath::lookup(texName);
	UTextureFile* tex = _Driver->createTextureFile(res);
	tex->setEnlargeCanvasNonPOW2Tex(true);
	_Images[imageName].Mat.setTexture(tex);
}

void CImager::setImagePos(const string &imageName, float x, float y)
{
	_Images[imageName].X = x;
	_Images[imageName].Y = y;
}

void CImager::addImage(const string &imageName, const string &texName, float x, float y, float width, float height)
{
	CImage image;

	image.Name = imageName;
	image.Height = height;
	image.Width = width;
	image.X = x;
	image.Y = y;
	image.Mat = _Driver->createMaterial();
	image.Mat.setBlend(true);
	image.Mat.setZFunc(UMaterial::always);
	image.Mat.setDoubleSided();

	if (texName.empty())
		return;

	string res = CPath::lookup(texName);
	UTextureFile *texture = _Driver->createTextureFile(res);
	nlassert(texture);
	
	image.Mat.setTexture(texture);




	CRGBA color = CRGBA(255,255,255,255);

	image.QcUv.Color0 = color;
	image.QcUv.Color1 = color;
	image.QcUv.Color2 = color;
	image.QcUv.Color3 = color;



	/*image.QcUv.V0 += _offset;
	image.QcUv.V1 += _offset;
	image.QcUv.V2 += _offset;
	image.QcUv.V3 += _offset;*/

	_Images.insert(make_pair(imageName, image));

}

}
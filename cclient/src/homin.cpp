/** 
 * Atyscape Atys viewer - Homin builder
 * Partly based on NEVRAX SNOWBALLS.
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

#include "homin.h"
#include <nel/misc/config_file.h>
#include <nel/3d/material.h>
#include <nel/3d/u_instance.h>

using namespace std;
using namespace NLMISC;

CHomin::CHomin(TSharedComponents share, string name) : CAnimated(share, name)
{

}

void CHomin::init(string filename)
{

	CConfigFile conf;
	conf.load(filename);

	_SkelFile = conf.getVar("Skeleton").asString();

	CConfigFile::CVar sVar = conf.getVar("Shapes");
	
	for(uint i = 0; i < sVar.size(); i++) {
		string sName = sVar.asString(i);
		CHominShape hs;

		hs.ShapeFile = conf.getVar(sName + "_File").asString();

		if (conf.exists(sName + "_Material")) {
			hs.SameMaterial = true;
			hs.Material = conf.getVar(sName + "_Material").asString();
		} else {
			hs.SameMaterial = false;
			for (uint j = 0; j < conf.getVar(sName + "_Materials").size(); j++) {
				hs.Materials.push_back(conf.getVar(sName + "_Materials").asString(j));
			}
		}
		_Shapes.push_back(hs);
	}
	createInstance();
}

void CHomin::createInstance()
{
	_Skeleton = _SC.Scene->createSkeleton(_SkelFile);
	_Skeleton.enableCastShadowMap(true);

	for(uint i = 0; i < _Shapes.size(); i++) {
		CHominShape hs = _Shapes[i];
		_Instance = _SC.Scene->createInstance(hs.ShapeFile);
		if (hs.SameMaterial) {
			for (uint j = 0; j < _Instance.getNumMaterials(); j++) {
				_Instance.getMaterial(j).setTextureFileName(hs.Material);
			}
		} else {
			nlassert(hs.Materials.size() <= _Instance.getNumMaterials());
			for (uint j = 0; j < hs.Materials.size(); j++) {
				_Instance.getMaterial(j).setTextureFileName(hs.Materials[j]);
			}
		}
		_Skeleton.bindSkin(_Instance);
		_Skeleton.setTransformMode(UTransformable::RotQuat);

	}

	loadAnimations();
}


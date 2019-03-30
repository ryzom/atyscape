/** 
 * Atyscape Atys viewer
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

#include "configuration.h"

using namespace std;
using namespace NLMISC;


CAtyscapeConfiguration::CAtyscapeConfiguration() {
}

CAtyscapeConfiguration::~CAtyscapeConfiguration(){
}

CAtyscapePoint CAtyscapeConfiguration::getPoint(string region, string point) {
	for(uint i = 0; i < Regions.size(); i++) {
		if (Regions[i].Name == region) {
			for (uint j = 0; j<  Regions[i].Points.size(); j++) {
				if (point == Regions[i].Points[j].Name)  return Regions[i].Points[j];
			}
		}
	}
	nlassert(false);
	CAtyscapePoint p;
	return p;
}

CAtyscapeRegion CAtyscapeConfiguration::getRegion(string region) {
	for(uint i = 0; i < Regions.size(); i++) {
		if (Regions[i].Name == region) return Regions[i];
	}
	nlassert(false);
	CAtyscapeRegion r;
	return r;
}

bool  CAtyscapeConfiguration::parse(string filename) {
	Conf.load(filename);

	Mode = Conf.getVar("GameMode").asString();
	Driver3D = Conf.getVar("Driver3D").asString();
	Season = Conf.getVar("Season").asString();
	ScreenH = Conf.getVar("ScreenH").asInt();
	ScreenV = Conf.getVar("ScreenV").asInt();
	FS = Conf.getVar("FullScreen").asString();
	Depth = Conf.getVar("Depth").asInt();
	RyzomDataPath = Conf.getVar("RyzomDataPath").asString();

	// Load interest points
	CConfigFile::CVar rVar = Conf.getVar("Regions");

	for(uint i = 0; i < rVar.size(); i++) {
		string regionName = rVar.asString(i);
		CAtyscapeRegion r;
		r.Name = regionName;
		r.Bank = Conf.getVar(regionName + "_Bank").asString();
		r.IgBNP = Conf.getVar(regionName + "_IGBNP").asString();
		r.MVG = Conf.getVar(regionName + "_MVG").asString();
		r.Pacs = Conf.getVar(regionName + "_Pacs").asString();
		CConfigFile::CVar pVar = Conf.getVar(regionName + "_Points");
		

		for (uint j = 0; j < pVar.size(); j++) {
			CAtyscapePoint p;
			CConfigFile::CVar thisPoint = Conf.getVar(pVar.asString(j) + "_Data");
			p.x = thisPoint.asFloat(0);
			p.y = thisPoint.asFloat(1);
			p.z = thisPoint.asFloat(2);
			p.Heading = thisPoint.asFloat(3);
			p.Attitude = thisPoint.asFloat(4);
			p.Name = Conf.getVar(pVar.asString(j) + "_Name").asString();
			r.Points.push_back(p);
		}
		Regions.push_back(r);
	}
	return true;
}

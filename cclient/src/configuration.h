
#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <nel/misc/config_file.h>
#include <vector>

using namespace std;
using namespace NLMISC;

class CAtyscapePoint {
public:
	string Name;
	float x;
	float y;
	float z;
	float Heading;
	float Attitude;
};

class CAtyscapeRegion {
public:
	string Name;
	string IgBNP;
	string Bank;
	string MVG; // Microveget texture prefix;
	string Pacs;
	vector<CAtyscapePoint> Points;
};

class CAtyscapeConfiguration {
public:
	CAtyscapeConfiguration();
	virtual ~CAtyscapeConfiguration();

	CAtyscapePoint getPoint(string region, string point);
	CAtyscapeRegion getRegion(string region);

	bool parse(string filename);

	CConfigFile Conf;
	vector<CAtyscapeRegion> Regions;

	string RyzomDataPath;
	string Mode;
	string Driver3D;
	uint ScreenH;
	uint ScreenV;
	uint Depth;
	string FS;
	string Season;
};

#endif

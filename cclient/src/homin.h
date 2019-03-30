
#ifndef _HOMIN_H_
#define _HOMIN_H_

#include <vector>
#include <nel/3d/u_scene.h>
#include <nel/3d/u_skeleton.h>
#include "animated.h"

using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CHominShape
{
public:
	string ShapeFile;
	bool SameMaterial;
	string Material;
	vector<string> Materials;
};

class CHomin : public CAnimated
{
public:

	CHomin(TSharedComponents share, string name);
	void init(string filename);
	void createInstance();

private:
	string				_SkelFile;
	vector<CHominShape> _Shapes;
};

#endif

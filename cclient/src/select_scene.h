
#ifndef _SELECT_H_
#define _SELECT_H_

#include <vector>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>
#include "configuration.h"
#include "common.h"

using namespace std;
using namespace NL3D;

class CLocationSelect {
public:
	CLocationSelect(TSharedComponents share);
	virtual ~CLocationSelect();

	void update();
	void render();

	CAtyscapeRegion SelectedRegion;
	CAtyscapePoint SelectedPoint;

	uint State; // 0 = selecting reggion, 1 = selecting point, 2 = done
private:
	
	TSharedComponents _SC;
	uint _CurRegion;
	uint _CurPoint;
};

#endif

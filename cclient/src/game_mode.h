
#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

#include "common.h"
#include "entity.h"

using namespace std;
using namespace NL3D;
using namespace NLMISC;

class CGameMode: public NLMISC::IEventListener {
public:
	CGameMode(TSharedComponents share);
	virtual ~CGameMode(){}

	virtual void init() = 0;
	virtual void update(float dt) = 0;
	virtual void animate(float curTime) = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
	virtual	uint getState();
	virtual void renderUI();
	virtual void finish();
	virtual void pause();
	virtual void resume();
	virtual void reset();
	
	//virtual void postInit() = 0;

	//virtual void doRegister() = 0;

	//virtual void setPosition(CAtyscapePoint p) = 0;
	
	//virtual void createLandScape();
	//virtual void loadRegion(string region);
	//virtual void loadPosition(CAtyscapePoint p);
	//void makeEntities();
	
	//CWorld* World;
	//UPlayList *pl;
	//UPlayList *plhom;
	//UInstance bone;	

	//UAnimationSet* _AnimationSet;
	//UPlayListManager* _PlayListManager;
	//CAnimated *_AnimatedYubo;
	//CAnimated *_AnimatedHomin;
	//CAnimated *_AnimatedHomine;

protected:
	TSharedComponents	_SC;
	uint				_State;

	//queue <CAnimated*> _AnimatedsList;


};
#endif

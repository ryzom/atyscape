/** 
 * Atyscape Atys viewer - Animated
 * 2007-02-25 - Zorglub / Ulukyn
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

#ifndef _ANIMATED_H_
#define _ANIMATED_H_

#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <fstream>
#include <nel/3d/u_instance.h>
#include <nel/3d/u_skeleton.h>
#include <nel/3d/u_play_list.h>
#include <nel/3d/u_play_list_manager.h>
#include <nel/3d/u_animation_set.h>
#include <nel/3d/u_animation.h>
#include <nel/misc/time_nl.h>

#include "entity.h"
#include "common.h"

using namespace NL3D;
using namespace std;
using namespace NLMISC;
using namespace NLPACS;


struct RandomAnims
{
	string AnimName;
	uint Proba;
};

struct AnimDescs
{
	string PreviousAnimName;
	string Filename;
	uint AnimId;
	UAnimation	*Animation;
	uint Cycles; // 0 = loop
	list<RandomAnims> NextAnim;
};

	typedef vector<AnimDescs> TAnimDescList;
	typedef map<std::string, TAnimDescList>::iterator TAnimDescIte;

class CAnimated : public CEntity
{
public:
	CAnimated(TSharedComponents share, string name);

	uint32					Id;
	string					Name;
	TSharedComponents		_SC;
	uint					_NextEmptySlot;
	UPlayList				*_PlayList;
	queue<std::string>		_AnimQueue;
	CAnimationTime			_StartAnimationTime;
	UAnimationSet			*_AnimationSet;
	UPlayListManager		*_PlayListManager;
	CAnimationTime			TransitionTime;
	string					_CurrentAnimName;
	AnimDescs				_CurrentAnimDesc;
	map<string, TAnimDescList> AnimsArray;

	void	init(const string &skelFile, const string &shapeFile);
	void	init(const string &skelFile);
	void	changeSkel(const string &skelFile);
	void	setShape(const string &id, const string &shapeFile, vector<string> texFiles);
	void	createAnimation();
//
	void	playAnimation(string anim,  bool force = false);
//
//	void	deleteAnimation();

	void	loadAnimations();
	void	loadAnimsDefinitions(const char *filename);
	bool	updateAnimation(bool force = false);
	void	computeAnimation(string anim);
	void	animate(float curTime);
//	void	releaseAnimation();
	void	applyQuat();
	CQuat	getQuat();
	void	setTexture(uint matId, string TextFileName);
	string	getKeyCodes();
	void	setKeyCodes(const string &keyCodes);
	void 	reset();

	void	setEnlighted();
	
	virtual void setPos(CVector pos);
	virtual CVector getPos();
	virtual void show();
	virtual void hide();
	
	virtual void update();
	virtual void render();
	USkeleton		_Skeleton;
	UInstance		_Instance;

protected:
	CQuat			_TransQuat;
	string			_SkelFile;
	map <string, UInstance> _ShapeByFile;
	map <string, string> _ShapeFileById;
	map <string, uint> _StageIndex;
	string			_KeyCodes;

};
#endif // ANIMATED_H



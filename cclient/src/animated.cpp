/** 
 * Atyscape Atys viewer	- Animated
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

#include <nel/pacs/u_move_container.h>
#include <nel/misc/vectord.h>

#include "animated.h"


using namespace std;
using namespace NLMISC;
using namespace NL3D;


CAnimated::CAnimated(TSharedComponents share, string name) : CEntity(name)
{
	_SC = share;
	TransitionTime = 0.25f;
	_CurrentAnimName = "*";
	_PlayList = NULL ;
	_AnimationSet = NULL ;
	_PlayListManager = NULL ;
	_CurrentAnimDesc.Animation = NULL ;
	_NextEmptySlot = 0;
	_StartAnimationTime = 0.f ;
	_ShapeByFile.clear();
	_ShapeFileById.clear();
	_StageIndex.clear();
	nlinfo("Ok");
}

void	CAnimated::init(const string &skelFile, const string &shapeFile)
{
	_Skeleton = _SC.Scene->createSkeleton(skelFile);
	_Instance = _SC.Scene->createInstance(shapeFile);
	_Skeleton.bindSkin(_Instance);
	_Skeleton.setTransformMode(UTransformable::RotQuat);
	_Skeleton.setClusterSystem((UInstanceGroup*)-1);
	_Skeleton.enableCastShadowMap(true);
	_Skeleton.enableReceiveShadowMap(true);

}

void	CAnimated::init(const string &skelFile)
{
	nlinfo("Skel = %s", skelFile.c_str());
	_SkelFile = skelFile;
	_Skeleton = _SC.Scene->createSkeleton(skelFile);
	_Skeleton.setTransformMode(UTransformable::RotQuat);
	_Skeleton.setClusterSystem((UInstanceGroup*)-1);
	_Skeleton.enableCastShadowMap(true);
	_Skeleton.enableReceiveShadowMap(true);
}


void CAnimated::changeSkel(const string &skelFile)
{
	if (skelFile == _SkelFile) return;
	for (map<string, UInstance>::iterator ite = _ShapeByFile.begin(); ite != _ShapeByFile.end(); ++ite)
	{
		if (!ite->second.empty())
		{
			_Skeleton.detachSkeletonSon(ite->second);
			_SC.Scene->deleteInstance(ite->second);
		}
	}
	_ShapeByFile.clear();
	_ShapeFileById.clear();
	_StageIndex.clear();

	CVector pos;
	CQuat quat;
	_Skeleton.getPos(pos);
	_Skeleton.getRotQuat(quat);
	_SC.Scene->deleteSkeleton(_Skeleton);
	if (skelFile != "")
	{
		init(skelFile);
		_PlayList->registerTransform(_Skeleton);
		_Skeleton.setPos(pos);
		_Skeleton.setRotQuat(quat);
	}
}

void 	CAnimated::reset()
{
	for(map <string, uint>::iterator it = _StageIndex.begin() ; it != _StageIndex.end() ; ++it)
	{
		nlinfo("reset of %s", it->first.c_str());
		it->second = -1;
	}
}

void	CAnimated::setShape(const string &id, const string &shapeFile, vector<string> texFiles)
{
	uint texIdx = 0;
	uint stageIdx = 0;

	UInstance instance;

	for (map <string, uint>::iterator i = _StageIndex.begin(); i != _StageIndex.end(); i++)
	{
		nlinfo("StageIndex have : %s", (*i).first.c_str());
	}

	nlinfo("Id = %s, ShapeFile = %s", id.c_str(), shapeFile.c_str());
	if (_ShapeFileById.find(id) == _ShapeFileById.end())
	{
		if (_StageIndex.find(shapeFile) == _StageIndex.end())
		{
			nlinfo("Is a New Shape and New ID");
			if (shapeFile.empty())
				return;
			instance = _SC.Scene->createInstance(shapeFile);
			instance.setMeanColor(CRGBA(0, 0, 255, 255));
			_ShapeFileById.insert(make_pair(id, shapeFile));
			_ShapeByFile.insert(make_pair(shapeFile, instance));
			_StageIndex.insert(make_pair(shapeFile, 0));
			_Skeleton.bindSkin(instance);
			_Skeleton.setTransformMode(UTransformable::RotQuat);
		}
		else
		{
			nlinfo("Is a Used Shape and New ID");
			instance = _ShapeByFile[shapeFile];
			_ShapeFileById.insert(make_pair(id, shapeFile));
			_StageIndex[shapeFile]++;
			stageIdx =_StageIndex[shapeFile];
		}
	}
	else
	{
		if (_StageIndex.find(shapeFile) == _StageIndex.end())
		{
			nlinfo("Is a New Shape in Used ID");
			_Skeleton.detachSkeletonSon(_ShapeByFile[_ShapeFileById[id]]);
			_SC.Scene->deleteInstance(_ShapeByFile[_ShapeFileById[id]]);
			if (shapeFile.empty())
				return;
			instance = _SC.Scene->createInstance(shapeFile);
			instance.setMeanColor(CRGBA(0, 0, 255, 255));
			_StageIndex.erase(_ShapeFileById[id]);
			_ShapeByFile.erase(_ShapeFileById[id]);
			_ShapeFileById[id] = shapeFile;
			_ShapeByFile.insert(make_pair(shapeFile, instance));
			_StageIndex.insert(make_pair(shapeFile, 0));
			_Skeleton.bindSkin(instance);
			_Skeleton.setTransformMode(UTransformable::RotQuat);
		}
		else
		{
			nlinfo("Is a Used Shape in Used ID", shapeFile.c_str());
			instance = _ShapeByFile[_ShapeFileById[id]];
			_StageIndex[shapeFile]++;
			stageIdx = _StageIndex[shapeFile];
		}
	}
	
	nlinfo("stage : %i", stageIdx);

	for (vector<string>::iterator ite=texFiles.begin(); ite != texFiles.end(); ite++)
	{
		nlinfo("tex = %s", (*ite).c_str());
		if (((uint)texFiles.size() == 1))
		{
			nlinfo("num of materials : %i", instance.getNumMaterials());
			for (uint j = 0; j < instance.getNumMaterials(); j++)
			{
				UInstanceMaterial material = instance.getMaterial(j);
				nlinfo("num of stages : %i", material.getLastTextureStage());
				if (material.isTextureFile(stageIdx))
				{
					nlinfo("texture file name : %s", material.getTextureFileName(stageIdx).c_str());
					material.setTextureFileName((*ite), stageIdx);
				}
			}
		}
		else
		{
			nlinfo("num of materials : %i", instance.getNumMaterials());
			nlinfo("texture file name : %s", instance.getMaterial(texIdx).getTextureFileName(stageIdx).c_str());
			instance.getMaterial(texIdx).setTextureFileName((*ite), stageIdx);
		}
		texIdx++;
	}
}


void	CAnimated::loadAnimations()
{
	_AnimationSet = _SC.Driver->createAnimationSet();
	_PlayListManager = _SC.Scene->createPlayListManager();

	nlinfo("Loading animations...");

	/** verification */
	TAnimDescIte adi, nextadi;
	list<RandomAnims> ranimCache;

	for (adi = AnimsArray.begin (); adi != AnimsArray.end (); )
	{
		nextadi = adi; nextadi++;

		TAnimDescList 	&adl = (*adi).second;
		nlinfo(adl.front().Filename.c_str());
		nlinfo(adl.front().PreviousAnimName.c_str());
		ranimCache = adl.front().NextAnim;
		while (!ranimCache.empty())
		{
			ranimCache.pop_front();
		}
		adi = nextadi;
	}
	/* **/

	for (adi = AnimsArray.begin (); adi != AnimsArray.end (); )
	{
		nextadi = adi; nextadi++;

		TAnimDescList *animDescList = &(*adi).second;
		
		TAnimDescList::iterator ite;
		for(ite = animDescList->begin(); ite != animDescList->end(); ite++)
		{
			AnimDescs *animDesc = &(*ite);

			nlinfo(animDesc->Filename.c_str());
			if (animDesc->Filename != "-")
			{
				animDesc->AnimId = _AnimationSet->addAnimation((animDesc->Filename+".anim").c_str(), animDesc->Filename.c_str());
				animDesc->Animation = _AnimationSet->getAnimation(animDesc->AnimId);
			}
		}

		adi = nextadi;
	}

	_AnimationSet->build ();

	_PlayList = _PlayListManager->createPlayList(_AnimationSet);
	_PlayList->registerTransform(_Skeleton);



		/** verification */
		for (adi = AnimsArray.begin (); adi != AnimsArray.end (); )
		{
			nextadi = adi; nextadi++;

			TAnimDescList 	adl = (*adi).second;
			adi = nextadi;
			
			TAnimDescList::iterator ite;
			for(ite = adl.begin(); ite != adl.end(); ite++)
			{
			}
			adi = nextadi;
		}
		/* **/
}

void	CAnimated::loadAnimsDefinitions(const char *filename)
{
	string line, animName;
	ifstream animdesc (filename);
	TAnimDescList animDescList;	

	AnimsArray.clear();
	if (animdesc.is_open())
	{
		while (!animdesc.eof())
		{
			getline(animdesc,line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if (line[0] == '{')
			{
				animDescList.clear();
				animName = line.substr(1, line.length()-1);
			}
			else if (line[0] == '}')
			{
				AnimsArray.insert(make_pair(animName, animDescList));
			}
			else if (!line.empty())
			{
				AnimDescs animDesc;

				uint indexOfBlank, oldIndexOfBlank;
				list<std::string> animParams;

				indexOfBlank = line.find_first_of(' ');
				animParams.push_back(line.substr(0, indexOfBlank));
				nlinfo(line.substr(0, indexOfBlank).c_str());

				while (indexOfBlank != string::npos)
				{
					oldIndexOfBlank = indexOfBlank;
					indexOfBlank = line.find_first_of(' ', indexOfBlank+1);
					animParams.push_back(line.substr(1+oldIndexOfBlank, indexOfBlank-oldIndexOfBlank-1));
					nlinfo(line.substr(1+oldIndexOfBlank, indexOfBlank-oldIndexOfBlank-1).c_str());
				}
				
				animDesc.PreviousAnimName = animParams.front();
				animParams.pop_front();
				animDesc.Filename = animParams.front().c_str();
				animParams.pop_front();

				std::istringstream iss(animParams.front());
				int number;
				iss >> number;
				animDesc.Cycles = number;
				animParams.pop_front();

				animDesc.AnimId = 0; // set in init
				animDesc.Animation = NULL; //set in init
				while (!animParams.empty())
				{
					RandomAnims randomAnim;

					randomAnim.AnimName = animParams.front();
					animParams.pop_front();
					istringstream iss(animParams.front());
					iss >> number;
					randomAnim.Proba = number;
					animParams.pop_front();
					animDesc.NextAnim.push_back(randomAnim);
				}

				animDescList.push_back(animDesc);
			}
		}
		animdesc.close();

		/** verification
		TAnimDescIte adi, nextadi;
		list<RandomAnims> ranimCache;

		for (adi = AnimsArray.begin (); adi != AnimsArray.end (); )
		{
			nextadi = adi; nextadi++;

			TAnimDescList 	&adl = (*adi).second;
			nlinfo(adl.front().Filename.c_str());
			nlinfo(adl.front().PreviousAnimName.c_str());
			ranimCache = adl.front().NextAnim;
			while (!ranimCache.empty())
			{
				ranimCache.pop_front();
			}
			adi = nextadi;
		}
		 **/
	}
}

void	CAnimated::computeAnimation (string anim)
{// Get the current time
	double currentTime = double (CTime::getLocalTime ())/1000.0f;

//	nlinfo ("%d playing animation", anim);
//	nlinfo ("%d playing animation %s ct%f st%f et%f", anim, AnimIdArray[anim][0].Name, currentTime, AnimIdArray[anim][0].Animation->getBeginTime (), AnimIdArray[anim][0].Animation->getEndTime ());

	// Find the new slot for the full animation (0 or 1)
	uint8 newSlot = _NextEmptySlot;
	uint8 oldSlot = 1 - _NextEmptySlot;
	_NextEmptySlot = 1 - _NextEmptySlot;

	TAnimDescList animDescList =  AnimsArray[anim];
	AnimDescs animDesc;
	bool haveFoundAnim = false;
	TAnimDescList::iterator ite;
	for(ite = animDescList.begin(); ite != animDescList.end(); ite++)
	{
		if ((!haveFoundAnim) && (((*ite).PreviousAnimName == _CurrentAnimName) || ((*ite).PreviousAnimName == "*")))
		{
			animDesc = (*ite);
			haveFoundAnim = true;
		}
	}

	_CurrentAnimDesc = animDesc;
	_CurrentAnimName = anim;

	if (animDesc.Filename == "-")
	{
		updateAnimation(true);
		return;
	}

	UPlayList::TWrapMode wrapMode = animDesc.Cycles == 0 ? UPlayList::Repeat : UPlayList::Clamp;
	
	_PlayList->setAnimation(newSlot, animDesc.AnimId);
	_PlayList->setTimeOrigin		(newSlot, currentTime);
	_PlayList->setWeightSmoothness	(newSlot, 1.0f);
	_PlayList->setWrapMode			(newSlot, wrapMode);

	double OldStartTime, OldEndTime;
	double NewStartTime, NewEndTime;

	// Get the starting time of the old animation slot
	_PlayList->getStartWeight	(oldSlot, OldStartTime);
	
	// Compute the time delta between start of the old animation and now
	double dt = currentTime - OldStartTime;

	// Compute the new transition value depending of the current time

	if (dt > TransitionTime)
		dt = TransitionTime;

	OldStartTime = currentTime - (TransitionTime - dt);
	OldEndTime = currentTime + dt;
		
	NewStartTime = currentTime;
	NewEndTime = currentTime + dt;

	// Set new weights on the old and the new animation slot

	_PlayList->setStartWeight	(oldSlot, 1.0f, OldStartTime);
	_PlayList->setEndWeight	(oldSlot, 0.0f, OldEndTime);

	_PlayList->setStartWeight	(newSlot, 0.0f, NewStartTime);
	_PlayList->setEndWeight	(newSlot, 1.0f, OldEndTime);

	// Keep in mind what is the last animation id we set
	_StartAnimationTime = (float)currentTime;
}

// This function is automatically called by playAnimation() the first time
void	CAnimated::createAnimation ()
{
	//nlassert (!Instance.empty() && !Skeleton.empty() && _AnimationSet != NULL);

	//_PlayList = _PlayListManager->createPlayList(_AnimationSet);
	//_PlayList->registerTransform(Instance);
	//_PlayList->registerTransform(Skeleton);
}



void	CAnimated::playAnimation (std::string anim,  bool force)
{
//	nlinfo ("playAnimation() %s", anim);

	// Get the current time
	CAnimationTime currentTime = NL3D::CAnimationTime(CTime::getLocalTime ())/1000.0f;

	// Can't do animation without skeleton
/** During tests
	if (Skeleton.empty())
		return;
*/

	// If the first time we play an animation, creates the animation class
	if (_PlayList == NULL)
		createAnimation();

	if (force || _AnimQueue.empty())
	{
		computeAnimation(anim);
		
		// clear the animation queue
		//nlinfo ("clearing animation queue");
		while (!_AnimQueue.empty())
			_AnimQueue.pop ();
	}	
}


//// This function must be called before releasing the animated to delete the animated animation
//void	CAnimated::deleteAnimation ()
//{
//
//}
//

bool	CAnimated::updateAnimation(bool force)
{
	CAnimationTime currentTime = CAnimationTime(CTime::getLocalTime ())/1000.0f;
//	nlinfo(_CurrentAnimDesc.Filename.c_str());
	if (force || (currentTime >= _StartAnimationTime + _CurrentAnimDesc.Animation->getEndTime() - TransitionTime/2))
	{
		std::string nextAnim;
		if (!_CurrentAnimDesc.NextAnim.empty())
		{
			uint randomInt = 1+int(100*rand()/(RAND_MAX + 1.0));
			list<RandomAnims> nextAnimList = _CurrentAnimDesc.NextAnim;
			uint nextAnimProba = 0;
			string nextAnimName;
			while ((randomInt > nextAnimProba) && (!nextAnimList.empty()))
			{
				nextAnimName = nextAnimList.front().AnimName;
				nextAnimProba += nextAnimList.front().Proba;
				nextAnimList.pop_front();
			}
			computeAnimation(nextAnimName);
		}
		return true;
	}

	return false;
}

void CAnimated::animate(float curTime)
{
	_PlayListManager->animate(curTime);
	_Skeleton.setPos(_Pos + CVector(0, 0, _Skeleton.getPos().z));

}


//
//	// compute new animation position depending of the current time
//	_PlayListManager->animate (double(CTime::getLocalTime ())/1000.0f);

//
////void	CAnimated::releaseAnimation ()
////{}
void CAnimated::setTexture(uint matId, string TextFileName)
{
	_Instance.getMaterial(matId).setTextureFileName(TextFileName);
}

string	CAnimated::getKeyCodes()
{
	return _KeyCodes;
}
void	CAnimated::setKeyCodes(const string &keyCodes)
{
	_KeyCodes = keyCodes;
}


void CAnimated::setEnlighted()
{
	for (uint j = 0; j < _Instance.getNumMaterials(); j++) {
		UInstanceMaterial mat = _Instance.getMaterial(j);
		CRGBA emi = mat.getEmissive();
		CRGBA amb = mat.getAmbient();
		CRGBA dif = mat.getDiffuse();
		CRGBA spe = mat.getSpecular();
		
		mat.setLighting(false, emi, amb, dif, spe, 10);
		mat.setColor(CRGBA(200, 200, 255 , 255));
	}
}

void	CAnimated::applyQuat()
{
	_Skeleton.setRotQuat(_Quat);
}


CQuat	CAnimated::getQuat()
{
	return _Skeleton.getRotQuat();
}

void CAnimated::setPos(CVector pos)
{
	CEntity::setPos(pos);
	//_Skeleton.setPos(_Pos);
}

CVector CAnimated::getPos()
{
//	nlinfo("%f %f %f", _pos.x, _pos.y, _pos.z);
	//_Pos = _Skeleton.getPos();
	return _Pos;
}

void CAnimated::show()
{}

void CAnimated::hide()
{}

void CAnimated::update()
{}

void CAnimated::render()
{}

/** 
 * Atyscape Atys viewer - Select Avatar mode
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

#include <nel/misc/types_nl.h>
#include <nel/misc/vectord.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_scene.h>
#include <nel/pacs/u_move_primitive.h>
#include <nel/3d/event_mouse_listener.h>

#include "select_avatar_mode.h"
#include "entity_manager.h"
#include "utils.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;



CSelAvatarMode::CSelAvatarMode(TSharedComponents share) : CGameMode(share)
{
	_SC = share;
	_MoveSpeed = 1.0f; // Base move speed, user set
	_SelectedAvatar = -1;
	_CurrentAvatar = -1;
	_InTonneauAvatar = -1;
	_CamSpeed = 0.1f;
	_CamPos = 2;
	_DoMove= false;
	_Run = false;
	_TonneauSpeed = 0.00f;
	_IdeaSpeed = 0.00f;

	_SC.Ui->Text->addTextZone("GameMode.Position", 0.01f, 0.05f, CRGBA(200, 255, 255), 14, UTextContext::TopLeft);
	_SC.Ui->Text->addTextZone("SelectAvatar.Infos", 0.5f, 0.15f, CRGBA(125, 255, 125), 16, UTextContext::MiddleTop);

}


void CSelAvatarMode::init()
{
	doRegister();
	CEntityManager::instance().loadOffsets( "data/defs/offsets.ddf" ) ;
	_SC.Scene->getCam().setTransformMode(UTransformable::DirectMatrix);
	_SC.Scene->getCam().setClusterSystem((UInstanceGroup*)-1);
	_SC.Ui->Text->loadRandomTexts("data/i18n/randoms/select_avatar.txt");

	_World = new CWorld(_SC);
	_World->createLight();

	//_Cam = new CEntity("Camera");

	CEntityManager *eManager = &CEntityManager::getInstance();

	for (uint avatarIdx = 0; avatarIdx < 5; avatarIdx++)
	{
		string avatarKc = eManager->getKeyCodesOfAvatar(avatarIdx);
		uint i = 1;
		string avatarName = "";

		while (avatarKc[i] != '_')
		{
			avatarName += avatarKc[i];
			++i;
		}
		_AvatarNames[avatarIdx] = avatarName;
		if (avatarName == "undefined")
		{
			avatarKc = eManager->getKeyCodesOfAvatar(5); // AvatarId > 4 = undefined
		}

		_AvatarOffsets[avatarIdx] = CEntityManager::instance().getOffset(avatarKc) ;
		
		_Avatars[avatarIdx] = eManager->createNewEntity(_AvatarNames[avatarIdx], avatarKc , 2);
// 		_Avatars[avatarIdx]->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
		_Avatars[avatarIdx]->loadAnimsDefinitions("data/anims/homins/fyros_hom.txt");
		_Avatars[avatarIdx]->loadAnimations();
		_Avatars[avatarIdx]->playAnimation("IDLE");
		_Avatars[avatarIdx]->setPos(CVector((float)avatarIdx, 0, _AvatarOffsets[avatarIdx]+.1f));
	}

	ifstream ideaDefFile("data/homins/yubette.def");
	string ideaDef = "";
	if (ideaDefFile.is_open())
	{
		getline(ideaDefFile, ideaDef);
	}
	else
	{
		nlerror("file % not found", "data/homins/yubette.def");
	}

	_Idea =  eManager->createNewEntity("Idea", ideaDef);
// 	_Idea->loadAnimsDefinitions("data\\anims\\fauna\\tr_dag.txt");
	_Idea->loadAnimsDefinitions("data/anims/fauna/tr_dag.txt");
	_Idea->loadAnimations();
	_Idea->setPos(CVector(0.0f, -3.0f, 0.3f));
	_Idea->setQuat(CQuat(CVector::K, (float)Pi/2.0f)*_Idea->getQuat());
	_Idea->applyQuat();
	_Idea->playAnimation("IDLE");

	CMatrix camMat = CMatrix::Identity;
	camMat.setPos(CVector(2.0f, -5.5f, 1.0f));
	_SC.Scene->getCam().setMatrix(camMat);


	_LastTime = CTime::getLocalTime();

	_Walker = 2;

	_Agora =  _SC.Scene->createInstance("agora_big_palmito.shape" );
	_Agora.setPos(-112.0f, -16.52f, 12.7f);
	_Agora.setRotQuat(CQuat(CVector::K, -1.90f)*_Agora.getRotQuat());
	//_Agora.setTransformMode(UTransformable::RotEuler);
	_Agora.setClusterSystem((UInstanceGroup*)-1);
	_Tonneau = _SC.Scene->createInstance("Gen_Mission_1_Tonneau.shape");
	_Tonneau.setClusterSystem((UInstanceGroup*)-1);
	_Tonneau.getMaterial(0).setTextureFileName("data/custom/g_tonneau_red.tga");
	_Tonneau.setPos(4.0f, -2.0f, 0);

	_TonneauBreak = _SC.Scene->createInstance("GE_Mission_Tonneau_broke.shape");
	_TonneauBreak.setClusterSystem((UInstanceGroup*)-1);
	_TonneauBreak.setPos(400.0f, -2.0f, 0);

	//_PopupMenu = new CPopupMenu("/SelectPlayer");
	//_PopupMenu->create(CWindowManager::getInstance().getWindow("[Root]"));
	//_PopupMenu->setPos(0.04f, 0.10f);
	//_PopupMenu->setSize(0.46f, 0.55f);
	//_PopupMenu->addItem("/SelectPlayer", "/SelectPlayer/GO", "SELECT");
	//_PopupMenu->setCallback(new CCallback(&CSelAvatarMode::go, this));
	//_PopupMenu->render();

	_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "DragAndDropAvatar");

	farCount[0] = 0;
}

void CSelAvatarMode::updateAvatars()
{
	doRegister();

	_SelectedAvatar = -1;
	_CurrentAvatar = -1;
	_InTonneauAvatar = -1;
	_CamSpeed = 0.1f;
	_CamPos = 2;
	_DoMove= false;
	_Run = false;
	_TonneauSpeed = 0.00f;
	_IdeaSpeed = 0.00f;

	_Idea->setPos(CVector(0.0f, -3.0f, 0.3f));
	_Idea->playAnimation("IDLE");
	
	_Tonneau.getMaterial(0).setTextureFileName("data/custom/g_tonneau_red.tga");

	CMatrix camMat = CMatrix::Identity;
	camMat.setPos(CVector(2.0f, -5.5f, 1.0f));
	_SC.Scene->getCam().setMatrix(camMat);

	CEntityManager *eManager = &CEntityManager::getInstance();

	for (uint avatarIdx = 0; avatarIdx < 5; avatarIdx++)
	{
		string avatarKc = eManager->getKeyCodesOfAvatar(avatarIdx);
		_AvatarOffsets[avatarIdx] = CEntityManager::instance().getOffset(avatarKc) ;
		uint i = 1;
		string avatarName = "";

		while (avatarKc[i] != '_')
		{
			avatarName += avatarKc[i];
			i++;
		}
		
		if (avatarName != _AvatarNames[avatarIdx])
		{
			 eManager->changeEntityShape(_Avatars[avatarIdx], avatarKc , 2);
		}
		else
		{
			/*_AvatarNames[avatarIdx] = avatarName;
			_Avatars[avatarIdx] = eManager->CreateNewEntity(_AvatarNames[avatarIdx], avatarKc , 2);
			_Avatars[avatarIdx]->loadAnimsDefinitions("data\\anims\\homins\\fyros_hom.txt");
			_Avatars[avatarIdx]->loadAnimations();
			_Avatars[avatarIdx]->playAnimation("IDLE");*/
		}
		
		_Avatars[avatarIdx]->setPos(CVector((float)avatarIdx, 0, _AvatarOffsets[avatarIdx]+.1f));
		_AvatarNames[avatarIdx] = avatarName;
	}
}

void CSelAvatarMode::operator ()(const CEvent& event)
{
	CEventMouse* mouseEvent=(CEventMouse*)&event;
	
	_SC.Ui->MouseX = mouseEvent->X;
	_SC.Ui->MouseY = mouseEvent->Y;


/*	if (event==EventMouseMoveId)
	{
		if (_CanMove)
		{

			if (mouseEvent->X > 0.60)
			{
				if (_CurrentPlayer < 3)
				{
					_CurrentPlayer++;
					_CamSpeed = abs(_CamSpeed);
				}
			}
			else if (mouseEvent->X < 0.40)
			{
				if (_CurrentPlayer > 0)
				{
					_CurrentPlayer--;
					_CamSpeed = -abs(_CamSpeed);
				}
			}
		}
	} 
	else */
	if (event == EventMouseUpId)
	{
		_DoMove = false;

		if (_TonneauSpeed == 0.05f)
		{
			nlerror("GO");
		}

		if (_CurrentAvatar != -1)
		{
			if (_Run)
			{
				_Avatars[_CurrentAvatar]->playAnimation("IDLE");
				_Run = false;
			}
			if (mouseEvent->X > 0.74f)
			{
				//_SelectedAvatar = _CurrentAvatar;
				if ((_InTonneauAvatar != -1) && (_InTonneauAvatar != _CurrentAvatar))
				{
					_Avatars[_InTonneauAvatar]->setPos(CVector((float)_InTonneauAvatar, 0, _AvatarOffsets[_InTonneauAvatar]+.1f));
					if (_AvatarNames[_CurrentAvatar] == "undefined")
					{
						_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "ChangeNewAvatar");
					}
					else
					{
						_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "ChangeAvatar");
					}
				}
				else
				{
					if (_AvatarNames[_CurrentAvatar] == "undefined")
					{
						_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "NewAvatar");
					}
					else
					{
						_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "AvatarReady");
					}
				}
				_Avatars[_CurrentAvatar]->setPos(CVector(4, -2, _AvatarOffsets[_CurrentAvatar]+.1f));
				_InTonneauAvatar =_CurrentAvatar;
				_Tonneau.getMaterial(0).setTextureFileName("data/custom/g_tonneau_green.tga");
				_TonneauSpeed = 0.02f;
			}
			else
			{
				_Avatars[_CurrentAvatar]->setPos(CVector((float)_CurrentAvatar, 0, _AvatarOffsets[_CurrentAvatar]+.1f));
				if (_CurrentAvatar == _InTonneauAvatar)
				{
					_InTonneauAvatar = -1;
					_Tonneau.getMaterial(0).setTextureFileName("data/custom/g_tonneau_red.tga");
					_SC.Ui->Text->setRandomText("SelectAvatar.Infos", "AvatarRemoved");
					_TonneauSpeed = 0.00f;
				}

			}
			_CurrentAvatar = -1;

		}
	}
	if (_DoMove)
	{
		float x = mouseEvent->X;
		float y = mouseEvent->Y;
		
		if ((x > 0.74f) && (y < 0.70f) && _Run)
		{
			_Run = false;
			_Avatars[_CurrentAvatar]->playAnimation("IDLE");
		}
		else if ((x < 0.74f) || (y > 0.70f) && !_Run)
		{
			_Run = true;
			_Avatars[_CurrentAvatar]->playAnimation("WALK");

		}
		if ((x > 0.60f) && (x < 0.74f) && (y < 0.65f))
		{
			_SC.Driver->setMousePos(0.60f, y);
			x = 0.60f;

		}
		

		y = 3.0f*(mouseEvent->Y-0.5f);
		x = (mouseEvent->X * 1.33f);
		if (x > 1)
			x = 1;
		if (y < 0)
			y = 0;
		_Avatars[_CurrentAvatar]->setPos(CVector(4.0f*x, -2.0f, 2.0f*y+_AvatarOffsets[_CurrentAvatar]+.1f));
	}
	else
	{
		CViewport vp = _SC.Driver->getViewport();

		if (_InTonneauAvatar != -1)
			_TonneauSpeed = 0.02f;
		else
			_TonneauSpeed = 0.00f;


		CVector tpos, tdir;
		vp.getRayWithPoint(_SC.Ui->MouseX, _SC.Ui->MouseY, tpos, tdir, _SC.Scene->getCam().getMatrix(), _SC.Scene->getCam().getFrustum());
		
		float dist2D;
		float distZ;

		bool fi = _Idea->_Skeleton.fastIntersect(tpos, tdir, dist2D, distZ, false);

		if ((_InTonneauAvatar != -1) && (dist2D == 0) && (event == EventMouseDownId))
		{
			_Idea->playAnimation("RUN");
			_IdeaSpeed = 0.20f;
		}

		for (uint i=0; i < 5; i++)
		{
			CVector tpos, tdir;
			vp.getRayWithPoint(_SC.Ui->MouseX, _SC.Ui->MouseY, tpos, tdir, _SC.Scene->getCam().getMatrix(), _SC.Scene->getCam().getFrustum());
		
			float dist2D;
			float distZ;

			bool fi = _Avatars[i]->_Skeleton.fastIntersect(tpos, tdir, dist2D, distZ, false);

			if (dist2D == 0)
			{
				
				if (event == EventMouseDownId)
				{
					_DoMove = true;
					_CurrentAvatar = i;
					if (_CurrentAvatar != _InTonneauAvatar)
					{
						_Avatars[_CurrentAvatar]->playAnimation("WALK");
						_Run = true;
					}
				}
			}
		}
	}
}

void CSelAvatarMode::update(float dt)
{
	_LastTime = _NewTime;
	_NewTime = CTime::getLocalTime();
	_DeltaTime = (double)(_NewTime - _LastTime) / 1000.0;
	if (_TonneauSpeed > 0)
	{
		_Tonneau.setRotQuat(CQuat(CVector::K, _TonneauSpeed)*_Tonneau.getRotQuat());
	}

	if (_Idea->getPos().x >= 3.0f)
	{
		_TonneauSpeed += 0.01f;
		_Avatars[_InTonneauAvatar]->setPos(CVector(0, 0, -0.012f)+_Avatars[_InTonneauAvatar]->getPos());
	}


	if (_TonneauSpeed > 0.5f)
	{
		_SelectedAvatar = _InTonneauAvatar;
	}

	if (_IdeaSpeed > 0)
	{
		_Idea->setPos(CVector(_IdeaSpeed, 0, 0) + _Idea->getPos());
	}
	
	//if ((((float)_CurrentAvatar - _CamPos)*(_CamSpeed<0?-1.0f:1.0f)) > 0)
	//{
	//	_CamPos += _CamSpeed;
	//	_CanMove = false;
	//}
	//else
	//{
	//	_CamPos = (float)_CurrentAvatar;
	//	//if (!_CanMove)
	//	//	_SC.Driver->setMousePos(0.5f, 0.5f);
	//	_CanMove = true;
	//	updateAnims(false);
	//}

	for (uint i = 0; i < 5; i++)
	{
		_Avatars[i]->updateAnimation();
	}
	_Idea->updateAnimation();
	//CMatrix camMat = CMatrix::Identity;
//	camMat.setPos(CVector(_CamPos, -5, 0.9f));
	//_SC.Scene->getCam().setMatrix(camMat);
	//_Agora.setPos(0.0f, 0.0f, 0.0f);

/*	fr = frustum.unProject(CVector(_MouseEventX, _MouseEventY, 0.5f));
	CLine line;
	line.V0.set(0.5, 0.5, 0);
	line.V1.set(0.5, 1, 0);
	
	CViewport vp = _SC.Driver->getViewport();
	CVector tpos, tdir;
	vp.getRayWithPoint(_MouseEventX, _MouseEventY, tpos, tdir, Cam, frustum);
	tdir.normalize();
	_AnimatedYubo->setEnlighted();*/

}
void CSelAvatarMode::handleEvents()
{
}

bool CSelAvatarMode::go(const string &winName)
{
	////_SelectedPlayer = _CurrentPlayer;
	////	_SC.Ui->removeWindow("/SelectPlayer", "Root");
	////	_SC.Ui->destroy("/SelectPlayer");
	_PopupMenu->destroy();
	_SelectedAvatar = _CurrentAvatar;

	_SC.Ui->Text->setText("SelectAvatar.Infos", "");

	return true;
}

void CSelAvatarMode::render()
{


	//_SC.Driver->setMatrixMode3D(_SC.Scene->getCam());
	CMatrix	mat = _SC.Scene->getCam().getMatrix();
	mat.scale(3.0f);
//	mat.setPos(CVector(0.0f, -0.5f, 0.0f));
////	_SC.Ui->writeText3D(mat, "Zorglor");
//	mat.setPos(CVector(1.0f, -0.5f, 0.0f));
////	_SC.Ui->writeText3D(mat, "Nymphea");
//	mat.setPos(CVector(2.0f, -0.5f, 0.0f));
////	_SC.Ui->writeText3D(mat, "Elhora");
//	mat.setPos(CVector(3.0f, -0.5f, 0.0f));
////	_SC.Ui->writeText3D(mat, "Yubette de Mermaidia");
//	_SC.Driver->setMatrixMode2D11();
	if (_DoMove)
	{
		CVector pos = _Avatars[_CurrentAvatar]->getPos();
		//_SC.Ui->Text->setText("GameMode.Position", "Avatar - X=%.4f Y=%.4f Z=%.4f / Mouse x=%.4f y=%.4f", pos.x, pos.y, pos.z, _SC.Ui->MouseX, _SC.Ui->MouseY);
	}
}


void CSelAvatarMode::animate(float curTime)
{
	
	_SC.Scene->animate(curTime);
	for (uint i = 0; i < 5; i++)
	{
		_Avatars[i]->animate(curTime);
	}
	_Idea->animate(curTime);
	_Idea->setQuat(CQuat(CVector::K, (float)Pi/2.0f)*_Idea->getQuat());
	_Idea->applyQuat();

}

uint  CSelAvatarMode::getSelectedPlayer(string &avatarName)
{
	avatarName = _AvatarNames[_SelectedAvatar];
	return _SelectedAvatar;
}

uint CSelAvatarMode::getState()
{
	if (_SelectedAvatar != -1)
	{
		_SC.Ui->Text->setText("SelectAvatar.Infos", "");
		return 1;
	}
	return 0;
}

void  CSelAvatarMode::finish()
{
	unRegister();
}

void CSelAvatarMode::pause()
{
	unRegister();
}

void CSelAvatarMode::resume()
{
	doRegister();
}
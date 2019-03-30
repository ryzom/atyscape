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

#define USE_JPEG

#include <iostream>

#include <nel/misc/types_nl.h>
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/vectord.h>


#include <nel/3d/u_scene.h>
#include <nel/3d/u_camera.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_landscape.h>

#include <nel/3d/scene_user.h>

#include <nel/3d/u_texture.h>
#include <nel/3d/u_instance.h>
#include <nel/3d/zone_search.h>
#include <nel/3d/u_material.h>
#include <nel/3d/event_mouse_listener.h>
#include <nel/3d/u_cloud_scape.h>
#include <nel/misc/progress_callback.h>
#include <nel/3d/water_shape.h>
#include <nel/misc/big_file.h>
#include <nel/3d/material.h>
#include <nel/3d/u_light.h>

#include <nel/3d/u_skeleton.h>

//#include "fly_move_handler.h"
#include "fly_mode.h"
#include "walk_mode.h"
#include "select_player_mode.h"
#include "select_avatar_mode.h"
#include "make_avatar_mode.h"
#include "configuration.h"
#include "homin.h"
#include "entity_manager.h"

#include "lg_ui.h"
#include "common.h"
#include "animated.h"

#include "game_modes/gm_make_avatar.h"
#include "mods/mod_nel.h"
#include "mods/mod_time.h"
#include "mods/mod_audio.h"

#include "views/view_fps.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;

//class Progressor : public IProgressCallback {
//public:
//	virtual void progress(float value) {
//		//nlinfo("Progress at %f", value);
//	}
//};

enum SSFormat {
	NoFormat = 0,
	Tga = 1,
	Jpeg = 2
} ;

class CAtyscapeClient {
public:
	CAtyscapeClient() : _GMode(NULL) {
	}
	virtual ~CAtyscapeClient(){
	}
	void run();

private:
	void setup();
	void selectAndLoadNewRegion();
	
	TSharedComponents _SC;

	CGameMode* _GMode;

//	CAnimated *animatedNyAmn;
//	CAnimated *animatedNyAmn2;

	CAtyscapeConfiguration _Config;

};

void CAtyscapeClient::setup() {
	// Load the configuration file
	
	_SC.Config = &_Config;

	_SC.Config->parse("atyscape.cfg");
	if (_SC.Config->Mode == "GetGraphicModes")
	{
		_SC.Driver = UDriver::createDriver(0, _SC.Config->Driver3D == "DirectX");
		nlassert(_SC.Driver);
		vector<UDriver::CMode> modes;
		_SC.Driver->getModes(modes);
		ofstream gmfile;
		gmfile.open("graphic_modes.nfo");

		for(uint i = 0; i < modes.size(); i++)
		{
			gmfile << modes[i].Width << "x" << modes[i].Height << " " << (uint16)modes[i].Depth << "Bit @" << modes[i].Frequency << "\n" ;
		}
		gmfile.close();
 
		exit(0);
	}
	else
	{
		_SC.Driver = UDriver::createDriver(0, _SC.Config->Driver3D == "DirectX");
		nlassert(_SC.Driver);

		_SC.Driver->setDisplay(UDriver::CMode(_SC.Config->ScreenH, _SC.Config->ScreenV, _SC.Config->Depth, _SC.Config->FS == "no"), true, true);
		vector<UDriver::CMode> modes;

		_SC.Scene = _SC.Driver->createScene(false);

		CModNel::getInstance().init(_SC.Scene, _SC.Driver);

		nlinfo("Creating UI...");
		_SC.Ui = &CUI::getInstance();
		nlinfo("Init UI...");
		_SC.Ui->init(_SC.Driver, "data/cegui/fonts/font.pfb");
		
		uint32 width, height;
		_SC.Driver->getWindowSize(width, height);

		_SC.Scene->getCam().setPerspective((float)Pi/2.f, (float)width/(float)height, 0.1f, 1000);

		CEntityManager *eManager = &CEntityManager::getInstance();
		eManager->init(_SC);
		eManager->loadShapeDefs("data/defs/shape.ddf");
		eManager->loadSkelDefs("data/defs/skel.ddf");
		eManager->loadTexDefs("data/defs/tex.ddf");
	}
}




void CAtyscapeClient::run()
{
	nlinfo("Entering setup...");
	setup();
	nlinfo("Leaving setup...");

	_SC.Ui->Text->addTextZone("Main.Info", 0.50f, 0.50f, CRGBA(255, 255, 255), 22, UTextContext::MiddleTop); 
	_SC.Ui->Text->setText("Main.Info", "AtysScape");
	_SC.Ui->Text->addTextZone("PressEnter", 0.50f, 0.45f, CRGBA(255, 255, 255), 22, UTextContext::MiddleTop); 
	_SC.Ui->Text->setText("PressEnter", "[ Press Enter ]");
	_SC.Ui->Text->setEffect("PressEnter", "AlphaPingPong");

	bool state = true;
	while(state)
	{
        _SC.Driver->clearBuffers(CRGBA (0, 0, 0));
		_SC.Driver->clearZBuffer();

		_SC.Driver->EventServer.pump();
		CEventListenerAsync* al = &_SC.Driver->AsyncListener;
		if (al->isKeyPushed(KeyRETURN))
			state = false;

		_SC.Ui->Text->render();
		_SC.Driver->swapBuffers ();
	}
	_SC.Ui->Text->delTextZone("PressEnter");
	_SC.Ui->Text->setEffect("Main.Info", "");
	_SC.Ui->Text->setColor("Main.Info", CRGBA(255, 255, 255, 255));

	CSelAvatarMode *selAvatarMode = new CSelAvatarMode(_SC);
	
	CMakeAvatarMode *makeAvatarMode = new CMakeAvatarMode(_SC);
	//CGmMakeAvatar *makeAvatarMode = new CGmMakeAvatar(_SC);

	if (_SC.Config->Mode == "fly")
	{
		_GMode = new CFlyMode(_SC);
	}
	else if (_SC.Config->Mode == "Beta")
	{
		_GMode = makeAvatarMode;
	}
	else
	{
		_GMode = selAvatarMode;
	}
	
	_SC.Ui->Text->addTextZone("Main.Version", 0.01f, 0.99f, CRGBA(255, 255, 150), 12, UTextContext::TopLeft);
	_SC.Ui->Text->setText("Main.Version", "Atyscape v0.9.7 - (Fantastic Four) - M to show map, M affiche la Carte - O/P to change speed, O/P pour ajuster la vitesse");

	_SC.Ui->Text->setText("Main.Info", "AtysScape - Loading data files");
	_SC.Ui->Text->update();

	/* Load all big files */
	nlinfo(_SC.Config->RyzomDataPath.c_str());
	CPath::addSearchPath(_SC.Config->RyzomDataPath, false, false);
	
	CPath::remapExtension("dds", "tga", true);
	// CPath::display();

	_SC.Ui->Text->setText("Main.Info", "AtysScape - Creating scene");
	_SC.Ui->Text->update();

	// !!! TEST !!!
	CModAudio* modAudio;
	modAudio = &CModAudio::getInstance();
	modAudio->init();

	CModTime* modTime;
	modTime = &CModTime::getInstance();
	modTime->init();

	CViewFPS* viewFPS = new CViewFPS();
	viewFPS->init();


	/* --- Anime debug mode ---
	_GMode->makeYubo();
	return;
	*/


	CViewport v;
	v.init(0.0f, 0.0f, 1.0f, 1.0f);
	_SC.Scene->setViewport(v);

	TTime curTime = CTime::getLocalTime();
	TTime oldTime;
	_GMode->init();

	_SC.Ui->Text->setEffect("Main.Info", "ZoomOut");

	//_GMode->postInit();

	//_GMode->createLandScape();
	//selectAndLoadNewRegion();

	bool needExit = false;
	uint8 takeSShot = NoFormat;
	bool haveMakeAvatar = false;
	/* First rendering */
	
	/*_GMode->update();
	_GMode->animate(float(curTime)/1000);
	_GMode->render();
	_SC.Driver->swapBuffers ();*/

	while ((!needExit) && _SC.Driver->isActive())
    {
		uint gModeState = _GMode->getState();
		if (gModeState != 0)
		{
			if (haveMakeAvatar)
				makeAvatarMode->pause();

			if (gModeState == 1)
			{
				if (_SC.Config->Mode != "Beta")
				{
					uint avatarId;
					string avatarName;
					avatarId = selAvatarMode->getSelectedPlayer(avatarName);
					// TEMP !!!
					//avatarName =  "undefined";
					//nlinfo("avatar name : ", avatarName.c_str());
					if (avatarName != "undefined")
					{
						if (haveMakeAvatar)
							makeAvatarMode->finish();
						_GMode->finish();
						CWalkMode *gMode = new CWalkMode(_SC);
						gMode->setPlayer(avatarId);
						_GMode = gMode;
						_GMode->init();
					}
					else
					{
						if (_SC.Config->Mode != "Beta")
							makeAvatarMode->setPlayer(avatarId);
						if (!haveMakeAvatar)
							makeAvatarMode->init();
						else
							makeAvatarMode->resume();
						haveMakeAvatar = true;
						_GMode->pause();
						_GMode = makeAvatarMode;

					}
				}
			}
			else
			{
				selAvatarMode->updateAvatars();
				_GMode = selAvatarMode;
				_GMode->resume();
			}
			
			 curTime = CTime::getLocalTime();
		}
		oldTime = curTime;
		curTime = (TTime)CTime::getLocalTime();
		// New Time managment
		modTime->update();
		//
		_SC.DeltaTime = (float)(curTime - oldTime)/1000.0f;
        // Clear all buffers

		_SC.Driver->clearBuffers(CRGBA (0, 0, 0));
		_SC.Driver->clearZBuffer();
 
		/* The whole loop */
		_SC.Driver->EventServer.pump();

		_GMode->handleEvents();
		_GMode->update(_SC.DeltaTime);
		_GMode->animate(float(curTime)/1000.0f);
		_GMode->render();
		_SC.Scene->render();
		_SC.Ui->render();
		_GMode->renderUI();
		_SC.Ui->Text->render();
		viewFPS->render();
		modAudio->update();
		_SC.Driver->swapBuffers ();

		if (takeSShot)
		{
			CBitmap btm;
			_SC.Driver->getBuffer(btm);
			
			string filename ;
			if (takeSShot == Tga) {
				filename = CFile::findNewFile("screenshot.tga");
				COFile fs(filename);
				btm.writeTGA(fs, 24, false);
			}
			else if (takeSShot == Jpeg) {
				filename = CFile::findNewFile("screenshot.jpg");
				COFile fs(filename);
				btm.writeJPG(fs);
			}

			nlinfo("Screenshot '%s' saved", filename.c_str());
			takeSShot = NoFormat ;
			_SC.Ui->Text->show();
		}

        // Manage the keyboard
        if (_SC.Driver->AsyncListener.isKeyDown(KeyESCAPE))
		{
            needExit = true;
        }

		/* Broken, memleaks, ...
		if (_Driver->AsyncListener.isKeyPushed(KeyS)) {
			selectAndLoadNewRegion();
		}
		*/

		if (_SC.Driver->AsyncListener.isKeyPushed(KeyF10))
		{
			takeSShot = Tga;
			_SC.Ui->Text->hide();
		}
		else if (_SC.Driver->AsyncListener.isKeyPushed(KeyF9)) {
			takeSShot = Jpeg;
			_SC.Ui->Text->hide();
		}
		else if (_SC.Driver->AsyncListener.isKeyPushed(KeyF5))
		{
			uint32 width, height;
			_SC.Driver->getWindowSize(width, height);
			_SC.Scene->getCam().setPerspective((float)Pi/2.f, (float)width/(float)height, 0.1f, 1000);

		}
    }
	
}


#ifdef NL_OS_WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdline, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{ 
	NLMISC::CApplicationContext myApplicationContext;
	CAtyscapeClient().run();
	return EXIT_SUCCESS;
}

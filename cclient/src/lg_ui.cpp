/** 
 * AtysScape - User Interface
 * 2008-05-15 - Ulukyn
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

#include "common.h"
#include "lg_window_manager.h"
#include "lg_imager.h"

#include "lg_ui.h"

namespace LG
{

CUI::CUI()
{
}

void CUI::init(UDriver* driver, string fontName)
{
	_Driver = driver;
	_Driver->showCursor(false);

	_GuiRenderer = new CEGUI::NeLRenderer(_Driver);
	_GuiRenderer->addSearchPath("data/cegui", true, false);
	_GuiSystem = new CEGUI::System(_GuiRenderer);
	_GuiRenderer->activateInput();

	nlinfo("Start up and configure the GUI system.");
	try	
	{		
		using namespace CEGUI;
		
		Logger::getSingleton().setLoggingLevel(Insane);
		SchemeManager::getSingleton().loadScheme(string(LOOK)+".scheme");
		System::getSingleton().setDefaultMouseCursor(string(LOOK), "MouseArrow");
		FontManager::getSingleton().createFont("gen-12.font");
		_CEGuiWm = WindowManager::getSingletonPtr();
		_Root = _CEGuiWm->createWindow("DefaultWindow", "Root");
		nlinfo("CREATE ROOT.");
		CWindow* root = new CWindow("[Root]");
		nlinfo("OK.");
		root->Container = _Root;
		root->Widget = _Root;
		_Root->setMaxSize(UVector2(UDim(1, 0), UDim(1, 0)));
		_Root->setArea(URect(UDim(0, 0), UDim(0, 0), UDim(1, 0), UDim(1, 0)));
    
		System::getSingleton().setGUISheet(_Root);
	}
	catch(CEGUI::Exception)
	{	// catch to prevent exit (errors will be logged).
		;
	}

	CWindowManager::getInstance().setDriver(_Driver);
	CImager::getInstance().setDriver(_Driver);

	Text = new CText("[TextContext]");
	Text->setDriver(_Driver);
	Text->setFont(fontName);
	Text->create(NULL);
}

void CUI::render()
{
	_GuiSystem->renderGUI();
	CImager::getInstance().render();
}
}

/** 
 * Atyscape Atys viewer - User Interface
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
/*
#include "common.h"
#include "ui.h"
#include "lg_frame.h"
#include "lg_listbox.h"
#include "lg_hbox.h"
#include "lg_vbox.h"
#include "lg_label.h"


void tokenize(const string& str, vector<string>& tokens, const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

/*string CUi::getWindowName()
{
	CEGUI::EventArgs* eventArgs = static_cast<CEGUI::EventArgs*>(this);
	CEGUI::WindowEventArgs* winEventArgs = static_cast<CEGUI::WindowEventArgs*>(eventArgs);
	return string(winEventArgs->window->getName().c_str());
	
}
*/
/*
CUi::CUi()
{
}


void CUi::init(UDriver* driver, string fontName)
{
	_Driver = driver;
	_TextContext = _Driver->createTextContext(fontName);
	_TextContext->setHotSpot(UTextContext::TopLeft);
	_Show = true;

	_GuiRenderer = new CEGUI::NeLRenderer(_Driver);
	_GuiRenderer->addSearchPath("data/gui", true, false);
	_GuiSystem = new CEGUI::System(_GuiRenderer);
	_GuiRenderer->activateInput();

	nlinfo("Start up and configure the GUI system.");
	try	{		
		using namespace CEGUI;
		
		Logger::getSingleton().setLoggingLevel(Insane);
		SchemeManager::getSingleton().loadScheme(string(LOOK)+".scheme");
		System::getSingleton().setDefaultMouseCursor(string(LOOK), "MouseArrow");
		FontManager::getSingleton().createFont("gen-12.font");
		_Wm = WindowManager::getSingletonPtr();
		//_Root = WindowManager::getSingleton().loadWindowLayout("ryturn.layout");
		_Root = _Wm->createWindow("DefaultWindow", "Root");
		_Root->setMaxSize(UVector2(UDim(1, 0), UDim(1, 0)));
		_Root->setArea(URect(UDim(0, 0), UDim(0, 0), UDim(1, 0), UDim(1, 0)));
    
		System::getSingleton().setGUISheet(_Root);
	}
	catch(CEGUI::Exception)
	{	// catch to prevent exit (errors will be logged).
		;
	}
	//CEGUI::Window* dlg = _Wm->createWindow(_Look+"/FrameWindow", "/Frame");
    //dlg->setMinSize(CEGUI::UVector2(CEGUI::UDim(0,250),CEGUI::UDim(0,100)));
    //dlg->setText("Frame");
    //_Root->addChildWindow(dlg);
	//static_cast<CEGUI::PopupMenu*>(CEGUI::WindowManager::getSingleton().getWindow("SR/Popup"))->openPopupMenu(false);
}

void CUi::textSetColor(CRGBA color)
{
	_TextContext->setColor (color);
}

void CUi::setFontSize(uint32 fontSize)
{
	_TextContext->setFontSize(fontSize);
}

void CUi::writeText(float x, float y, const char * format, ...)
{
	if (_Show)
	{
		char *str;
		NLMISC_CONVERT_VARGS (str, format, NLMISC::MaxCStringSize);
		_TextContext->printAt(x, y, ucstring(str));
	}
}

void CUi::writeText3D(CMatrix mat, const char * format, ...)
{
	_TextContext->setHotSpot (UTextContext::MiddleTop);
	_TextContext->setColor (CRGBA(255, 255, 255, 255));
	_TextContext->setFontSize (14);

	_TextContext->render3D(mat, format);
}


void CUi::addWindow(string type, string name, string parent)
{
	//CEGUI::Window* window = CEGUI::WindowManager::getSingleton().loadWindowLayout(layout);
	//_Root->addChildWindow(window);
	//Windows.insert(make_pair(name, window));

	nlinfo((string(LOOK)+"/"+string(type)).c_str());
	CEGUI::Window* win = _Wm->createWindow(string(LOOK)+"/"+type, name);
	_Wm->getWindow(parent)->addChildWindow(win);
}

void CUi::removeWindow(string name, string parent)
{
	_Wm->getWindow(parent)->removeChildWindow(name);
}

void CUi::windowSetText(string name, string text)
{
	_Wm->getWindow(name)->setText(text);
}

void CUi::windowSetVisible(string name, bool visibility)
{
	_Wm->getWindow(name)->setVisible(visibility);
}

void CUi::setScaleArea(string name, float x1, float y1, float x2, float y2)
{
	_Wm->getWindow(name)->setArea(CEGUI::URect(CEGUI::UDim(x1, 0), CEGUI::UDim(y1, 0), CEGUI::UDim(x2, 0), CEGUI::UDim(y2, 0)));
}


CEGUI::Window* CUi::getRoot()
{
	return _Root;
}

void CUi::addPopupMenu(string name, string parent)
{
	_IsPopupMenuClicked = false;
	CEGUI::Window* popup = _Wm->createWindow(string(LOOK)+"/PopupMenu", name);
    _Wm->getWindow(parent)->addChildWindow(popup);
}

void CUi::addMenuItem(string name, string text, string parent)
{
	CEGUI::Window* menuItem = _Wm->createWindow(string(LOOK)+"/MenuItem", name);
    menuItem->setText(text);
   _Wm->getWindow(parent)->addChildWindow(menuItem);

}

void CUi::addSelectMenuItem(string name, string text, string parent)
{
	CEGUI::Window* menuItem = _Wm->createWindow(string(LOOK)+"/MenuItem", name);
    menuItem->setText(text);
	menuItem->subscribeEvent("Clicked", CEGUI::Event::Subscriber(&CUi::_CB_OnPopupMenuClick, this));
   _Wm->getWindow(parent)->addChildWindow(menuItem);

}

bool CUi::handleEvent(const CUiEvent &e)
{
	const CEGUI::EventArgs& eventArgs = static_cast<const CEGUI::EventArgs&>(e);
	const CEGUI::WindowEventArgs& winEventArgs = static_cast<const CEGUI::WindowEventArgs&>(eventArgs);
	
	nlinfo("Window (%s)", winEventArgs.window->getName().c_str());
	return true;
}

void CUi::createConfigWindow(float x, float y, string defFile, string translateFile)
{

	ifstream cwDef(defFile.c_str());
	ifstream cwTrn(translateFile.c_str());

	map<string, string> translations;

	if (cwTrn.is_open())
	{
		string line, eName, eTransl;

		while (!cwTrn.eof())
		{
			getline(cwTrn, line);
			vector<string> tokens;
			tokenize(line, tokens);
			if (tokens.size() > 1)
			{
				eName = tokens[0];
				eTransl = tokens[1];
				nlinfo("NEW TRS : %s = %s", eName.c_str(), eTransl.c_str() );
				translations.insert(make_pair(eName, eTransl));
			}
		}
	}

	if (cwDef.is_open())
	{
		string line, eName, eType;
		list<string> eList;
		list<string>::iterator eListIte;
		map<string, string> parents;
		map<string, uint> nmbChilds;
		map<string, string>::iterator ite;

		LG::CFrame* mainFrame;
		while (!cwDef.eof())
		{
			getline(cwDef, line);

			if (line[0] == '{')
			{
				vector<string> tokens;
				eList.clear();
				tokenize(line, tokens);
				if (tokens.size() > 1)
				{
					eType = tokens[0];
					eName = tokens[1];
					nlinfo("NEW DEF : %s = %s", eType.c_str() , eName.c_str());
				}
			}	
			else if (line[0] == '}')
			{
				if (eType == "{MAIN")
				{
					mainFrame = new LG::CFrame(eName);
					LG::CWindow* winMainFrame = (LG::CWindow*) mainFrame;
					_Windows.insert(make_pair(eName, winMainFrame));
					mainFrame->create(NULL);
					mainFrame->setPos(x, y);
					mainFrame->setSize(1-x, 1-y);
					_Root->addChildWindow(mainFrame->Widget);
					//mainFrame->setChilds(eList);
					//CEGUI::Window* win = _Wm->createWindow(string(LOOK)+"/FrameWindow", eName);
					//win->setArea(CEGUI::URect(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0), CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));

					//_Wm->getWindow(eName)->addChildWindow(_Wm->getWindow(line));
				}
				if (eType == "{SECTION")
				{
					if (parents[eName] == "")
						continue;

					LG::CHBox* hbox = new LG::CHBox(eName);
					LG::CWindow* winHbox = (LG::CWindow*) hbox;
					_Windows.insert(make_pair(eName, winHbox));
					hbox->create(_Windows[parents[eName]]);
				}
				else if(eType == "{LIST")
				{
					if (parents[eName] == "")
						continue;

					LG::CVBox* vbox = new LG::CVBox(eName+"_vbox");
					LG::CListBox* listbox = new LG::CListBox(eName);
					LG::CLabel* label = new LG::CLabel(eName+"_label");
					vbox->Expand = 1;
					label->Expand = 0;
					listbox->Expand = 1;
					LG::CWindow* winListbox = (LG::CWindow*) listbox;
					_Windows.insert(make_pair(eName, winListbox));
					vbox->create(_Windows[parents[eName]]);
					label->create(vbox);
					listbox->create(vbox);
					listbox->setCallback("Selected", &CUi::handleEvent, this);
					label->setText(translations[eName]);
					label->setOffset(0, 0, 30, 0);
	
					float sizeH = 0;
					while(!eList.empty())
					{
						string item = eList.front();
						nlinfo("add item : %s", item.c_str());
						eList.pop_front();
						//CEGUI:ListBoxItem lbi = new CEGUI:ListBoxItem(child);
						CVector sizeItem = listbox->addItem(item, translations[eName+"."+item]);
						nlinfo("Size : %f", sizeItem.y);
						sizeH += sizeItem.y;
					}

					listbox->setPos(0, 0);
					listbox->setSize(1, 1);
					listbox->setOffset(0, -10, 0, 10);
				}


				/*while (!eList.empty())
				{


				}*//*
				ite = parents.find(line);
				if (ite != parents.end())
				{
					parents[line];
				}

				
			}
			else if (!line.empty())
			{
				if ((eType == "{MAIN") || (eType == "{SECTION"))
				{
					nlinfo("%s has new child : %s", eName.c_str(), line.c_str());
					parents.insert(make_pair(line, eName));
				}
				eList.push_back(line);
			}
		}
		mainFrame->render();
	}
	cwDef.close();
}

void CUi::openPopupMenu(string name)
{
	static_cast<CEGUI::PopupMenu*>(_Wm->getWindow(name))->openPopupMenu(false);
}

void CUi::destroy(string name)
{
	_Wm->getWindow(name)->destroy();
}

bool CUi::isPopupMenuClicked()
{
	return _IsPopupMenuClicked;
}

void CUi::update()
{
	_Driver->swapBuffers();
}

void CUi::clear()
{
	_Driver->clearBuffers(CRGBA (0, 0, 0));
}

void CUi::showText(bool show)
{
	_Show = show;
}

void CUi::render()
{
	_GuiSystem->renderGUI();
}


bool CUi::_CB_OnPopupMenuClick(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs& we = static_cast<const CEGUI::WindowEventArgs&>(e);

	SelectedMenuItem = string(we.window->getName().c_str());
	_IsPopupMenuClicked = true;

	return true;
}
*/

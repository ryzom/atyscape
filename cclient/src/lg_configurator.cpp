/** 
 * AtysScape - Configurator
 * 2008-05-17 - Ulukyn
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
#include "utils.h"
#include "lg_configurator.h"
#include "lg_frame.h"
#include "lg_listbox.h"
#include "lg_hbox.h"
#include "lg_vbox.h"
#include "lg_entry.h"
#include "lg_label.h"
#include "lg_button.h"


//void tokenizer(const string& str, vector<string>& tokens, const string& delimiters = " ")
//{
//    // Skip delimiters at beginning.
//    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
//    // Find first "non-delimiter".
//    string::size_type pos     = str.find_first_of(delimiters, lastPos);
//
//    while (string::npos != pos || string::npos != lastPos)
//    {
//        // Found a token, add it to the vector.
//        tokens.push_back(str.substr(lastPos, pos - lastPos));
//        // Skip delimiters.  Note the "not_of"
//        lastPos = str.find_first_not_of(delimiters, pos);
//        // Find next "non-delimiter"
//        pos = str.find_first_of(delimiters, lastPos);
//    }
//}

namespace LG
{

CConfigurator::CConfigurator(string name) : CWindow(name)
{
	Name = name;
	FullName = name;
	nlinfo("created");
	_ActiveCallbacks["ListBox"] = false;
	_ActiveCallbacks["Ok"] = false;
	_ActiveCallbacks["Cancel"] = false;

}

void CConfigurator::create(CWindow* parent)
{
	ifstream cwDef(_DefFile.c_str());
	ifstream cwTrn(_TranslateFile.c_str());

	if (cwTrn.is_open())
	{
		string line, eName, eTransl;

		while (!cwTrn.eof())
		{
			getline(cwTrn, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			vector<string> tokens;
			tokenizer(line, tokens);
			if (tokens.size() > 1)
			{
				eName = tokens[0];
				eTransl = tokens[1];
				for(vector<string>::iterator i = tokens.begin()+2; i != tokens.end(); ++i)
				{
					eTransl += " "+(*i);
				}
				nlinfo("NEW TRS : %s = %s", eName.c_str(), eTransl.c_str() );
				_Translations.insert(make_pair(eName, eTransl));
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

		CFrame* mainFrame;
		while (!cwDef.eof())
		{
			getline(cwDef, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if (line[0] == '{')
			{
				vector<string> tokens;
				eList.clear();
				tokenizer(line, tokens);
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
					mainFrame = new CFrame(eName);
					Widget = mainFrame->Widget;
					mainFrame->create(CWindowManager::getInstance().getWindow("[Root]"));
					mainFrame->setTitle(_Translations[eName]);
					Widget = mainFrame->Widget;
					CWindow* winmainFrame = (CWindow*) mainFrame;
					//mainFrame->setChilds(eList);
					//CEGUI::Window* win = _Wm->createWindow(string(LOOK)+"/FrameWindow", eName);
					//win->setArea(CEGUI::URect(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0), CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));

					//_Wm->getWindow(eName)->addChildWindow(_Wm->getWindow(line));
					//mainFrame->setExpand(0.5f, 0.9f);
					//mainFrame->setPos(0, 0.05f);
					mainFrame->printInfos();
				}
				if (eType == "{SECTION")
				{
					if (parents[eName] == "")
						continue;

					CHBox* hbox = new CHBox(eName);
					CWindow* winHbox = (CWindow*) hbox;
					hbox->create(CWindowManager::getInstance().getWindow(parents[eName]));
					hbox->setExpand(1.0f, 0.7f);
				}
				else if (eType == "{ENTRY")
				{
					CVBox* vbox = new CVBox(eName+"_vbox");
					CEntry* entry = new CEntry(eName);
					CLabel* label = new CLabel(eName+"_label");
					CWindow* winListbox = (CWindow*) entry;
					vbox->create(CWindowManager::getInstance().getWindow(parents[eName]));
					label->create(vbox);
					entry->create(vbox);
					label->setText(_Translations[eName]);
					label->setExpand(1.0f, 0.0f);
					entry->setExpand(1.0f, 0.0f);
				}
				else if (eType == "{OK_BUTTON")
				{
					CButton* button = new CButton(eName);
					button->create(CWindowManager::getInstance().getWindow(parents[eName]));
					CWindow* winButton = (CWindow*)button;
					button->setText(_Translations[eName]);
					button->Widget->subscribeEvent("Clicked", CEGUI::Event::Subscriber(&CConfigurator::handleOKEvent, this));
				}
				else if (eType == "{BUTTON")
				{
					CButton* button = new CButton(eName);
					button->create(CWindowManager::getInstance().getWindow(parents[eName]));
					CWindow* winButton = (CWindow*)button;
					button->setText(_Translations[eName]);
					button->Widget->subscribeEvent("Clicked", CEGUI::Event::Subscriber(&CConfigurator::handleButtonEvent, this));
					_ActiveCallbacks.insert(make_pair(eName+"Event", false));
				}
				else if(eType == "{LIST")
				{
					if (parents[eName] == "")
						continue;

					CVBox* vbox = new CVBox(eName+"_vbox");
					CListBox* listbox = new CListBox(eName);
					CLabel* label = new CLabel(eName+"_label");
					CWindow* winListbox = (CWindow*) listbox;
					vbox->create(CWindowManager::getInstance().getWindow(parents[eName]));
					label->create(vbox);
					listbox->create(vbox);
					listbox->setCallback("Selected", &CConfigurator::handleListBoxEvent, this);
					label->setText(_Translations[eName]);
					label->setExpand(1.0f, 0.0f);
					listbox->setExpand(1.0f, 1.0f);
	
					float sizeH = 0;
					while(!eList.empty())
					{
						string item = eList.front();
						nlinfo("add item : %s", item.c_str());
						eList.pop_front();
						//CEGUI:ListBoxItem lbi = new CEGUI:ListBoxItem(child);
						CVector sizeItem = listbox->addItem(item, _Translations[eName+"."+item]);
						_UnTranslateMap.insert(make_pair(eName+"."+_Translations[eName+"."+item], item));
						nlinfo("Size : %f", sizeItem.y);
						sizeH += sizeItem.y;
					}
					//listbox->setSize(1, 1);
				}


				/*while (!eList.empty())
				{


				}*/
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

				if (eType == "{KEYCODES")
				{
					vector<string> tokens;
					tokenizer(line, tokens, ".");
					for(vector<string>::iterator i = tokens.begin(); i != tokens.end();++i)
					{
						_KeyCodesDefs.push_back((*i));
						nlinfo("Keycode added : %s", (*i).c_str());
					}
					_KeyCodesDefs.push_back(string("\t"));
				}
			}
		}

		mainFrame->render();
	}
	cwDef.close();
}

bool CConfigurator::handleListBoxEvent(const CUiEvent &e)
{
	const CEGUI::EventArgs& eventArgs = static_cast<const CEGUI::EventArgs&>(e);
	const CEGUI::WindowEventArgs& winEventArgs = static_cast<const CEGUI::WindowEventArgs&>(eventArgs);
	CEGUI::Combobox* cb = static_cast<CEGUI::Combobox *>(winEventArgs.window);

	nlinfo(_KeyCodes.c_str());
	uint kci = 0;
	for(vector<string>::iterator i = _KeyCodesDefs.begin(); i != _KeyCodesDefs.end();++i)
	{
		if ((*i) != "$")
		{
			if ((*i) == "$"+winEventArgs.window->getName())
			{
				string new_code = _UnTranslateMap[string((winEventArgs.window->getName()+"."+cb->getSelectedItem()->getText()).c_str())];
				nlinfo("%s : %s", (*i).c_str(), new_code.c_str());
				_KeyCodes = _KeyCodes.replace(kci, new_code.length(), new_code);
			}
		}
		if (_KeyCodes[kci] == '_')
		{
			kci++;
			while (_KeyCodes[kci] != '_')
			{
				kci++;;
			}
		}
		kci++;
	}
	if (_ActiveCallbacks["ListBox"])
	{
		(*_Callbacks["ListBox"])(_KeyCodes);
	}
	return true;
}

bool CConfigurator::handleOKEvent(const CUiEvent &e)
{
	if (_ActiveCallbacks["Ok"])
	{
		(*_Callbacks["Ok"])(_KeyCodes);
	}
	return true;
}

bool CConfigurator::handleButtonEvent(const CUiEvent &e)
{
	const CEGUI::EventArgs& eventArgs = static_cast<const CEGUI::EventArgs&>(e);
	const CEGUI::WindowEventArgs& winEventArgs = static_cast<const CEGUI::WindowEventArgs&>(eventArgs);
	string name = string(winEventArgs.window->getName().c_str());

	if (_ActiveCallbacks[name+"Event"])
	{
		(*_Callbacks[name+"Event"])(_KeyCodes);
	}
	nlinfo("event of button : %s", name.c_str());
	return true;
}

string CConfigurator::getKeycodes()
{
	return _KeyCodes;
}

void CConfigurator::setDefsFile(const string &defFile, const string &translateFile)
{
	_DefFile = defFile;
	_TranslateFile = translateFile;
}

void CConfigurator::initKeyCodes(const string &keycodes)
{
	_KeyCodes = keycodes;
	uint kci = 0;
	for(vector<string>::iterator i = _KeyCodesDefs.begin(); i != _KeyCodesDefs.end();++i)
	{
		if ((*i) != "$")
		{
			string value;
			if (_KeyCodes[kci] == '_')
			{
				kci++;
				value = "";
				while (_KeyCodes[kci] != '_')
				{
					value += _KeyCodes[kci];
					kci++;
				}
			}
			else
			{
				value = _KeyCodes[kci];
			}
			nlinfo("win %s = %s", value.c_str(), (*i).substr(1, (*i).length()-1).c_str());
			CWindow *win = CWindowManager::getInstance().getWindow((*i).substr(1, (*i).length()-1));

			if (win != NULL)
			{
				if (win->Type == "Editbox")
				{
					static_cast<CEntry* >(win)->setText(value);
				}
				if (win->Type == "Listbox")
				{
					static_cast<CListBox* >(win)->setText(_Translations[(*i).substr(1, (*i).length()-1)+"."+value]);
				}
			}

		}
		kci++;
	}
	nlinfo("ok");
}


void CConfigurator::setRandomKeyCodes()
{
	_KeyCodes = "";

	map<string, string> randItems;

	for(vector<string>::iterator i = _KeyCodesDefs.begin(); i != _KeyCodesDefs.end();++i)
	{
		nlinfo("[%s]", (*i).c_str());

		if ((*i) != "$")
		{
			if ((*i)[0] == '$')
			{

				CWindow *win = CWindowManager::getInstance().getWindow((*i).substr(1, (*i).length()-1));

				if (win != NULL)
				{
					if (win->Type == "Editbox")
					{
						static_cast<CEntry* >(win)->setText(" ");
						_KeyCodes += "__";
					}
					if (win->Type == "Listbox")
					{
						string value, winName;

						winName = (*i).substr(1, (*i).length()-1);

						if (randItems.find(winName) == randItems.end())
						{
							vector<string> items;
							static_cast<CListBox* >(win)->getItemsList(items);
							uint random = ((items.size())*rand())/RAND_MAX;
							value = items[random];
							randItems.insert(make_pair(winName, value));
						}
						else
						{
							value = randItems[winName];
						}
						static_cast<CListBox* >(win)->setText(_Translations[winName+"."+value]);
						_KeyCodes += value;
					}
				}
			}
			else
			{
				_KeyCodes += (*i);
			}
		}
	}
	nlinfo("Random keyCodes : %s", _KeyCodes.c_str());
}


void CConfigurator::show()
{}

void CConfigurator::hide()
{}

void CConfigurator::update()
{}

void CConfigurator::render()
{
}


}

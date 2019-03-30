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

#ifndef _LG_CONFIGURATOR_H_
#define _LG_CONFIGURATOR_H_

#include "lg_window.h"


namespace LG
{

class CConfigurator : public CWindow
{

public:
	CConfigurator(string name);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	void setDefsFile(const string &defFile, const string &translateFile);
	bool handleListBoxEvent(const CUiEvent &e);
	bool handleOKEvent(const CUiEvent &e);
	bool handleButtonEvent(const CUiEvent &e);
	void initKeyCodes(const string &keycodes);	
	void setRandomKeyCodes();

	string getKeycodes();
	void setListBoxCallback(CCallback* cb);
	void setOkCallback(CCallback* cb);
	void setCancelCallback(CCallback* cb);

private:
	string _DefFile;
	string _TranslateFile;
	map<string, string> _Translations;
	string _KeyCodes;
	vector<string> _KeyCodesDefs;
	map<string, string> _UnTranslateMap;
};

}

#endif

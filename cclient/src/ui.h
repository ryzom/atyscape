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
#ifndef _UI_H_
#define _UI_H_
/*
#include <nel/misc/types_nl.h>
#include <nel/misc/ucstring.h>
#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>

#include "lg_window_manager.h"
#include "CEGUI.h"
#include "nel/cegui/nelrenderer.h"


using namespace std;
using namespace NL3D;
using namespace NLMISC;

namespace LG 
{

typedef CEGUI::EventArgs CUiEvent;

class CUi
{
public:
	CUi();
		
	void init(UDriver* drive, string fontName);
	
	void textSetColor(CRGBA color);
	void writeText(float x, float y, const char * format, ...);
	void writeText3D(CMatrix mat, const char * format, ...);
	void setFontSize(uint32 fontSize);
	void update();
	void clear();
	void render();
	void showText(bool show);
	void addWindow(string type, string name, string parent);
	void removeWindow(string name, string parent);
	void windowSetText(string name, string text);
	void windowSetVisible(string name, bool visibility);
	void destroy(string name);
	CEGUI::Window* getRoot();
	void addPopupMenu(string name, string parent);
	void addMenuItem(string name, string text, string parent);
	void addSelectMenuItem(string name, string text, string parent);
	bool isPopupMenuClicked();
	bool _CB_OnPopupMenuClick(const CEGUI::EventArgs& e);
	void openPopupMenu(string name);
	void createConfigWindow(float x, float y, string defFile, string translateFile);

	void setScaleArea(string name, float x1, float y1, float x2, float y2);
	bool handleEvent(const CUiEvent &e);

	map<string, CEGUI::Window*>	Windows;
	string SelectedMenuItem;

	float MouseX;
	float MouseY;

protected:
	UDriver* _Driver;
	UTextContext* _TextContext;

private:
	bool		_Show;
	CWindowManager*		_LGWm;
	uint16		_ScreenWidth;
	uint16		_ScreenHeight;

	CEGUI::System		*_GuiSystem;
	CEGUI::NeLRenderer	*_GuiRenderer;
	
	CEGUI::Window		*_Root;
	CEGUI::WindowManager *_Wm;
	string				_Look;

	bool				_IsPopupMenuClicked;

};

}
*/
#endif

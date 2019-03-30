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

#ifndef _LG_UI_H_
#define _LG_UI_H_

#include <nel/3d/u_driver.h>
#include <nel/3d/u_text_context.h>

#include "CEGUI.h"
#include "nel/cegui/nelrenderer.h"

#include "lg_window_manager.h"
#include "lg_text.h"

using namespace NL3D;
using namespace NLMISC;
using namespace std;

namespace LG
{

typedef CEGUI::EventArgs CUiEvent;

class CUI : public CSingleton<CUI>
{

public:
	CUI();

	void init(UDriver* driver, string fontName);
	void render();
	CText* Text;

	float MouseX;
	float MouseY;


private:
	UDriver* _Driver;

	CEGUI::WindowManager* _CEGuiWm;

	CEGUI::System		*_GuiSystem;
	CEGUI::NeLRenderer	*_GuiRenderer;
	
	CEGUI::Window		*_Root;

};

}

#endif

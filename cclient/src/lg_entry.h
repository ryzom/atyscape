/** 
 * AtysScape - Entry
 * 2008-05-08 - Ulukyn
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

#ifndef _LG_ENTRY_H_
#define _LG_ENTRY_H_

#include "lg_window.h"

namespace LG
{

class CEntry : public CWindow
{

public:
	CEntry(string name);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	const string &getText();
	void setText(const string &text);

private:
	string _Text;
};

}

#endif

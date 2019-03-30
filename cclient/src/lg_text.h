/** 
 * AtysScape - Text
 * 2008-05-13 - Ulukyn
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

#ifndef _LG_TEXT_H_
#define _LG_TEXT_H_

#include <nel/3d/u_text_context.h>
#include "lg_window.h"

using namespace NLMISC;
using namespace NL3D;
using namespace std;

namespace LG
{

struct TText
{
	string Name;
	float X;
	float Y;
	CRGBA Color;
	uint32 FontSize;
	string Effect;
	UTextContext::THotSpot HotSpot;
	string Message;
	uint FxValue;
};

class CText : public CWindow
{

public:
	CText(string name);
	
	virtual void show();
	virtual void hide();
	
	virtual void create(CWindow* parent);
	virtual void update();
	virtual void render();

	void loadRandomTexts(const string &filename);

	void setFont(string fontName);
	void addTextZone(string name, float x, float y, CRGBA color, uint32 fontSize, UTextContext::THotSpot hotSpot = UTextContext::TopLeft);
	void delTextZone(string name);
	void setText(string zone, const char * format, ...);
	void setRandomText(const string &zone, const string &rtName);
	string getRandomText(const string &rtName);
	void setColor(const string &zone, CRGBA color);
	void setPos(const string &zone, float x, float y);
	void setFontSize(const string &zone, uint32 fontSize);
	void setProps(const string &zone, float x, float y, CRGBA color, uint32 fontSize, UTextContext::THotSpot hotSpot);

	/* Effects */
	void setEffect(const string &zone, const string &effect);
	void fxFadeOut(TText &text);
	void fxAlphaPingPong(TText &text);
	void fxZoomOut(TText &text);

private:
	bool				isCreated;
	string				_Font;
	CRGBA				_Color;
	map<string, TText>	_Texts;
	UTextContext*		_TextContext;
	map<string, vector<string> >	_RandomsTexts; 

};

}

#endif

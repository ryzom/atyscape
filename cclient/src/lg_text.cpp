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

#include <nel/misc/ucstring.h>

#include "common.h"
#include "lg_text.h"

namespace LG
{


CText::CText(string name) : CWindow(name)
{
	Name = name;
	_Font = "!!!NO NAME!!!";
	_Color = CRGBA(255, 255, 255);
	isCreated = false;
	Visible = true;
}

void CText::setFont(string fontName)
{
	_Font = fontName;
}

void CText::addTextZone(string name, float x, float y, CRGBA color, uint32 fontSize, UTextContext::THotSpot hotSpot)
{
	nlinfo("add zone text (%s) at (%f, %f) with size : %i", name.c_str(),  x, y,  fontSize);
	TText text;
	text.Name = name;
	text.X = x;
	text.Y = y;
	text.Color = color;
	text.FontSize = fontSize;
	text.Effect = "";
	text.HotSpot = hotSpot;
	text.Message = "";
	_Texts.insert(make_pair(name, text));
}

void CText::delTextZone(string name)
{
	nlinfo("del zone text (%s)", name.c_str());
	_Texts.erase(name);
}

void CText::setText(string zone, const char * format, ...)
{
	char *str;
	NLMISC_CONVERT_VARGS (str, format, NLMISC::MaxCStringSize);
	_Texts[zone].Message = string(str);

}

void CText::setRandomText(const string &zone, const string &rtName)
{
	uint random = ((_RandomsTexts[rtName].size())*rand())/RAND_MAX;

	_Texts[zone].Message = _RandomsTexts[rtName][random]; 
	nlinfo("rtName = %s, # of rands = %i, selected text = %s", rtName.c_str(), _RandomsTexts[rtName].size(), _RandomsTexts[rtName][random].c_str());
}

string CText::getRandomText(const string &rtName)
{
	uint random = ((_RandomsTexts[rtName].size())*rand())/RAND_MAX;

	return _RandomsTexts[rtName][random]; 

}

void CText::setColor(const string &zone, CRGBA color)
{
	_Texts[zone].Color = color;
}

void CText::setPos(const string &zone, float x, float y)
{
	_Texts[zone].X = x;
	_Texts[zone].Y = y;
}

void CText::setFontSize(const string &zone, uint32 fontSize)
{
	_Texts[zone].FontSize = fontSize;
}

void CText::setProps(const string &zone, float x, float y, CRGBA color, uint32 fontSize, UTextContext::THotSpot hotSpot)
{
	_Texts[zone].X = x;
	_Texts[zone].Y = y;
	_Texts[zone].Color = color;
	_Texts[zone].FontSize = fontSize;
	_Texts[zone].Effect = "";
	_Texts[zone].HotSpot = hotSpot;
}

void CText::setEffect(const string &zone, const string &effect)
{
	_Texts[zone].Effect = effect;
}

void CText::create(CWindow* parent)
{
	if (_Font == "!!!NO NAME!!!")
	{
		nlerror("(%s), No Font Set : please call .setFont(FONT_NAME)", _Font.c_str());
	}
	_TextContext = _Driver->createTextContext(_Font);
	_TextContext->setShaded(true);
	_TextContext->setKeep800x600Ratio(false);
	isCreated = true;

}

void CText::loadRandomTexts(const string &filename)
{
	ifstream cwDef(filename.c_str());

	if (cwDef.is_open())
	{
		string line, rtName;
		vector<string> rtList;

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
				rtName = line.substr(1, line.length()-1);	
			}	
			else if (line[0] == '}')
			{
				_RandomsTexts.insert(make_pair(rtName, rtList));
				rtList.clear();
			}
			else if (!line.empty())
			{
				nlinfo("Add Random text : %s = %s", rtName.c_str(), line.c_str());
				rtList.push_back(line);
			}
		}
	}
}


void CText::show()
{
	Visible = true;
}

void CText::hide()
{
	Visible = false;
}

void CText::update()
{
	_Driver->clearBuffers(CRGBA (0, 0, 0));
	render();
	_Driver->swapBuffers();
}

void CText::render()
{
	if (Visible)
	{
		map<string, TText>::iterator ite;

		for (ite = _Texts.begin(); ite != _Texts.end(); ite++)
		{
			if (ite->second.Effect == "FadeOut") fxFadeOut(ite->second);
			else if (ite->second.Effect == "AlphaPingPong") fxAlphaPingPong(ite->second);
			else if (ite->second.Effect == "ZoomOut") fxZoomOut(ite->second);
			_TextContext->setHotSpot(ite->second.HotSpot);
			_TextContext->setColor(ite->second.Color);
			_TextContext->setFontSize(ite->second.FontSize);
			_TextContext->printAt(ite->second.X, ite->second.Y, ucstring(ite->second.Message));
		}
	}
}

void CText::fxFadeOut(TText &text)
{
	text.Color.A -= 5;
	if (text.Color.A <= 0)
	{
		text.Color.A = 0;
		text.Effect = "";
	}
}

void CText::fxAlphaPingPong(TText &text)
{
	if (text.FxValue == 0)
	{
		text.Color.A -= 5;
		if (text.Color.A <= 0)
		{
			text.Color.A = 0;
			text.FxValue = 1;
		}
	}
	else
	{
		text.Color.A += 5;
		if (text.Color.A >= 255)
		{
			text.Color.A = 255;
			text.FxValue = 0;
		}
	}
}

void CText::fxZoomOut(TText &text)
{
	text.Color.A -= 5;
	text.FontSize += 1;
	if (text.Color.A <= 0)
	{
		text.Color.A = 0;
		text.Effect = "";
	}
}
}

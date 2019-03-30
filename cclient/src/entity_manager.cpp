/** 
 * Atyscape Atys viewer	- Entity Creator
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

#include "entity_manager.h"
#include "utils.h"

CEntityManager::CEntityManager()
{
}

void CEntityManager::init(TSharedComponents share)
{
	_SC = share;
	_AvatarConf.load("user/avatars/list.cfg");
}
	
string CEntityManager::getKeyCodesOfAvatar(uint avatarId)
{
	if (avatarId < 5)
	{
		string avatarIdStr;
		stringstream out;
		out << avatarId;
		avatarIdStr = "Avatar"+out.str();

		return _AvatarConf.getVar(avatarIdStr).asString();
	}
	else
	{
		return "_undefined_	_homin_	xm***	xm*f***	xmnp***	xmnb***	xmns***	xm*ch**	xmng***	xmnv***";
	}
}

void CEntityManager::saveKeyCodesOfAvatar(uint avatarId, const string &keyCodes)
{
	string avatarIdStr;
	stringstream out;
	out << avatarId;
	avatarIdStr = "Avatar"+out.str();

	_AvatarConf.getVar(avatarIdStr).setAsString(keyCodes);
	_AvatarConf.save();
}

void CEntityManager::loadShapeDefs(const string &filename)
{
	string line, shapeName;
	ifstream shapeDesc(filename.c_str());

	_ShapeArray.clear();
	if (shapeDesc.is_open())
	{
		while (!shapeDesc.eof())
		{
			getline(shapeDesc, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if (line[0] == '{')
			{
				shapeName = line.substr(1, line.length()-1);
			}
			else if (line[0] == '}')
			{
			}
			else if (!line.empty())
			{
				_ShapeArray.insert(make_pair(shapeName, line));
			}
		}
	}
	shapeDesc.close();
}

void CEntityManager::loadSkelDefs(const string &filename)
{
	string line, skelName;
	ifstream skelDesc(filename.c_str());

	_SkelArray.clear();
	if (skelDesc.is_open())
	{
		while (!skelDesc.eof())
		{
			getline(skelDesc, line);

#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX

			if (line[0] == '{')
			{
				skelName = line.substr(1, line.length()-1);
			}
			else if (line[0] == '}')
			{
			}
			else if (!line.empty())
			{
				_SkelArray.insert(make_pair(skelName, line));
				nlinfo("add skel %s = %s", skelName.c_str(), line.c_str());
			}
		}
	}
	skelDesc.close();
}

void CEntityManager::loadTexDefs(const string &filename)
{
	string line, texName;
	ifstream texDesc (filename.c_str());
	TtexList texList;

	_TexArray.clear();
	if (texDesc.is_open())
	{
		while (!texDesc.eof())
		{
			getline(texDesc, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if (line[0] == '{')
			{
				texList.clear();
				texName = line.substr(1, line.length()-1);
			}
			else if (line[0] == '}')
			{
				_TexArray.insert(make_pair(texName, texList));
			}
			else if (!line.empty())
			{
				texList.push_back(line);
			}
		}
	}
	texDesc.close();
}

void CEntityManager::loadOffsets( const string& filename )
{
	string line, race ;
	float offset ;
	ifstream offsetDesc(filename.c_str());

	_Offsets.clear();
	if (offsetDesc.is_open())
	{
		while (!offsetDesc.eof())
		{
			getline(offsetDesc, line);
#ifdef NL_OS_UNIX
			// to remove windows' endls (\r\n) under unix systems
			if (line[line.size()-1] == 13) {
				line = line.substr(0, line.size()-1) ;
			}
#endif // NL_OS_UNIX
			if (line[0] == '{')
			{
				race = line.substr(1, line.length()-1) ;
			}
			else if (line[0] == '}')
			{
			}
			else if (!line.empty())
			{
				fromString(line.substr(0, line.length()), offset) ;
				nldebug("race = %s, offset = %f", race.c_str(), offset) ;
				_Offsets.insert(make_pair(race, offset));
			}
		}
	}
	offsetDesc.close();
}

CAnimated *CEntityManager::createNewEntity(const string &name, const string &defs, uint offset)
{ 

	vector<string> tokens;
	tokenizer(defs, tokens, "\t");

	CAnimated *newAnimated = new CAnimated(_SC, name);
	string keyCodes;

	
	string skelFile = tokens[offset];
	
	keyCodes = "";
	for (uint i=0; i < offset; i++)
	{
		keyCodes += tokens[i] + "\t";
	}
	keyCodes += tokens[offset];

	newAnimated->init(_SkelArray[skelFile]);

	string id = "*";
	for(vector<string>::iterator i = tokens.begin() + offset + 1; i != tokens.end(); ++i)
	{
		string line;

		line = string((*i));
		nlinfo("TEX!!! : %s", line.c_str());
		string subline = string(line);
		uint pos = line.length();
		string stars = "";
		map<string, string>::iterator ite;
		ite = _ShapeArray.find(subline);
		while ((pos > 0) && (ite == _ShapeArray.end()))
		{
			subline = subline.substr(0, pos);
			stars += "*";
			pos--;
			nlinfo(subline.c_str());
			ite = _ShapeArray.find(subline);
		}

		keyCodes += "\t" + line ;
		newAnimated->setShape(id, _ShapeArray[subline], _TexArray[line]);
		id += "*";
	}
	newAnimated->loadAnimations();
	newAnimated->setKeyCodes(keyCodes);
	return newAnimated;

}

void CEntityManager::changeEntityShape(CAnimated *animated, const string &defs, uint offset)
{
	
	vector<string> tokens;

	tokenizer(defs, tokens, "\t");

	string id = "*";
	string keyCodes;

	keyCodes = "";
	for (uint i=0; i <= offset; i++)
	{
		keyCodes += tokens[i] + "\t";
	}

	nlinfo("(%s)", defs.c_str());
	animated->changeSkel(_SkelArray[tokens[offset]]);
	animated->reset();
	for(vector<string>::iterator i = tokens.begin() + offset + 1; i != tokens.end(); ++i)
	{
		string subline = string((*i));
		uint pos = (*i).length();
		string stars = "";
		map<string, string>::iterator ite;
		ite = _ShapeArray.end();
		while ((pos > 0) && (ite == _ShapeArray.end()))
		{
			subline = subline.substr(0, pos);
			stars += "*";
			pos--;
			nlinfo(subline.c_str());
			ite = _ShapeArray.find(subline);
		}
		keyCodes += (*i) + "\t";
		animated->setShape(id, _ShapeArray[subline], _TexArray[(*i)]);
		id += "*";
	}
	animated->setKeyCodes(keyCodes);
}

void CEntityManager::deleteEntity(CAnimated *animated)
{
	animated->changeSkel("");
}

float CEntityManager::getOffset( const string& keyCode ) const {
	vector<string> tokens;
	tokenizer(keyCode, tokens, "\t");
	if (tokens.size() > 2 && !tokens.at(1).empty()) {
		map<string,float>::const_iterator it = _Offsets.find(tokens.at(2)) ;
		if (it != _Offsets.end()) {
			nlinfo("keycode = %s, offset = %f", keyCode.c_str(), it->second) ;
			return it->second ;
		}
	}
	else {
		nlwarning("Unreadable avatar code, can not read offset") ;
	}

	return 0.f ;
}

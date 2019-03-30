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

#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <nel/misc/singleton.h>

#include "animated.h"

typedef vector<string> TtexList;

class CEntityManager : public CSingleton<CEntityManager>
{
public:
	CEntityManager();
	void init(TSharedComponents share);
	void loadShapeDefs(const string &filename);
	void loadSkelDefs(const string &filename);
	void loadTexDefs(const string &filename);
	
	/// Loads from file and fills _AvatarOffsets
	void loadOffsets(const string &filename) ;
	
	CAnimated *createNewEntity(const string &name, const string &defs, uint offset = 0);
	void deleteEntity(CAnimated *animated);
	void changeEntityShape(CAnimated *animated, const string &defs, uint offset = 0);
	string getKeyCodesOfAvatar(uint avatarId);
	void saveKeyCodesOfAvatar(uint avatarId, const string &keyCodes);

	/// \returns The offset of the entity keycode given
	float getOffset( const string& keyCode ) const ;

private:
	TSharedComponents		_SC;
	map<string, string>		_ShapeArray;
	map<string, string>		_SkelArray;
	map<string, TtexList>	_TexArray;
	vector<CAnimated *>		_Animateds;
	vector<string>			_KeyCodes;

	/// To place correctly the entities against the floor
	map<string,float>		_Offsets ;

protected:
	friend class CMakeAvatarMode;
	friend class CSelAvatarMode;

	CConfigFile			_AvatarConf;
};


#endif

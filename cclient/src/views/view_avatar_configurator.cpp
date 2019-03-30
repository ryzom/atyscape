/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	View of Avatar Configurator
	____________________________________________________________________

	This file is part of Ryturn Home Crafted MMORPG.

    Ryturn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ryturn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ryturn.  If not, see <http://www.gnu.org/licenses/>.
	____________________________________________________________________

 */

#include "view_avatar_configurator.h"

CViewAvatarConfigurator::CViewAvatarConfigurator()
{
}

void CViewAvatarConfigurator::init()
{
	// Main window
	_Configurator = new CConfigurator("ViewAvatarConfigurator");
	_Configurator->setDefsFile("data/tmpl/homin.tmpl", "data/i18n/tmpl/homin_tmpl_fr.txt");

	_Configurator->create(CWindowManager::getInstance().getRoot());
	_Configurator->setPos(0.5f, 0.05f);
	_Configurator->setExpand(0.4f, 0.9f);

	// Mods
	_ModAvatar = &CModAvatar::getInstance();
	_Configurator->setRandomKeyCodes();
	_ModAvatar->init(_Configurator->getKeycodes());

	// Callbacks of configurator
	_Configurator->setCallback("ListBox", new CCallback(&CModAvatar::setKeyCodes, _ModAvatar));
	_Configurator->setCallback("Ok", new CCallback(&CModAvatar::saveKeyCodes, _ModAvatar));
	_Configurator->setCallback("randomEvent", new CCallback(&CViewAvatarConfigurator::setRandomKeyCodes, this));
}

bool CViewAvatarConfigurator::setRandomKeyCodes(const string &event)
{	
	_Configurator->setRandomKeyCodes();
	_ModAvatar->setKeyCodes(_Configurator->getKeycodes());
	return true;
}

void CViewAvatarConfigurator::render()
{
}


/** 
	   ___ __  __ ______ __  __ ___   _  __
	  / _ \\ \/ //_  __// / / // _ \ / |/ /
	 / , _/ \  /  / /  / /_/ // , _//    / 
	/_/|_|  /_/  /_/   \____//_/|_|/_/|_/

	____________________________________________________________________

	Module for Nel Audio Component
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

#include "mod_audio.h"

CModAudio::CModAudio()
{
}

void CModAudio::init()
{
	vector< pair<string, uint> > samples;
	vector<TStringId> soundNames;

	AudioMixer = UAudioMixer::createAudioMixer();
	// For test on windows (maybe FMod exists on Unix systems)
	AudioMixer->init(32, false, false, NULL, false, NLSOUND::UAudioMixer::DriverFMod, true);
	AudioMixer->getLoadedSampleBankInfo(samples);
	AudioMixer->getSoundNames(soundNames);
	//AudioMixer->playMusic("Main Menu Loop.ogg");
	//USource* audioSource = AudioMixer->createSource(soundNames[828]);
	//audioSource->setLooping(true);
	//audioSource->play();
	// !!! Test !!!
	//AudioMixer->loadSampleBank(true, "_creatures_ambiance", &samples);
	for (uint i=0; i < soundNames.size(); i++)
	{
		//nlinfo("sample : %s", soundNames[i]->c_str());
	}
	//
}

uint CModAudio::update()
{
	AudioMixer->update();
	return 0;
}
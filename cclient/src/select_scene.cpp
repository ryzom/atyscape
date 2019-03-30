/** 
 * Atyscape Atys viewer - Location selector 
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
#include "select_scene.h"

using namespace std;
using namespace NLMISC;
using namespace NL3D;


CLocationSelect::CLocationSelect(TSharedComponents share) {
	//_SC = share;
	//State = 0;
	//_CurRegion = 0;
	//_CurPoint = 0;
//	_Writer = _Driver->createTextContext("font.pfb");
//	_Writer->setHotSpot(UTextContext::TopLeft);	
}

CLocationSelect::~CLocationSelect() {
//	_SC.Driver->deleteTextContext(_Writer);
}

void CLocationSelect::update() {
	//CEventListenerAsync* al = &_SC.Driver->AsyncListener;

	//if (al->isKeyPushed(KeyDOWN) ) {
	//	if (State == 0 && (_CurRegion+1) < _SC.Config->Regions.size()) {
	//		_CurRegion++;
	//	} else if (State == 1 && (_CurPoint+1) < SelectedRegion.Points.size()){
	//		_CurPoint++;
	//	}
	//} else if (al->isKeyPushed(KeyUP) ) {
	//	if (State == 0 && _CurRegion > 0) {
	//		_CurRegion--;
	//	} else if (State == 1 && _CurPoint > 0) {
	//		_CurPoint--;
	//	}
	//} else if (al->isKeyPushed(KeyRETURN) || State == 0 && al->isKeyPushed(KeyRIGHT)) {
	//	if (State == 0) {
	//		State = 1;
	//		SelectedRegion = _SC.Config->Regions[_CurRegion];
	//	} else if (State == 1) {
	//		State = 2;
	//		SelectedPoint = SelectedRegion.Points[_CurPoint];
	//	}
	//} else if (al->isKeyPushed(KeyLEFT) && State == 1) {
	//	State = 0;
	//}
}

void CLocationSelect::render() {
	//_SC.Driver->clearBuffers (CRGBA (0, 0, 0));
	//CRGBA white = CRGBA(255, 255, 255);
	//CRGBA red = CRGBA(255, 0, 0);

	//_SC.Ui->Text->addTextZone("
	//setFontSize (18);
	//_SC.Ui->textSetColor(white);
	//if (State == 0) {
	//	_SC.Ui->writeText(0.1f, 0.99f, "Choose a starting region");
	//} else if (State == 1) {
	//	_SC.Ui->writeText(0.1f, 0.99f, "Choose a starting point in region %s", SelectedRegion.Name.c_str());
	//}
	//_SC.Ui->setFontSize(14);

	//if (State == 1) {
	//	_SC.Ui->writeText(0.1f, 0.90f, "Press <- to go back");
	//}
	//	
	//for (uint i = 0; i < _SC.Config->Regions.size(); i++) {
	//	if (i == _CurRegion)	_SC.Ui->textSetColor(red);
	//	else _SC.Ui->textSetColor(white);
	//	_SC.Ui->writeText(0.1f, 0.80f - (float)(0.04f*i), "%s", _SC.Config->Regions[i].Name.c_str());
	//}

	//if (State >= 1) {
	//	for (uint i = 0; i < SelectedRegion.Points.size(); i++) {
	//		if (i == _CurPoint)	_SC.Ui->textSetColor(red);
	//		else _SC.Ui->textSetColor(white);
	//		_SC.Ui->writeText(0.5f, 0.80f - (float)(0.04f*i), "%s", SelectedRegion.Points[i].Name.c_str());
	//	}
	//}
	//_SC.Driver->swapBuffers();
}

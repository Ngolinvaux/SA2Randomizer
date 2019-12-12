#include "stdafx.h"
#include "FogRando.h"


Fog currentFog;
Fog dynamicFog;

bool rFogChecked = false;

bool checkFog() {
	//for(int i = 0; i < 3; i++) if (myFogData->argb[i] != dynamicFog.argb[i]) return false;
	if (dynamicFog.minDist != myFogData->minDist) return false;
	if (dynamicFog.maxDist != myFogData->maxDist) return false;
	return true;
}

void createDynamicFog() {
	dynamicFog.argb[0] = (char)rand() % 256;
	dynamicFog.argb[1] = (char)rand() % 256;
	dynamicFog.argb[2] = (char)rand() % 256;

	dynamicFog.minDist = (float)0 - (rand() % 100);
	dynamicFog.maxDist = (float)(rand() % 500) * 10;

}


void updateFog() {
	if (checkFog()) createDynamicFog();

	/*if (rFogColor) {
		for (int i = 0; i < 3; i++) {
			unsigned __int8 n = 256 - dynamicFog.argb[i];
			unsigned __int8 c = 256 - myFogData->argb[i];
			if (n > c) myFogData->argb[i]+= (char)1;
			if (n < c) myFogData->argb[i]-= (char)1;
			//PrintDebug(std::to_string(dynamicFog.argb[i] - myFogData->argb[i]).c_str());
		}
	}*/
	if (rFogChecked) {
		if (dynamicFog.minDist > myFogData->minDist) myFogData->minDist++;
		if (dynamicFog.minDist < myFogData->minDist) myFogData->minDist--;
		if (dynamicFog.maxDist > myFogData->maxDist) myFogData->maxDist += 10;
		if (dynamicFog.maxDist < myFogData->maxDist) myFogData->maxDist -= 10;
	}
}


void randomizeFogColor() {
	rFogChecked = true;
	myFogData->argb[0] = (char)rand() % 256;
	myFogData->argb[1] = (char)rand() % 256;
	myFogData->argb[2] = (char)rand() % 256;

	currentFog.argb[0] = myFogData->argb[0];
	currentFog.argb[1] = myFogData->argb[1];
	currentFog.argb[2] = myFogData->argb[2];
	dynamicFog = currentFog;
}

void randomizeFog() {
	myFogData->minDist = (float)30 - (rand() % 70);
	myFogData->maxDist = (float)(rand() % 500) * 10;
	myFogData->fogParam = (unsigned __int16)rand() % 2 + 2;
	myFogData->fogType = (unsigned __int16)2;

	currentFog.minDist = myFogData->minDist;
	currentFog.maxDist = myFogData->maxDist;
	dynamicFog = currentFog;
}

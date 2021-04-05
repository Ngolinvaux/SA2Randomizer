// SA2CharSel.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "HelperFuns.h"


extern "C"
{

	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions) {}

	__declspec(dllexport) void OnFrame()
	{

		if (MainCharObj1[0]) {
			if (MainCharObj1[0]->Status & Status_Ground && GameState == 16 && MainCharObj1[0]->Action!= Action_Grind && MainCharObj1[0]->Action != Action_Fall && MainCharObj1[0]->NextAction != Action_Fall) {
				MainCharObj1[0]->Status = Status_Hurt;
			}
		}
		if (RingCount[0] > 0) RingCount[0] = 0;
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };


}
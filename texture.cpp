// SA2CharSel.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include "SA2ModLoader.h"
#include <string>

extern "C"
{
	__declspec(dllexport) void OnFrame()
	{
		if(CurrentLevel == LevelIDs_HiddenBase)PrintDebug(std::to_string(CurrentDeathZones[0].Flags).c_str());
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };

}
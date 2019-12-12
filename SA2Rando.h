#pragma once
#include <stdint.h>
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/MemAccess.h"
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/SA2Structs.h"
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/SA2Enums.h"
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/ninja.h"
#include <string>
#include "SA2RStructs.h"
#include <Mmsystem.h>
#include <mciapi.h>
#include <filesystem>
#include <iostream>
#include <locale>
#include <cctype>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
//SA2R Variables
DataArray(struct_a1R, ChaoKarateOpponentsR, 0x1296C10, 28);
DataPointer(char, voiceLineLang, 0x174AFD2);
DataPointer(char, CCFlag, 0x174b02B);
DataPointer(const int, MHTimer1, 0x006f41c6);
DataPointer(const int, MHTimer2, 0x006f41d4);
DataPointer(const int, MHTimer3, 0x006f41db);
DataPointer(const int, MHTimer4, 0x006f443b);
DataPointer(const int, MHTimerMinus660, 0x006f43f9);

DataPointer(int, StageMessageCount, 0xB5D200);
DataPointer(char**, StageMessageList, 0x1AEFD6C);
DataPointer(char**, SysMessageList, 0x1AEFD70);
DataPointer(int, SysMessageCount, 0xB5D204);
DataArray(RaceBotData, ChaoRaceOpponents, 0x011CE2A0, 115);

DataPointer(char, KartTimer, 0x1D9442C);
DataArray(KartPtr, tracks, 0xef82bc, 6);
DataPointer(char, StageSelectLocked, 0x1D1BC02);
DataPointer(int, CameraMode, 0x1DCFF4C);
DataPointer(Fog*, myFogData, 0x1AEFEA4);
DataPointer(int, CameraFOV, 0x1DCFF40);
DataPointer(char, LevelComplete, 0x174B002);
DataPointer(DemoInput, DemoInputStart, 0x024CFE20);
DataPointer(char, ESG, 0x174B08C);
DataArray(char, ChaoRacesBeaten, 0x019F6BF3, 13);
DataPointer(ChaoDataBaseGap, Chao1Data, 0x019F6ED6);
DataPointer(ChaoDataBaseGap, Chao2Data, 0x019F76D6);
DataPointer(ChaoDataBaseGap, Chao3Data, 0x019F7ED6);
DataPointer(ChaoDataBaseGap, Chao4Data, 0x019F86D6);

DataArray(ChaoDataBaseGap, ChaoDataAll, 0x019F6ED6, 24);
DataArray(M4Timer, m4timers, 0x173B318, 30);
DataPointer(char, SHTimer, 0x4520AB);

DataArray(BlackMarketItems, BlackMarketSlots, 0x1DBEDC0, 32);
DataPointer(char, M4Centis, 0x173CAD8);
DataPointer(char, M4Seconds, 0x173CA98);
DataPointer(char, M4Minutes, 0x173CA58);


DataArray(KartData, kartAlts, 0xffa058, 6);
DataArray(KartData, karts, 0xff9ef0, 8);
DataPointer(int, levelTimer, 0x019457F8);
DataPointer(bool, controlActive, 0x174AFFE);
DataPointer(float, CameraX, 0x1DCFF0C);
DataPointer(float, CameraY, 0x1DCFF10);
DataPointer(float, CameraZ, 0x1DCFF14);
DataPointer(int, CameraXRot, 0x1DCFF18);
DataPointer(int, CameraYRot, 0x1DCFF1C);
DataPointer(int, CameraZRot, 0x1DCFF20);

DataArray(CreditEntry, Credits, 0x966400, 549);
DataArray(LevelLookupEntry, Levellist, 0x0173A148, 113);










#define ObjectFunc(NAME, ADDRESS) FunctionPointer(void,NAME,(ObjectMaster *obj),ADDRESS)
// SA2R Functions

ObjectFunc(sub_6BE2E0, 0x6BE2E0);

FunctionPointer(ObjectMaster*, displayText, (int a1, const char* message, int displayTime, int language), 0x6B6E20);
FunctionPointer(char**, LoadMessageFile, (const char* filename, int* count), 0x6F1E80);
VoidFunc(ReleaseMessageLists, 0x6BD5D0);



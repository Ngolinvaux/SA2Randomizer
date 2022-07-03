#pragma once
#include <stdint.h>
#include "MemAccess.h"
#include "SA2Structs.h"
#include "SA2Enums.h"
#include "ninja.h"
#include "AnimationFile.h"
#include "GameObject.h"
#include "LandTableInfo.h"
#include "ModelInfo.h"
#include "Trampoline.h"



#include <string>
#include "SA2RStructs.h"
#include "SA2RStructs.h"
#include <Mmsystem.h>
//#include <mciapi.h>
#include <filesystem>
#include <iostream>
#include <locale>
#include <cctype>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
//SA2R Variables

//Eggman
DataArray(ObjectListEntry, IronGateObjs, 0xbed8f0, 0x5b);
DataArray(ObjectListEntry, SandOceanObjs, 0xd00c80, 0x58);
DataArray(ObjectListEntry, LostColonyObjs, 0x9fee78, 0x4f);
DataArray(ObjectListEntry, WeaponsBedObjs, 0x9cc1f8, 0x55);
DataArray(ObjectListEntry, CosmicWallObjs, 0xeae9c8, 0x4c);
DataArray(ObjectListEntry, CCEggmanObjs, 0x1445a98, 0x51);

//Rouge
DataArray(ObjectListEntry, DryLagoonObjs, 0xdeb558, 0x61);
DataArray(ObjectListEntry, EggQuartersObjs, 0xc45500, 0x5d);
DataArray(ObjectListEntry, SecurityHallObjs, 0xe8cc00, 0x54);
DataArray(ObjectListEntry, MadSpaceObjs, 0xd9b670, 0x5c);
DataArray(ObjectListEntry, CCRougeObjs, 0x16132c8, 0x4f);

//Shadow
DataArray(ObjectListEntry, RadicalHighwayObjs, 0x158d750, 0x5b);
DataArray(ObjectListEntry, WhiteJungleObjs, 0xe995d0, 0x52);
DataArray(ObjectListEntry, SkyRailObjs, 0x1178038, 0x54);
DataArray(ObjectListEntry, FinalChaseObjs, 0x1178038, 0x53);

//Knuckle
DataArray(ObjectListEntry, WildCanyonObjs, 0xbd7440, 0x54);
DataArray(ObjectListEntry, PumpkinHillObjs, 0x1689818, 0x57);
DataArray(ObjectListEntry, AquaticMineObjs, 0x1638760, 0x6e);
DataArray(ObjectListEntry, DeathChamberObjs, 0xBA5130, 0x5f);
DataArray(ObjectListEntry, MeteorHerdObjs, 0x1155B08, 0x5c);
DataArray(ObjectListEntry, CCKnuxObjs, 0xCCE0B8, 0x53);

//Tails
DataArray(ObjectListEntry, PrisonLaneObjs, 0x104BDD8, 0x62);
DataArray(ObjectListEntry, MissionStreetObjs, 0x11B8528, 0x54);
DataArray(ObjectListEntry, HiddenBaseObjs, 0xA2D730, 0x58);
DataArray(ObjectListEntry, EternalEngineObjs, 0x983EC0, 0x5C);
DataArray(ObjectListEntry, CCTailsObjs, 0xE5E070, 0x53);

//Sonic
DataArray(ObjectListEntry, CityEscapeObjs, 0x109E830, 0x65);
DataArray(ObjectListEntry, MetalHarborObjs, 0xAEC550, 0x5C);
DataArray(ObjectListEntry, GreenForestObjs, 0x1085C30, 0x58);
DataArray(ObjectListEntry, PyramidCaveObjs, 0xAB6080, 0x5E);
DataArray(ObjectListEntry, CrazyGadgetObjs, 0x9BB0D0, 0x4E);
DataArray(ObjectListEntry, FinalRushObjs, 0x16A3D30, 0x56);
DataArray(ObjectListEntry, CCSonicObjs, 0x164A570, 0x52);
DataArray(ObjectListEntry, GreenHillZoneObjs, 0x10EDF28, 0x4B);


DataPointer(unsigned int, creditsCounter, 0x1a55650);
DataPointer(unsigned int, creditsSpeed, 0x1a55660);
DataPointer(unsigned int, creditsThing, 0x1a5565c);
DataPointer(ObjectMaster*, EfMsgWnd0, 0x1AEFD50);
DataPointer(char, chaoObjCount, 0x1DC0F80);
DataArray(ObjectMaster*, ChaoObjectArrayR, 0x1DC0FFC, 32);
DataArray(ChaoData*, ChaoDataArrayR, 0x1DC0FC8,32); // TODO: fix

DataPointer(NJS_ARGB, chaoStaminaMeter, 0x25effd0);
DataPointer(KnuxMemoryMap*, HuntingInfo, 0x01af014c);
DataArray(struct_a1R, ChaoKarateOpponentsR, 0x1296C10, 28);
DataArray(short, ChaoKarateOpponentsStats, 0x1296A50, 224);
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
//DataPointer(int, CameraMode, 0x1DCFF4C);
DataPointer(Fog*, myFogData, 0x1AEFEA4);
DataPointer(int, CameraFOV, 0x1DCFF40);
DataPointer(char, LevelComplete, 0x174B002);
DataPointer(DemoInput, DemoInputStart, 0x024CFE20);
DataPointer(char, ESG, 0x174B08C);
DataArray(char, ChaoRacesBeaten, 0x019F6BF3, 13);
DataArray(char, ChaoRacesActuallyBeaten, 0x019F6BE6, 13);

DataPointer(ChaoDataBaseGap, Chao1Data, 0x019F6ED6);
DataPointer(ChaoDataBaseGap, Chao2Data, 0x019F76D6);
DataPointer(ChaoDataBaseGap, Chao3Data, 0x019F7ED6);
DataPointer(ChaoDataBaseGap, Chao4Data, 0x019F86D6);

DataArray(ChaoDataBaseGap, ChaoDataAll, 0x019F6ED6, 24);
DataArray(ChaoDataBase, ChaoDataAllNoGap, 0x019F6ED6, 24);
DataArray(M4Timer, m4timers, 0x173B318, 30);
const char* SHTimer = (const char*)0x4520AB;

DataArray(BlackMarketItems, BlackMarketSlots, 0x1DBEDC0, 32);
DataPointer(char, M4Centis, 0x173CAD8);
DataPointer(char, M4Seconds, 0x173CA98);
DataPointer(char, M4Minutes, 0x173CA58);

DataArray(char, chaoCharacters, 0x1def829, 8);
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
DataPointer(NJS_VECTOR, Gravity_Direction, 0x01de94a0);
DataPointer(unsigned int, GravityRotX, 0x1de94ac);
DataPointer(unsigned int, GravityRotZ, 0x1de949c);
DataPointer(unsigned int, GravityRotY, 0x1945e08);
DataPointer(CharObj2Base, Boss2pMaybe, 0x01a51f0c);

DataArray(CreditEntry, Credits, 0x966400, 549);



DataArray(char, DigTableM2, 0xa132f8, 32);
DataArray(char, DigTable2P, 0xa132a8, 32);
DataArray(char, DigTable, 0xa13280, 32);






// SA2R Functions

ObjectFunc(sub_6BE2E0, 0x6BE2E0);


VoidFunc(loadAISVS1, 0x61a2b0);
VoidFunc(loadAISVS2, 0x4c8fc0);
VoidFunc(loadAIKVR, 0x64b6c0);
VoidFunc(loadAITVE1, 0x627c30);
VoidFunc(loadAITVE2, 0x663900);


FunctionPointer(void,globalToRelativeForces,(GlobalMetricStruct* a, CharObj2Base* a2, EntityData1* a3) ,0x45f9e0);
FunctionPointer(ObjectMaster*, displayText, (int a1, const char* message, int displayTime, int language), 0x6B6E20);
//FunctionPointer(ef_message_cheat*, displayText, (int a1, const char* message, int displayTime, int language), 0x6B6E20);
FunctionPointer(char**, LoadMessageFile, (const char* filename, int* count), 0x6F1E80);
VoidFunc(ReleaseMessageLists, 0x6BD5D0);
FunctionPointer(void, spawnBigFoot, (NJS_VECTOR *pos), 0x5CC350);
FunctionPointer(void, spawnFlyingDog, (NJS_VECTOR *pos), 0x5d0d70);
FunctionPointer(void, spawnHotShot, (NJS_VECTOR *pos), 0x5c7120);
FunctionPointer(void, loadStageStuffIDK, (), 0x43c970);
FunctionPointer(void, loadBossRel, (char* string), 0x4549c0);




FunctionPointer(void, loadMechBossTextures, (int type), 0x5c7000);// 0:BigFoot 1:HotShot 2:FlyingDog
FunctionPointer(void, spawnEggGolemHero, (NJS_VECTOR *pos), 0x4be1a0);
FunctionPointer(void, spawnFinalHazard, (), 0x499320);
FunctionPointer(void, spawnBigBogy, (NJS_VECTOR *pos, int yRot, NJS_VECTOR* center), 0x60b1e0);



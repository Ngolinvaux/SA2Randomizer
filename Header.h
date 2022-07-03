#pragma once
#include <stdint.h>
#include "MemAccess.h"
#include "SA2Structs.h"
#include "SA2Enums.h"
#include "ninja.h"
#include <string>

//SA2R Variables
DataPointer(char, voiceLineLang, 0x174AFD2);
DataPointer(byte, CCFlag, 0x174b02B);
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
DataPointer(ChaoDataBase, Chao1Data, 0x019F6ED6);
DataPointer(ChaoDataBase, Chao2Data, 0x019F76D6);
DataPointer(ChaoDataBase, Chao3Data, 0x019F7ED6);
DataPointer(ChaoDataBase, Chao4Data, 0x019F86D6);

DataArray(ChaoDataBase, ChaoDataAll, 0x019F6ED6, 24);
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



typedef void(__cdecl* ObjectFuncPtr)(ObjectMaster*);
//SA2R Structs
// All structs should be packed.
#pragma pack(push, 1)
struct SubtitleQueue {
	std::string text;
	int time;
	int ogID;
};

struct KartPtr {
	void* ptr;
	int len;
};


struct M4Timer {
	char level;
	char min;
	char sec;
};


struct KartSegment {
	byte segmentID;
	NJS_VECTOR endPos;
	unsigned short yRot;
	NJS_VECTOR center;
	float radius;
};

struct KartCourseModel {
	byte model_ptr[4];
	byte collision_ptr[4];
	NJS_VECTOR end_point;
	int y_rot;
	byte gap[84];

};


struct ChaoRealData {
	byte name[7];
	byte swimFraction;
	byte flyFraction;
	byte runFraction;
	byte powerFraction;
	byte stamFraction;

	byte swimGrade;
	byte flyGrade;
	byte runGrade;
	byte powerGrade;
	byte stamGrade;

	byte swimLevel;
	byte flyLevel;
	byte runLevel;
	byte powerLevel;
	byte stamLevel;

	short swimStat;
	short flyStat;
	short runStat;
	short powerStat;
	short stamStat;

	byte type;
	byte garden;
	byte reincarnate;//255=yes
	byte clocks;
	short remainingTime;
	int lifeClock; //max 120
	float powerRun;//pos = power, neg = run
	float flySwim;//pos = fly, neg = swim
	float evol;//1 = evolve
	byte eye;
	byte mouth;
	byte ball;
	byte headgear;
	byte feet;
	byte medal;
	byte color;
	byte highlights;
	byte jewel;
	byte shiny;//boolean
	byte eggColor;
	byte model;
	byte happy;// (-100,100)

};


struct KartData {
	float accel;
	float breakForce;
	float letOffGas;
	float maxDriveSpeed;
	float gravity;
	float unknown1;
	float drift_factor; //[1, 1.5]
	float drift_treshold;
	float unknown2;
	float speed_cap;
};


struct CreditEntry {
	int type;
	float alpha;
	float red;
	float green;
	float blue;
	const char* text;
};

struct DemoInput
{
	int buttons;
	int buttonsP2;
	int pressed;
	int pressedP2;
	short joyX;
	short joyXP2;
	short joyY;
	short joyYP2;
	bool stick_pushed;
	bool stick_pusedP2;
	bool gap;
	bool gapP2;
	int angle;
	float mag;
	int angleP2;
	float magP2;
};

struct LevelLookupEntry {
	char entry_type;
	char character_id;
	short level_id;
	short cutscene_events[4];
};

#pragma pack(pop)
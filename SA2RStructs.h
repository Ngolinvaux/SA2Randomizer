#pragma once
#include <stdint.h>
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/ninja.h"
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/SA2Enums.h"
#include <string>
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/MemAccess.h"
#include "D:/Steam/steamapps/common/Sonic Adventure 2/programming/SA2Structs.h"


struct struct_a1R;
struct Fog;
struct BlackMarketItems;
struct __declspec(align(1)) ChaoDataBaseGap;
struct setObj;
struct TwitchMsg;
struct TwitchChatter;
struct RaceBotData;
struct ChaoDataBase;

struct SubtitleQueue;
struct KartPtr;

struct M4Timer;
struct KartSegment;
struct KartCourseModel;
struct ChaoRealData;
struct KartData;
struct CreditEntry;

struct DemoInput;

struct LevelLookupEntry;
struct KnuxMemoryMap;
struct Emerald;
struct GlobalMetricStruct;
typedef void(__cdecl* ObjectFuncPtr)(ObjectMaster*);
typedef void(__cdecl* ObjectListPtr)(ObjectListEntry*);


//SA2R Structs
// All structs should be packed.
#pragma pack(push, 1)


struct MCO2 {
	char gap[0xB8];
	LoopHead* path;
};





struct ef_message_cheat {
	ObjectMaster* PrevObject;
	ObjectMaster* NextObject;
	ObjectMaster* Parent;
	ObjectMaster* Child;
	ObjectFuncPtr MainSub;
	ObjectFuncPtr DisplaySub;
	ObjectFuncPtr DeleteSub;
	ObjectFuncPtr field_1C;
	ObjectFuncPtr field_20;
	ObjectFuncPtr SomethingSub;
	ObjectFuncPtr field_28;
	void* field_2C;
	SETObjectData* SETData;
	ef_message_b* ef;
	UnknownData2* EntityData2;
	ObjUnknownA* UnknownA_ptr;
	Data2Ptr Data2;
	char* Name;
	char* NameAgain;
	void* field_4C;
	
};

struct __declspec(align(8)) KarateChaoExec_Data2
{
	__int16 char0;
	__int16 isopponent;
	__int16 flag;
	__int16 rival;
	ObjectMaster* pointerToChao;
	void* currActionInfo;
	ChaoData* chaoDataPointer;
	int field_14;
	NJS_VECTOR* BaseTranslationPos;
	NJS_VECTOR* HeadTranslationPos;
	float SwimStat;
	float FlyStat;
	float RunStat;
	float PowerStat;
	float field_30;
	float field_34;
	float zeal;
	float StaminaStat;
	float LuckStat;
	float float44;
	float field_48;
};



struct MechEggmanCharObj2R
{
	CharObj2Base base;
	//char field_1BC[128];
	char field_1BC[124];
	NJS_VECTOR laserPos;
	NJS_VECTOR gunPos;
	NJS_VECTOR weirdCannonRot;
	char field_260[120];
	NJS_VECTOR weirdCannonOffset;
	NJS_VECTOR gunRot;
	NJS_VECTOR laserRot;
	char field_2FC[96]; //first 12 bytes look like another rotation
	char field_35C;
	char field_35D;
	char field_35E;
	char field_35F;
	char field_360;
	char field_361[3];
	__int16 laserTimer;
	__int16 stopLockTimer;
	__int16 numberOfLocks;
	__int16 numOfTargetsYetToKill; //only counts after release
	__int16 field_36C;//appears to be the laser balls animation frame or something, default 8, lower works. higher doesnt spawn ball
	__int16 field_36E;
	char field_370[4];
	float field_374;
	char field_378[8];
	int field_380;//changes on lockon
	char field_384[12];
	NJS_VECTOR lockOnLoc;
	int field_39C;//lock on rot?
	char field_3A0[132];
	int field_424;//interesting rot after shot
	int UpperBodyRot;//upper body rot
	int field_42C;//always counts up
	int field_430;
	int field_434;
	NJS_VECTOR something;
	NJS_TEXLIST* CommonTextureList;
	NJS_TEXLIST* TextureList;
	ModelIndex* ModelList;
	AnimationIndex* MotionList;
};


struct Ai {
	float a[110];
};


struct GlobalMetricStruct {
	NJS_VECTOR global_speed;
	NJS_VECTOR applied_force;
	int rotX;
	int rotY;
	int rotZ;
};


struct ModelCredits {
	std::string name;
	std::string creator;
};


struct Fog {
	unsigned __int16 fogType; //usually 02
	unsigned __int16 fogParam; //usually 02
	char argb[4]; //alpha ignored  actually stored as bgra
	float maxDist;
	float minDist;
};

struct Emerald {
	int id;
	NJS_VECTOR position;
};


struct KnuxMemoryMap {
	char state;
	char gap[2];
	char hintsRead;
	char veryClose;
	char emeraldsSpawned;
	char p1ArrayLen;
	char p2ArrayLen;
	char p3ArrayLen;
	char pEnemyArrayLen;
	char gap2[2];
	Emerald u1;
	Emerald u2;
	Emerald p1;
	Emerald p2;
	Emerald p3;
	Emerald* p1List;
	Emerald* p2List;
	Emerald* p3List;
	Emerald* pEnemyList;
	int timer;

};



struct BlackMarketItems
{
	char Category;
	char Type;
};

struct __declspec(align(1)) ChaoDataBaseGap
{
	//char gap_0[18];
	char Name[7];
	char gap_19[7];
	char SwimFraction;
	char FlyFraction;
	char RunFraction;
	char PowerFraction;
	char StaminaFraction;
	char LuckyFraction;
	char IntelligenceFraction;
	char UnknownFraction;
	char SwimGrade;
	char FlyGrade;
	char RunGrade;
	char PowerGrade;
	char StaminaGrade;
	char LuckGrade;
	char IntelligenceGrade;
	char UnknownGrade;
	char SwimLevel;
	char FlyLevel;
	char RunLevel;
	char PowerLevel;
	char StaminaLevel;
	char LuckLevel;
	char IntelligenceLevel;
	char UnknownLevel;
	__int16 SwimStat;
	__int16 FlyStat;
	__int16 RunStat;
	__int16 PowerStat;
	__int16 StaminaStat;
	__int16 LuckStat;
	char IntelligenceStat;
	char UnknownStat;
	char field_46[58];
	//ChaoType Type;
	__int8 Type;
	char Garden;
	char reincarnate;
	char blank1;
	char blank2;
	char blank4;
	char ClockRollovers;
	char field_88;
	short Lifespan;
	char blank3[26];
	int LifeClock;
	float PowerRun;
	float FlySwim;
	char gap_B4[12];
	float EvolutionProgress;
	char gap_C4[17];
	char EyeType;
	char MouthType;
	char BallType;
	char gap_D4[1];
	char Headgear;
	char HideFeet;
	char Medal;
	char Color;
	char MonotoneHighlights;
	char Texture;
	char Shiny;
	char EggColor;
	//SADXBodyType BodyType;
	char BodyType;
	char BodyTypeAnimal;
	char field_DF[57];
	int SA2AnimalBehavior;
	char SA2BArmType;
	char SA2BEarType;
	char SA2BForeheadType;
	char SA2BHornType;
	char SA2BLegType;
	char SA2BTailType;
	char SA2BWingType;
	char SA2BFaceType;
	char field_124[8];
	char Joy;
	char field_12D;
	char UrgeToCry;
	char Fear;
	char field_130;
	char Dizziness;
	char field_132[2];
	__int16 Sleepiness;
	__int16 Tiredness;
	__int16 Hunger;
	__int16 MateDesire;
	__int16 Boredom;
	char field_13E[10];
	__int16 Energy;
	char Normal_Curiosity;
	char field_14B;
	char CryBaby_Energetic;
	char Naive_Normal;
	char field_14E[2];
	char Normal_BigEater;
	char field_151[4];
	char Normal_Carefree;
	char field_156;
	char FavoriteFruit;
	char field_158[2];
	char CoughLevel;
	char ColdLevel;
	char RashLevel;
	char RunnyNoseLevel;
	char HiccupsLevel;
	char StomachAcheLevel;
	char field_160[4];
	__int16 SA2BToys;
	char field_166[6];
	ChaoCharacterBond SA2BCharacterBonds[6];
	char field_190[680];
	ChaoDNA DNA;
	char gapToEnd[822];
};


struct setObj {
	unsigned short id;
	unsigned short xRot;
	unsigned short yRot;
	unsigned short zRot;
	float x;
	float y;
	float z;
	float v1;
	float v2;
	float v3;
};

struct TwitchMsg {
	std::string user;
	std::string msg;

};


struct TwitchChatter {
	std::string name;
	int currency;
	bool active;
	time_t lastActive;
	bool old;
};

struct __declspec(align(4)) RaceBotData
{
	char name;
	char typeRandom;
	char eyeRandom;
	char mouthRandom;
	char BallType;
	char field5;
	char HeadGear;
	char HideFeet;
	char Medal;
	char Color;
	char Texture;
	char ShinyMonotone;
	char animalpartRandom;
	char field_D[3];
	float PowerRunBase;
	float PowerRunRandomMultiplier;
	float FlySwimBase;
	float FlySwimRandomMultiplier;
	float AlignmentBase;
	float AlignmentRandomMultiplier;
	float MagnitudeBase;
	float MagnitudeRandomMultiplier;
	__int16 someStatThing;
	__int16 field_32;
	int stat; 
	__int16 swim;
	__int16 field_3A;
	__int16 fly;
	__int16 field_3E;
	__int16 run;
	__int16 field_42;
	__int16 power;
	__int16 field_46;
	__int16 stamina;
	__int16 field_4A;
	__int16 intelligence;
	__int16 field_4E;
	__int16 luck;
	__int16 field_52;
};




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
	char segmentID;
	NJS_VECTOR endPos;
	unsigned short yRot;
	NJS_VECTOR center;
	float radius;
};

struct KartCourseModel {
	char model_ptr[4];
	char collision_ptr[4];
	NJS_VECTOR end_point;
	int y_rot;
	char gap[84];

};


struct ChaoRealData {
	char name[7];
	char swimFraction;
	char flyFraction;
	char runFraction;
	char powerFraction;
	char stamFraction;

	char swimGrade;
	char flyGrade;
	char runGrade;
	char powerGrade;
	char stamGrade;

	char swimLevel;
	char flyLevel;
	char runLevel;
	char powerLevel;
	char stamLevel;

	short swimStat;
	short flyStat;
	short runStat;
	short powerStat;
	short stamStat;

	char type;
	char garden;
	char reincarnate;//255=yes
	char clocks;
	short remainingTime;
	int lifeClock; //max 120
	float powerRun;//pos = power, neg = run
	float flySwim;//pos = fly, neg = swim
	float evol;//1 = evolve
	char eye;
	char mouth;
	char ball;
	char headgear;
	char feet;
	char medal;
	char color;
	char highlights;
	char jewel;
	char shiny;//boolean
	char eggColor;
	char model;
	char happy;// (-100,100)

};

struct struct_a1R
{
	__int8 ChaoType;
	char EyeType;
	char MouthType;
	char BallType;
	char Headgear;
	char HideFeet;
	char Medal;
	char Color;
	char Monotone;
	char Texture;
	char Shiny;
	char SA2BArmType;
	char SA2BEarType;
	char SA2BForeheadType;
	char SA2BHornType;
	char SA2BLegType;
	char SA2BTailType;
	char SA2BWingType;
	char SA2BFaceType;
	char f13[1];
	__int16 PowerRun;
	__int16 FlySwim;
	__int16 Alignment;
	__int16 Magnitude;
	char Name[7];
	char unused;
	__int16 StatPoints[8];
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


struct LevelLookupEntry {
	char entry_type;
	char character_id;
	short level_id;
	short cutscene_events[4];
};

#pragma pack(pop)

// SA2CharSel.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>
#include "SA2ModLoader.h"
#include <unordered_map>
#include <random>
#include <fstream>
#include "IniFile.h"


//#define upgradecheck(chara,name) bool Disable##chara##name = settings->getBool("OnOff", "upmods");
//#define upgradecheck(chara,name) bool Disable##chara##name = false;
//#include "IniFile.hpp"

using std::vector;
using std::string;
using std::unordered_map;
using std::transform;
using std::shuffle;


LevelCutscene *const stru_173A808 = (LevelCutscene*)0x173A808;
signed int __cdecl sub_458970()
{
	signed int v0; // ecx@3
	unsigned int v1; // eax@6
	if (CurrentLevel == LevelIDs_GreenForest && CurrentCharacter != Characters_Sonic && AltCharacter[0] == 0) return 0;
	if (CurrentLevel == LevelIDs_BigFoot && CurrentCharacter != Characters_Sonic && AltCharacter[0] == 0) return 0;
	if (MainCharObj2[0])
		v0 = MainCharObj2[0]->CharID2;
	else
		v0 = -1;
	if (v0 >= Characters_Amy) return 0;
	if (MainCharObj2[1] && MainCharObj2[1]->CharID2 >= Characters_Amy) return 0;
	if ( *(char*)0x1DEB321 && *(char*)0x1DEB320)
	{
		v1 = 0;
		while ( stru_173A808[v1].Level != (signed __int16)CurrentLevel
			|| stru_173A808[v1].Character )
		{
			v1++;
			if ( v1 >= 16 )
				return 0;
		}
		return 1;
	}
	else
		return 0;
}

bool __cdecl CheckEmeraldManager()
{
	if (MissionNum == 1 || MissionNum == 2)
		return false;
	if (*(int*)0x1AF014C)
		return false;
	switch ((short)CurrentLevel)
	{
	case LevelIDs_PumpkinHill:
	case LevelIDs_AquaticMine:
	case LevelIDs_SecurityHall:
	case LevelIDs_WildCanyon:
	case LevelIDs_DryLagoon:
	case LevelIDs_DeathChamber:
	case LevelIDs_EggQuarters:
	case LevelIDs_MeteorHerd:
	case LevelIDs_WildCanyon2P:
	case LevelIDs_MadSpace:
	case LevelIDs_DryLagoon2P:
	case LevelIDs_PoolQuest:
	case LevelIDs_PlanetQuest:
	case LevelIDs_DeathChamber2P:
		return true;
	}
	return false;
}

static const void *const loc_73AAC2 = (void*)0x73AAC2;
__declspec(naked) void LoadEmeraldManager_r()
{
	if (!CheckEmeraldManager())
		__asm retn;
	__asm
	{
		push	esi
			push	edi
			jmp loc_73AAC2
	}
}

template <typename T1, typename T2> struct pair { T1 key; T2 value; };

pair<short, short> SonicAnimReplacements[] = {
	//{ 211, 1 },
	{ 212, 77 },
	{ 215, 15 }
};

pair<short, short> OthersAnimReplacements[] = {
	{75,0},
	{ 76, 0 },
	{ 77, 15 },
	{ 185, 62 },
	{ 186, 62 },
	{ 187, 62 },
	{ 189, 62 },
	{ 190, 62 },
	{ 192, 15 },
	{ 193, 15 },
	{ 194, 15 },
	{ 195, 15 },
	{ 196, 15 },
	{ 197, 15 },
	{ 198, 15 },
	{ 211, 1 },
	{ 212, 62 },
	{ 215, 15 }
};

pair<short, short> KnucklesAnimReplacements[] = {
	{ 185, 62 },
	{ 186, 62 },
	{ 187, 62 },
	{ 189, 62 },
	{ 190, 62 },
	{ 192, 105 },
	{ 193, 105 },
	{ 194, 15 },
	{ 195, 15 },
	{ 196, 15 },
	{ 197, 15 },
	{ 198, 15 },
	{ 211, 1 },
	{ 212, 77 },
	{ 215, 15 }
};

pair<short, short> MechAnimReplacements[] = {
	//{ 76, 0 },
	{ 76, 15 },
	//{ 77, 15 },
	{ 77, 75 },
	{ 185, 75 },
	{ 186, 75 },
	{ 187, 75 },
	{ 189, 75 },
	{ 190, 15 },
	{ 192, 15 },
	{ 193, 15 },
	{ 194, 15 },
	{ 195, 15 },
	{ 196, 15 },
	{ 197, 15 },
	{ 198, 15 },
	{ 211, 1 },
	{ 212, 77 },
	{ 215, 15 }
};

#define altcostume 0x80u
#define altcharacter 0x40
#define charmask ~(altcostume|altcharacter)
int defaultcharacters[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultalts[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultcosts[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int storedPrefs[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultcharactersM5[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };

int storeVL[2727];
int storeADX[MusicList_Length];

char* nonlooping[55] = { "btl_opng.adx",
"chao_g_born_c.adx",
"chao_g_born_d.adx",
"chao_g_born_d2.adx",
"chao_g_born_h.adx",
"chao_g_born_h2.adx",
"chao_g_born_hc.adx",
"chao_g_dance.adx",
"chao_g_dead.adx",
"chao_g_gate_open.adx",
"chao_g_new_garden.adx",
"chao_k_net_fault.adx",
"chao_k_net_fine.adx",
"chao_k_sing_dark1.adx",
"chao_k_sing_dark2.adx",
"chao_k_sing_dark3.adx",
"chao_k_sing_hero1.adx",
"chao_k_sing_hero2.adx",
"chao_k_sing_hero3.adx",
"chao_new_garden.adx",
"chao_r_a.adx",
"chao_r_gate_open.adx",
"chao_r_item_get.adx",
"continue.adx",
"c_btl_ch.adx",
"c_btl_dr.adx",
"c_btl_ls.adx",
"c_btl_wn.adx",
"e000_sng.adx",
"e019_sng.adx",
"E027_SNG.ADX",
"E028_SNG.ADX",
"E101_SNG.ADX",
"E106_SNG.ADX",
"E111_SNG.ADX",
"E119_SNG.ADX",
"e127_sng.adx",
"E130_SNG.ADX",
"E205_SNG.ADX",
"e207_sng.adx",
"E208_SNG.ADX",
"E210_SN1.ADX",
"E210_SN2.ADX",
"e350_sng.adx",
"invncibl.adx",
"item_get.adx",
"one_up.adx",
"rndclear.adx",
"speedup.adx",
"t1_shado.adx",
"t1_sonic.adx",
"T4_SONIC.ADX",
"T9_KNUCK.ADX",
"timer.adx",
"title.adx" };
char* looping[102] = { "advsng_1.adx",
"advsng_2.adx",
"advsng_3.adx",
"advsng_4.adx",
"advsng_5.adx",
"a_mine.adx",
"boss_01.adx",
"BOSS_02A.ADX",
"BOSS_02B.ADX",
"boss_03.adx",
"boss_04.adx",
"boss_05.adx",
"boss_06.adx",
"BOSS_07.ADX",
"btl_ce.adx",
"btl_hb.adx",
"btl_ig.adx",
"btl_mh.adx",
"btl_pc.adx",
"btl_rh.adx",
"btl_sel.adx",
"btl_so.adx",
"btl_wb.adx",
"btl_wj.adx",
"chao_g_bgm_d.adx",
"chao_g_bgm_h.adx",
"chao_g_bgm_n.adx",
"chao_g_iede.adx",
"chao_g_radicase1.adx",
"chao_g_radicase2.adx",
"chao_g_radicase3.adx",
"chao_g_radicase4.adx",
"chao_g_tv_cartoon.adx",
"chao_g_tv_drama.adx",
"chao_g_tv_sports.adx",
"chao_hall.adx",
"CHAO_K_M.ADX",
"chao_k_m2.adx",
"chao_k_net_connect.adx",
"chao_l_m.adx",
"chao_r_b.adx",
"chao_r_c.adx",
"chao_r_d.adx",
"CHAO_R_E.ADX",
"chao_r_h.adx",
"chao_r_j.adx",
"c_btl_cv.adx",
"c_btl_gm.adx",
"c_btl_sl.adx",
"c_core_1.adx",
"c_core_2.adx",
"c_core_5.adx",
"C_CORE_6.ADX",
"c_escap1.adx",
"c_escap2.adx",
"c_escap3.adx",
"c_gadget.adx",
"c_wall.adx",
"d_chambr.adx",
"d_lagoon.adx",
"E006_SNG.ADX",
"e021_sng.adx",
"E112_SNG.ADX",
"e_engine.adx",
"e_quart.adx",
"f_chase.adx",
"f_rush.adx",
"g_fores.adx",
"g_hill.adx",
"h_base.adx",
"i_gate.adx",
"kart.adx",
"l_colony.adx",
"m_harb1.adx",
"m_harb2.adx",
"m_herd.adx",
"m_space.adx",
"m_street.adx",
"p_cave.adx",
"p_hill.adx",
"p_lane.adx",
"r_hwy.adx",
"s_hall.adx",
"s_ocean.adx",
"s_rail.adx",
"T2_MILES.ADX",
"T2_ROUGE.ADX",
"t3_eggma.adx",
"T3_KNUCK.ADX",
"T3_MILES.ADX",
"T3_SHADO.ADX",
"T4_KNUCK.ADX",
"T4_ROUGE.ADX",
"t9_amy.adx",
"T9_EGGMA.ADX",
"T9_MILES.ADX",
"T9_ROUGE.ADX",
"T9_SHADO.ADX",
"T9_SONIC.ADX",
"w_bed.adx",
"w_canyon.adx",
"w_jungl.adx"};

const int TOTALSTAGEOPTIONS = 43;
char stageOptionS[TOTALSTAGEOPTIONS][14] = {"set0013_s","set0003_s","set0004_s","set0009_s" ,"set0011_s","set0010_s","set0012_s" ,"set0017_s" ,"set0017_u" ,"set0021_s" ,"set0021_u",
"set0022_s","set0023_s" ,"set0024_s" ,"set0027_s","set0028_s" ,"set0030_s" ,"set0043_s" ,"set0043_u","set0014_s" ,"set0005_s","set0005_u",
"set0007_s","set0007_u","set0008_s","set0008_u" ,"set0016_s","set0016_u" ,"set0018_s" ,"set0025_s" ,"set0026_s","set0026_u","set0032_s","set0037_s" ,"set0038_s",
"set0009_u", "set0011_u", "set0012_u", "set0023_u" , "set0035_s", "set0035_u" , "set0040_s","set_b_Golem_s"}; //file
int stageOptionT[TOTALSTAGEOPTIONS];  //0 = speed  1 = hunt   2 = mech  3 = mechless
//int stageOptionReset[TOTALSTAGEOPTIONS] = { 1 ,1 , 1,1,1}; //rando vanilla version number

const int SonicVersions = 7;
int SonicStages[SonicVersions] = {0,1,5,11,15,16,42};

const int ShadowVersions = 3;
int ShadowStages[ShadowVersions] = {2,19,41};

const int KnuxVersions = 9;
int KnuxStages[KnuxVersions] = {20,21,22,23,26,27,29,32,34};

const int RougeVersions = 6;
int RougeStages[RougeVersions] = {24,25,28,30,31,33};

const int EggmanVersions = 11;
int EggmanStages[EggmanVersions] = {4,6,9,10,14,17,18,36,37,39,40};

const int TailsVersions = 7;
int TailsStages[TailsVersions] = {3,7,8,12,13,35,38};

bool createrMode = false;
int alt;
int cost; 
int choose = 0;
int altncost = 1;
int nocosts = 0;
int heroonly = 0;
int bossInPool = 0;
boolean sehar = false;
int cutoff; 
unsigned int seed = time(NULL);
boolean randomMissions = false;
int RmissionNum;
int RandoSeed;
boolean logThisV = false;
boolean disRL = false;
boolean rchar = false;
boolean maxChaoStats = false;
boolean setRNG = false;
boolean randoSV = false;
boolean showN = false;
boolean rVoices = false;
std::string story;
int speedMult = 1;
boolean disKill = false;
string savePath;
boolean cVoices = false;
boolean noVanillaChars = false;
boolean cADX = false;
boolean rkart = false;
int totalHours = 0;
int totalMins = 0;
int totalSecs = 0;
int totalCentis = 0;
string fTime;
int igtSlot = 20;
int totalScore = 0;
string score;
std::unordered_map<string, int> nonloopingMap;
std::unordered_map<string, int> loopingMap;
bool deathAdded = false;
int totalDeaths = 0;
int totalJumps = 0;
string deaths = "";
string jumpsCount = "";
int hintsRead = 0;
string hintCounts;
bool hintRead;
ChaoDataBase saveChao;
boolean rChao = false;
int hiddenGlitchChao;
boolean colorChao = false;
//boolean inplaceCut;
boolean disTempChaoFile = false;
int lastUse = 0;
int cooldown = 180;
int springID = 3;
int itemBoxID = 10;
int saveSETCount;
int createCount = 3000;
int MMID = 37;
int Bcount = 0;
string Bstring = "";
int Acount = 0;
string Astring = "";
int Xcount = 0;
string Xstring = "";
int Ycount = 0;
string Ystring = "";
int Startcount = 0;
string Startstring = "";


int bfPlayers[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter,Characters_Shadow, Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int hsPlayers[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow,Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int eggPlayers[] = {Characters_MechTails,Characters_MechTails|altcharacter, Characters_MechEggman,Characters_MechEggman | altcharacter};
int bioLizard[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow };

int hunters[4] = { Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int speedsters[4] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow, };
int mechs[4] = { Characters_MechTails,Characters_MechTails | altcharacter, Characters_MechEggman,Characters_MechEggman | altcharacter };


int hotShotSwap;
int bigFootSwap;
int flyDogSwap;
int KBBSwap;
int EGESwap;
int biolizSwap;
int CCSonicSwap;
int EGSSwap;
bool disChaoReload = false;
bool objPlacedInStage = false;

const int shoutCNT = 564;
char* shouts[shoutCNT] = { "DRUMBASHER004", "MEKHIALTEY02" ,"DAGE4", "TRAITOR", "SERAPHIM", "DRAKODAN", "ETHMAR", "IDEN", "BROKENARTHRITIS", "TYLENOL", "DARKPR0", "IDGEEK121", "MODIFIEDMONKEE", "CRYPHON", "SHIBAKEE", "A_MOUSTACHE", "AURAACE", "TALON2461", "JW13", "EMERUA", "VIBLOSH", "COEMPATHY", "EPICFROGSKATER", "JETSETHRADIO", "EDWARDBOTTLE", "SILENTMOTORBOAT", "PINER", "AXLTHUNDER", "TOMMYEASY", "SORA", "METALGLENNSOLID", "NIMPUTS", "AAAA", "MR.TORTELLINI", "MASTER-KURUK", "NINEBALL", "PHANTOMS83", "ETHMAR", "DRYWALLEATER69", "MATTMURPZ", "IRREGULARZERO", "EMERLDD", "PRAHAHA", "BUFFALOPRIME", "SAVAC", "DRUNK_LOLI", "ASINISTERTACO", "SHININGFACE", "JAZZSPEEDRUNS", "CHAINCHUMP", "NICK902", "AGUEDOUF", "CLAIRESV", "PRIMZI", "LITTLEBIGNESS", "RAVEL", "DAISUKEMARA", "THEALPHADOLPHIN", "PRISMATICBLACK", "SPADES", "ZELLNUUEON", "FORD373", "MYSTICREBEL", "KINKYCADENCE", "MRDARKICE", "STLLR", "BLAZINZZETTI", "AREYTOREMEMBER", "SON1CGU1TAR", "JRK9", "BOOSTEDBANDCAMP", "FREEFALL", "PRIMZI", "KOINU93", "TEHCHEROKEE", "DRX-VECTOR", "THEWAYTODAWNNN", "INEORETRO", "JELLYFISHSWIMMER", "SPACEBROJAKOB", "JONSUPEREMERALD", "KINOKOJULES", "REZEPHOS", "NIMPUTS", "MASTER-KURUK", "THEJOKERNAUT", "BIKEE", "BLAZINZZETTI", "FORD373", "NOTHISISSTUPIDER", "DUSTY_PECKER", "ENU", "EMERAULD", "YOSHIFAN", "SUPERDENNYBOI", "SEKANOR", "SIMPLETON216", "OUTRAGEOUSJOSH", "TIKAL", "STIRLIING", "SHADOWFROST", "CRITICALCYD", "ACS13123", "COOKIEPOCALYPSE", "THE0NLYKYD", "CAPTSAMERICA", "GODLY79", "BADLEX727", "PHAT-BOSS", "ENPASSANT", "SWEARIMNOTAWEEB", "PUDDINGHOUSE", "JUSTALOT123", "DIESERFMG", "DIMES", "GRUMBLEBUNDLE", "TONESBALONES", "R3FR4G", "AKUREIKORINEKO", "AMBERCYPRIAN", "MRWOOFIES", "FALLENFURY777", "HUGASAURUS", "MCSHUGGETS", "EXCEL", "ONVAR", "SANICSPACEPARTY", "AIOPROJECT", "SHADOWCERO", "DEMOTEDSTAFF", "ASYLIX", "SNODECA", "AMBLOOPS", "PRISMATICBLACK", "SUPRA", "SHADY_", "OXTANE", "MENSTILO", "PKMNTRAINERGIAN", "DREWBIIE", "MASTAKIRBY", "BAYLEE", "GUYSTREAMSSTUFF", "JOEEY", "VENTIYORDLE", "LONEWO1F001", "1219NEKOGAMI", "WEEGEEZV", "CERETH", "DRAKODAN", "LAUGHTRACK", "TORPY", "PEPEYE", "ZEPH", "MASTAKIRBY", "MECKLEMISUER", "PHIJKCHU_TDK", "MIDBOSS", "HOMES1CK", "DIGG3RZ", "KHEARTZ", "FROKENOK", "CRYSTALCHAOS", "THEPUDDINGFIGHTER", "CAPTSAMERICA", "RENEGADE522", "GRANDSTARYOSHI", "DOLPHINDASHER", "DFESFSFS", "GAMERCAL", "SAMITIAN", "FURYRISING", "CRISPIAN", "LINKKIRO", "THEWAYTODAWNNN", "YUUUTAAAAPOONNN", "NIISOKS", "_GIMMICK", "CAITLYNMARV", "AHOYKMS", "CONKLESTOTHEMAX", "DRMINUS", "SANICSPACEPARTY", "KOINU93", "UNDEADFORCE22", "NERFNED2000", "DUSTY_PECKER", "FURYRISING", "ZYLDARA", "XONOS117", "MRSANDERSS", "JOEDOR", "CHRONOON", "SPARKKY", "LEIF26", "HAZEL", "VIXUZEN", "JORDIEBEE", "IVEGOTDATFEEL", "JERKRO", "TS4EVER1201", "BAYLEE", "WEREY", "CHANMAN", "NEVERDOORS", "BUDMIN", "TAPE1", "MIDNIGHTRAMBLER", "LEWISB99", "AIR_IQ", "MOETER", "DRASAMII", "HUGASAURUS", "MARUMIJU", "RAPTURE", "FLOWLEYD", "PROJECT", "JOERUNNER", "XGONZO", "FALEROTH", "BRIAN_PSO", "CLEEKOH", "TOGAIN", "44MOTH", "RETRORUNS", "MELONSPEEDRUNS", "CUUKIESODEATH", "DJSHOVEL", "KENDALLSWAN", "GHOUL02", "MASTERWAFFLED", "WELSAR55", "PROTO", "CONKERBANDICOOT", "ELECTRICMILES", "TYHILL111", "DABBINGJESUS", "TRIX", "CLAIRESV", "BRODYZERA", "RJASSOA", "NIGHTMARE47", "WELLDOODER64", "GOLDWOLF11", "NEBBII", "THEREALMRJANGLE", "KEONEON", "TWOFERTUESDAY", "ARGICK", "TOLVENGYR", "CANARIABIRD", "AQUOVA", "BIRDY", "GHOULSTON", "THESTRANGEMENTLEGEN", "ALTAIRAN", "DEARMONDZFTW", "IZAYOI83", "TOUCH", "OUTRAGEOUSJOSH", "FIVAVOA", "MAR", "TRICOLOUR", "ELITECARNAGE", "CLUMZY_CHAO24", "KYTES", "CLUMZY_CHAO24", "NEBBII", "YOSHIS2NDCOUSIN", "F_AUX", "SUZURU", "ISHMON", "STONIE", "RAZZZ", "DREAMTORA", "RINGENERGY", "DRPHYSIC", "SCT", "LIQUID_BOSSCELOT", "BARELYFUNCTIONAL", "KINGSHADOWCLOCK", "2D", "PIKAPALS", "SHAMANA", "BURNINGSKULL123", "VYNNEVE", "WADDLEDAISY", "AERO_TRIGGER", "WOSIGE", "DIZZYPRIME", "PRICE211066", "TILTEDSTILTS", "MITSURAY", "WOOGUY78", "THORN", "OKAM", "KURAYAMI", "SLICKEVAN", "SONICKU", "POKESTUCK33", "CONDUS", "THEBRICKTATOR", "JAMCEPTION", "RAGECAT", "MRHAPPYISMISSING", "IAMBPBURKE", "DHRGR", "ASTERISK254", "RAIUPLAYS", "MIE_DAX", "RANDYBUMGARDENER", "PIKA_CHOO1", "DHRGR", "RODYONCE", "SUPERSONIC", "SURFINGPIKACHU", "AVENTO128BITS", "SIRCHARLES", "TECHIYO", "GRAYMAGICGAMMA", "THE_GODS", "MELANCHOLYMATOI", "BOWLERCAPTAIN", "RAJAXX", "GPRO", "CTAGENT", "BLATAN", "DRGNDRAGS123", "BIZKIT", "TIMPZ", "CCNEVERENDER", "DARTANIAN881", "CLASSIC", "INDEXTIC", "WARPWHISTLE", "AMERICANCHOIRBOY", "RINGRUSH", "MESSMYPANTS", "SAYURI", "GOLD", "XALLESII", "KEEFYY", "YES", "BOOHEAD86", "MAR", "DAWNGAWARD", "LEEYUNA", "LEETUS", "BRASSMONKEJR", "APHEXARCADE", "NEROBRON", "TOXICFAKER", "FRISKYHARAMBE", "SCAMPER", "WOLFII", "PROUDS1LVER", "JTNOBLE321", "RHAPSODY", "THEMANUAL768", "MINAMIYO", "TJREDEEMER", "SILO_SIMON", "THECOBRA931", "BUSHIIDOX", "FOXDRA", "DRACO655", "JOSHIFIRE", "STICKFIGUREVECTOR", "CHAOZ163", "FINITECHAOS", "ASPARCEL", "METROIDMASTER", "FLOPPYDISK", "ARMORYSONS", "VALIOA", "PATAFOIN", "FIERCECLASH", "LERGI", "RAQIBMARVELOUS", "TENACITY", "BONZI77", "0RBIS", "PAULIE9990", "GURDILL63", "EVERLASTINGSAINT", "ARUKI", "VARK", "BMW0401_2", "LURAXTHUNDER", "KYYRIE", "SUPERNERDMILES", "ALLEGRO", "LOTUSKI24", "MAYAKANAI65", "ABSENTSR", "YOSHIPARTOUT", "RANDOMGUY55", "LIGHTNING55", "DEKU_SR", "HYPEMASTER2020", "NICKIREDA", "NINJEMBRO", "NEPTUNE", "REDSKY764", "TIKWI", "PARAMETER152", "NINJAOWNED", "SPOOKYSPEEDRUNS", "DIRTYDILLERS", "THERIO", "KEETA", "OSC", "FOMAKO", "DISCONNECTOID", "FASTLIKESANIC", "HOOPYHOOP1", "GUPPLY", "SSJPICHU", "JEL", "FROZER", "CKARL_BOBADINE", "CPTPUFF", "SONIKKU", "MR_MANGO", "DNYCEBOY", "BILLPZC", "JACKWITHERELL", "TALLCAT", "COOLCOLEGAMER", "SAZABI0093", "CREAM147", "ICEDOG158", "EAT4THELOLZ", "SKULL_KID_64", "RAVAILDISNEY", "G00GLY0EYES", "ATIRCERILE", "YESTHROUGH", "SLURM_KING", "TREASURE", "NIGHTMARE47", "DIABUK", "BUCKETHEAD222", "RINGENERGY", "SAINTSFIGHTER", "CENTARI", "DANIDESU", "MAR", "SQUIDTEPIG", "NATHACSA", "WOOFPACK", "MOVELLANDRONE", "TEKKIE", "HUGHMANPHIST", "SHANEKILZ", "MELANCHOLYMATOI", "ZACKOON49", "THEUNEXPECTED5", "ISLEDELFINO", "AGGRESSIVELY MEDIUM", "SENZURA", "TANDOM_GAMER1", "BASOUIFICATION", "CHARAMELMOU", "OZZI9816", "AFROGAMER2660", "STLLR", "COWTECH", "VILSOL", "KIMSHI", "TOMMYSPUD", "TOON_RITO", "HEYTALLMAN", "JBIRD", "TIMIC", "ENIGMA20", "GC4EVER4001", "SIMPLICITYWALRUS", "KIMMSTAA", "GVOLTT", "WOLFLUKE", "MARSHY", "JUSTGOODPOP", "A_BOWL_OF_CEREAL", "JOLTEONTRAINER", "_HOUSTON", "MRGENERICNAME", "SALMONBUFFALO", "VENOMBYTE", "NAPUC", "XNOSE", "HOOPY", "NINJAHENRIK", "JAILKAT7", "MARKUSMAN64DS", "JATENK", "MITOREQUIEM", "USIKU", "GRIEVENOMORE", "HAWKREX", "GREG", "BUXSTEVEN", "PRINNY", "NIGHTOPIAN", "DOROCCO", "IVANGS", "VIDEO2GUD", "WINDSSUNRISE1", "XELONIOUS", "SPARK3", "PSYMAR", "STEVEWONTLEAVE", "TWINKIESWF", "THEKIWITURTLE", "ZODIAC92", "JBUZZYBEE", "KYONEXE", "GAILARDIA", "SIMLOLA661", "DUNHAM", "UNSUPERVISEDFUN", "SB737", "SSBMSTUFF", "SUPER_SANIC123", "CHUCAT", "PIXELLE", "THEJUICE", "BLUELIGHTDIMMING", "CASUSBY", "ARMAGEDDUN", "JPAINTRAIN", "GRAPHOX", "POKEMANAPHY", "RACKSBLUE", "DARKARIA21", "RELIK9R", "CYBERSONICSTARZX655", "JHOBZ", "ZOMBIEMASTER", "SWAAGGYY", "ZYNC", "PRINCEKARO", "PERDONIUM", "MARKHEST", "GENO", "FIERCEFRANKIE", "ANDZURA", "ITLAU", "TRUNKYNUGGET", "LAMBO", "PUCHIEDARCY", "X10POWER", "MATTHEWFUPP", "PARKRAFT123", "GOLDENBOY", "ZELDRAK", "CHELSEYXLYNN", "TIGERKYLE1", "FAILGAMES100", "BONY", "BBQSAUZ", "SPIKEVEGETA", "CRICKETDX", "LORDFARTAMOR" };


const int chaoCNT = 567;
char* chao[chaoCNT] = {"Mekhialtey02" , "_Gimmick", "_Houston", "0rbis", "1219nekogami", "2D", "44moth", "A_Bowl_Of_Cereal", "a_moustache", "aaaa", "AbsentSR", "acs13123", "Aero_Trigger", "�zir", "afrogamer2660", "Aggressively Medium", "aguedouf", "AhoyKMS", "aioproject", "Air_iq", "akureikorineko", "Allegro", "Altairan", "AmberCyprian", "Ambloops", "Americanchoirboy", "andzura", "anthonyjuice", "AphexArcade", "Aquova", "AReytoRemember", "Argick", "Armageddun", "ArmorySons", "Aruki", "ASINISTERTACO", "asparcel", "Asterisk254", "Asylix", "Atircerile", "auraace", "Avento128bits", "AxlThunder", "Badlex727", "BarelyFunctional", "Basouification", "Baylee", "bbqsauz", "Bikee", "BillPzc", "Birdy", "Bizkit", "Blatan", "BlazinZzetti", "BlitzBlatt", "Bluelightdimming", "BMW0401_2", "bony", "bonzi77", "Boohead86", "BoostedBandCamp", "bowlercaptain", "brassmonkejr", "Brian_pso", "Brodyzera", "BrokenArthritis", "buckethead222", "Budmin", "BuffaloPrime", "Burningskull123", "Bushiidox", "BUxSteven", "CaitlynMarv", "canariabird", "Captsamerica", "Casusby", "CCNeverender", "Centari", "Cereth", "chainchump", "chanman", "ChaoticChao", "Chaoz163", "CharamelMou", "ChelseyxLynn", "chronoon", "Chucat", "Ckarl_Bobadine", "ClaireSV", "Classic", "Cleekoh", "Clumzy_Chao24", "Lexi", "Condus", "ConkerBandicoot", "Conklestothemax", "cookiepocalypse", "coolcolegamer", "CowTech", "CptPuff", "Cream147", "Cricketdx", "Crispian", "CriticalCyd", "Cryphon", "CrystalChaos", "ctagent", "CuukiesODeath", "CyanideKry", "cybersonicstarzx655", "dabbingjesus", "Dage4", "Daisukemara", "Danidesu", "Darkaria21", "Darkpr0", "Dartanian881", "Dawngaward", "DearmondzFTW", "Deku_sr", "DemotedStaff", "Desura", "Dfesfsfs", "DhrGR", "Diabuk", "DieserFMG", "DiGG3rZ", "dimes", "DirtyDillers", "disconnectoid", "DizzyPrime", "DjShovel", "Dnyceboy", "DolphinDasher", "donniesmithers", "Dorocco", "Draco655", "Drakodan", "drasamii", "Dreamtora", "Drewbiie", "DRGNDrags123", "drminus", "DrPhysic", "Drum", "Drunk_Loli", "DRX-Vector", "drywalleater69", "Dunham", "dusty_pecker", "Eat4thelolz", "EdwardBottle", "ElectricMiles", "EliteCarnage", "Emerauld", "Emerldd", "emerua", "enigma20", "EnPassant", "enu", "Epicfrogskater", "ethmar", "EverlastingSaint", "eXceL", "F_aux", "failgames100", "Failinator", "Faleroth", "FallenFury777", "fastlikesanic", "FierceClash", "FierceFrankie", "FiniteChaos", "Fivavoa", "FloppyDisk", "Flowleyd", "Fomako", "ford373", "foxdra", "Freefall", "FriskyHarambe", "Frokenok", "Frozer", "FuryRising", "g00gly0eyes", "Gailardia", "Gamercal", "Gc4ever4001", "Geno", "Gerp", "Ghoul02", "Ghoulston", "Godly79", "Gold", "Goldenboy", "Goldwolf11", "Gpro", "GrandStarYoshi", "Graphox", "GrayMagicGamma", "Greg", "Grievenomore", "grumblebundle", "Gupply", "Gurdill63", "GuyStreamsStuff", "Gvoltt", "Hawkrex", "Hazel", "Hephlex", "heytallman", "Homes1ck", "Hoopy", "Hoopyhoop1", "Hugasaurus", "Hughmanphist", "HypeMaster2020", "iambpburke", "icedog158", "Iden", "IDGeek121", "iexrrr", "Indextic", "iNeoRetro", "IrregularZero", "Ishmon", "IsleDelfino", "ITLAU", "IvanGS", "Ivegotdatfeel", "Izayoi83", "Jackwitherell", "Jailkat7", "jamception", "Jatenk", "JazzSpeedruns", "jbird", "JBuzzyBee", "Jel", "jellyfishswimmer", "JerKro", "JetSethRadio", "JHobz", "Joedor", "Joeey", "Joerunner", "jolteontrainer", "JonSuperEmerald", "Jordiebee", "Joshifire", "Jpaintrain", "jrk9", "jtnoble321", "Justalot123", "Justgoodpop", "jw13", "Keefyy", "Keeta", "Keewy", "kendallswan", "Keoneon", "Kheartz", "Kimmstaa", "Kimshi", "Kingshadowclock", "kinkycadence", "KinokoJules", "koinu93", "Kurayami", "Kyonexe", "Kytes", "Kyyrie", "Lambo", "LaughTrack", "Leetus", "Leeyuna", "Leif26", "Lergi", "Lewisb99", "Lightning55", "Linkkiro", "Liquid_Bosscelot", "LittleBigness", "Lonewo1f001", "Lordfartamor", "Lotuski24", "LuraxThunder", "Mar", "Markhest", "markusman64ds", "Marshy", "Marumiju", "Mastakirby", "Master-Kuruk", "MasterWaffled", "Matthewfupp", "Mattmurpz", "Mayakanai65", "mcshuggets", "Mecklemisuer", "Matoi", "MelonSpeedruns", "Meltrs", "Menstilo", "MessMyPants", "MetalGlennSolid", "MetroidMaster", "Midboss", "MidnightRambler", "mie_Dax", "Minamiyo", "Mitorequiem", "Mitsuray", "ModifiedMonkee", "Moeter", "Movellandrone", "Mr_Mango", "Mr.Tortellini", "MrDarkIce", "Mrgenericname", "Mrhappyismissing", "MrSanderss", "MrWoofies", "MyPairOfSocks", "MysticRebel", "Napuc", "Nathacsa", "nebbii", "Neptune", "Nerfned2000", "NeroBron", "NEVERDOORS", "Nick902", "Nickireda", "Nightmare47", "NiGHTOPiAN", "Niisoks", "Nimputs", "Nineball", "ninjahenrik", "NiNJaOwNeD", "Ninjembro", "NoThisIsStupider", "Okam", "OnVar", "OSC", "OutrageousJosh", "Oxtane", "Ozzi9816", "Parameter152", "Parkraft123", "Patafoin", "Paulie9990", "Pearstrike", "Pepeye", "Perdonium", "petrie911", "phantoms83", "Phat-Boss", "Phijkchu_tdk", "Pika_choo1", "Pikapals", "piner", "Pixelle", "PKMNtrainerGian", "Pokemanaphy", "Pokestuck33", "Prahaha", "price211066", "Primzi", "PrinceKaro", "Prinny", "PrismaticBlack", "Project", "Proto", "prouds1lver", "Psyknux", "PsyMar", "puchiedarcy", "Puddinghouse", "R3FR4G", "racksblue", "Ragecat", "Raikou", "RaiuPlays", "Rajaxx", "Randomguy55", "RandyBumgardener", "Rapture", "raqibmarvelous", "Ravaildisney", "Ravel", "Razzz", "redsky764", "relik9r", "Renegade522", "RetroRuns", "rezephos", "Rhapsody", "RingEnergy", "Ringrush", "RinKagamine1", "RjassoA", "rodyonce", "SaimeZX", "saintsfighter", "SalmonBuffalo", "Samitian", "SanicSpaceParty", "Savac", "Sayuri", "Sazabi0093", "SB737", "Scamper", "SCT", "Sekanor", "Selphos", "Senzura", "Seraphim", "Shadow2701", "ShadowCero", "ShadowFrost", "Shady_", "shamana", "Shanekilz", "shibakee", "ShiningFace", "SMB", "Silo_Simon", "SimLola661", "simpleton216", "SimplicityWalrus", "Sircharles", "skull_kid_64", "SlickEvan", "Slurm_king", "Snodeca", "Son1cgu1tar", "Sonicku", "Sonikku", "Sora", "SpaceBroJakob", "spades", "Spark3", "Sparkky", "spikevegeta", "spinful", "SpookySpeedruns", "squidtepig", "SqwareEcks", "SSBMstuff", "SSJPichu", "Stevewontleave", "StickFigureVector", "Stirliing", "stllr", "Stonie", "super_alice", "super_sanic123", "SuperDennyBoi", "SuperNerdMiles", "SuperSonic", "Supra", "surfingpikachu", "Suzuru", "Swaaggyy", "SwearImNotAWeeb", "Tallcat", "Talon2461", "Tandom_gamer1", "Tape1", "Techiyo", "TehCherokee", "Tekkie", "Tenacity", "The_Gods", "the0nlykyd", "TheAlphaDolphin", "TheBricktator", "Thecobra931", "TheJokernaut", "theJUICE", "TheKiwiTurtle", "themanual768", "thepuddingfighter", "TheRealMrJangle", "Therio", "TheStrangeMentlegen", "Theunexpected5", "thewaytodawnnn", "Thorn", "Tigerkyle1", "Tikal", "Tikwi", "TiltedStilts", "Timic", "TimpZ", "TJRedeemer", "togain", "tolvengyr", "Tommy", "Tommyspud", "TonesBalones", "toon_rito", "Torpy", "Touch", "ToxicFaker", "Traitor", "Treasure", "Tricolour", "Trix", "trunkynugget", "Ts4ever1201", "TwinkieSWF", "TwoferTuesday", "tyhill111", "Tylenol", "undeadforce22", "Unrealodin", "UnsupervisedFun", "Usiku", "Valioa", "Vark", "Venombyte", "ventiyordle", "Viblosh", "Video2gud", "Vilsol", "Vixuzen", "Vynneve", "WaddleDaisy", "WarpWhistle", "Weegeezv", "welldooder64", "welsar55", "Werey", "Whizzy_the_Elephant", "windssunrise1", "WindsSunrise1", "Wolfii", "Wolfluke", "woofpack", "Wooguy78", "wosige", "Wub", "x10power", "Xallesii", "Xelonious", "xGonzo", "xNose", "Xonos117", "Yes", "Yesjong", "YESR", "Yesthrough", "yoshifan", "yoshipartout", "Yoshis2ndcousin", "yuuutaaaapoonnn", "Zackoon49", "Zeldrak", "ZellnuuEon", "Zeph", "Zodiac92", "Zombiemaster", "Zyldara", "Zync" };


int charPool[12] = { Characters_Sonic,Characters_Shadow,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter,
					Characters_Knuckles,Characters_Rouge,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter,
					Characters_MechTails,Characters_MechEggman,Characters_MechTails|altcharacter, Characters_MechEggman|altcharacter};
bool inPool[12] = { true,true,true,true,
					true,true,true,true,
					true,true,true,true };

int useThisPool[12];
int numCharsinPool = 1;


double dist(NJS_VECTOR a, NJS_VECTOR b) {
	return(pow(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2), 0.5));
}

double findClosestMM() {
	double closestMM = 9999999999;
	double currentMM = 0.0;
	for (int i = 0; i < SETObjectCount; i++) {
		if (SETEntries[i].ID == MMID) {
			currentMM = dist(MainCharObj1[0]->Position, SETEntries[i].Position);
			if (currentMM < closestMM) closestMM = currentMM;
		}
	}
	return closestMM;
}


char* getcwd()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return buf;
}


void moveMessage(string from, string to, string file) {
	string f = from + file;
	string t = to + file;
	CopyFileA(f.c_str(), t.c_str(), FALSE);
}

void soHints(int i) {
	string baseFrom = savePath + "\\Options\\SOMessage\\";
	string baseTo = savePath + "\\gd_PC\\Message\\";
	if (i == 0) {
		moveMessage(baseFrom, baseTo, "eh0005e.prs");
		moveMessage(baseFrom, baseTo, "eh0007e.prs");
		moveMessage(baseFrom, baseTo, "eh0016e.prs");
		moveMessage(baseFrom, baseTo, "eh0025e.prs");
		moveMessage(baseFrom, baseTo, "eh0032e.prs");
	}
	if (i == 1) {
		moveMessage(baseFrom, baseTo, "eh0008e.prs");
		moveMessage(baseFrom, baseTo, "eh0018e.prs");
		moveMessage(baseFrom, baseTo, "eh0026e.prs");
	}

}

void vanHints(int i) {
	string baseFrom = savePath + "\\Options\\VanillaMessage\\";
	string baseTo = savePath + "\\gd_PC\\Message\\";
	if (i == 0) {
		moveMessage(baseFrom, baseTo, "eh0005e.prs");
		moveMessage(baseFrom, baseTo, "eh0007e.prs");
		moveMessage(baseFrom, baseTo, "eh0016e.prs");
		moveMessage(baseFrom, baseTo, "eh0025e.prs");
		moveMessage(baseFrom, baseTo, "eh0032e.prs");
	}
	if (i == 1) {
		moveMessage(baseFrom, baseTo, "eh0008e.prs");
		moveMessage(baseFrom, baseTo, "eh0018e.prs");
		moveMessage(baseFrom, baseTo, "eh0026e.prs");
	}

}

void mechHints(int i) {
	string baseFrom = savePath + "\\Options\\MechMessage\\";
	string baseTo = savePath + "\\gd_PC\\Message\\";
	if (i == 0) {
		moveMessage(baseFrom, baseTo, "eh0005e.prs");
		moveMessage(baseFrom, baseTo, "eh0007e.prs");
		moveMessage(baseFrom, baseTo, "eh0016e.prs");
		moveMessage(baseFrom, baseTo, "eh0025e.prs");
		moveMessage(baseFrom, baseTo, "eh0032e.prs");
	}
	if (i == 1) {
		moveMessage(baseFrom, baseTo, "eh0008e.prs");
		moveMessage(baseFrom, baseTo, "eh0018e.prs");
		moveMessage(baseFrom, baseTo, "eh0026e.prs");
	}

}


void copyFileBin(const char* f,const char* num){
	string from = savePath + "\\Options\\" + f + "\\" + num + ".bin";
	string to = savePath + "\\gd_PC\\" + f + ".bin";
	//CopyFileA(strcat(strcat(strcat(strcat(strcat(getcwd(), "\\mods\\SA2Rando\\Options\\"),f),"\\"),num),".bin"), strcat(strcat(strcat(getcwd(), "\\mods\\SA2Rando\\gd_PC\\"),f),".bin"), false);
	CopyFileA(from.c_str(), to.c_str(), FALSE);
	return;
}

void setSonicStages() {
	int type = defaultcharacters[0] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < SonicVersions; i++) {
		stageOptionT[SonicStages[i]] = type;
	}

}

void setShadowStages() {
	int type = defaultcharacters[1] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < ShadowVersions; i++) {
		stageOptionT[ShadowStages[i]] = type;
	}

}

void setKnuxStages() {
	int type = defaultcharacters[4] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) {
		type = 0;
		soHints(0);
	}
	else if (type == Characters_Knuckles || type == Characters_Rouge) {
		type = 1;
		vanHints(0);
	}
	else {
		type = 2;
		mechHints(0);
	}
	for (int i = 0; i < KnuxVersions; i++) {
		stageOptionT[KnuxStages[i]] = type;
	}

}

void setRougeStages() {
	int type = defaultcharacters[5] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) {
		type = 0;
		soHints(1);
	}
	else if (type == Characters_Knuckles || type == Characters_Rouge) {
		type = 1;
		vanHints(1);
	}
	else {
		type = 2;
		mechHints(1);
	}
	for (int i = 0; i < RougeVersions; i++) {
		stageOptionT[RougeStages[i]] = type;
	}

}

void setEggmanStages() {
	int type = defaultcharacters[7] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < EggmanVersions; i++) {
		stageOptionT[EggmanStages[i]] = type;
	}

}

void setTailsStages() {
	int type = defaultcharacters[6] & charmask;
	if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < TailsVersions; i++) {
		stageOptionT[TailsStages[i]] = type;
	}

}

void setStages() {
	setSonicStages();
	setShadowStages();
	setKnuxStages();
	setRougeStages();
	setEggmanStages();
	setTailsStages();
}

void stageV() {
	setStages();
	for (int q = 0; q < TOTALSTAGEOPTIONS; q++) {
		char num[2];
		itoa(stageOptionT[q], num, 10);
		copyFileBin(stageOptionS[q], num);
	}
}

void resetStageV() {
	for (int q = 0; q < TOTALSTAGEOPTIONS; q++) {
		//char num[2];
		//itoa(stageOptionReset[q], num, 10);
		//copyFileBin(stageOptionS[q], num);
		copyFileBin(stageOptionS[q], "1");
	}
}


boolean isHuntingStage() {
	if (CurrentLevel == LevelIDs_MadSpace || CurrentLevel == LevelIDs_SecurityHall || CurrentLevel == LevelIDs_DryLagoon || CurrentLevel == LevelIDs_EggQuarters || CurrentLevel == LevelIDs_WildCanyon || CurrentLevel == LevelIDs_PumpkinHill || CurrentLevel == LevelIDs_AquaticMine || CurrentLevel == LevelIDs_DeathChamber || CurrentLevel == LevelIDs_MeteorHerd)
		return true;
	return false;
}


void setChao() {
	//Chao1Data = saveChao;
	//Chao2Data = saveChao;
}

byte encodeLetter(char a) {
	switch (a){
	case '-':
		return 0x0D;
	case '_':
		return 0x3F;
	case '0':
		return 0x10;
	case '1':
		return 0x11;
	case '2':
		return 0x12;
	case '3':
		return 0x13;
	case '4':
		return 0x14;
	case '5':
		return 0x15;
	case '6':
		return 0x16;
	case '7':
		return 0x17;
	case '8':
		return 0x18;
	case '9':
		return 0x19;
	case 'A':
		return 0x21;
	case 'B':
		return 0x22;
	case 'C':
		return 0x23;
	case 'D':
		return 0x24;
	case 'E':
		return 0x25;
	case 'F':
		return 0x26;
	case 'G':
		return 0x27;
	case 'H':
		return 0x28;
	case 'I':
		return 0x29;
	case 'J':
		return 0x2A;
	case 'K':
		return 0x2B;
	case 'L':
		return 0x2C;
	case 'M':
		return 0x2D;
	case 'N':
		return 0x2E;
	case 'O':
		return 0x2F;
	case 'P':
		return 0x30;
	case 'Q':
		return 0x31;
	case 'R':
		return 0x32;
	case 'S':
		return 0x33;
	case 'T':
		return 0x34;
	case 'U':
		return 0x35;
	case 'V':
		return 0x36;
	case 'W':
		return 0x37;
	case 'X':
		return 0x38;
	case 'Y':
		return 0x39;
	case 'Z':
		return 0x3A;
	case ' ':
		return 0x5F;
	case 'a':
		return 0x41;
	case 'b':
		return 0x42;
	case 'c':
		return 0x43;
	case 'd':
		return 0x44;
	case 'e':
		return 0x45;
	case 'f':
		return 0x46;
	case 'g':
		return 0x47;
	case 'h':
		return 0x48;
	case 'i':
		return 0x49;
	case 'j':
		return 0x4A;
	case 'k':
		return 0x4B;
	case 'l':
		return 0x4C;
	case 'm':
		return 0x4D;
	case 'n':
		return 0x4E;
	case 'o':
		return 0x4F;
	case 'p':
		return 0x50;
	case 'q':
		return 0x51;
	case 'r':
		return 0x52;
	case 's':
		return 0x53;
	case 't':
		return 0x54;
	case 'u':
		return 0x55;
	case 'v':
		return 0x56;
	case 'w':
		return 0x57;
	case 'x':
		return 0x58;
	case 'y':
		return 0x59;
	case 'z':
		return 0x5A;
	default:
		return 0x5F;
	}
}

ChaoDataBase randomizeChao(ChaoDataBase cdb) {
	
	ChaoGardensUnlocked = 255;
	for (int i = 0; i < 32; i++) {
		BlackMarketSlots[i].Category = 1;
		BlackMarketSlots[i].Type = rand() % 68;
	}


	saveChao = cdb;
	if (colorChao) {
		saveChao.Color = rand() % 256;
		saveChao.Shiny = rand() % 2;
		saveChao.MonotoneHighlights = rand() % 2;
		saveChao.Texture = rand() % 110;
	}


	int modelNo = rand() % 69;
	if (modelNo > 4) modelNo = 0;
	saveChao.BodyType = modelNo;
	if (modelNo == 3) {
		int animal = rand() % 21;
		if (animal == 2) animal = 20;
		saveChao.BodyTypeAnimal = animal;
	}


	string name(chao[rand() % chaoCNT]);
	int len = 7;
	if (name.length() < 7) len = name.length();
	for (int i = 0; i < len; i++) {
		saveChao.Name[i] = encodeLetter(name[i]);
	}


	saveChao.RunLevel = rand() % 99 + 1;
	saveChao.FlyLevel = rand() % 99 + 1;
	saveChao.SwimLevel = rand() % 99 + 1;
	saveChao.PowerLevel = rand() % 99 + 1;
	saveChao.StaminaLevel = rand() % 99 + 1;
	saveChao.LuckLevel = rand() % 99 + 1;
	saveChao.IntelligenceLevel = rand() % 99 + 1;
	//saveChao.Happiness = rand() % 201 - 100;
	saveChao.Type = rand() % 25 + 1;
	//saveChao.Alignment = rand() % 3 - 1;
	saveChao.FlyGrade = rand() % 6;
	saveChao.RunGrade = rand() % 6;
	saveChao.SwimGrade = rand() % 6;
	saveChao.PowerGrade = rand() % 6;
	saveChao.StaminaGrade = rand() % 6;
	saveChao.LuckGrade = rand() % 256;
	saveChao.IntelligenceGrade = rand() % 256;

	int lvlStat = rand() % 20 + 13;
	saveChao.FlyStat = saveChao.FlyLevel *6 * (saveChao.FlyGrade + 1);
	saveChao.RunStat = saveChao.RunLevel *lvlStat* (saveChao.RunGrade + 1);
	saveChao.PowerStat = saveChao.PowerLevel *6 * (saveChao.PowerGrade + 1);
	saveChao.SwimStat = saveChao.SwimLevel *lvlStat * (saveChao.SwimGrade + 1);
	saveChao.StaminaStat = saveChao.StaminaLevel *lvlStat * (saveChao.StaminaGrade + 1);
	saveChao.LuckStat = saveChao.LuckLevel *lvlStat * (saveChao.LuckGrade + 1);
	saveChao.IntelligenceStat = saveChao.IntelligenceLevel *6 * (saveChao.IntelligenceGrade + 1);
	
	
	if(rand()%2 == 0) saveChao.PowerRun = rand() % 3 - 1;
	else saveChao.FlySwim = rand() % 3 - 1;

	saveChao.Lifespan = 200;

	//saveChao.Garden = 1;
	cdb = saveChao;
	return saveChao;
}

ChaoDataBase maxChao(ChaoDataBase cdb) {



	saveChao = cdb;

	saveChao.RunLevel = 99;
	saveChao.FlyLevel = 99;
	saveChao.SwimLevel = 99;
	saveChao.PowerLevel = 99;
	saveChao.StaminaLevel = 99;
	saveChao.LuckLevel = 99;
	saveChao.IntelligenceLevel = 99;
	//saveChao.Happiness = rand() % 201 - 100;
	saveChao.Type = 2 + (3*(rand()%8));
	//saveChao.Alignment = rand() % 3 - 1;
	saveChao.FlyGrade = 5;
	saveChao.RunGrade = 5;
	saveChao.SwimGrade = 5;
	saveChao.PowerGrade =5;
	saveChao.StaminaGrade = 5;
	saveChao.LuckGrade = 255;
	saveChao.IntelligenceGrade = 255;

	//int lvlStat = rand() % 20 + 10;
	saveChao.FlyStat = 3600;
	saveChao.RunStat = 9999;
	saveChao.PowerStat = 3600;
	saveChao.SwimStat = 9999;
	saveChao.StaminaStat = 65535;
	saveChao.LuckStat = 3600;
	saveChao.IntelligenceStat = 3600;
	//saveChao.PowerRun = rand() % 500 - 250;
	//saveChao.FlySwim = rand() % 500 - 250;
	//saveChao.Lifespan = 200;

	//saveChao.Garden = 1;
	cdb = saveChao;
	return saveChao;
}



void setUpCredits() {
	CreditEntry newCredits[Credits_Length];
	int count = 0;
	for (int i = 0; i < Credits_Length; i++) {
		if (Credits[i].type == 0) newCredits[count++] = Credits[i];
	}
	for (int i = 0; i < Credits_Length; i++) {
		if (Credits[i].type != 0) newCredits[count++] = Credits[i];
	}
	for (int i = 0; i < Credits_Length; i++) {
		Credits[i] = newCredits[i];
	}


	const int teamSize = 4;
	const int varT = 5;
	const int praT = 5;
	const int tomT = 20;
	const int izzyT = 5;
	char* tommyTitles[tomT] = { "Q&A TESTER", "DON'T CALL ME TOMMYE KKTHX","WILD CANYON MISSION 4 WR HOLDER","PUMPKIN HILL MISSION 4 WR HOLDER",
								"AQUATIC MINE MISSION 4 WR HOLDER", "DRY LAGOON MISSION 4 WR HOLDER", "EQQ QUARTERS MISSION 4 WR HOLDER",
								"SECURITY HALL MISSION 4 WR HOLDER", "MAD SPACE MISSION 4 WR HOLDER", "METEOR HERD MISSION 1 WR HOLDER",
								"METEOR HERD X20 WR HOLDER", "MAD SPACE X25 WR HOLDER", "KNUCKLES CENTURION WR HOLDER","PUMPKIN HILL X20 WR HOLDER",
								"EQQ QUARTERS X25 WR HOLDER","SECURITY HALL X25 WR HOLDER","WILD CANYON X20 WR HOLDER","DRY LAGOON X25 WR HOLDER",
								"ONE DAY I'LL BOP CHAINCHUMPER'S SH M4","UNDERTALE EARLY EMPTY GUN GENOCIDE WR HOLDER"};


	char* onvarTitles[varT] = { "SCIENCE GUY","BIT-FLIPPER","ONVARPAUSE","ONE DAY I'LL BOP CHAINCHUMPER'S SH M4","SUBSCRIBE TO TWITCH.TV / IDGEEK121"};
	
	
	char* boostedTitles[izzyT] = { "GIGACHAD","WORKED IN THE NEUTRAL BY","LEVEL DESIGN","SUBSCRIBE TO MY YOUTUBE CHANNEL","PLEASE DONT ASK ME ABOUT MY CHAO" };
	
	
	char* praTitles[praT] = { "PIECER TOGETHERER", "I LIVE ON RAMEN", "SLEEP DEPRIVED" ,"HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA","LETS PLAY BIG STORY"};
	
	
	char** titles[teamSize] = { praTitles,boostedTitles,onvarTitles,tommyTitles };
	const int noTits[teamSize] = { praT,izzyT,varT,tomT };
	char* names[teamSize] = {"Prahaha","BoostedBandCamp","OnVar","TommyeAsY"};

	int start = 1;
	int spacing = 2;


	Credits[igtSlot - 3].type = 2;
	Credits[igtSlot - 3].text = "Stats";

	Credits[igtSlot-1].type = 2;
	Credits[igtSlot-1].text = "In-Game Time Total";
	Credits[igtSlot].type = 1;
	Credits[igtSlot].text = "";

	Credits[igtSlot + 2].type = 2;
	Credits[igtSlot + 2].text = "Score Total";
	Credits[igtSlot + 3].type = 1;
	Credits[igtSlot + 3].text = "";

	Credits[igtSlot + 5].type = 2;
	Credits[igtSlot + 5].text = "Total Deaths";
	Credits[igtSlot + 6].type = 1;
	Credits[igtSlot + 6].text = "";

	Credits[igtSlot + 8].type = 2;
	Credits[igtSlot + 8].text = "Total Jumps";
	Credits[igtSlot + 9].type = 1;
	Credits[igtSlot + 9].text = "";

	Credits[igtSlot + 11].type = 2;
	Credits[igtSlot + 11].text = "Hints Read";
	Credits[igtSlot + 12].type = 1;
	Credits[igtSlot + 12].text = "";

	Credits[igtSlot + 14].type = 2;
	Credits[igtSlot + 14].text = "A Presses";
	Credits[igtSlot + 15].type = 1;
	Credits[igtSlot + 15].text = "";

	Credits[igtSlot + 17].type = 2;
	Credits[igtSlot + 17].text = "B Presses";
	Credits[igtSlot + 18].type = 1;
	Credits[igtSlot + 18].text = "";

	Credits[igtSlot + 20].type = 2;
	Credits[igtSlot + 20].text = "X Presses";
	Credits[igtSlot + 21].type = 1;
	Credits[igtSlot + 21].text = "";

	Credits[igtSlot + 23].type = 2;
	Credits[igtSlot + 23].text = "Y Presses";
	Credits[igtSlot + 24].type = 1;
	Credits[igtSlot + 24].text = "";

	Credits[igtSlot + 26].type = 2;
	Credits[igtSlot + 26].text = "Start Presses";
	Credits[igtSlot + 27].type = 1;
	Credits[igtSlot + 27].text = "";


	for (int i = 0; i < teamSize; i++) {
		Credits[start].type = 1;
		Credits[start].red = 186;
		Credits[start].green = 244;
		Credits[start].blue = 50;
		Credits[start].text = titles[i][rand()%noTits[i]];
		start++;
		Credits[start].type = 2;
		Credits[start].text = names[i];
		start += spacing;
	}

	start += 50;
	Credits[start].type = 2;
	Credits[start].text = "Shout outs";
	start++;
	Credits[start].type = 1;
	Credits[start].text = "MAINMEMORY";


	int cnt = rand() % 11 + 9;
	for (int i = 0; i < cnt; i++) {
		start++;
		Credits[start].type = 1;
		Credits[start].text = shouts[rand()%shoutCNT];
	}


}


void addUpTime() {
	int mins = (levelTimer >> 0) & 0xFF;
	int seconds = (levelTimer >> 8) & 0xFF;
	int centi = (levelTimer >> 16) & 0xFF;
	centi = ceil(centi*(10 / 6.0));

	totalCentis += centi;
	if (totalCentis > 100) {
		totalSecs += totalCentis / 100;
		totalCentis %= 100;
	}

	totalSecs += seconds;
	if (totalSecs > 60) {
		totalMins += totalSecs / 60;
		totalSecs %= 60;
	}

	totalMins += mins;
	if (totalMins > 60) {
		totalHours += totalMins / 60;
		totalMins %= 60;
	}

	fTime = "";

	if (totalHours != 0) {
		fTime += std::to_string(totalHours);
		if(totalHours == 1) fTime += " HOUR ";
		else fTime += " HOURS ";
	}

	fTime += std::to_string(totalMins);
	if (totalMins == 1) fTime += " MIN ";
	else fTime += " MINS ";

	fTime += std::to_string(totalSecs);

	fTime += ".";

	if (totalCentis < 10) fTime += "0" + std::to_string(totalCentis);
	else fTime += std::to_string(totalCentis);

	fTime += " SECONDS";
	Credits[igtSlot].text = fTime.c_str();


	score = "";
	if(ScoreP1 > 0) totalScore += ScoreP1;
	score += std::to_string(totalScore);
	Credits[igtSlot + 3].text = score.c_str();

	deaths = "";
	deaths += std::to_string(totalDeaths);
	Credits[igtSlot + 6].text = deaths.c_str();

	jumpsCount = "";
	jumpsCount += std::to_string(totalJumps);
	Credits[igtSlot + 9].text = jumpsCount.c_str();


	hintCounts = "";
	hintCounts += std::to_string(hintsRead);
	Credits[igtSlot + 12].text = hintCounts.c_str();


	Astring = "";
	Astring += std::to_string(Acount);
	Credits[igtSlot + 15].text = Astring.c_str();
	Bstring = "";
	Bstring += std::to_string(Bcount);
	Credits[igtSlot + 18].text = Bstring.c_str();
	Xstring = "";
	Xstring += std::to_string(Xcount);
	Credits[igtSlot + 21].text = Xstring.c_str();
	Ystring = "";
	Ystring += std::to_string(Ycount);
	Credits[igtSlot + 24].text = Ystring.c_str();
	Startstring = "";
	Startstring += std::to_string(Startcount);
	Credits[igtSlot + 27].text = Startstring.c_str();



}

std::string stageNumToName(int num) {

	switch (num) {
	case LevelIDs_CityEscape:
		return "City Escape";
	case LevelIDs_BigFoot:
		return "Big Foot";
	case LevelIDs_WildCanyon:
		return "Wild Canyon";
	case LevelIDs_TailsVsEggman1:
		return "Tails/Eggman 1";
	case LevelIDs_PrisonLane:
		return "Prison Lane";
	case LevelIDs_MetalHarbor:
		return "Metal Harbor";
	case LevelIDs_SonicVsShadow1:
		return "Sonic/Shadow 1";
	case LevelIDs_GreenForest:
		return "Green Forest";
	case LevelIDs_PumpkinHill:
		return "Pumpkin Hill";
	case LevelIDs_MissionStreet:
		return "Mission Street";
	case LevelIDs_AquaticMine:
		return "Aquatic Mine";
	case 70:
		return "Route 101/280";
	case LevelIDs_HiddenBase:
		return "Hidden Base";
	case LevelIDs_PyramidCave:
		return "Pyramid Cave";
	case LevelIDs_DeathChamber:
		return "Death Chamber";
	case LevelIDs_KingBoomBoo:
		return "King Boom Boo";
	case LevelIDs_EggGolemS:
		return "Hero Golem";
	case LevelIDs_EternalEngine:
		return "Eternal Engine";
	case LevelIDs_MeteorHerd:
		return "Meteor Herd";
	case LevelIDs_KnucklesVsRouge:
		return "Knuckles/Rouge";
	case LevelIDs_CrazyGadget:
		return "Crazy Gadget";
	case LevelIDs_TailsVsEggman2:
		return "Tails/Eggman 2";
	case LevelIDs_FinalRush:
		return "Final Rush";
	case LevelIDs_SonicVsShadow2:
		return "Sonic/Shadow 2";
	case LevelIDs_IronGate:
		return "Iron Gate";
	case LevelIDs_HotShot:
		return "Hot Shot";
	case LevelIDs_DryLagoon:
		return "Dry Lagoon";
	case LevelIDs_SandOcean:
		return "Sand Ocean";
	case LevelIDs_RadicalHighway:
		return "Radical Highway";
	case LevelIDs_EggQuarters:
		return "Egg Quarters";
	case LevelIDs_LostColony:
		return "Lost Colony";
	case LevelIDs_WeaponsBed:
		return "Weapons Bed";
	case LevelIDs_SecurityHall:
		return "Security Hall";
	case LevelIDs_FlyingDog:
		return "Flying Dog";
	case LevelIDs_WhiteJungle:
		return "White Jungle";
	case 71:
		return "Route 280";
	case LevelIDs_SkyRail:
		return "Sky Rail";
	case LevelIDs_EggGolemE:
		return "Dark Golem";
	case LevelIDs_MadSpace:
		return "Mad Space";
	case LevelIDs_CosmicWall:
		return "Cosmic Wall";
	case LevelIDs_FinalChase:
		return "Final Chase";
	case LevelIDs_CannonsCoreT:
		return "Cannons Core";
	case LevelIDs_Biolizard:
		return "Biolizard";
	case LevelIDs_FinalHazard:
		return "Final Hazard";

	}

	return "Uh? Oops";
}

void createSplits(int start, int end, std::string category) {
	std::ofstream myfile("RandomizerSplits.lss");
	//Header
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myfile << "<Run version=\"1.7.0\">\n";
	myfile << "<GameIcon />\n<GameName>Sonic Adventure 2: Battle</GameName>\n<CategoryName>Randomizer: ";
	myfile << category << "</CategoryName>\n<Metadata>\n";
	myfile << "<Run id = \"\" />\n";
	myfile << "<Platform usesEmulator = \"False\">\n";
	myfile << "</Platform>\n<Region>\n</Region>\n<Variables />\n</Metadata>\n<Offset>00:00:00</Offset>\n<AttemptCount>0</AttemptCount>\n";
	myfile << "<AttemptHistory />\n<Segments>\n";

	//
	for (int i = start; i <= end; i++) {
		if (Levellist[i].entry_type == 1) {
			if (Levellist[i].level_id == LevelIDs_CannonsCoreT) {
				for (int j = 0; j < 5; j++) {
					myfile << "<Segment>\n";
					myfile << "<Name>";
					if (showN)
						myfile << stageNumToName(Levellist[i].level_id) << " " << j;
					else
						myfile << "Stage: " << Levellist[i].level_id <<" "<< j;
					myfile << "</Name>\n";
					myfile << "<Icon />\n";
					myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
					myfile << "</Segment>\n";

				}
			}
			else {
				myfile << "<Segment>\n";
				myfile << "<Name>";
				if (showN)
					myfile << stageNumToName(Levellist[i].level_id);
				else
					myfile << "Stage: " << Levellist[i].level_id;
				myfile << "</Name>\n";
				myfile << "<Icon />\n";
				myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
				myfile << "</Segment>\n";
			}
		}
	}
	//
	if (category.compare("173 Emblems")==0) {
		for (int i = 0; i < 124;i++) {
			myfile << "<Segment>\n";
			myfile << "<Name>";
			myfile << "Emblem: " << i+35;
			myfile << "</Name>\n";
			myfile << "<Icon />\n";
			myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
			myfile << "</Segment>\n";
		}

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Chao 9 Emblems";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Beginner Karts";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Standard Karts";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Expert Karts";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Hero Boss Rush";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Dark Boss Rush";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";

		myfile << "<Segment>\n";
		myfile << "<Name>";
		myfile << "Last Boss Rush";
		myfile << "</Name>\n";
		myfile << "<Icon />\n";
		myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
		myfile << "</Segment>\n";



	}



	myfile << "</Segments>\n<AutoSplitterSettings />\n</Run>";

	//footer

	myfile.close();
}

void randomizeKartStats() {
	for (int i = 0; i < karts_Length; i++) {
		karts[i].accel *= float((rand() % 300 + 100) / 100.0);
		karts[i].speed_cap *= float((rand() % 400 + 100) / 100.0);
		karts[i].maxDriveSpeed *= float((rand() % 500 + 100) / 100.0);
		karts[i].breakForce *= float((rand() % 300 + 100) / 100.0);
	}
	for (int i = 0; i < kartAlts_Length; i++) {
		kartAlts[i].accel *= float((rand() % 300 + 100) / 100.0);
		kartAlts[i].speed_cap *= float((rand() % 400 + 100) / 100.0);
		kartAlts[i].maxDriveSpeed *= float((rand() % 500 + 100) / 100.0);
		kartAlts[i].breakForce *= float((rand() % 300 + 100) / 100.0);
	}

}



void LogThis(std::string file) {
	std::ofstream myfile(file);
	//myfile.open("LevelLists.txt");

	char Chars[Characters_Amy][12] = { "Sonic","Shadow","dead","dead","Knuckles","Rouge","Mech Tails","Mech Eggman" };
	char Swaps[Characters_Amy][20] = { "Amy","Metal Sonic","dead","dead","Tikal","Choas","Chao Walker","Dark Chao Walker" };
	myfile << "Seed: " << (int)seed << "\n\n";

	for (int j = 0; j < cutoff + 1; j++) {
		if (j == 0) myfile << "Hero Story\n\n";
		if (j == 47) myfile << "Dark Story\n\n";
		if (j == 91) myfile << "Last Story\n\n";
		switch (Levellist[j].entry_type) {
		case 0:
			myfile << j << ": Entry Type: Cutscene \n\t";
			break;
		case 1:
			myfile << j << ":Entry Type: Level \n\t";
			break;
		case 2:
			myfile << j << ":Entry Type: End \n\t";
			break;
		case 3:
			myfile << j << ":Entry Type: Credits\n\t";
			break;
		}

		myfile << "Character: ";
		if (Levellist[j].character_id & altcharacter) myfile << Swaps[Levellist[j].character_id] << "\n\t";
		else  myfile << Chars[Levellist[j].character_id] << "\n\t";
		myfile << "Level id: " << Levellist[j].level_id << "\n\t";
		for (int x = 0; x < 4; x++)
			myfile << "Cutscene Data: " << Levellist[j].cutscene_events[x] << ", ";
		myfile << "\n\n";
	}
	myfile.flush();
	myfile.close();
}

void Randomize(int seeda) {


	srand(seeda);

	bigFootSwap = bfPlayers[rand() % 8];
	hotShotSwap = hsPlayers[rand() % 8];
	flyDogSwap = hsPlayers[rand() % 8];
	KBBSwap = hsPlayers[rand() % 8];
	EGESwap = eggPlayers[rand() % 4];
	biolizSwap = bioLizard[rand() % 4];
	EGSSwap = bioLizard[rand() % 4];
	CCSonicSwap = bioLizard[rand() % 4];

	int r;
	RmissionNum = rand() % 5 + 0;

	for (int i = 0; i < Characters_Amy; i++) {

		for (int i = 0; i < 55; i++) {
			nonloopingMap[nonlooping[i]] = rand() % 55;
		}
		for (int i = 0; i < 102; i++) {
			loopingMap[looping[i]] = rand() % 102;
		}
		for (int i = 0; i < 2727; i++) {
			storeVL[i] = i;
		}
		for (int i = 0; i < 2727; i++) {
			int store = storeVL[i];
			int r = rand() % 2727;
			storeVL[i] = storeVL[r];
			storeVL[r] = store;
		}


		alt = rand() % 3;
		if (alt == 2) alt = 1;
		else alt = 0;
		cost = rand() % 2;
		//defaultalts[i] = alt;
		//defaultcosts[i] = cost;
		//r = rand() % 6 + 2;

		//if (r < 4) r -= 2;
		r = useThisPool[rand() % numCharsinPool];
		//PrintDebug(std::to_string(r).c_str());


		if (noVanillaChars) {
			if (i == r) r++; //crashes as one if
			r = r % Characters_Amy;
			if (r == Characters_Tails) { //Means this was shadow before vanilla chars
				int canBePicked[5] = { Characters_Sonic, Characters_MechTails,Characters_MechEggman,Characters_Rouge,Characters_Knuckles };
				r = canBePicked[rand() % 5];
				if (alt == 1) r |= altcharacter;
			}
		}

		if (i == Characters_Rouge) {
			if (noVanillaChars) {
				int canBePicked[3] = { Characters_Sonic, Characters_Shadow,Characters_Knuckles };
				r = canBePicked[rand() % 3];
				if (alt == 1) r |= altcharacter;
			}
			else {
				int canBePicked[4] = { Characters_Sonic, Characters_Shadow,Characters_Knuckles,Characters_Rouge };
				r = canBePicked[rand() % 4];
				if (alt == 1) r |= altcharacter;
			}
		}
		
		/*if (i == Characters_Knuckles) {
			if (noVanillaChars) {
				int canBePicked[3] = { Characters_Sonic, Characters_Shadow,Characters_Rouge};
				r = canBePicked[rand() % 3];
			}
			else {
				int canBePicked[4] = { Characters_Sonic, Characters_Shadow,Characters_Knuckles,Characters_Rouge };
				r = canBePicked[rand() % 4];
			}
		}*/


		defaultcharacters[i] = r;
		if (i == Characters_Sonic || i == Characters_Shadow)defaultcharactersM5[i] = speedsters[rand() % 4];
		if (i == Characters_Knuckles || i == Characters_Rouge)defaultcharactersM5[i] = hunters[rand() % 4];
		if (i == Characters_MechEggman || i == Characters_MechTails)defaultcharactersM5[i] = mechs[rand() % 4];
		//else defaultcharactersM5[i] = 0;

		//if(alt == 1 && altncost == 1) defaultcharacters[i] = r | altcharacter;
		else if (cost == 1 && nocosts == 0) {
			//if(r != Characters_MechEggman)
				defaultcharacters[i] = r | altcostume;
		}

		//if (nocosts == 1) defaultcosts[i] = 0;
		//if (altncost == 0) defaultalts[i] = 0;
		//if( r == 0) defaultcosts[i] = 0;
		//if (r == 7) defaultcosts[i] = 0;
		//if (defaultalts[i] == 1) defaultcosts[i] = 0;
	}

	//defaultcharacters[Characters_Knuckles] = Characters_Knuckles + rand() % 2;
	//defaultcharacters[Characters_Rouge] = Characters_Knuckles + rand() % 2;



	cutoff = 0;
	int firstcut = 0;

	for (int j = 0; j < 113; j++) {
		if (Levellist[j].entry_type == 2 && firstcut == 0) {
			cutoff = j;
			if (heroonly == 1) firstcut = 1;
		}
	}

	if (bossInPool == 0)cutoff = 98;

	DataArray(LevelLookupEntry, randoMeDaddy, 0x0173A148, cutoff);
	//LogThis("PreShuffle.txt");
	if (!disRL) {
		for (int j = 0; j < cutoff; j++) {
			int spot = rand() % cutoff;

			if (randoMeDaddy[j].entry_type != 2 && randoMeDaddy[spot].entry_type != 2 && j != 41 && j != 42 && j != 43 && j != 44 && j != 85 && j != 86 && j != 87 && j != 88 && j != 95 && j != 96 && j != 98 && spot != 41 && spot != 42 && spot != 43 && spot != 44 && spot != 85 && spot != 86 && spot != 87 && spot != 88 && spot != 95 && spot != 96 && spot != 98) {
					LevelLookupEntry temp = randoMeDaddy[j];
					randoMeDaddy[j] = randoMeDaddy[spot];
					randoMeDaddy[spot] = temp;
			}
			//if (randoMeDaddy[j].entry_type == 1)
				//for (int i = 0; i < 4; i++)
					//randoMeDaddy[j].cutscene_events[i] = -1;
		}

		//sehar = settings->getBool("OnOff", "setchars");
		//boolean sehar = false;
	}

		if (sehar) {
			for (int i = 0; i < Characters_Amy; i++) {
				defaultalts[i] = 0;
				defaultcosts[i] = 0;
				defaultcharacters[i] = storedPrefs[i];
			}
		}
	

	//int repper[8] = {0,1,2,3,4,5,6};
	//for (int i = 0; i < StageSelectLevels_Length; i++) 
	//	StageSelectLevels[i].Character = defaultcharacters[repper[StageSelectLevels[i].Character]];

		if (seed == 69) {
			for (int i = 0; i < Characters_Amy; i++) {
				defaultcharacters[i] = Characters_Rouge | altcostume;
			}
		}

		if (true) stageV();
		else resetStageV();

		if(story.compare("Hero") == 0)
			createSplits(0,45, "Hero Story");
		if (story.compare("Dark") == 0)
			createSplits(46, 89, "Dark Story");
		if (story.compare("All") == 0)
			createSplits(0, 98, "All Stories");
		if (story.compare("173") == 0)
			createSplits(0, 98, "173 Emblems");
}



static char* __cdecl randMusic(char* song) {
	srand(rand() *time(NULL));
	//cADX = true;
	for (int i = 0; i < 55; i++) {
		if (strcmp(song, nonlooping[i]) == 0) {
			if(!cADX)	return nonlooping[rand() % 55];
			else	return nonlooping[nonloopingMap[song]];
		}
	}
	if(!cADX) return looping[rand() % 102];
	return looping[loopingMap[song]];
}


static const int loc_jmpbackM = 0x442cf5;
__declspec(naked) void PlayMusic_r() {
	__asm
	{
		push edi
		call randMusic
		add esp, 4
		mov edi, eax
		mov EAX, [0x01A55998]
		jmp loc_jmpbackM
	}
}

static int __cdecl randVoice(int a) {
	srand(rand() *time(NULL));
	if (cVoices) return storeVL[a];
	return rand() % 2727;//4734 both or 2727 SA2 Only
}


static const int loc_jmpback = 0x44313D;
__declspec(naked) void PlayVoice_r() {
	__asm
	{
		mov eax, [esp + 4]
		push eax
		call randVoice
		add esp, 4 
		mov [esp + 0x04], eax
		jmp loc_jmpback
	}
}


boolean is2PChar() {
	if (CurrentCharacter == Characters_Eggman || CurrentCharacter == Characters_Tails) return false;
	if (CurrentCharacter == Characters_Shadow | altcharacter || CurrentCharacter == Characters_Sonic | altcharacter || CurrentCharacter == Characters_Rouge | altcharacter || CurrentCharacter == Characters_Knuckles | altcharacter || CurrentCharacter == Characters_MechTails | altcharacter || CurrentCharacter == Characters_MechEggman | altcharacter)
		return true;
	return false;
}


void __cdecl LoadCharacters_r()
{
	createCount = 3000;
	if (CurrentLevel != LevelIDs_ChaoWorld)
	{
		if ((CurrentCharacter & ~1) == Characters_Tails)
			CurrentCharacter += Characters_MechTails - Characters_Tails;
	}
	else
	{
		if (!disChaoReload) {
			srand(time(NULL));
			seed = rand();
			Randomize(seed);
			if (rkart) randomizeKartStats();
			if (true) LogThis("LevelLists.txt");
		}
		if ((CurrentCharacter & ~1) == Characters_MechTails)
			CurrentCharacter -= Characters_MechTails - Characters_Tails;
	}
	if (!TwoPlayerMode && CurrentLevel != LevelIDs_FinalHazard && CurrentLevel != LevelIDs_ChaoWorld)
	{
		if (randomMissions) MissionNum = rand() % 5;
		int ch = defaultcharacters[CurrentCharacter];
		if(MissionNum == 4) ch = defaultcharactersM5[CurrentCharacter];
		CurrentCharacter = ch & charmask;
		AltCostume[1] = AltCostume[0] = ch & altcostume ? 1 : 0;
		AltCharacter[1] = AltCharacter[0] = ch & altcharacter ? 1 : 0;
	}
	int playerNum = 0;
	int *character = &CurrentCharacter;
	int buttons = MenuButtons_Held[0];
	int allUps = 1;

	if (CurrentLevel == LevelIDs_ChaoWorld) {
		int canPick[6] = { 0,1,4,5 };
		*character = canPick[rand()%6];
		AltCostume[0] = 0;
		AltCharacter[0] = 0;
	}

LoopStart:

	///STUFF//////////
	


	objPlacedInStage = false;
	//if (randomMissions) MissionNum = rand() % 5;
	Life_Count[0] = 99;
	TimeStopped = 0;
	//Chao_Display(CreateChao(ChaoDataArray[0], CurrentChaoArea, GetCurrentChaoStage_ptr, (0, 0, 0), (0, 0, 0)));

	if (false) {
		*character = rand() % 6 + 2;
		if (*character < 4) *character -= 2;
		int ctype = 2;
		if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow) ctype = 0;
		if (CurrentCharacter == Characters_Rouge || CurrentCharacter == Characters_Knuckles) ctype = 1;
		string cfb = "00";
		if (CurrentLevel < 10) cfb += "0";
		cfb += std::to_string(CurrentLevel);
		string scfb = cfb + "_s";
		string ucfb = cfb + "_u";

		copyFileBin(scfb.c_str(), std::to_string(ctype).c_str());
		copyFileBin(ucfb.c_str(), std::to_string(ctype).c_str());
	}

	/*//Testing Stuff


	for (int i = 0; i < StageSelectLevels_Length; i++)
		StageSelectLevels[i].Character = 0;

	StageSelectLevel *chao = new StageSelectLevel();
	chao->Level = 60;
	chao->Character = 0;
	chao->Row = 1;
	chao->Column = 1;
	StageSelectLevels[22] = *chao;*///
	

	
	///SET STARTING UPGRADES
	if (allUps == 1) {
		SonicMysticMelodyGot = 1;
		SonicBounceBraceletGot = 1;
		SonicFlameRingGot = 1;
		SonicLightShoesGot = 1;
		SonicAncientLightGot = 0;

		ShadowMysticMelodyGot = 1;
		ShadowFlameRingGot = 1;
		ShadowAirShoesGot = 1;
		ShadowAncientLightGot = 0;

		KnucklesMysticMelodyGot = 1;
		KnucklesHammerGlovesGot = 1;
		KnucklesShovelClawGot = 1;
		KnucklesSunglassesGot = 1;

		RougeMysticMelodyGot = 1;
		RougeIronBootsGot = 1;
		RougePickNailsGot = 1;
		RougeTreasureScopeGot = 1;

		TailsMysticMelodyGot = 1;
		TailsBoosterGot = 1;
		TailsBazookaGot = 1;
		TailsLaserBlasterGot = 1;


		EggmanMysticMelodyGot = 1;
		EggmanJetEngineGot = 1;
		EggmanLargeCannonGot = 1;
		EggmanLaserBlasterGot = 1;
		EggmanProtectiveArmorGot = 1;
	}
	else if (allUps == 2) {
		SonicMysticMelodyGot = 1;
		ShadowMysticMelodyGot = 1;
		KnucklesMysticMelodyGot = 1;
		RougeMysticMelodyGot = 1;
		TailsMysticMelodyGot = 1;
		TailsBoosterGot = 1;
		EggmanMysticMelodyGot = 1;
		EggmanJetEngineGot = 1;
	}

	//srand(time(NULL));


	if (!disKill) WriteData<1>((void*)0x46AD50, 0x55);
	springID = 3;
	itemBoxID = 10;
	MMID = 37;
	//saveSETCount = SETObjects->LoadCount;

	//safety checks for testing purps
	if (allUps != 3) {
		//BOSSES

		if (CurrentLevel == LevelIDs_BigFoot) {
			int ch = bigFootSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_HotShot) {
			int ch = hotShotSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_FlyingDog) {
			int ch = flyDogSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_KingBoomBoo) {
			int ch = KBBSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_EggGolemE) {
			int ch = EGESwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_Biolizard){
			int ch = biolizSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}
		
		if (CurrentLevel == LevelIDs_CannonsCoreS) {
			int ch = CCSonicSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}

		if (CurrentLevel == LevelIDs_EggGolemS) {
			int ch = EGSSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
		}
		
		switch (CurrentLevel) {
			int cha;
		case LevelIDs_TailsVsEggman1:
			*character = Characters_MechTails + rand() % 2;
			break;
		case LevelIDs_TailsVsEggman2:
			*character = Characters_MechTails;
			break;
		case LevelIDs_KnucklesVsRouge:
			*character = Characters_Knuckles + rand() % 2;
			break;
		case LevelIDs_SonicVsShadow1:
			*character = Characters_Sonic + rand() % 2;
			AltCostume[1] = AltCostume[0] = 0;
			break;
		case LevelIDs_SonicVsShadow2:
			if (CurrentCharacter == Characters_MechEggman) *character = Characters_MechTails;
			AltCostume[1] = AltCostume[0] = 0;
			break;
		case LevelIDs_WhiteJungle:
			if (CurrentCharacter == Characters_MechTails)	*character = Characters_Tails;
			if (CurrentCharacter == Characters_MechEggman)	*character = Characters_Eggman;
			springID = 1;
			itemBoxID = 6;
			MMID = 49;
			break;
		case LevelIDs_SkyRail:
			springID = 1;
			itemBoxID = 6;
			MMID = 33;
			break;
		case LevelIDs_PumpkinHill:
			springID = 1;
			itemBoxID = 6;
			MMID = 33;
			break;
		case LevelIDs_AquaticMine:
			if (CurrentCharacter == Characters_MechTails) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Tails;
			}
			if (CurrentCharacter == Characters_MechEggman) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Eggman;
			}
			springID = 1;
			itemBoxID = 6;
			MMID = 30;
			break;

		case LevelIDs_DeathChamber:
			if (CurrentCharacter == Characters_MechTails) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Tails;
			}
			if (CurrentCharacter == Characters_MechEggman) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Eggman;
			}
			break;

		case LevelIDs_CannonsCoreK:
			if (CurrentCharacter == Characters_MechTails) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Tails;
			}
			if (CurrentCharacter == Characters_MechEggman) {
				AltCharacter[0] = 0;
				AltCostume[0] = 0;
				*character = Characters_Eggman;
			}
			break;

		case LevelIDs_IronGate:
			springID = 1;
			itemBoxID = 6;
			break;
		case LevelIDs_GreenForest:
			if (CurrentCharacter == Characters_Sonic) AltCostume[0] = 0;
			if (CurrentCharacter == Characters_MechTails)	*character = Characters_Tails;
			if (CurrentCharacter == Characters_MechEggman)	*character = Characters_Eggman;
			springID = 1;
			itemBoxID = 6;
			MMID = 51;
			break;
		case LevelIDs_HiddenBase:
			if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow || CurrentCharacter == Characters_MechEggman) WriteData<1>((void*)0x46AD50, 0xC3); //C3
			break;
		case LevelIDs_MadSpace:
			if (!noVanillaChars) {
				if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_MechTails) *character = Characters_Knuckles;
				if (CurrentCharacter == Characters_Shadow || CurrentCharacter == Characters_MechEggman) *character = Characters_Rouge;
			}
			if (noVanillaChars) {
				*character = Characters_Knuckles;
			}
			break;

		case LevelIDs_FinalHazard:
			
			break;
		case LevelIDs_CrazyGadget:
			if (CurrentCharacter == Characters_MechTails) AltCostume[0] = 0;
			MMID = 35;
			break;


		}


	}

	if (CurrentLevel != LevelIDs_CosmicWall) {
		SonicAncientLightGot = 1;
		ShadowAncientLightGot = 1;
	}

	if (CurrentCharacter == Characters_MechEggman && randoSV) AltCostume[0] = 0;

	if (setRNG) {
		if (isHuntingStage()) {
			FrameCount = seed % 1023 + 1;
			FrameCountIngame = seed % 1023 + 1;
		}
	}



	int repcnt;
	pair<short, short> *replst;
	switch (*character)
	{

	case Characters_Sonic:
		LoadSonic(playerNum);
		repcnt = (int)LengthOfArray(SonicAnimReplacements);
		replst = SonicAnimReplacements;
		break;
	case Characters_Shadow:
		LoadShadow(playerNum);
		repcnt = (int)LengthOfArray(SonicAnimReplacements);
		replst = SonicAnimReplacements;
		break;
	case Characters_Tails:
		LoadTails(playerNum);
		repcnt = (int)LengthOfArray(OthersAnimReplacements);
		replst = OthersAnimReplacements;
		break;
	case Characters_Eggman:
		LoadEggman(playerNum);
		repcnt = (int)LengthOfArray(OthersAnimReplacements);
		replst = OthersAnimReplacements;
		break;
	case Characters_Knuckles:
		LoadKnuckles(playerNum);
		repcnt = (int)LengthOfArray(KnucklesAnimReplacements);
		replst = KnucklesAnimReplacements;
		break;
	case Characters_Rouge:
		LoadRouge(playerNum);
		repcnt = (int)LengthOfArray(KnucklesAnimReplacements) - 3;
		replst = KnucklesAnimReplacements;
		break;
	case Characters_MechTails:
		LoadMechTails(playerNum);
		repcnt = (int)LengthOfArray(MechAnimReplacements);
		replst = MechAnimReplacements;
		break;
	case Characters_MechEggman:
		LoadMechEggman(playerNum);
		repcnt = (int)LengthOfArray(MechAnimReplacements);
		replst = MechAnimReplacements;
		break;
	}

	InitPlayer(playerNum);
	AnimationInfo *anilst = MainCharObj2[playerNum]->AnimInfo.Animations;
	for (int i = 0; i < repcnt; i++)
		//if (!CharacterAnimations[anilst[replst[i].key].AnimNum].Animation)
			anilst[replst[i].key] = anilst[replst[i].value];
	if (playerNum == 1)
		goto end;
	playerNum++;
	buttons = MenuButtons_Held[1];
	if (buttons & Buttons_Start)
		CurrentCharacter2P = CurrentCharacter ^ 1;
	else if (!TwoPlayerMode)
		goto end;
	character = &CurrentCharacter2P;
	goto LoopStart;
end:
	LoadEmeraldManager_r();
}

#define Texlist_SonEff 0xA08B94
#define Texlist_ShadEff 0xA08D94
#define Texlist_AmyEff 0xA08F94
#define Texlist_MetEff 0xA0917C
const int loc_75783C = 0x75783C;
__declspec(naked) void __cdecl sub_757810()
{
	__asm
	{
		mov     eax, [esp+4]
		mov     eax, [eax]ObjectMaster.Data2
			movsx   ecx, [eax].CharID
			mov     edx, MainCharObj2
			mov edx, [edx+ecx*4]
		mov ecx, 0xA0B3B8
			mov dl, [edx].CharID2
			cmp     dl, Characters_Sonic
			jnz NotSonic
			mov     dword ptr [ecx], Texlist_SonEff
			jmp loc_75783C

NotSonic:
		cmp     dl, Characters_Shadow
			jnz NotShadow
			mov     dword ptr [ecx], Texlist_ShadEff
			jmp loc_75783C

NotShadow:
		cmp     dl, Characters_Amy
			jnz NotAmy
			mov     dword ptr [ecx], Texlist_AmyEff
			jmp loc_75783C

NotAmy:
		mov     dword ptr [ecx], Texlist_MetEff
			jmp loc_75783C
	}
}

const int loc_759A3C = 0x759A3C;
__declspec(naked) void loc_759A18()
{
	__asm
	{
		movsx	eax, [eax].CharID2
			mov	ecx, 0x2670544
			mov ecx, [ecx]
		cmp	eax, Characters_Sonic
			jne	short NotSonic
			mov	dword ptr [ecx+20h], Texlist_SonEff
			jmp	loc_759A3C

NotSonic:
		cmp	eax, Characters_Shadow
			jne	short NotShadow
			mov	dword ptr [ecx+20h], Texlist_ShadEff
			jmp	loc_759A3C

NotShadow:
		cmp	eax, Characters_Amy
			jne	short NotAmy
			mov	dword ptr [ecx+20h], Texlist_AmyEff
			jmp	loc_759A3C

NotAmy:
		mov	dword ptr [ecx+20h], Texlist_MetEff
			jmp	loc_759A3C
	}
}

#pragma warning(disable : 4838)
StartPosition KnucklesStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_AquaticMine, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_DeathChamber, 0xA000u, 0x8000u, 0xC000u, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_KingBoomBoo, 0, 0, 0, { 276, -40, 190 }, { 276, -40, 190 }, { 276, -40, 190 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { -20, 0, 0 }, { -20, 0, 0 }, { -20, 0, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 66, -345 }, { 180, 66, -345 } },
	{ LevelIDs_CannonsCoreK, 0x8000u, 0x8000u, 0x8000u, { 0, 580, 60 }, { 0, 580, 60 }, { 0, 580, 60 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -450, -1025 }, { 25, -450, -1025 }, { -25, -450, -1025 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 220, 210, 1350 }, { 225, 480, 1325 }, { 185, 480, 1325 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_PlanetQuest, 0, 0x4000, 0x4000, { 0, 660, 0 }, { -470, 1500, -630 }, { -430, 1500, -630 } },
	{ LevelIDs_SecurityHall, 0xA000u, 0xA000u, 0xE000u, { 405, -830, 410 }, { 405, -830, 410 }, { -405, -830, 410 } },
	{ LevelIDs_EggQuarters, 0xA000u, 0xC000u, 0xC000u, { 940, -30, 940 }, { 20, 110, 40 }, { -20, 110, 40 } },
	{ LevelIDs_MadSpace, 0x7000, 0xC000u, 0xC000u, { 0, 660, 0 }, { 30, 630, 17 }, { 0, 630, -35 } },
	{ LevelIDs_DeathChamber2P, 0xA000u, 0x8000u, 0xC000u, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 0, -400, -910 }, { -40, -400, -910 }, { 40, -400, -910 } },
	{ LevelIDs_CannonsCoreS, 0xC000u, 0xC000u, 0xC000u, { 0, -480, -1000 }, { 0, -480, -1000 }, { 0, -480, -1000 } },
	{ LevelIDs_FinalChase, 0xC000u, 0xC000u, 0xC000u, { 3192, -4045,2228 }, { 3192, -4045,2228 }, { 3192, -4045,2228 } },
	{ LevelIDs_Invalid }
};

StartPosition MechEggmanStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_IronGate },
	{ LevelIDs_WeaponsBed, 0xC000u, 0xC000u, 0xC000u, { 0 }, { 10, 0, 0 }, { -10, 0, 0 } },
	{ LevelIDs_WeaponsBed2P, 0xC000u, 0xC000u, 0x4000, { 50, -170, 50 }, { 20, -170, 95 }, { 20, -170, -95 } },
	{ LevelIDs_TailsVsEggman1, 0xB200u, 0xB200u, 0xB200u, { 50, -170, 50 }, { 50, -170, 50 }, { 50, -170, 50 } },
	{ LevelIDs_SandOcean, 0xC000u, 0xC000u, 0xC000u, { 0, 80, 0 }, { 0, 80, 0 }, { 0, 80, 0 } },
	{ LevelIDs_EternalEngine, 0xC000u, 0xC000u, 0xC000u, { 0, 370, 0 }, { 0, 370, 0 }, { 0, 370, 0 } },
	{ LevelIDs_LostColony, 0xC000u, 0xC000u, 0xC000u, { 0, -175, 29 }, { 0, -175, 29 }, { 0, -175, 29 } },
	{ LevelIDs_TailsVsEggman2, 0xB200u, 0xB200u, 0xB200u, { 50, -50, 80 }, { 50, -50, 80 }, { 50, -50, 80 } },
	{ LevelIDs_MissionStreet2P, 0, 0, 0x8000u, { -520, 0, 0 }, { -520, 0, 0 }, { 0 } },
	{ LevelIDs_EggGolemE, 0, 0, 0, { 0, 200, 210 }, { 0, 200, 210 }, { 0, 200, 210 } },
	{ LevelIDs_CannonsCoreE, 0xC000u, 0xC000u, 0xC000u, { 0, 20.1f, -200 }, { 0, 20.1f, -200 }, { 0, 20.1f, -200 } },
	{ LevelIDs_SandOcean2P, 0, 0, 0x8000u, { -60, 35, 0 }, { -60, 35, 0 }, { 60, 35, 0 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0xC000u, { 0 }, { -15, -170, 1480 }, { 15, -170, 1480 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x8000u, { -280, 150, 280 }, { -280, 150, 280 }, { 280, 150, -280 } },
	{ LevelIDs_PyramidRace, 0, 0xC000u, 0xC000u, { 0 }, { -35, 10, -20 }, { 35, 10, -20 } },
	{ LevelIDs_HiddenBase2P, 0, 0, 0x8000u, { 60, 0, 10 }, { -60, 0, 10 }, { 60, 0, 10 } },
	{ LevelIDs_CosmicWall2P, 0, 0, 0x8000u, { -80, 0, 0 }, { -80, 0, 0 }, { 80, 0, 5 } },
	{ LevelIDs_EternalEngine2P, 0x4000, 0x4000, 0xC000u, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_IronGate2P, 0, 0, 0x8000u, { 0 }, { -50, -10, -20 }, { 50, -10, -20 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 0, 0, -1330 }, { -40, 0, -1330 }, { 40, 0, -1330 } },
	//{ LevelIDs_FinalRush, 0xC000u, 0xC000u, 0xC000u, { 3220, -975, 0 }, { 3220, -975, 0 }, { 3220, -975, 0 } },
	{ LevelIDs_FinalChase, 0xC000u, 0xC000u, 0xC000u, { 3192, -4045,2228 }, { 3192, -4045,2228 }, { 3192, -4045,2228 } },
	{ LevelIDs_GreenForest, 0xC000u, 0xC000u, 0xC000u, {2,-870,1290 }, {2,-870,1290 }, {2,-870,1290 } },
	{ LevelIDs_CannonsCoreS, 0xC000u, 0xC000u, 0xC000u, { 0, -480, -1000 }, { 0, -480, -1000 }, { 0, -480, -1000 } },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_Invalid }
};

StartPosition MechTailsStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PrisonLane, 0x8000u, 0x8000u, 0x8000u, { 115, 10, 4 }, { 115, 10, 4 }, { 115, 10, 4 } },
	{ LevelIDs_WeaponsBed, 0xC000u, 0xC000u, 0xC000u, { 0 }, { 10, 0, 0 }, { -10, 0, 0 } },
	{ LevelIDs_WeaponsBed2P, 0xC000u, 0xC000u, 0x4000, { 50, -170, 50 }, { 20, -170, 95 }, { 20, -170, -95 } },
	{ LevelIDs_MissionStreet, 0xC000u, 0xC000u, 0xC000u, { 0, 200, 0 }, { 0, 200, 0 }, { 0, 200, 0 } },
	{ LevelIDs_TailsVsEggman1, 0x3800, 0x3800, 0x3800, { 50, -170, -250 }, { 50, -170, -250 }, { 50, -170, -250 } },
	{ LevelIDs_HiddenBase, 0xC000u, 0xC000u, 0xC000u, { 0, 140, 0 }, { 0, 140, 0 }, { 0, 140, 0 } },
	{ LevelIDs_EternalEngine, 0xC000u, 0xC000u, 0xC000u, { 0, 370, 0 }, { 0, 370, 0 }, { 0, 370, 0 } },
	{ LevelIDs_TailsVsEggman2, 0x3800, 0x3800, 0x3800, { 50, -50, -80 }, { 50, -50, -80 }, { 50, -50, -80 } },
	{ LevelIDs_MissionStreet2P, 0x8000u, 0, 0x8000u, { 0 }, { -520, 0, 0 }, { 0 } },
	{ LevelIDs_CannonsCoreT, 0xC000u, 0xC000u, 0xC000u, { 0, 670, 0 }, { 0, 670, 0 }, { 0, 670, 0 } },
	{ LevelIDs_SandOcean2P, 0, 0, 0x8000u, { -60, 35, 0 }, { -60, 35, 0 }, { 60, 35, 0 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0xC000u, { 0 }, { -15, -170, 1480 }, { 15, -170, 1480 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x8000u, { -280, 150, 280 }, { -280, 150, 280 }, { 280, 150, -280 } },
	{ LevelIDs_PyramidRace, 0, 0xC000u, 0xC000u, { 0 }, { -35, 10, -20 }, { 35, 10, -20 } },
	{ LevelIDs_HiddenBase2P, 0, 0, 0x8000u, { 60, 0, 10 }, { -60, 0, 10 }, { 60, 0, 10 } },
	{ LevelIDs_EternalEngine2P, 0x4000, 0x4000, 0xC000u, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_IronGate2P, 0, 0, 0x8000u, { 0 }, { -50, -10, -20 }, { 50, -10, -20 } },
	{ LevelIDs_CosmicWall2P, 0, 0, 0x8000u, { -80, 0, 0 }, { -80, 0, 0 }, { 80, 0, 5 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 0, 0, -1330 }, { -40, 0, -1330 }, { 40, 0, -1330 } },
	//{ LevelIDs_FinalRush, 0xC000u, 0xC000u, 0xC000u, { 3220, -975, 0 }, { 3220, -975, 0 }, { 3220, -975, 0 } },
	{ LevelIDs_FinalChase, 0xC000u, 0xC000u, 0xC000u, { 3192, -4045,2228 }, { 3192, -4045,2228 }, { 3192, -4045,2228 } },
	{ LevelIDs_GreenForest, 0xC000u, 0xC000u, 0xC000u, {2,-870,1290 }, {2,-870,1290 }, {2,-870,1290 } },
	{ LevelIDs_CannonsCoreS, 0xC000u, 0xC000u, 0xC000u, { 0, -480, -1000 }, { 0, -480, -1000 }, { 0, -480, -1000 } },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_Invalid }
};

StartPosition RougeStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SecurityHall, 0xA000u, 0xA000u, 0xE000u, { 405, -830, 410 }, { 405, -830, 410 }, { -405, -830, 410 } },
	{ LevelIDs_DeathChamber, 0xA000u, 0x8000u, 0xC000u, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_EggQuarters, 0xA000u, 0xC000u, 0xC000u, { 940, -30, 940 }, { 20, 110, 40 }, { -20, 110, 40 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 65, -400 }, { 200, 65, -400 }, { 200, 65, -400 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_KnucklesVsRouge, 0x8000u, 0x8000u, 0x8000u, { 20, 0, 0 }, { 20, 0, 0 }, { 20, 0, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 66, -345 }, { 180, 66, -345 } },
	{ LevelIDs_CannonsCoreR, 0xC000u, 0xC000u, 0xC000u, { 0, 480, 150 }, { 0, 480, 150 }, { 0, 480, 150 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -450, -1025 }, { 25, -450, -1025 }, { -25, -450, -1025 } },
	{ LevelIDs_MadSpace, 0x7000, 0xC000u, 0xC000u, { 0, 660, 0 }, { 30, 630, 17 }, { 0, 630, -35 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 220, 210, 1350 }, { 225, 480, 1325 }, { 185, 480, 1325 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_PlanetQuest, 0, 0x4000, 0x4000, { 0, 660, 0 }, { -470, 1500, -630 }, { -430, 1500, -630 } },
	{ LevelIDs_DeathChamber2P, 0xA000u, 0x8000u, 0xC000u, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 0, -400, -910 }, { -40, -400, -910 }, { 40, -400, -910 } },
	{ LevelIDs_CannonsCoreS, 0xC000u, 0xC000u, 0xC000u, { 0, -480, -1000 }, { 0, -480, -1000 }, { 0, -480, -1000 } },
	{ LevelIDs_FinalChase, 0xC000u, 0xC000u, 0xC000u, { 3192, -4045,2228 }, { 3192, -4045,2228 }, { 3192, -4045,2228 } },
	{ LevelIDs_Invalid }
};

StartPosition ShadowStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0x7000u, 0x7000u, 0x7000u, { 2240, -1305, -1662 }, { 2240, -1305, -1662 }, { 2240, -1305, -1662 } },
	{ LevelIDs_GreenForest, 0x4000, 0x4000, 0x4000, { 1.61f, 40, -416 }, { 15, 40, -416 }, { -15, 40, -416 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0x4000, 0x4000, { 0, -85, -45 }, { 15, -85, -45 }, { -15, -85, -45 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -9.5f, 800, -526.1438f }, { -9.5f, 800, -526.1438f }, { 8.7f, 800, -526.1438f } },
	{ LevelIDs_CityEscape, 0x4000, 0x4000, 0x4000, { 0, 300, 340 }, { 10, 300, 340 }, { -10, 300, 340 } },
	{ LevelIDs_MetalHarbor, 0xC000u, 0xC000u, 0xC000u, { 0, 500, 40 }, { 10, 500, 45 }, { -10, 500, 45 } },
	{ LevelIDs_MetalHarbor2P, 0xC000u, 0xC000u, 0xC000u, { 0, 500, 40 }, { -10, 500, 45 }, { 10, 500, 45 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 103, 182, -39 }, { 103, 182, -39 }, { -103, 182, -39 } },
	{ LevelIDs_SonicVsShadow1, 0x8000u, 0x8000u, 0x8000u, { 60, 64, 0 }, { 60, 64, 0 }, { 60, 64, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0xC000u, 0xC000u, { 0, 180, 340 }, { 20, 180, 340 }, { -20, 180, 340 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, -1000 }, { 0, 0, -1000 }, { 0, 0, -1000 } },
	{ LevelIDs_SonicVsShadow2, 0, 0, 0, { 0, 0, 15 }, { 0, 0, 15 }, { 0, 0, 15 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, 0 }, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_FinalChase, 0, 0x4000, 0x4000, { -223, -100, 63 }, { 3206, -4000, 2455 }, { 3176, -4000, 2455 } },
	{ LevelIDs_GreenHill, 0xC000u, 0xC000u, 0xC000u, { 0, 40, 0 }, { 15, 40, 0 }, { -15, 40, 0 } },
	{ LevelIDs_DowntownRace, 0x4000, 0x4000, 0x4000, { -2215, 4320, -4670 }, { -2235, 4320, -4670 }, { -2195, 4320, -4670 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 10, -445, -900 }, { 10, -795, -900 }, { -10, -795, -900 } },
	{ LevelIDs_Invalid }
};

StartPosition SonicStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0x7000u, 0x7000u, 0x7000u, { 2240, -1305, -1662 }, { 2240, -1305, -1662 }, { 2240, -1305, -1662 } },
	{ LevelIDs_GreenForest, 0x4000, 0x4000, 0x4000, { 1.61f, 40, -416 }, { 15, 40, -416 }, { -15, 40, -416 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -9.5f, 800, -526.1438f }, { -9.5f, 800, -526.1438f }, { 8.7f, 800, -526.1438f } },
	{ LevelIDs_MetalHarbor, 0xC000u, 0xC000u, 0xC000u, { 0, 500, 40 }, { 10, 500, 45 }, { -10, 500, 45 } },
	{ LevelIDs_MetalHarbor2P, 0xC000u, 0xC000u, 0xC000u, { 0, 500, 40 }, { -10, 500, 45 }, { 10, 500, 45 } },
	{ LevelIDs_CityEscape, 0x4000, 0x4000, 0x4000, { 0, 300, 340 }, { 10, 300, 340 }, { -10, 300, 340 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0x4000, 0x4000, { 0, -85, -45 }, { 15, -80, -45 }, { -15, -80, -45 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 103, 182, -39 }, { 103, 182, -39 }, { -103, 182, -39 } },
	{ LevelIDs_SonicVsShadow1, 0, 0, 0, { -60, 64, 0 }, { -60, 64, 0 }, { -60, 64, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0xC000u, 0xC000u, { 0, 180, 340 }, { 20, 180, 340 }, { -20, 180, 340 } },
	{ LevelIDs_PyramidCave, 0xC000u, 0xC000u, 0xC000u, { 0, 300, 0 }, { 0, 300, 0 }, { 0, 300, 0 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, 0 }, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_FinalChase, 0, 0x4000, 0x4000, { -223, -100, 63 }, { 3206, -4000, 2455 }, { 3176, -4000, 2455 } },
	{ LevelIDs_CannonsCoreS, 0xC000u, 0xC000u, 0xC000u, { 0, 45, 0 }, { 0, 45, 0 }, { 0, 45, 0 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 210 }, { 0, 200, 210 }, { 0, 200, 210 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_SonicVsShadow2, 0, 0, 0, { 0, 0, -15 }, { 0, 0, -15 }, { 0, 0, -15 } },
	{ LevelIDs_GreenHill, 0xC000u, 0xC000u, 0xC000u, { 0, 40, 0 }, { 15, 40, 0 }, { -15, 40, 0 } },
	{ LevelIDs_DowntownRace, 0x4000, 0x4000, 0x4000, { -2215, 4320, -4670 }, { -2235, 4320, -4670 }, { -2195, 4320, -4670 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 10, -445, -900 }, { 10, -795, -900 }, { -10, -795, -900 } },
	{ LevelIDs_Invalid }
};

StartPosition SuperShadowStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, -1000 }, { 0, 0, -1000 }, { 0, 0, -1000 } },
	{ LevelIDs_Invalid }
};

StartPosition SuperSonicStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_Invalid }
};

StartPosition TailsStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalChase, 0xC000u, 0xC000u, 0xC000u, { 3192, -4045,2228 }, { 3192, -4045,2228 }, { 3192, -4045,2228 } },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { 0, -400, -910 }, { -40, -400, -910 }, { 40, -400, -910 } },
	{ LevelIDs_Invalid }
};
#pragma warning(default : 4838)

StartPosition *SonicStartList[] = { SonicStart, ShadowStart, MechTailsStart, MechEggmanStart, KnucklesStart, RougeStart, SuperSonicStart, SuperShadowStart, TailsStart };
StartPosition *ShadowStartList[] = { ShadowStart, SonicStart, MechEggmanStart, MechTailsStart, RougeStart, KnucklesStart, SuperShadowStart, SuperSonicStart, TailsStart };
StartPosition *MechTailsStartList[] = { MechTailsStart, MechEggmanStart, SonicStart, ShadowStart, KnucklesStart, RougeStart, SuperSonicStart, SuperShadowStart, TailsStart };
StartPosition *MechEggmanStartList[] = { MechEggmanStart, MechTailsStart, ShadowStart, SonicStart, RougeStart, KnucklesStart, SuperShadowStart, SuperSonicStart, TailsStart };
StartPosition *KnucklesStartList[] = { KnucklesStart, RougeStart, SonicStart, ShadowStart, MechTailsStart, MechEggmanStart, SuperSonicStart, SuperShadowStart, TailsStart };
StartPosition *RougeStartList[] = { RougeStart, KnucklesStart, ShadowStart, SonicStart, MechEggmanStart, MechTailsStart, SuperShadowStart, SuperSonicStart, TailsStart };
StartPosition *SuperSonicStartList[] = { SuperSonicStart, SuperShadowStart, SonicStart, ShadowStart, MechTailsStart, MechEggmanStart, KnucklesStart, RougeStart, TailsStart };
StartPosition *SuperShadowStartList[] = { SuperShadowStart, SuperSonicStart, ShadowStart, SonicStart, MechEggmanStart, MechTailsStart, RougeStart, KnucklesStart, TailsStart };
StartPosition *TailsStartList[] = { TailsStart, SonicStart, ShadowStart, MechTailsStart, MechEggmanStart, KnucklesStart, RougeStart, SuperSonicStart, SuperShadowStart };
StartPosition *EggmanStartList[] = { TailsStart, ShadowStart, SonicStart, MechEggmanStart, MechTailsStart, RougeStart, KnucklesStart, SuperShadowStart, SuperSonicStart };

int __cdecl LoadStartPosition_ri(int playerNum, NJS_VECTOR *position, Rotation *rotation)
{
	
	ObjectMaster *v1; // eax@1
	CharObj2Base *v4; // eax@7
	StartPosition **list;
	StartPosition *v5; // eax@9
	int v6; // edx@25
	NJS_VECTOR *v8; // edx@35

	TimeStopped = 0;
	v1 = MainCharacter[playerNum];
	if ( position )
	{
		position->z = 0.0;
		position->y = 0.0;
		position->x = 0.0;
	}
	if ( rotation )
	{
		rotation->z = 0;
		rotation->y = 0;
		rotation->x = 0;
	}
	if ( v1 )
	{
		v4 = MainCharObj2[playerNum];
		if ( v4 )
		{
			if(CurrentLevel == LevelIDs_PumpkinHill || CurrentLevel == LevelIDs_EggQuarters) v4->Upgrades = v4->Upgrades | 0x2002400;
			switch ( v4->CharID )
			{
			case Characters_Sonic:
				list = SonicStartList;
				break;
			case Characters_Shadow:
				list = ShadowStartList;
				break;
			case Characters_Knuckles:
				list = KnucklesStartList;
				break;
			case Characters_Rouge:
				list = RougeStartList;
				if(AltCharacter[0] == 1) v4->PhysData.BaseSpeed = 1.9;
				break;
			case Characters_Tails:
				list = TailsStartList;
				v4->PhysData.BaseSpeed = 2;
				break;
			case Characters_Eggman:
				list = EggmanStartList;
				v4->PhysData.InitialJumpSpeed = 2.2;
				break;
			case Characters_MechEggman:
				list = MechEggmanStartList;
				if (AltCharacter[0] == 1) {
					v4->PhysData.BaseSpeed = 1.3;
				}
				break;
			case Characters_MechTails:
				list = MechTailsStartList;
				break;
			case Characters_SuperSonic:
				list = SuperSonicStartList;
				break;
			case Characters_SuperShadow:
				list = SuperShadowStartList;
				break;
			default:
				return 1;
			}
		}
		else
			return 1;
		if ( TwoPlayerMode
			|| (short)CurrentLevel == LevelIDs_SonicVsShadow1
			|| (short)CurrentLevel == LevelIDs_SonicVsShadow2
			|| (short)CurrentLevel == LevelIDs_TailsVsEggman1
			|| (short)CurrentLevel == LevelIDs_TailsVsEggman2
			|| (short)CurrentLevel == LevelIDs_KnucklesVsRouge )
			v6 = (playerNum != 0) + 1;
		else
			v6 = 0;
		for (int i = 0; i < (int)LengthOfArray(SonicStartList); i++)
		{
			v5 = list[i];
			if ( v5 )
			{
				while ( v5->Level != LevelIDs_Invalid )
				{
					if ( v5->Level == (short)CurrentLevel )
					{
						if ( rotation )
							rotation->y = *(&v5->Rotation1P + v6);
						if ( position )
						{
							v8 = &(&v5->Position1P)[v6];
							position->x = v8->x;
							position->y = v8->y;
							position->z = v8->z;
						}
						return 1;
					}
					++v5;
				}
			}
		}
		return 1;
	}
	return 0;
}

__declspec(naked) void LoadStartPosition_r()
{
	__asm
	{
		mov eax, [esp+4]
		push eax
			push edi
			push ecx
			call LoadStartPosition_ri
			add esp, 12
			retn
	}
}

#pragma warning(disable : 4838)
LevelEndPosition KnucklesEnd[] = {
	{ LevelIDs_PumpkinHill, 0x8000u, 0xC000u, 0, { 530, -986, -770 }, { -13, 34.8f, 1275 } },
	{ LevelIDs_AquaticMine, 0, 0, 0, { 0, 130, -365 }, { -600, 211, 443 } },
	{ LevelIDs_WildCanyon, 0xC000u, 0xC000u, 0, { 705, 1010, -14 }, { 1700, 0, 121 } },
	{ LevelIDs_DeathChamber, 0, 0xE000u, 0, { 100, 100, 180 }, { -805, -35, -805 } },
	{ LevelIDs_MeteorHerd, 0, 0x5200, 0, { 10, 170, 140 }, { -438, 2752, -432 } },
	{ LevelIDs_CannonsCoreK, 0xC000u, 0xFFFFu, 0, { 0, 660, -160 }, { 0, 580, 60 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition MechEggmanEnd[] = {
	{ LevelIDs_IronGate, 0x8000u, 0xC000u, 0, { 1490, -270, -1025 }, { 3184, -233, -702 } },
	{ LevelIDs_WeaponsBed, 0x4000, 0xFA00u, 0, { -4, -160, -40 }, { 1500, -220, -6008 } },
	{ LevelIDs_SandOcean, 0x4000, 0x4A00, 0, { 0, 80, 0 }, { 659, 120, -4660 } },
	{ LevelIDs_LostColony, 0x8000u, 0, 0, { 595, -518, -2350 }, { 2225, -308, -2400 } },
	{ LevelIDs_CannonsCoreE, 0, 0xFFFFu, 0, { 80, -30, -1570 }, { 0, 20, -200 } },
	{ LevelIDs_CosmicWall, 0x4000, 0xA000u, 0, { 6673, 4000, 11677 }, { 2753, 2583, -1045 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition MechTailsEnd[] = {
	{ LevelIDs_PrisonLane, 0x8000u, 0x8000u, 0, { -350, 117, 410 }, { -3129, 790, -242 } },
	{ LevelIDs_MissionStreet, 0x8000u, 0, 0, { 2200, 800, -3500 }, { 4065, 758, -4170 } },
	{ LevelIDs_HiddenBase, 0, 0x4000, 0, { -2295, 110, -2845 }, { -3525, 920, -4960 } },
	{ LevelIDs_EternalEngine, 0x4000, 0x4000, 0, { -2055, 936, -5825 }, { -652, 788, -4426 } },
	{ LevelIDs_CannonsCoreT, 0, 0xFFFFu, 0, { -1050, 638, -1540 }, { 0, 670, 0 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition RougeEnd[] = {
	{ LevelIDs_SecurityHall, 0, 0x4000, 0, { 100, -573, 490 }, { 0, 314.6f, 110 } },
	{ LevelIDs_DryLagoon, 0x8000u, 0x7000, 0, { 191, 211, 1317 }, { 1728, 0, -382 } },
	{ LevelIDs_EggQuarters, 0x8000u, 0x8000u, 0, { 100, 70, 1255 }, { -655, -20, 2680 } },
	{ LevelIDs_CannonsCoreR, 0x4000, 0xFFFFu, 0, { 80, 135, 80 }, { 0, 480, 150 } },
	{ LevelIDs_MadSpace, 0xEC00u, 0, 0, { 272.5f, 2358, -334.5f }, { -154, 3350, 481 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition ShadowEnd[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0x8000u, 0, { -40, -400, -970 }, { -6330, -4500, -8830 } },
	{ LevelIDs_WhiteJungle, 0xC000u, 0xB000u, 0, { 5040, -2220, -1550 }, { 13280, -3157, -7370 } },
	{ LevelIDs_FinalChase, 0xC000u, 0xE000u, 0, { 3408, -6592, 16865 }, { -695, -6959.5f, 10275 } },
	{ LevelIDs_SkyRail, 0x8000u, 0xA000u, 0, { -2411, -1792, 4260 }, { -3457, -1047, 3001 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition SonicEnd[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_GreenForest, 0x8000u, 0x8000u, 0, { 5858, -1812, 7541 }, { 6890, -1610, 7542 } },
	{ LevelIDs_MetalHarbor, 0, 0x4000, 0, { 2158, -160, -5294 }, { 1707, -170, -6583 } },
	{ LevelIDs_CityEscape, 0xC000u, 0x4000, 0, { -1570, -6060, 8860 }, { 7700, -13145, 5570 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0x8000u, 0, { -9710, -1045, -4005 }, { -8725, -537, -2905 } },
	{ LevelIDs_PyramidCave, 0x4000, 0, 0, { -685, -4190, -19525 }, { -2170, -3970, -21870 } },
	{ LevelIDs_FinalRush, 0, 0xC000u, 0, { 5776, -15687, 20080 }, { 4207, -16632, 24462 } },
	{ LevelIDs_CannonsCoreS, 0x4000, 0x4000, 0, { 0, -480, -1550 }, { -510, -655, -4700 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition *SonicEndList[] = { SonicEnd, ShadowEnd, MechTailsEnd, MechEggmanEnd, KnucklesEnd, RougeEnd };
LevelEndPosition *ShadowEndList[] = { ShadowEnd, SonicEnd, MechEggmanEnd, MechTailsEnd, RougeEnd, KnucklesEnd };
LevelEndPosition *MechTailsEndList[] = { MechTailsEnd, MechEggmanEnd, SonicEnd, ShadowEnd, KnucklesEnd, RougeEnd };
LevelEndPosition *MechEggmanEndList[] = { MechEggmanEnd, MechTailsEnd, ShadowEnd, SonicEnd, RougeEnd, KnucklesEnd };
LevelEndPosition *KnucklesEndList[] = { KnucklesEnd, RougeEnd, SonicEnd, ShadowEnd, MechTailsEnd, MechEggmanEnd };
LevelEndPosition *RougeEndList[] = { RougeEnd, KnucklesEnd, ShadowEnd, SonicEnd, MechEggmanEnd, MechTailsEnd };

StartPosition KnucklesStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_AquaticMine, 0x4000, 0, 0, { 0, 130, -340 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 856, -140 }, { 220, 856, -140 }, { 180, 856, -140 } },
	{ LevelIDs_DeathChamber, 0x2000, 0x2000, 0x2000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_EggQuarters, 0x2000, 0xA000u, 0xA000u, { 980, -30, 980 }, { -820, 20, 820 }, { -820, 20, 820 } },
	{ LevelIDs_KingBoomBoo, 0x1800, 0x1800, 0x1800, { 374, -40, -120 }, { 374, -40, -120 }, { 374, -40, -120 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { 0, -340, 10 }, { 0, -340, 10 }, { 0, -340, 10 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0xF000u, 0xF000u, { 200, 856, -140 }, { -359, 927, -44 }, { -359, 927, -44 } },
	{ LevelIDs_CannonsCoreK, 0, 0, 0, { -435, -175, -1735 }, { -435, -175, 1735 }, { -435, -175, 1735 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -500, -1025 }, { 25, -500, -1025 }, { -25, -500, -1025 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 200, 210, 1350 }, { 200, 210, 1350 }, { 200, 210, 1350 } },
	{ LevelIDs_PoolQuest, 0, 0, 0, { 0, 130, -200 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { 0, 620, 0 }, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_SecurityHall, 0xA000u, 0x6000, 0xA000u, { 405, -933, 410 }, { 217, -933, 410 }, { 217, -933, 410 } },
	{ LevelIDs_MadSpace, 0xF000u, 0xF000u, 0xF000u, { 0, 620, 0 }, { 0, 620, 5 }, { 0, 620, 5 } },
	{ LevelIDs_DeathChamber2P, 0x2000, 0x2000, 0x2000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_Invalid }
};

StartPosition MechEggmanStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_IronGate, 0, 0, 0, { 6150, -1521, -1230 }, { 6150, -1521, -1230 }, { 6150, -1521, -1230 } },
	{ LevelIDs_WeaponsBed, 0, 0, 0, { 4251, -220, -10138 }, { 4231, -220, -10138 }, { 4281, -220, -10138 } },
	{ LevelIDs_WeaponsBed2P, 0x4000, 0x4000, 0x4000, { 140, -170, 20 }, { 140, -170, 20 }, { 140, -170, 20 } },
	{ LevelIDs_TailsVsEggman1, 0x4000, 0x4000, 0x4000, { 140, -170, 20 }, { 140, -170, 20 }, { 140, -170, 20 } },
	{ LevelIDs_SandOcean, 0x8000u, 0x8000u, 0x8000u, { 2895, 155, -7185 }, { 2895, 155, -7185 }, { 2895, 155, -7185 } },
	{ LevelIDs_EternalEngine, 0xC000u, 0xC000u, 0xC000u, { 207, -1826, -9150 }, { 207, -1826, -9150 }, { 207, -1826, -9150 } },
	{ LevelIDs_LostColony, 0, 0, 0, { 4710, 1552, -2400 }, { 4710, 1552, -2400 }, { 4710, 1552, -2400 } },
	{ LevelIDs_TailsVsEggman2, 0x4000, 0x4000, 0x4000, { 0, -50, -181.5f }, { 0, -50, -181.5f }, { 0, -50, -181.5f } },
	{ LevelIDs_MissionStreet2P, 0xC000u, 0xC000u, 0xC000u, { 0, 0, -25 }, { 0, 0, -25 }, { 0, 0, -25 } },
	{ LevelIDs_SandOcean2P, 0x4000, 0x4000, 0x4000, { 17, 30, -150 }, { 17, 30, -150 }, { 17, 30, -150 } },
	{ LevelIDs_CannonsCoreE, 0xC000u, 0xC000u, 0xC000u, { 570, -2630, -3450 }, { 570, -2630, -3450 }, { 570, -2630, -3450 } },
	{ LevelIDs_EggGolemE, 0, 0, 0, { 0, 200, 220 }, { 0, 200, 220 }, { 0, 200, 220 } },
	{ LevelIDs_CosmicWall, 0x8000u, 0x8000u, 0x8000u, { 3550, -1600, 29690 }, { 3550, -1600, 29690 }, { 3550, -1600, 29690 } },
	{ LevelIDs_HiddenBase2P, 0, 0x4000, 0x4000, { 0, 0, 30 }, { -20, 0, 25 }, { -20, 0, 25 } },
	{ LevelIDs_IronGate2P, 0, 0xC000u, 0xC000u, { 0 }, { -30, -10, -20 }, { -30, -10, -20 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x2000, { -150, 0, 0 }, { -150, 0, 0 }, { -280, 0, -170 } },
	{ LevelIDs_PyramidRace, 0, 0, 0, { 0 }, { 0, 0, -2020 }, { 0, 0, -2020 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0xC000u, { 0 }, { 0, -170, -475 }, { 0, -170, -475 } },
	{ LevelIDs_EternalEngine2P, 0x6000, 0x6000, 0x6000, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_Invalid }
};

StartPosition MechTailsStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PrisonLane, 0xC000u, 0xC000u, 0xC000u, { -4440, 940, -1178 }, { -4440, 940, -1178 }, { -4440, 940, -1178 } },
	{ LevelIDs_WeaponsBed, 0, 0, 0, { 4251, -220, -10138 }, { 4231, -220, -10138 }, { 4281, -220, -10138 } },
	{ LevelIDs_WeaponsBed2P, 0xC000u, 0xC000u, 0xC000u, { 140, -170, -40 }, { 140, -170, -40 }, { 140, -170, -40 } },
	{ LevelIDs_MissionStreet, 0xC000u, 0xC000u, 0xC000u, { 7170, 598, -6913 }, { 7170, 598, -6913 }, { 7170, 598, -6913 } },
	{ LevelIDs_TailsVsEggman1, 0xC000u, 0xC000u, 0xC000u, { 140, -170, -40 }, { 140, -170, -40 }, { 140, -170, -40 } },
	{ LevelIDs_HiddenBase, 0x4000, 0x4000, 0x4000, { -3035, 1280, -5400 }, { -3035, 1280, -5400 }, { -3035, 1280, -5400 } },
	{ LevelIDs_EternalEngine, 0xC000u, 0xC000u, 0xC000u, { 207, -1826, -9150 }, { 207, -1826, -9150 }, { 207, -1826, -9150 } },
	{ LevelIDs_TailsVsEggman2, 0xC000u, 0xC000u, 0xC000u, { 140, -50, -40 }, { 140, -50, -40 }, { 140, -50, -40 } },
	{ LevelIDs_MissionStreet2P, 0x4000, 0x4000, 0x4000, { 0, 0, 25 }, { 0, 0, 25 }, { 0, 0, 25 } },
	{ LevelIDs_SandOcean2P, 0x4000, 0x4000, 0x4000, { 17, 30, -150 }, { 17, 30, -150 }, { 17, 30, -150 } },
	{ LevelIDs_CannonsCoreE, 0xC000u, 0xC000u, 0xC000u, { -1990, -1258, -2500 }, { -1990, -1258, -2500 }, { -1990, -1258, -2500 } },
	{ LevelIDs_HiddenBase2P, 0, 0x4000, 0x4000, { 0, 0, 30 }, { -20, 0, 25 }, { -20, 0, 25 } },
	{ LevelIDs_IronGate2P, 0, 0xC000u, 0xC000u, { 0 }, { -30, -10, -20 }, { -30, -10, -20 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x2000, { -150, 0, 0 }, { -150, 0, 0 }, { -280, 0, -170 } },
	{ LevelIDs_PyramidRace, 0, 0, 0, { 0 }, { 0, 0, -2020 }, { 0, 0, -2020 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0xC000u, { 0 }, { 0, -170, -475 }, { 0, -170, -475 } },
	{ LevelIDs_EternalEngine2P, 0x6000, 0x6000, 0x6000, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_Invalid }
};

StartPosition RougeStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SecurityHall, 0xA000u, 0x6000, 0xA000u, { 405, -933, 410 }, { 217, -933, 410 }, { 217, -933, 410 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 15, -140 }, { 200, 15, -140 }, { 200, 15, -140 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 856, -140 }, { 220, 856, -140 }, { 180, 856, -140 } },
	{ LevelIDs_DeathChamber, 0x2000, 0xE000u, 0xE000u, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_EggQuarters, 0x2000, 0x2000, 0x2000, { 980, -30, 980 }, { -820, 20, 820 }, { -820, 20, 820 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { 10, -340, 0 }, { 10, -340, 0 }, { 10, -340, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0xF000u, 0xF000u, { 200, 856, -400 }, { -359, 927, -44 }, { -359, 927, -44 } },
	{ LevelIDs_CannonsCoreR, 0x8000u, 0x8000u, 0x8000u, { 120, 20, 0 }, { 120, 20, 0 }, { 120, 20, 0 } },
	{ LevelIDs_FlyingDog },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -500, -1025 }, { 25, -500, -1025 }, { -25, -500, -1025 } },
	{ LevelIDs_MadSpace, 0xF000u, 0xF000u, 0xF000u, { 0, 620, 0 }, { 0, 620, 5 }, { 0, 620, 5 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 200, 210, 1350 }, { 200, 210, 1350 }, { 200, 210, 1350 } },
	{ LevelIDs_PoolQuest, 0, 0, 0, { 0, 130, -200 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { 0, 620, 0 }, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_DeathChamber2P, 0x2000, 0xE000u, 0xE000u, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_Invalid }
};

StartPosition ShadowStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_GreenForest, 0x8000u, 0x8000u, 0x8000u, { 10935, -1854, 11056 }, { 10935, -1854, 11076 }, { 10935, -1854, 11066 } },
	{ LevelIDs_WhiteJungle, 0xC000u, 0xC000u, 0xC000u, { 13166, -3599, -5518 }, { 9135, -3154, -4930 }, { 9135, -3154, -4930 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -1343.7f, -4928, 10098 }, { -1333.7f, -4928, 10098 }, { -1353.7f, -4928, 10098 } },
	{ LevelIDs_CityEscape, 0x4000, 0x8000u, 0x8000u, { 3955, -22175, 16130 }, { 6450, -15915, 9070 }, { 6450, -15915, 9070 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { -9970, -6999, -18430 }, { -9970, -6999, -18350 }, { -9970, -6999, -18350 } },
	{ LevelIDs_SonicVsShadow1, 0x6C00, 0x6C00, 0x6C00, { 10, -42, 0 }, { 10, -42, 0 }, { 10, -42, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0xC000u, 0xC000u, { -8470, -1097, -2904 }, { -8470, -1097, -2904 }, { -8470, -1097, -2904 } },
	{ LevelIDs_HotShot },
	{ LevelIDs_Biolizard, 0, 0, 0, { -265, 10, 0 }, { -265, 10, 0 }, { -265, 10, 0 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, -1000 }, { 0, 0, -1000 }, { 0, 0, -1000 } },
	{ LevelIDs_SonicVsShadow2, 0x4000, 0x4000, 0x4000, { -292, 0, 0 }, { -292, 0, 0 }, { -292, 0, 0 } },
	{ LevelIDs_FinalChase, 0, 0xC000u, 0xC000u, { 122, -9960, 7627 }, { 3440, -6812, 17730 }, { 3440, -6812, 17730 } },
	{ LevelIDs_GreenHill, 0xC000u, 0xC000u, 0xC000u, { -1970, -1390, -6940 }, { -1970, -1390, -6940 }, { -1970, -1390, -6910 } },
	{ LevelIDs_FinalRush, 0, 0x4000, 0x4000, { 2530, -26495.5f, 7465 }, { 2531, -20965, 11350 }, { 2531, -20965, 11350 } },
	{ LevelIDs_MetalHarbor2P, 0, 0x8000u, 0x8000u, { 8854, -31, -10370 }, { 4913, -31, -10370 }, { 4913, -31, -10370 } },
	{ LevelIDs_GrindRace, 0x8000u, 0x8000u, 0x8000u, { 13990, -35280, 10050 }, { 13990, -35280, 10050 }, { 13990, -35280, 10050 } },
	{ LevelIDs_DowntownRace, 0xC000u, 0xC000u, 0xC000u, { -1540, -6060, 8800 }, { -1540, -6060, 8800 }, { -1540, -6060, 8770 } },
	{ LevelIDs_Invalid }
};

StartPosition SonicStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_GreenForest, 0x8000u, 0x8000u, 0x8000u, { 10935, -1854, 11056 }, { 10935, -1854, 11076 }, { 10935, -1854, 11066 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -1343.7f, -4928, 10098 }, { -1333.7f, -4928, 10098 }, { -1353.7f, -4928, 10098 } },
	{ LevelIDs_MetalHarbor, 0x6000, 0, 0, { 8777, -170, -10240 }, { 8854, -170, -10241 }, { 8854, -170, -10281 } },
	{ LevelIDs_CityEscape, 0x4000, 0x8000u, 0x8000u, { 3955, -22175, 16130 }, { 6450, -15915, 9070 }, { 6450, -15915, 9070 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { -9970, -6999, -18430 }, { -9970, -6999, -18350 }, { -9970, -6999, -18350 } },
	{ LevelIDs_SonicVsShadow1, 0x800, 0x800, 0x800, { -10, -42, 0 }, { -10, -42, 0 }, { -10, -42, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0xC000u, 0xC000u, { -8470, -1097, -2904 }, { -8470, -1097, -2904 }, { -8470, -1097, -2904 } },
	{ LevelIDs_PyramidCave, 0x4000, 0x4000, 0x4000, { 940, -4060, -22190 }, { 940, -4060, -22190 }, { 940, -4060, -22190 } },
	{ LevelIDs_FinalRush, 0, 0x4000, 0x4000, { 2530, -26495.5f, 7465 }, { 2531, -20965, 11350 }, { 2531, -20965, 11350 } },
	{ LevelIDs_BigFoot, 0, 0, 0, { 0, -1, 0 }, { 0, -1, 0 }, { 0, -1, 0 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 220 }, { 0, 200, 220 }, { 0, 200, 220 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_CannonsCoreS, 0x1000, 0x1000, 0x1000, { -1600, -5755, -9565 }, { -308, 0, 0 }, { -308, 0, 0 } },
	{ LevelIDs_SonicVsShadow2, 0x4000, 0x4000, 0x4000, { -308, 0, 0 }, { -308, 0, 0 }, { -308, 0, 0 } },
	{ LevelIDs_GreenHill, 0xC000u, 0xC000u, 0xC000u, { -1970, -1390, -6940 }, { -1970, -1390, -6940 }, { -1970, -1390, -6910 } },
	{ LevelIDs_DowntownRace, 0xC000u, 0xC000u, 0xC000u, { -1540, -6060, 8800 }, { -1540, -6060, 8800 }, { -1540, -6060, 8770 } },
	{ LevelIDs_GrindRace, 0x8000u, 0x8000u, 0x8000u, { 13990, -35280, 10050 }, { 13990, -35280, 10050 }, { 13990, -35280, 10050 } },
	{ LevelIDs_MetalHarbor2P, 0, 0x8000u, 0x8000u, { 8854, -31, -10370 }, { 4913, -31, -10370 }, { 4913, -31, -10370 } },
	{ LevelIDs_FinalChase, 0, 0xC000u, 0xC000u, { 122, -9960, 7627 }, { 3440, -6812, 17730 }, { 3440, -6812, 17730 } },
	{ LevelIDs_WhiteJungle, 0xC000u, 0xC000u, 0xC000u, { 13166, -3599, -5518 }, { 9135, -3154, -4930 }, { 9135, -3154, -4930 } },
	{ LevelIDs_Invalid }
};

StartPosition SuperShadowStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 600, -400, 200 }, { 600, -400, 200 }, { 600, -400, 200 } },
	{ LevelIDs_Invalid }
};

StartPosition SuperSonicStart2[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 600, -400, 200 }, { 600, -400, 200 }, { 600, -400, 200 } },
	{ LevelIDs_Invalid }
};
#pragma warning(default : 4838)

StartPosition *SonicStartList2[] = { SonicStart2, ShadowStart2, MechTailsStart2, MechEggmanStart2, KnucklesStart2, RougeStart2, SuperSonicStart2, SuperShadowStart2 };
StartPosition *ShadowStartList2[] = { ShadowStart2, SonicStart2, MechEggmanStart2, MechTailsStart2, RougeStart2, KnucklesStart2, SuperShadowStart2, SuperSonicStart2 };
StartPosition *MechTailsStartList2[] = { MechTailsStart2, MechEggmanStart2, SonicStart2, ShadowStart2, KnucklesStart2, RougeStart2, SuperSonicStart2, SuperShadowStart2 };
StartPosition *MechEggmanStartList2[] = { MechEggmanStart2, MechTailsStart2, ShadowStart2, SonicStart2, RougeStart2, KnucklesStart2, SuperShadowStart2, SuperSonicStart2 };
StartPosition *KnucklesStartList2[] = { KnucklesStart2, RougeStart2, SonicStart2, ShadowStart2, MechTailsStart2, MechEggmanStart2, SuperSonicStart2, SuperShadowStart2 };
StartPosition *RougeStartList2[] = { RougeStart2, KnucklesStart2, ShadowStart2, SonicStart2, MechEggmanStart2, MechTailsStart2, SuperShadowStart2, SuperSonicStart2 };
StartPosition *SuperSonicStartList2[] = { SuperSonicStart2, SuperShadowStart2, SonicStart2, ShadowStart2, MechTailsStart2, MechEggmanStart2, KnucklesStart2, RougeStart2 };
StartPosition *SuperShadowStartList2[] = { SuperShadowStart2, SuperSonicStart2, MechEggmanStart2, MechTailsStart2, RougeStart2, KnucklesStart2, ShadowStart2, SonicStart2 };

static const void *const sub_46DC70Ptr = (void*)0x46DC70;
void sub_46DC70(int a1, NJS_VECTOR *a2, char a3)
{
	__asm
	{
		xor eax, eax
			mov al, [a3]
		push eax
			mov eax, [a1]
		mov ecx, [a2]
		call sub_46DC70Ptr
			add esp, 4
	}
}

DataArray(char, byte_1DE4664, 0x1DE4664, 2);
DataPointer(void *, off_1DE95E0, 0x1DE95E0);

signed int sub_46DBD0(int a1)
{
	CharObj2Base *v1; // eax@1
	signed int result; // eax@2

	v1 = MainCharObj2[a1];
	if ( v1 )
		result = v1->CharID;
	else
		result = -1;
	return result;
}

signed int LoadEndPosition_r(int playerNum)
{

	addUpTime();

	int v1; // edi@1
	__int16 v2; // bp@2
	int v3; // edx@12
	EntityData1 *v4; // esi@12
	LevelEndPosition **list;
	LevelEndPosition *v5; // eax@13
	int v8; // edi@24
	int v9; // ecx@24
	NJS_VECTOR *v10; // eax@24
	float v11; // ST14_4@24


	v1 = playerNum;
	if ( TwoPlayerMode
		|| (v2 = CurrentLevel, (short)CurrentLevel == LevelIDs_SonicVsShadow1)
		|| (short)CurrentLevel == LevelIDs_SonicVsShadow2
		|| (short)CurrentLevel == LevelIDs_TailsVsEggman1
		|| (short)CurrentLevel == LevelIDs_TailsVsEggman2
		|| (short)CurrentLevel == LevelIDs_KnucklesVsRouge
		|| (short)CurrentLevel > LevelIDs_BigFoot && (short)CurrentLevel != LevelIDs_Route101280
		|| MissionNum != 1 && MissionNum != 2 )
		return 0;
	else
	{
		v3 = MissionNum == 1 ? 0 : 1;
		v4 = MainCharacter[playerNum]->Data1.Entity;
		switch ( sub_46DBD0(playerNum) )
		{
		case Characters_Sonic:
		case Characters_Tails:
		case Characters_SuperSonic:
			list = SonicEndList;
			break;
		case Characters_Shadow:
		case Characters_Eggman:
		case Characters_SuperShadow:
			list = ShadowEndList;
			break;
		case Characters_Knuckles:
			list = KnucklesEndList;
			break;
		case Characters_Rouge:
			list = RougeEndList;
			break;
		case Characters_MechEggman:
			list = MechEggmanEndList;
			break;
		case Characters_MechTails:
			list = MechTailsEndList;
			break;
		default:
			return 0;
		}
		for (int i = 0; i < (int)LengthOfArray(SonicEndList); i++)
		{
			v5 = list[i];
			while ( v5->Level != LevelIDs_Invalid )
			{
				if ( v5->Level == v2 )
					goto endloop;
				++v5;
			}
		}
endloop:
		if ( *(&v5->Mission2YRotation + v3) == 0xFFFF )
			return 0;
		v4->Rotation.z = 0;
		v4->Rotation.x = 0;
		v9 = *(&v5->Mission2YRotation + v3);
		v4->Rotation.y = v9;
		*((int *)*(&off_1DE95E0 + v1) + 7) = v9;
		v10 = (NJS_VECTOR *)((char *)&v5->Mission2Position + 12 * v3);
		v4->Position = *v10;
		v11 = v4->Position.y - 10.0f;
		*(float *)&MainCharObj2[v1]->field_1A0[5] = v11;
		MainCharObj2[v1]->field_144[0] = 0;
		sub_46DC70(v1, &v4->Position, 0);
		v4->Collision->CollisionArray->field_2 |= 0x70u;
		*(int*)&MainCharObj2[v1]->gap_70[24] = 0;
		v8 = v1 & 1;
		if ( (short)CurrentLevel == LevelIDs_LostColony )
		{
			byte_1DE4664[v8] = 5;
			return 1;
		}
		else
		{
			byte_1DE4664[v8] = *(char*)0x1DE4660;
			return 1;
		}
	}
}

void __cdecl sub_43DF30_i(int playerNum)
{
	int v1; // edi@1
	ObjectMaster *v2; // esi@1
	CharObj2Base *v3; // eax@3
	EntityData1 *v4; // esi@3
	StartPosition **list;
	StartPosition *v5; // eax@5
	int v6; // edx@20
	int v8; // ecx@30
	float v10; // ST14_4@30

	v1 = playerNum;
	v2 = MainCharacter[playerNum];
	if ( v2 && LoadEndPosition_r(playerNum) != 1 )
	{
		v3 = MainCharObj2[v1];
		v4 = v2->Data1.Entity;
		if ( v3 )
		{
			switch ( v3->CharID )
			{
			case Characters_Sonic:
			case Characters_Tails:
				list = SonicStartList2;
				break;
			case Characters_Shadow:
			case Characters_Eggman:
				list = ShadowStartList2;
				break;
			case Characters_Knuckles:
				list = KnucklesStartList2;
				break;
			case Characters_Rouge:
				list = RougeStartList2;
				break;
			case Characters_MechEggman:
				list = MechEggmanStartList2;
				break;
			case Characters_MechTails:
				list = MechTailsStartList2;
				break;
			case Characters_SuperSonic:
				list = SuperSonicStartList2;
				break;
			case Characters_SuperShadow:
				list = SuperShadowStartList2;
				break;
			default:
				goto LABEL_13;
			}
		}
		else
		{
LABEL_13:
			list = 0;
		}
		if ( TwoPlayerMode
			|| (short)CurrentLevel == LevelIDs_SonicVsShadow1
			|| (short)CurrentLevel == LevelIDs_SonicVsShadow2
			|| (short)CurrentLevel == LevelIDs_TailsVsEggman1
			|| (short)CurrentLevel == LevelIDs_TailsVsEggman2
			|| (short)CurrentLevel == LevelIDs_KnucklesVsRouge )
			v6 = (v1 != 0) + 1;
		else
			v6 = 0;
		if ( list )
		{
			for (int i = 0; i < (int)LengthOfArray(SonicStartList2); i++)
			{
				v5 = list[i];
				while ( v5->Level != LevelIDs_Invalid )
				{
					if ( v5->Level == (short)CurrentLevel )
					{
						v4->Rotation.z = 0;
						v4->Rotation.x = 0;
						v8 = *(&v5->Rotation1P + v6);
						v4->Rotation.y = v8;
						*((int *)*(&off_1DE95E0 + v1) + 7) = v8;
						v4->Position = (&v5->Position1P)[v6];
						v10 = v4->Position.y - 10.0f;
						*(float *)&MainCharObj2[v1]->field_1A0[5] = v10;
						MainCharObj2[v1]->field_144[0] = 0;
						goto LABEL_27;
					}
					++v5;
				}
			}
		}
		v4->Rotation.z = 0;
		v4->Rotation.y = 0;
		v4->Rotation.x = 0;
		v4->Position.z = 0.0;
		v4->Position.y = 0.0;
		v4->Position.x = 0.0;
		*((int *)*(&off_1DE95E0 + v1) + 7) = 0;
LABEL_27:
		sub_46DC70(v1, &v4->Position, 0);
		v4->Collision->CollisionArray->field_2 |= 0x70u;
		*(int*)&MainCharObj2[v1]->gap_70[24] = 0;
		if ( (short)CurrentLevel == LevelIDs_RadicalHighway || (short)CurrentLevel == LevelIDs_LostColony )
			byte_1DE4664[v1 & 1] = 5;
		else
			byte_1DE4664[v1 & 1] = *(char*)0x1DE4660;
	}
}

__declspec(naked) void sub_43DF30()
{
	__asm
	{
		push eax
		call sub_43DF30_i
		add esp, 4
		retn
	}
}

#pragma warning(disable : 4838)
LevelEndPosition Knuckles2PIntro[] = {
	{ LevelIDs_PumpkinHill, 0x5800, 0x5800, 0, { -193, -742.38f, -908.24f }, { -193, -742.38f, -908.24f } },
	{ LevelIDs_DeathChamber, 0, 0xC000u, 0, { 0, 210, 150 }, { 150, 210, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_MeteorHerd, 0, 0x8000u, 0, { 190, -340, 0 }, { -190, -340, 0 } },
	{ LevelIDs_DryLagoon2P, 0, 0x8000u, 0, { 40, 270, 1438 }, { 355, 270, 1438 } },
	{ LevelIDs_EggQuarters, 0x2000, 0x6000, 0, { -845, 20, 845 }, { 845, 20, 845 } },
	{ LevelIDs_SecurityHall, 0x6000, 0xB000u, 0, { 470, -573, 490 }, { -395, -416, -20 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0, { 10, 130, -225 }, { -10, 130, -225 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_MadSpace, 0x9800u, 0x4000, 0, { 30, 620, 17 }, { 0, 620, -35 } },
	{ LevelIDs_DeathChamber2P, 0, 0xC000u, 0, { 0, 210, 150 }, { 150, 210, 0 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition MechEggman2PIntro[] = {
	{ LevelIDs_WeaponsBed2P, 0xC000u, 0xC000u, 0, { 50, -170, 50 }, { 50, -170, 50 } },
	{ LevelIDs_MissionStreet2P, 0, 0, 0, { -450, 0, 0 }, { -450, 0, 0 } },
	{ LevelIDs_SandOcean2P, 0, 0x8000u, 0, { -155, 30, -15 }, { 155, 30, -15 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0, { -15, -170, 1480 }, { 15, -170, 1480 } },
	{ LevelIDs_PyramidRace, 0x4000, 0x4000, 0, { -35, 0, -200 }, { 35, 0, -220 } },
	{ LevelIDs_HiddenBase2P, 0, 0x8000u, 0, { 60, 0, 10 }, { -60, 0, 10 } },
	{ LevelIDs_CosmicWall2P, 0, 0x8000u, 0, { -80, 0, 0 }, { 80, 0, 0 } },
	{ LevelIDs_EternalEngine2P, 0x4000, 0xC000u, 0, { 0, -50, 120 }, { 0, -50, -150 } },
	{ LevelIDs_IronGate2P, 0, 0x8000u, 0, { -50, -10, -20 }, { 50, -10, -20 } },
	{ LevelIDs_LostColony2P, 0xC000u, 0, 0, { 280, 65, -110 }, { -90, 0, 0 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition MechTails2PIntro[] = {
	{ LevelIDs_WeaponsBed2P, 0x4000, 0x4000, 0, { 50, -170, -250 }, { 50, -170, -250 } },
	{ LevelIDs_MissionStreet2P, 0x8000u, 0x8000u, 0, { 0 }, { 0 } },
	{ LevelIDs_SandOcean2P, 0, 0x8000u, 0, { -155, 30, -15 }, { 155, 30, -15 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0, { -15, -170, 1480 }, { 15, -170, 1480 } },
	{ LevelIDs_PyramidRace, 0x4000, 0x4000, 0, { -35, 0, -200 }, { 35, 0, -220 } },
	{ LevelIDs_HiddenBase2P, 0, 0x8000u, 0, { 60, 0, 10 }, { -60, 0, 10 } },
	{ LevelIDs_CosmicWall2P, 0, 0x8000u, 0, { -80, 0, 0 }, { 80, 0, 0 } },
	{ LevelIDs_EternalEngine2P, 0x4000, 0xC000u, 0, { 0, -50, 120 }, { 0, -50, -150 } },
	{ LevelIDs_IronGate2P, 0, 0x8000u, 0, { -50, -10, -20 }, { 50, -10, -20 } },
	{ LevelIDs_LostColony2P, 0xC000u, 0, 0, { 280, 65, -110 }, { -90, 0, 0 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition Rouge2PIntro[] = {
	{ LevelIDs_PumpkinHill, 0xC000u, 0xC000u, 0, { 0, -590, -1642 }, { 0, -590, -1642 } },
	{ LevelIDs_DeathChamber, 0, 0xC000u, 0, { 0, 210, 150 }, { 150, 210, 0 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_MeteorHerd, 0, 0x8000u, 0, { 190, -340, 0 }, { -190, -340, 0 } },
	{ LevelIDs_DryLagoon2P, 0, 0x8000u, 0, { 40, 270, 1438 }, { 355, 270, 1438 } },
	{ LevelIDs_EggQuarters, 0x2000, 0x6000, 0, { -845, 20, 845 }, { 845, 20, 845 } },
	{ LevelIDs_SecurityHall, 0x6000, 0xB000u, 0, { 470, -573, 490 }, { -395, -416, -20 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0, { 10, 130, -225 }, { -10, 130, -225 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_MadSpace, 0x9800u, 0x4000, 0, { 30, 620, 17 }, { 0, 620, -35 } },
	{ LevelIDs_DeathChamber2P, 0, 0xC000u, 0, { 0, 210, 150 }, { 150, 210, 0 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition Shadow2PIntro[] = {
	{ LevelIDs_GreenForest, 0, 0, 0, { 1247, -955, 2920 }, { 1247, -955, 2920 } },
	{ LevelIDs_SkyRail, 0xED00u, 0xED00u, 0, { -297, -724.9f, 2118 }, { -297, -724.9f, 2118 } },
	{ LevelIDs_MetalHarbor2P, 0x4000, 0x4000, 0, { 2065, -160, -4325 }, { 2065, -160, -4325 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0, { 105, 200, 0 }, { -105, 200, 0 } },
	{ LevelIDs_GreenHill, 0x5800, 0x5800, 0, { -760, -70, -2930 }, { -760, -70, -2930 } },
	{ LevelIDs_CityEscape, 0x8000u, 0x8000u, 0, { 150, -2226, 4010 }, { 150, -2226, 4010 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_FinalChase, 0x8000u, 0x4000, 0, { 3600, -4525, 4675 }, { 3600, -4525, 4675 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 0, -815, -910 }, { 0, -815, -910 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0xA000u, 0, { 4205, -2126, 430 }, { 6395, -1919, -2650 } },
	{ LevelIDs_DowntownRace, 0xF700u, 0xB00, 0, { -2010, 4793, -5215 }, { -2010, 4793, -5110 } },
	{ LevelIDs_Invalid },
};

LevelEndPosition Sonic2PIntro[] = {
	{ LevelIDs_GreenForest, 0, 0, 0, { -87, -860, 1305 }, { -87, -860, 1305 } },
	{ LevelIDs_SkyRail, 0x1800, 0x1800, 0, { -2548, -1762.4f, 3508 }, { -2548, -1762.4f, 3508 } },
	{ LevelIDs_MetalHarbor2P, 0x4000, 0x4000, 0, { 2065, -160, -4325 }, { 2065, -160, -4325 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0, { 105, 200, 0 }, { -105, 200, 0 } },
	{ LevelIDs_GreenHill, 0x4000, 0x4000, 0, { -80, 70, -480 }, { -80, 70, -480 } },
	{ LevelIDs_CityEscape, 0xC000u, 0xC000u, 0, { 90, -2813, 5000 }, { 90, -2813, 5000 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_FinalChase, 0x8000u, 0x4000, 0, { 3600, -4525, 4675 }, { 3600, -4525, 4675 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 0, -815, -910 }, { 0, -815, -910 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0xA000u, 0, { 4205, -2126, 430 }, { 6395, -1919, -2650 } },
	{ LevelIDs_DowntownRace, 0xF700u, 0xB00, 0, { -2010, 4793, -5215 }, { -2010, 4793, -5110 } },
	{ LevelIDs_Invalid },
};
#pragma warning(default : 4838)

LevelEndPosition *Sonic2PIntroList[] = { Sonic2PIntro, Shadow2PIntro, MechTails2PIntro, MechEggman2PIntro, Knuckles2PIntro, Rouge2PIntro };
LevelEndPosition *Shadow2PIntroList[] = { Shadow2PIntro, Sonic2PIntro, MechEggman2PIntro, MechTails2PIntro, Rouge2PIntro, Knuckles2PIntro };
LevelEndPosition *MechTails2PIntroList[] = { MechTails2PIntro, MechEggman2PIntro, Sonic2PIntro, Shadow2PIntro, Knuckles2PIntro, Rouge2PIntro };
LevelEndPosition *MechEggman2PIntroList[] = { MechEggman2PIntro, MechTails2PIntro, Shadow2PIntro, Sonic2PIntro, Rouge2PIntro, Knuckles2PIntro };
LevelEndPosition *Knuckles2PIntroList[] = { Knuckles2PIntro, Rouge2PIntro, Sonic2PIntro, Shadow2PIntro, MechTails2PIntro, MechEggman2PIntro };
LevelEndPosition *Rouge2PIntroList[] = { Rouge2PIntro, Knuckles2PIntro, Shadow2PIntro, Sonic2PIntro, MechEggman2PIntro, MechTails2PIntro };

void __cdecl Load2PIntroPos_ri(int playerNum)
{
	ObjectMaster *v1; // eax@1
	int v2; // edi@1
	CharObj2Base *v3; // eax@2
	EntityData1 *v4; // esi@2
	LevelEndPosition **list;
	LevelEndPosition *v5; // eax@4
	bool v6; // edx@11
	NJS_VECTOR *v8; // ecx@15
	CharObj2Base *v9; // eax@16
	int v10; // edi@16
	char v11; // al@16
	NJS_VECTOR *v12; // eax@20
	float v13; // ST10_4@20

	v2 = playerNum;
	v1 = MainCharacter[playerNum];
	if ( v1 )
	{
		v4 = v1->Data1.Entity;
		v3 = MainCharObj2[v2];
		if ( v3 )
		{
			switch ( v3->CharID )
			{
			case Characters_Sonic:
			case Characters_Tails:
			case Characters_SuperSonic:
				list = Sonic2PIntroList;
				break;
			case Characters_Shadow:
			case Characters_Eggman:
			case Characters_SuperShadow:
				list = Shadow2PIntroList;
				break;
			case Characters_Knuckles:
				list = Knuckles2PIntroList;
				break;
			case Characters_Rouge:
				list = Rouge2PIntroList;
				break;
			case Characters_MechEggman:
				list = MechEggman2PIntroList;
				break;
			case Characters_MechTails:
				list = MechTails2PIntroList;
				break;
			default:
				goto LABEL_10;
			}
		}
		else
		{
LABEL_10:
			list = 0;
		}
		v6 = v2 != 0;
		if ( list )
		{
			for (int i = 0; i < (int)LengthOfArray(Sonic2PIntroList); i++)
			{
				v5 = list[i];
				while ( v5->Level != LevelIDs_Invalid )
				{
					if ( v5->Level == (short)CurrentLevel )
					{
						v4->Rotation.y = *(&v5->Mission2YRotation + v6);
						v12 = (NJS_VECTOR *)((char *)&v5->Mission2Position + 12 * v6);
						v4->Position = *v12;
						v8 = &v4->Position;
						*((int *)*(&off_1DE95E0 + v2) + 7) = v4->Rotation.y;
						v13 = v4->Position.y - 10.0f;
						*(float *)&MainCharObj2[v2]->field_1A0[5] = v13;
						goto LABEL_16;
					}
					++v5;
				}
			}
		}
		v4->Position.z = 0.0;
		v8 = &v4->Position;
		v4->Position.y = 0.0;
		v4->Rotation.y = 0;
		v4->Position.x = 0.0;
LABEL_16:
		sub_46DC70(v2, v8, 0);
		v4->Collision->CollisionArray->field_2 |= 0x70u;
		v11 = *(char*)0x1DE4660;
		*(int*)&MainCharObj2[v2]->gap_70[24] = 0;
		byte_1DE4664[v2 & 1] = v11;
		v9 = MainCharObj2[v2];
		v10 = (int)*(&off_1DE95E0 + v2);
		if ( v9 )
		{
			v9->Speed.x = 0.0;
			v9->Speed.y = 0.0;
			v9->Speed.z = 0.0;
		}
		if ( v10 )
		{
			*(float *)(v10 + 8) = 0.0;
			*(float *)(v10 + 4) = 0.0;
			*(float *)v10 = 0.0;
		}
	}
}

__declspec(naked) void Load2PIntroPos_r()
{
	__asm
	{
		push eax
			call Load2PIntroPos_ri
			add esp, 4
			retn
	}
}

void __cdecl LoadBossCharacter()
{

	int character = CurrentCharacter ^ 1;
	AltCharacter[1] = rand() % 2;


	/*switch (CurrentLevel) {
	case LevelIDs_TailsVsEggman1:
		character = Characters_MechTails + rand() % 2;
		break;
	case LevelIDs_TailsVsEggman2:
		character = Characters_MechTails + rand() % 2;
		break;
	case LevelIDs_KnucklesVsRouge:
		character = Characters_Knuckles + rand() % 2;
		break;
	case LevelIDs_SonicVsShadow1:
		character = Characters_Sonic + rand() % 2;
		break;
	case LevelIDs_SonicVsShadow2:
		character = Characters_Sonic + rand() % 2;
		break;
	}*/
	if (choose == 1) {
		int buttons = MenuButtons_Held[1];
		if (buttons & Buttons_Left)
			character = Characters_Sonic;
		if (buttons & Buttons_Right)
			character = Characters_Shadow;
		if (buttons & Buttons_Down)
			character = Characters_Knuckles;
		if (buttons & Buttons_Up)
			character = Characters_Rouge;
		if (buttons & Buttons_R)
			character = Characters_MechTails;
		if (buttons & Buttons_L)
			character = Characters_MechEggman;
		if (buttons & Buttons_Y)
			character = Characters_Tails;
		if (buttons & Buttons_X)
			character = Characters_Eggman;
		if (buttons & Buttons_B)
			AltCharacter[1] = 1;
		if (buttons & Buttons_A)
			AltCostume[1] = 1;
	}
	switch (character)
	{
	case Characters_Sonic:
		LoadSonic(1);
		break;
	case Characters_Shadow:
		LoadShadow(1);
		break;
	case Characters_Tails:
		LoadTails(1);
		break;
	case Characters_Eggman:
		LoadEggman(1);
		break;
	case Characters_Knuckles:
		LoadKnuckles(1);
		break;
	case Characters_Rouge:
		LoadRouge(1);
		break;
	case Characters_MechTails:
		LoadMechTails(1);
		break;
	case Characters_MechEggman:
		LoadMechEggman(1);
		break;
	}
}

const void *const loc_6193F5 = (void*)0x6193F5;

__declspec(naked) void sub_6193D0()
{
	LoadBossCharacter();
	__asm
	{
		push ebx
		push esi
		push edi
		xor ebx, ebx
		jmp loc_6193F5
	}
}

const void *const loc_4C7120 = (void*)0x4C7120;
__declspec(naked) void sub_4C7100()
{
	LoadBossCharacter();
	__asm jmp loc_4C7120
}

const void *const loc_6486B2 = (void*)0x6486B2;
__declspec(naked) void sub_648690()
{
	LoadBossCharacter();
	__asm jmp loc_6486B2
}

const void *const loc_6266A2 = (void*)0x6266A2;
__declspec(naked) void sub_626680()
{
	LoadBossCharacter();
	__asm jmp loc_6266A2
}

const void *const loc_661D12 = (void*)0x661D12;
__declspec(naked) void sub_661CF0()
{
	LoadBossCharacter();
	__asm jmp loc_661D12
}

CharObj2Base *__cdecl loc_727E5B_i(int playerNum)
{
	CharObj2Base *v13 = MainCharObj2[playerNum];
	NJS_TEXLIST *v12 = 0;
	if ( v13 )
	{
		switch ( v13->CharID2 )
		{
		case Characters_Sonic:
		case Characters_SuperSonic:
			v12 = &TexList_SonicLife;
			break;
		case Characters_Shadow:
		case Characters_SuperShadow:
			v12 = &TexList_ShadowLife;
			break;
		case Characters_Amy:
			v12 = &TexList_AmyLife;
			break;
		case Characters_MetalSonic:
			v12 = &TexList_MetalLife;
			break;
		case Characters_Tails:
		case Characters_MechTails:
			v12 = &TexList_TailsLife;
			break;
		case Characters_ChaoWalker:
			v12 = &TexList_ChaoLife;
			break;
		case Characters_DarkChaoWalker:
			v12 = &TexList_DarkChaoLife;
			break;
		case Characters_Knuckles:
			v12 = &TexList_KnucklesLife;
			break;
		case Characters_Rouge:
			v12 = &TexList_RougeLife;
			break;
		case Characters_Tikal:
			v12 = &TexList_TikalLife;
			break;
		case Characters_Chaos:
			v12 = &TexList_ChaosLife;
			break;
		default:
			return 0;
		}
		(*(int**)0x2670544)[8] = (int)v12;
	}
	return v13;
}

const void *const loc_727F34 = (void*)0x727F34;
const void *const loc_727EA8 = (void*)0x727EA8;
__declspec(naked) void loc_727E5B()
{
	__asm
	{
		push esi
			call loc_727E5B_i
			add esp, 4
			test eax, eax
			jz lab
			xor ecx, ecx
			jmp loc_727EA8
lab:
		jmp loc_727F34
	}
}

static const void *const loc_6C6431 = (void*)0x6C6431;
static const void *const loc_6C6412 = (void*)0x6C6412;
__declspec(naked) void loc_6C63E7()
{
	__asm
	{
		mov eax, MissionNum
			cmp	long ptr [eax], 1
			je	_loc_6C6412
			mov	eax, [ebp+8]
		cdq
			mov	esi, 3
			idiv	esi
			cmp	edx, 1
			je _loc_6C6431
			mov	eax, CurrentLevel
			mov eax, [eax]
		cmp	ax, LevelIDs_PumpkinHill
			je	short loc_6C659A
			cmp	ax, LevelIDs_AquaticMine
			je	short loc_6C659A
			cmp	ax, LevelIDs_SecurityHall
			je	short loc_6C659A
			cmp	ax, LevelIDs_WildCanyon
			je	short loc_6C659A
			cmp	ax, LevelIDs_DryLagoon
			je	short loc_6C659A
			cmp	ax, LevelIDs_DeathChamber
			je	short loc_6C659A
			cmp	ax, LevelIDs_EggQuarters
			je	short loc_6C659A
			cmp	ax, LevelIDs_MeteorHerd
			je	short loc_6C659A
			cmp	ax, LevelIDs_WildCanyon2P
			je	short loc_6C659A
			cmp	ax, LevelIDs_MadSpace
			je	short loc_6C659A
			cmp	ax, LevelIDs_DryLagoon2P
			je	short loc_6C659A
			cmp	ax, LevelIDs_PoolQuest
			je	short loc_6C659A
			cmp	ax, LevelIDs_PlanetQuest
			je	short loc_6C659A
			cmp	ax, LevelIDs_DeathChamber2P
			jne	_loc_6C6431

loc_6C659A:
		pop	esi
			pop	ebp
			pop	ebx
			retn
_loc_6C6412:
		mov ecx, 2
			jmp loc_6C6412
_loc_6C6431:
		mov ecx, 2
			jmp [loc_6C6431]
	}
}

static const void *const Knuckles_LevelBounds_o = (void*)0x737B50;
__declspec(naked) void Knuckles_LevelBounds_r()
{
	__asm
	{
		mov	ebx, [CurrentLevel]
		mov ebx, [ebx]
		cmp	bx, LevelIDs_PumpkinHill
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_AquaticMine
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_SecurityHall
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_WildCanyon
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DryLagoon
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DeathChamber
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_EggQuarters
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_MeteorHerd
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_WildCanyon2P
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_MadSpace
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DryLagoon2P
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_PoolQuest
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_PlanetQuest
		je	j_Knuckles_LevelBounds
		cmp	bx, LevelIDs_DeathChamber2P
		je	j_Knuckles_LevelBounds
		xor	eax, eax
		retn
j_Knuckles_LevelBounds:
		jmp [Knuckles_LevelBounds_o]
	}
}

DataPointer(NJS_TEXLIST, stru_1738D90, 0x1738D90);
DataPointer(NJS_TEXLIST, stru_1738DB0, 0x1738DB0);
void LoadTitleCardTextures()
{
	char *v15; // esi@19
	char filename[24]; // [sp+Ch] [bp-20h]@27

	if ( TwoPlayerMode || CurrentLevel == LevelIDs_Route101280 )
	{
		switch ( CurrentCharacter )
		{
		case Characters_Knuckles:
		case Characters_Rouge:
			v15 = "RO";
			break;
		case Characters_Tails:
		case Characters_Eggman:
		case Characters_MechTails:
		case Characters_MechEggman:
			v15 = "TA";
			break;
		default:
			v15 = "SO";
			break;
		}
	}
	else
	{
		if ( CurrentLevel == LevelIDs_CannonsCoreT )
			goto LABEL_26;
		switch ( MainCharObj2[0]->CharID2 )
		{
		case Characters_Shadow:
		case Characters_SuperShadow:
			v15 = "SH";
			break;
		case Characters_Eggman:
		case Characters_MechEggman:
			v15 = "EG";
			break;
		case Characters_Tails:
		case Characters_MechTails:
			v15 = "TA";
			break;
		case Characters_Knuckles:
			v15 = "KN";
			break;
		case Characters_Rouge:
			v15 = "RO";
			break;
		case Characters_Amy:
			v15 = "AM";
			break;
		case Characters_MetalSonic:
			v15 = "ME";
			break;
		case Characters_Tikal:
			v15 = "TI";
			break;
		case Characters_Chaos:
			v15 = "C0";
			break;
		case Characters_ChaoWalker:
			v15 = "CH";
			break;
		case Characters_DarkChaoWalker:
			v15 = "DC";
			break;
		default:
LABEL_26:
			v15 = "SO";
			break;
		}
	}
	sprintf_s(filename, "MISSIONTEX_%s", v15);
	LoadTextureList(filename, &stru_1738D90);
	sprintf_s(filename, "MISSIONTEX_%s2", v15);
	LoadTextureList(filename, &stru_1738DB0);
}

static const void *const loc_472B12 = (void*)0x472B12;
__declspec(naked) void loc_472A7D()
{
	LoadTitleCardTextures();
	__asm jmp loc_472B12
}

DataArray(char, byte_174AFF5, 0x174AFF5, 2);
void PlayEndLevelVoice(int playerNum)
{
	bool v3;
	__int16 v6; // cx@12
	CharObj2Base *v14; // edx@29
	bool v15; // eax@30
	int v16; // eax@42
	bool v17; // eax@62

	if (!HaveChaoKey)
		*(int *)AltCostume = 0;
	v3 = !playerNum;
	v6 = CurrentLevel;
	v14 = MainCharObj2[playerNum];
	if ( TwoPlayerMode )
	{
		v15 = byte_174AFF5[playerNum] != 1;
		switch ( v14->CharID2 )
		{
		case Characters_Sonic:
			if ( byte_174AFF5[playerNum] == 1 )
				v16 = 1529;
			else
				v16 = (char)(MainCharObj2[v3]->CharID2 - 1) != 0 ? 1613 : 1531;
			break;
		case Characters_Shadow:
			if ( byte_174AFF5[playerNum] == 1 )
				v16 = MainCharObj2[v3]->CharID2 != 0 ? 1604 : 1528;
			else
				v16 = 1530;
			break;
		case Characters_Knuckles:
			v16 = 2 * (v15 != 0) + 1254;
			break;
		case Characters_Rouge:
			v16 = 2 * (v15 != 0) + 1255;
			break;
		case Characters_MechTails:
			if ( byte_174AFF5[playerNum] == 1 )
				v16 = 1643;
			else
				v16 = (((MainCharObj2[v3]->CharID2 != Characters_MechEggman) - 1) & 0xFFFFFFBA) + 1715;
			break;
		case Characters_MechEggman:
			if ( byte_174AFF5[playerNum] != 1 || *(char*)0x174AFD2 )
				v16 = 1644;
			else
				v16 = 1642;
			break;
		case Characters_Amy:
			if ( byte_174AFF5[playerNum] == 1 )
			{
				if ( RingCount[playerNum] <= 100 )
					v16 = 8 * (RingCount[v3] < 20) + 2670;
				else
					v16 = 2680;
			}
			else
			{
				if ( RingCount[playerNum] <= 100 )
				{
					v17 = RingCount[v3] < 20;
					v17 = RingCount[v3] >= 20;
					v16 = ((v17 - 1) & 6) + 2673;
				}
				else
				{
					v16 = 2681;
				}
			}
			break;
		case Characters_Tikal:
			v16 = 2716;
			break;
		case Characters_Chaos:
			v16 = 2687;
			break;
		case Characters_MetalSonic:
			v16 = 2712;
			break;
		case Characters_ChaoWalker:
			v16 = 2692;
			break;
		case Characters_DarkChaoWalker:
			v16 = 2703;
			break;
		default:
			return;
		}
	}
	else
	{
		switch ( v14->CharID2 )
		{
		case Characters_Sonic:
			switch ( v6 )
			{
			case LevelIDs_BigFoot:
				v16 = 1605;
				break;
			case LevelIDs_SonicVsShadow1:
				v16 = 1606;
				break;
			case LevelIDs_EggGolemS:
				v16 = 1607;
				break;
			case LevelIDs_SonicVsShadow2:
				v16 = 1608;
				break;
			default:
				v16 = 1593;
				break;
			}
			break;
		case Characters_SuperSonic:
			v16 = (((v6 == LevelIDs_FinalHazard) - 1) & 0xFFFFFFEF) + 1610;
			break;
		case Characters_Shadow:
			switch ( v6 )
			{
			case LevelIDs_HotShot:
				v16 = 1594;
				break;
			case LevelIDs_SonicVsShadow1:
				v16 = 1596;
				break;
			case LevelIDs_SonicVsShadow2:
				v16 = 1598;
				break;
			case LevelIDs_Biolizard:
				v16 = 1600;
				break;
			default:
				v16 = 1552;
				break;
			}
			break;
		case Characters_SuperShadow:
			v16 = (((v6 == LevelIDs_FinalHazard) - 1) & 0xFFFFFFCE) + 1602;
			break;
		case Characters_Knuckles:
			if ( v6 == LevelIDs_KnucklesVsRouge )
				v16 = 1344;
			else
				v16 = v6 != LevelIDs_KingBoomBoo ? 1330 : 1342;
			break;
		case Characters_Rouge:
			if ( v6 == LevelIDs_KnucklesVsRouge )
				v16 = 1345;
			else
				v16 = v6 != LevelIDs_FlyingDog ? 1331 : 1343;
			break;
		case Characters_MechTails:
			v16 = (((v6 == LevelIDs_TailsVsEggman1) - 1) & 0xFFFFFFF4) + 1715;
			break;
		case Characters_MechEggman:
			v16 = (((v6 == LevelIDs_TailsVsEggman1) - 1) & 0x3A) + 1642;
			break;
		case Characters_Amy:
			v16 = 2679;
			break;
		case Characters_Tikal:
			v16 = 2716;
			break;
		case Characters_Chaos:
			v16 = 2687;
			break;
		case Characters_MetalSonic:
			v16 = 2712;
			break;
		case Characters_ChaoWalker:
			v16 = 2692;
			break;
		case Characters_DarkChaoWalker:
			v16 = 2703;
			break;
		default:
			return;
		}
	}
	PlayVoice(2, v16);
}

static const void *const loc_43F1FC = (void*)0x43F1FC;
__declspec(naked) void loc_43EE5F()
{
	__asm
	{
		push esi
			call PlayEndLevelVoice
			pop esi
			jmp loc_43F1FC
	}
}

void LoadAquaticMineCharAnims_r()
{
	if (CurrentCharacter == Characters_Knuckles)
		LoadAquaticMineCharAnims();
	else
		LoadDryLagoon2PCharAnims();

}

void LoadDryLagoonCharAnims_r()
{
	if (CurrentCharacter == Characters_Rouge)
		LoadDryLagoonCharAnims();
	else
		LoadDryLagoon2PCharAnims();
}

void LoadCannonsCoreRCharAnims_r()
{
	if (CurrentCharacter == Characters_Rouge || CurrentCharacter == Characters_Knuckles)
		LoadCannonsCoreRCharAnims();
	else if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow)
		LoadBiolizardCharAnims();
	else
	LoadDryLagoon2PCharAnims();
}

void LoadCannonsCoreKCharAnims_r()
{
	if (CurrentCharacter == Characters_Knuckles)
		LoadCannonsCoreKCharAnims();
	else
		LoadDryLagoon2PCharAnims();
}

void LoadSandOceanCharAnims_r()
{
	if (CurrentCharacter == Characters_MechEggman || CurrentCharacter == Characters_MechTails)
		LoadSandOceanCharAnims();
	else if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow)
		LoadEggGolemCharAnims();
	else
		LoadSandOcean2PCharAnims();
}

void LoadHiddenBaseCharAnims_r()
{
	if (CurrentCharacter == Characters_MechTails || CurrentCharacter == Characters_MechEggman)
		LoadHiddenBaseCharAnims();
	else if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow)/////////////////////////////////////////////////////////////////
		LoadBiolizardCharAnims();
	else
		LoadSandOcean2PCharAnims();
}

void LoadEggGolemECharAnims_r()
{
	if (CurrentCharacter == Characters_MechEggman || CurrentCharacter == Characters_MechTails)
		LoadEggGolemECharAnims();
	else if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow)
		LoadEggGolemCharAnims();
	else
		LoadSandOcean2PCharAnims();
}

ThiscallFunctionPointer(void, sub_435880, (char *), 0x435880);
void LoadChaoWorldSoundBank()
{
	char *v4;

	int v2 = MainCharObj2[0]->CharID2;
	switch ( v2 )
	{
	case Characters_Amy:
	case Characters_MetalSonic:
		v4 = "chao_chara_sn.mlt";
		break;
	case Characters_Knuckles:
	case Characters_Rouge:
		v4 = "chao_chara_kr.mlt";
		break;
	case Characters_Tikal:
	case Characters_Chaos:
		v4 = "se_ch_kn_BATTLE.mlt";
		break;
	case Characters_Tails:
	case Characters_Eggman:
		v4 = "chao_chara_te.mlt";
		break;
	case Characters_MechTails:
	case Characters_MechEggman:
		v4 = "se_ch_wk.mlt";
		break;
	case Characters_ChaoWalker:
	case Characters_DarkChaoWalker:
		v4 = "se_ch_wk_BATTLE.mlt";
		break;
	default:
		v4 = "chao_chara_ss.mlt";
		break;
	}
	sub_435880(v4);
}

static const int loc_532054 = 0x532054;
__declspec(naked) void loc_532029()
{
	LoadChaoWorldSoundBank();
	__asm jmp loc_532054
}

static const int stru_173A0B8 = 0x173A0B8;
static const int sub_459010 = 0x459010;
static const int loc_45923B = 0x45923B;
__declspec(naked) void loc_2800440()
{
	__asm
	{
		mov ecx, MainCharObj2
			movzx ecx, [ecx].CharID2
			cmp ecx, Characters_Amy
			jle	short loc_280045F
			cmp	ecx, Characters_Tikal
			jz	short loc_280045A
			cmp	ecx, Characters_Amy
			jnz	short loc_280045F
			mov	esi, stru_173A0B8
			jmp	short loc_280045F
			; ---------------------------------------------------------------------------

loc_280045A:
		mov	esi, (stru_173A0B8+20h)

loc_280045F:
		call	sub_459010
			jmp	loc_45923B
	}
}

static const int loc_72F528 = 0x72F528;
static const int loc_72F4DB = 0x72F4DB;
static NJS_OBJECT **const KnucklesSunglassesModel = &CharacterModels[161].Model;
__declspec(naked) void KnucklesSunglassesFix()
{
	__asm
	{
		mov eax, KnucklesSunglassesModel
			mov eax, [eax]
		test eax, eax
			jz label
			jmp loc_72F4DB
label:
		jmp loc_72F528
	}
}

static const int loc_72F564 = 0x72F564;
static const int loc_72F537 = 0x72F537;
static NJS_OBJECT **const KnucklesAirNecklaceModel = &CharacterModels[168].Model;
__declspec(naked) void KnucklesAirNecklaceFix()
{
	__asm
	{
		mov ecx, KnucklesAirNecklaceModel
			mov ecx, [ecx]
		test ecx, ecx
			jz label
			jmp loc_72F537
label:
		jmp loc_72F564
	}
}

static const int loc_74496B = 0x74496B;
static const int loc_74491A = 0x74491A;
static NJS_OBJECT **const EggmanLaserBlasterModel = &CharacterModels[260].Model;
__declspec(naked) void EggmanLaserBlasterFix()
{
	__asm
	{
		mov edx, EggmanLaserBlasterModel
			mov edx, [edx]
		test edx, edx
			jz label
			jmp loc_74491A
label:
		jmp loc_74496B
	}
}

static const int loc_744E59 = 0x744E59;
static const int loc_744E08 = 0x744E08;
static NJS_OBJECT **const EggmanLargeCannonModel1 = &CharacterModels[262].Model;
static NJS_OBJECT **const EggmanLargeCannonModel2 = &CharacterModels[263].Model;
static const float *const flt_8AF004 = (const float *)0x8AF004;
__declspec(naked) void EggmanLargeCannonFix()
{
	__asm
	{
		mov eax, EggmanLargeCannonModel1
			mov eax, [eax]
		test eax, eax
			jz label
			mov eax, EggmanLargeCannonModel2
			mov eax, [eax]
		test eax, eax
			jz label
			mov eax, flt_8AF004
			fld [eax]
		jmp loc_744E08
label:
		jmp loc_744E59
	}
}

static const int loc_7481C3 = 0x7481C3;
static const int loc_74816E = 0x74816E;
static NJS_OBJECT **const TailsLaserBlasterModel = &CharacterModels[306].Model;
__declspec(naked) void TailsLaserBlasterFix()
{
	__asm
	{
		mov edx, TailsLaserBlasterModel
			mov edx, [edx]
		test edx, edx
			jz label
			jmp loc_74816E
label:
		jmp loc_7481C3
	}
}

static const int loc_748717 = 0x748717;
static const int loc_748620 = 0x748620;
static NJS_OBJECT **const TailsBazookaModel = &CharacterModels[309].Model;
__declspec(naked) void TailsBazookaFix()
{
	__asm
	{
		mov esi, TailsBazookaModel
			mov esi, [esi]
		test esi, esi
			jz label
			jmp loc_748620
label:
		jmp loc_748717
	}
}

static const int loc_4EB2B5 = 0x4EB2B5;
__declspec(naked) void InitSplitscreen_r()
{
	__asm
	{
		mov eax, [MenuButtons_Held]
		mov eax, [eax+4]
		and eax, Buttons_Start
		jz label
		mov dword ptr [esp+4], 2
label:
		push    ebx
		xor     ebx, ebx
		push    esi
		push    edi
		jmp loc_4EB2B5
	}
}

const int loc_757BC8 = 0x757BC8;
__declspec(naked) void loc_757BB2()
{
	__asm
	{
		test ecx, ecx
		jz NotAmy
		movsx ecx, [ecx].CharID2
		cmp	ecx, Characters_Sonic
		jne	short NotSonic
		mov	ecx, Texlist_SonEff
		jmp	loc_757BC8

		NotSonic :
		cmp	ecx, Characters_Shadow
			jne	short NotShadow
			mov	ecx, Texlist_ShadEff
			jmp	loc_757BC8

			NotShadow :
		cmp	ecx, Characters_Amy
			jne	short NotAmy
			mov	ecx, Texlist_AmyEff
			jmp	loc_757BC8

			NotAmy :
		mov	ecx, Texlist_MetEff
			jmp	loc_757BC8
	}
}

const int loc_757D68 = 0x757D68;
__declspec(naked) void loc_757D52()
{
	__asm
	{
		test ecx, ecx
		jz NotAmy
		movsx ecx, [ecx].CharID2
		cmp	ecx, Characters_Sonic
		jne	short NotSonic
		mov	ecx, Texlist_SonEff
		jmp	loc_757D68

		NotSonic :
		cmp	ecx, Characters_Shadow
			jne	short NotShadow
			mov	ecx, Texlist_ShadEff
			jmp	loc_757D68

			NotShadow :
		cmp	ecx, Characters_Amy
			jne	short NotAmy
			mov	ecx, Texlist_AmyEff
			jmp	loc_757D68

			NotAmy :
		mov	ecx, Texlist_MetEff
			jmp	loc_757D68
	}
}



AnimationInfo TailsAnimList2[ChaosAnimList_Length];
AnimationInfo MechEggmanAnimList2[ChaosAnimList_Length];
AnimationInfo MechTailsAnimList2[ChaosAnimList_Length];
AnimationInfo ChaoWalkerAnimList2[ChaosAnimList_Length];
AnimationInfo DarkChaoWalkerAnimList2[ChaosAnimList_Length];
AnimationInfo EggmanAnimList2[ChaosAnimList_Length];
AnimationInfo SonicAnimList2[ChaosAnimList_Length];

pair<int, int> listend = { -1, 0 };
template <size_t N>
void actionlistthing(pair<int, int> *(&order)[N], void **ptr, bool skipmagichands)
{
	vector<pair<int, int>> tmp;
	for (size_t i = 0; i < LengthOfArray(order); i++)
	{
		while (order[i]->key != -1)
		{
			if (skipmagichands && order[i]->key == 74)
				goto next;
			for (size_t j = 0; j < tmp.size(); j++)
				if (tmp[j].key == order[i]->key)
					goto next;
			tmp.emplace_back(*order[i]);
		next:
			++order[i];
		}
	}
	tmp.emplace_back(listend);
	pair<int, int> *buf = new pair<int, int>[tmp.size()];
	memcpy(buf, tmp.data(), tmp.size() * sizeof(pair<int, int>));
	WriteData(ptr, (void*)buf);
}

static string trim(const string &s)
{
	auto st = s.find_first_not_of(' ');
	if (st == string::npos)
		st = 0;
	auto ed = s.find_last_not_of(' ');
	if (ed == string::npos)
		ed = s.size() - 1;
	return s.substr(st, (ed + 1) - st);
}

static const unordered_map<string, uint8_t> charnamemap = {
	{ "sonic", Characters_Sonic },
	{ "shadow", Characters_Shadow },
	{ "tails", Characters_Tails },
	{ "eggman", Characters_Eggman },
	{ "knuckles", Characters_Knuckles },
	{ "rouge", Characters_Rouge },
	{ "mechtails", Characters_MechTails },
	{ "mecheggman", Characters_MechEggman },
	{ "amy", Characters_Sonic | altcharacter },
	{ "metalsonic", Characters_Shadow | altcharacter },
	{ "tikal", Characters_Knuckles | altcharacter },
	{ "chaos", Characters_Rouge | altcharacter },
	{ "chaowalker", Characters_MechTails | altcharacter },
	{ "darkchaowalker", Characters_MechEggman | altcharacter },
	{ "sonicalt", Characters_Sonic | altcostume },
	{ "shadowalt", Characters_Shadow | altcostume },
	{ "knucklesalt", Characters_Knuckles | altcostume },
	{ "rougealt", Characters_Rouge | altcostume },
	{ "mechtailsalt", Characters_MechTails | altcostume },
	{ "mecheggmanalt", Characters_MechEggman | altcostume }
};

static uint8_t ParseCharacterID(const string &str, Characters def)
{
	string s = trim(str);
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	auto ch = charnamemap.find(s);
	if (ch != charnamemap.end())
		return ch->second;
	return def;
}




const string charnames[Characters_Amy] = { "Sonic", "Shadow", "Tails", "Eggman", "Knuckles", "Rouge", "MechTails", "MechEggman" };

extern "C"
{

	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		savePath = path;
		AnimationInfo *buf = TailsAnimList2;
		WriteData((AnimationInfo**)0x74CFD7, buf);
		memcpy(TailsAnimList2, TailsAnimList, TailsAnimList_Length * sizeof(AnimationInfo));

		buf = MechEggmanAnimList2;
		WriteData((AnimationInfo**)0x740D50, buf);
		memcpy(MechEggmanAnimList2, MechEggmanAnimList, MechEggmanAnimList_Length * sizeof(AnimationInfo));

		buf = MechTailsAnimList2;
		WriteData((AnimationInfo**)0x740FB0, buf);
		memcpy(MechTailsAnimList2, MechTailsAnimList, MechTailsAnimList_Length * sizeof(AnimationInfo));

		buf = ChaoWalkerAnimList2;
		WriteData((AnimationInfo**)0x7411DC, buf);
		memcpy(ChaoWalkerAnimList2, ChaoWalkerAnimList, ChaoWalkerAnimList_Length * sizeof(AnimationInfo));

		buf = DarkChaoWalkerAnimList2;
		WriteData((AnimationInfo**)0x7413BC, buf);
		memcpy(DarkChaoWalkerAnimList2, DarkChaoWalkerAnimList, DarkChaoWalkerAnimList_Length * sizeof(AnimationInfo));

		buf = EggmanAnimList2;
		WriteData((AnimationInfo**)0x73C2F2, buf);
		memcpy(EggmanAnimList2, EggmanAnimList, EggmanAnimList_Length * sizeof(AnimationInfo));

		buf = SonicAnimList2;
		WriteData((AnimationInfo**)0x716F0A, buf);
		memcpy(SonicAnimList2, SonicAnimList, SonicAnimList_Length * sizeof(AnimationInfo));

		pair<int, int> *sonic = (pair<int, int>*)0x96EC80;
		pair<int, int> *amy = (pair<int, int>*)0x96ECD0;
		pair<int, int> *shadow = (pair<int, int>*)0x96ED18;
		pair<int, int> *knuckles = (pair<int, int>*)0x96ED58;
		pair<int, int> *tikal = (pair<int, int>*)0x96EDB8;
		pair<int, int> *rouge = (pair<int, int>*)0x96EE10;
		pair<int, int> *chaos = (pair<int, int>*)0x96EE80;
		pair<int, int> *mecheggman = (pair<int, int>*)0x96EED8;
		pair<int, int> *darkchaowalker = (pair<int, int>*)0x96EF08;
		pair<int, int> *mechtails = (pair<int, int>*)0x96EF38;
		pair<int, int> *chaowalker = (pair<int, int>*)0x96EF68;
		pair<int, int> *eggman = (pair<int, int>*)0x96EF98;
		pair<int, int> *tails = (pair<int, int>*)0x96EFA8;
		{
			pair<int, int> *order[] = { sonic, shadow, rouge, knuckles, mechtails, mecheggman };
			actionlistthing(order, (void**)0x7952E5, false);
		}
		{
			pair<int, int> *order[] = { amy, sonic, shadow, rouge, knuckles, mechtails, mecheggman };
			actionlistthing(order, (void**)0x7952EC, false);
		}
		{
			pair<int, int> *order[] = { shadow, sonic, rouge, knuckles, mechtails, mecheggman };
			actionlistthing(order, (void**)0x7952F3, false);
		}
		{
			pair<int, int> *order[] = { tails, mechtails, mecheggman, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x7952FA, true);
		}
		{
			pair<int, int> *order[] = { knuckles, rouge, sonic, shadow, mechtails, mecheggman };
			actionlistthing(order, (void**)0x795301, true);
		}
		{
			pair<int, int> *order[] = { tikal, rouge, knuckles, sonic, shadow, mechtails, mecheggman };
			actionlistthing(order, (void**)0x795308, true);
		}
		{
			pair<int, int> *order[] = { rouge, knuckles, sonic, shadow, mechtails, mecheggman };
			actionlistthing(order, (void**)0x79530F, true);
		}
		{
			pair<int, int> *order[] = { chaos, rouge, knuckles, sonic, shadow, mechtails, mecheggman };
			actionlistthing(order, (void**)0x795316, true);
		}
		{
			pair<int, int> *order[] = { eggman, mecheggman, mechtails, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x79531D, true);
		}
		{
			pair<int, int> *order[] = { mecheggman, mechtails, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x795324, true);
		}
		{
			pair<int, int> *order[] = { darkchaowalker, mecheggman, mechtails, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x79532B, true);
		}
		{
			pair<int, int> *order[] = { chaowalker, mechtails, mecheggman, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x795332, true);
		}
		{
			pair<int, int> *order[] = { mechtails, mecheggman, sonic, shadow, rouge, knuckles };
			actionlistthing(order, (void**)0x795339, true);
		}

		WriteCall((void*)0x729D16, Knuckles_LevelBounds_r);
		WriteCall((void*)0x729DC5, Knuckles_LevelBounds_r);
		WriteCall((void*)0x72B0F1, Knuckles_LevelBounds_r);
		WriteCall((void*)0x72B2E8, Knuckles_LevelBounds_r);
		WriteCall((void*)0x4D45F0, LoadAquaticMineCharAnims_r);
		WriteCall((void*)0x63D727, LoadDryLagoonCharAnims_r);
		WriteCall((void*)0x4DB351, LoadCannonsCoreRCharAnims_r);
		WriteCall((void*)0x65E8F1, LoadCannonsCoreKCharAnims_r);
		WriteCall((void*)0x65662A, LoadSandOceanCharAnims_r);
		WriteCall((void*)0x4DDE49, LoadHiddenBaseCharAnims_r);
		WriteCall((void*)0x4A53AC, LoadEggGolemECharAnims_r);
		WriteData<2>((void*)0x723E1F, 0x90u);
		WriteJump((void*)0x757BB2, loc_757BB2);
		WriteJump((void*)0x757D52, loc_757D52);
		WriteData<2>((void*)0x72386C, 2);
//////////////////START ALL MY RANDO STUFF
		const IniFile *settings = new IniFile(std::string(path) + "\\config.ini");
		RandoSeed = settings->getInt("OnOff", "seed");
		//if (RandoSeed == 122) RandoSeed = 123;
		randomMissions = settings->getBool("OnOff", "rmissions");
		RmissionNum = rand() % 5 + 1;
		sehar = settings->getBool("OnOff", "setchars");
		story = settings->getString("OnOff", "story");
		showN = settings->getBool("OnOff", "showNames");

		if (settings->getBool("OnOff", "r2pc")) altncost = 0;
		if (settings->getBool("OnOff", "rAltCost")) nocosts = 1;
		//rchar = settings->getBool("OnOff", "rChar");
		setRNG = settings->getBool("OnOff", "setRNG");
		//randoSV = settings->getBool("OnOff", "rVers");
		randoSV = true;
		rVoices = settings->getBool("OnOff", "rVL");
		cVoices = settings->getBool("OnOff", "cVL");
		cADX = settings->getBool("OnOff", "cADX");
		noVanillaChars = settings->getBool("OnOff", "noVanilla");
		if(rVoices) WriteJump((void*)0x443130, PlayVoice_r);  /// VOICES


		if (RandoSeed != 0)
			seed = RandoSeed;
		else {
			srand(seed);
			seed = rand();
		}

		srand(seed);



		if(settings->getBool("OnOff", "rMusic")) WriteJump((void*)0x442CF0, PlayMusic_r);

		//boolean sehar = false;
		if (sehar) {
			for (int i = 0; i < Characters_Amy; i++) {
				defaultalts[i] = 0;
				defaultcosts[i] = 0;
				defaultcharacters[i] = ParseCharacterID(settings->getString("1Player", charnames[i]), (Characters)i);
				storedPrefs[i] = defaultcharacters[i];
			}
		}


		if (settings->getBool("pool", "Sonic")) inPool[0] = false;
		if (settings->getBool("pool", "Shadow")) inPool[1] = false;
		if (settings->getBool("pool", "Amy")) inPool[2] = false;
		if (settings->getBool("pool", "Metal Sonic")) inPool[3] = false;

		if (settings->getBool("pool", "Knuckles")) inPool[4] = false;
		if (settings->getBool("pool", "Rouge")) inPool[5] = false;
		if (settings->getBool("pool", "Tikal")) inPool[6] = false;
		if (settings->getBool("pool", "Chaos")) inPool[7] = false;

		if (settings->getBool("pool", "Mech Tails/Tails")) inPool[8] = false;
		if (settings->getBool("pool", "Mech Eggman/Eggman")) inPool[9] = false;
		if (settings->getBool("pool", "Chao Walker/Tails")) inPool[10] = false;
		if (settings->getBool("pool", "Dark Chao Walker/Eggman")) inPool[11] = false;

		numCharsinPool = 0;
		for (int i = 0; i < 12; i++) {
			if (inPool[i]) {
				//PrintDebug("here");
				useThisPool[numCharsinPool] = charPool[i];
				//PrintDebug(std::to_string(numCharsinPool).c_str());
				numCharsinPool++;
				//PrintDebug(std::to_string(numCharsinPool).c_str());
			}
		}




		//inplaceCut = settings->getBool("OnOff", "cuts");
		disRL = settings->getBool("OnOff", "disRandL");
		Randomize(seed);



		/*for (int j = 0; j < cutoff; j++) {
			if (Levellist[j].entry_type == 1)
				Levellist[j].character_id = defaultcharacters[Levellist[j].character_id];
		}*/
		


		if(settings->getBool("OnOff", "upmods")){
			WriteJump((void*)0x7207CC, (void*)0x720A82);
			WriteJump((void*)0x72F4CD, (void*)0x72F601);
			WriteJump((void*)0x730FEF, (void*)0x73112A);
			WriteJump((void*)0x74490B, (void*)0x74496B);
			WriteJump((void*)0x744DF3, (void*)0x744E59);
			WriteJump((void*)0x744FD1, (void*)0x745064);
			WriteJump((void*)0x745112, (void*)0x74515D);
			WriteJump((void*)0x74815F, (void*)0x7481C3);
			WriteJump((void*)0x74860E, (void*)0x748717);
			WriteJump((void*)0x7488CF, (void*)0x748948);

		}//Upgrade Model Stuff

		if (true) LogThis("LevelLists.txt");
		logThisV = settings->getBool("OnOff", "llg");
		//boolean logs = false;

		//WriteData<2>((void*)0x459110, 0x90);
		//WriteData<2>((void*)0x45913B, 0x90);

		
		if (settings->getBool("OnOff", "fastLoad")) WriteData<1>((void*)0x43A889, 0x03);
		if (settings->getBool("OnOff", "disKill")) WriteData<1>((void*)0x46AD50, 0xC3);
		disKill = settings->getBool("OnOff", "disKill");

		rkart = settings->getBool("OnOff", "rKart");
		if( rkart) randomizeKartStats();


		rChao = settings->getBool("chaoSets", "rChao");
		maxChaoStats = settings->getBool("chaoSets", "maxChao");
		colorChao = settings->getBool("chaoSets", "colorChao");
		disChaoReload = settings->getBool("chaoSets", "disChaoRR");
		disTempChaoFile = settings->getBool("chaoSets", "disChaoTemp");



		string baseFrom = savePath + "\\Options\\SAVEDATA\\";
		string baseTo = savePath + "\\gd_PC\\SAVEDATA\\";
		string f = "SONIC2B__ALF";
		baseFrom += f;
		baseTo += f;
		if (true) CopyFileA(baseFrom.c_str(), baseTo.c_str(), false);
		
		
		if(settings->getBool("OnOff", "setESG")) ESG = 1;


		


		delete settings;


		setUpCredits();

		hiddenGlitchChao = rand() % 100;

		//for(int i = 0; i < 4;i++) PrintDebug(std::to_string(EggmanActionWindowTextIndexes[i]).c_str());
		//WriteJump((void*)0x459110, SFX_r);//Work on SFX here

//////////////////////END OF RANDO STUFF
	}

	unsigned __int8 twobytenop[] = { 0x66, 0x90 };
	unsigned __int8 fivebytenop[] = { 0x66, 0x90, 0x66, 0x90, 0x90 };
	unsigned __int8 shortjmp[] = { 0xEB };

	PatchInfo patches[] = {
		patchdecl(0x44E63B, twobytenop), // Dark Chao Walker Life Icon Patch
		//patchdecl(0x459110, twobytenop), // 2P Sound Effects Patch
		patchdecl(0x45913B, twobytenop), // 2P Voice Patch
		patchdecl(0x4CD255, twobytenop), // Sonic's Cannon's Core Control Patch
		patchdecl(0x724261, shortjmp), // Sonic Boss Special Patch
		patchdecl(0x736211, shortjmp), // Knuckles Boss Special Patch
		patchdecl(0x7374E4, shortjmp), // Dry Lagoon Turtle Grab Patch
		patchdecl(0x749921, shortjmp), // Mech Boss Special Patch
		patchdecl(0x741690, shortjmp), // Dark Chao Walker Fix
		patchdecl(0x7416DC, shortjmp), // Chao Walker Fix
		patchdecl(0x728141, fivebytenop), // Knuckles emerald manager
		patchdecl(0x728491, fivebytenop), // Rouge emerald manager
		patchdecl(0x7288B7, fivebytenop), // Tikal emerald manager
		patchdecl(0x728B64, fivebytenop), // Chaos emerald manager
		patchdecl(0x716E13, twobytenop), // Amy
		patchdecl(0x716F2C, twobytenop), // Sonic costume
		patchdecl(0x717373, twobytenop), // Metal Sonic
		patchdecl(0x71748C, twobytenop), // Shadow costume
		patchdecl(0x728123, twobytenop), // Tikal
		patchdecl(0x728241, twobytenop), // Knuckles costume
		patchdecl(0x728473, twobytenop), // Chaos
		patchdecl(0x728591, twobytenop), // Rouge costume
		patchdecl(0x740C61, twobytenop), // Dark Chao Walker
		patchdecl(0x740D72, twobytenop), // Eggman costume
		patchdecl(0x740EC1, twobytenop), // Chao Walker
		patchdecl(0x740FD2, twobytenop), // Tails costume
		patchdecl(0x061f19d,shortjmp) //r101/r280 respawn
	};

	__declspec(dllexport) void OnFrame()
	{

		if (MenuButtons_Pressed[0] & Buttons_A) Acount++;
		if (MenuButtons_Pressed[0] & Buttons_B) Bcount++;
		if (MenuButtons_Pressed[0] & Buttons_X) Xcount++;
		if (MenuButtons_Pressed[0] & Buttons_Y) Ycount++;
		if (MenuButtons_Pressed[0] & Buttons_Start) Startcount++;

		if (is2PChar()) {
			WriteData<1>((void*)0x459110, 0x66);
			WriteData<1>((void*)0x459111, 0x90);
		}
		else{
			WriteData<1>((void*)0x459110, 0x74);
			WriteData<1>((void*)0x459111, 0x05);
		}


		if (CurrentLevel == LevelIDs_HiddenBase)
			if(CurrentCharacter != Characters_MechTails)
				if (MainCharObj1[0] != NULL)
					if (MainCharObj1[0]->Position.y <= -3 && controlActive) {
						MainCharObj1[0]->Status = Status_Hurt;
						MainCharObj1[0]->Position.y = 10;
					}

		if (CurrentLevel == LevelIDs_EggGolemS)
			if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Shadow)
				if (MainCharObj1[0] != NULL)
					if (MainCharObj1[0]->Position.y <= 0 && controlActive) {
						MainCharObj1[0]->Status = Status_Hurt;
						MainCharObj1[0]->Position.y = 10;
					}
		if (CurrentLevel == LevelIDs_SandOcean)
			if (CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Rouge)
				if (MainCharObj1[0] != NULL) {
					int limit = -3;
					int z = MainCharObj1[0]->Position.z;
					if ((z<-2000 && z >-2300) || (z<-3500 && z >-4400) || (z<-5600 && z >-6200)) limit = -130;
					if (MainCharObj1[0]->Position.y <= limit && controlActive) {
						MainCharObj1[0]->Status = Status_Hurt;
						MainCharObj1[0]->Position.y = 10;
					}
				}




		if (MainCharObj1[0] != NULL) {
			if (MainCharObj1[0]->Action == Action_Death) {
				//addUpTime();
				if(levelTimer != 0) totalDeaths++;
				levelTimer = 0;
				//PrintDebug(std::to_string(totalDeaths).c_str());
			}
			else {
				if (CurrentLevel == LevelIDs_CannonsCoreE || CurrentLevel == LevelIDs_CannonsCoreT || CurrentLevel == LevelIDs_CannonsCoreR || CurrentLevel == LevelIDs_CannonsCoreS || CurrentLevel == LevelIDs_CannonsCoreK) {
					if (TimeStopped != 0) totalCentis++;
				}
					
			}

			if (MainCharObj1[0]->Action == Action_Jump ) {
				if(!deathAdded) totalJumps++;
				deathAdded = true;
				//PrintDebug(std::to_string(totalJumps).c_str());
			}
			else if(MainCharObj1[0]->Action != Action_Fall && MainCharObj1[0]->Action != Action_Jump && MainCharObj1[0]->Action != Action_Glide && MainCharObj1[0]->Action != Action_MechHover){
				deathAdded = false;
			}

			if (MainCharObj1[0]->Action == Action_MonitorLook) {
				if (!hintRead) hintsRead++;
				hintRead = true;
				//PrintDebug(std::to_string(hintsRead).c_str());
			}
			else {
				hintRead = false;
			}
		
		
		}

		if (rChao) {
			if (CurrentLevel == LevelIDs_ChaoWorld) {
				//if(hiddenGlitchChao == 69 ) 
				if(maxChaoStats) Chao1Data.EggColor = rand() % 55;
				if (Chao1Data.Type == 2) {
					Chao1Data = randomizeChao(Chao1Data);
					if (maxChaoStats) Chao1Data = maxChao(Chao1Data);
				}
				if (Chao2Data.Type == 2) {
					Chao2Data = randomizeChao(Chao2Data);
				}
				if (Chao3Data.Type == 2) {
					Chao3Data = randomizeChao(Chao3Data);
				}
				if (Chao4Data.Type == 2) {
					Chao4Data = randomizeChao(Chao4Data);
				}

			}
		}
		
		/*if (CurrentLevel == LevelIDs_CannonsCoreS) {
			if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Sonic) {
				if(MainCharObj1[0] != NULL) if (MainCharObj1[0]->Action == 72) MainCharObj1[0]->Action = Action_None;
			}
		}*/

		if (CurrentLevel == LevelIDs_CannonsCoreT && GameState == GameStates_ReturnRing && (MissionNum == 1 || MissionNum == 2)) {
			NextLevel = LevelIDs_CannonsCoreE;
			GameState = GameStates_GoToNextLevel;
		}
		if (CurrentLevel == LevelIDs_CannonsCoreE && GameState == GameStates_ReturnRing && (MissionNum == 1 || MissionNum == 2)) {
			NextLevel = LevelIDs_CannonsCoreR;
			GameState = GameStates_GoToNextLevel;
		}
		if (CurrentLevel == LevelIDs_CannonsCoreR && GameState == GameStates_ReturnRing && (MissionNum == 1 || MissionNum == 2)) {
			NextLevel = LevelIDs_CannonsCoreK;
			GameState = GameStates_GoToNextLevel;
		}
		if (CurrentLevel == LevelIDs_CannonsCoreK && GameState == GameStates_ReturnRing && (MissionNum == 1 || MissionNum == 2)) {
			NextLevel = LevelIDs_CannonsCoreS;
			GameState = GameStates_GoToNextLevel;
		}


		if (MainCharObj2[0] != NULL && MainCharObj1[0] !=NULL) {
			if (CurrentCharacter == Characters_Eggman || CurrentCharacter == Characters_Tails) {
				if (MainCharObj1[0]->Action == 45) MainCharObj1[0]->Action = Action_None;
				//if ((MenuButtons_Pressed[0] & Buttons_L) && (MenuButtons_Pressed[0] & Buttons_Y) && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run)) {
				//	MainCharObj1[0]->Action = 45;
				//}
				if ((MenuButtons_Pressed[0] & Buttons_B) && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run)) {
					if (findClosestMM() < 50) {
						MainCharObj1[0]->Action = 45;
					}
				}

				if (createrMode) {
					if ((MenuButtons_Held[0] & Buttons_Down) && ControllerPointers[0]->y1 == 0 && levelTimer > 0 && lastUse == 0 && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run) && GameState != GameStates_Pause) {
						//if(objPlacedInStage) SETObjects->SETEntry[SETObjects->LoadCount - 1].ID = 1;
						SETEntries[SETObjectCount].Position = MainCharObj1[0]->Position;
						SETEntries[SETObjectCount].ID = springID;
						SETEntries[SETObjectCount].Scale.y = 3;
						SETEntries[SETObjectCount].XRot = MainCharObj1[0]->Rotation.x;
						SETEntries[SETObjectCount].ZRot = MainCharObj1[0]->Rotation.z;
						SETObjects->LoadCount = SETObjectCount;
						lastUse = cooldown;
					}
					if ((MenuButtons_Held[0] & Buttons_Up) && ControllerPointers[0]->y1 == 0 && levelTimer > 0 && lastUse == 0 && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run) && GameState != GameStates_Pause) {
						//if (objPlacedInStage) SETObjects->SETEntry[SETObjects->LoadCount-1].ID = 1;
						SETObjects->SETEntry[SETObjects->LoadCount].Position = MainCharObj1[0]->Position;
						SETObjects->SETEntry[SETObjects->LoadCount].ID = itemBoxID;
						SETObjects->SETEntry[SETObjects->LoadCount].Scale.x = 6;
						SETObjects->LoadCount++;
						lastUse = cooldown;
					}
				}

			}
		}

		if (lastUse > 0 && controlActive && GameState != GameStates_Pause) lastUse--;
	}



	__declspec(dllexport) PatchList Patches = { arrayptrandlengthT(patches, int) };

	PointerInfo jumps[] = {
		ptrdecl(0x458970, sub_458970), // Level Cutscene Function
		ptrdecl(LoadCharacters, LoadCharacters_r), // LoadCharacters replacement
		ptrdecl(0x757810, sub_757810), // Somersault Fix 1
		ptrdecl(0x759A18, loc_759A18), // Somersault Fix 2
		ptrdecl(LoadStartPositionPtr, LoadStartPosition_r), // LoadStartPosition replacement
		ptrdecl(0x43DF30, sub_43DF30), // End position
		ptrdecl(Load2PIntroPos, Load2PIntroPos_r), // 2P Intro position
		ptrdecl(0x6193D0, sub_6193D0), // Sonic vs Shadow 1
		ptrdecl(0x4C7100, sub_4C7100), // Sonic vs Shadow 2
		ptrdecl(0x648690, sub_648690), // Knuckles vs Rouge
		ptrdecl(0x626680, sub_626680), // Tails vs Eggman 1
		ptrdecl(0x661CF0, sub_661CF0), // Tails vs Eggman 2
		ptrdecl(0x727E5B, loc_727E5B), // 2P Race Bar
		ptrdecl(0x6C63E7, loc_6C63E7), // Goal Ring
		ptrdecl(0x43C9D0, 0x43CADF), // Tails/Eggman fix
		ptrdecl(0x472A7D, loc_472A7D), // Title Card textures
		ptrdecl(0x43EE5F, loc_43EE5F), // End Level voices
		ptrdecl(0x532029, loc_532029), // Chao World sounds
		ptrdecl(0x459236, loc_2800440), // Chao World voices
		ptrdecl(0x72F4D6, KnucklesSunglassesFix),
		ptrdecl(0x72F531, KnucklesAirNecklaceFix),
		ptrdecl(0x744914, EggmanLaserBlasterFix),
		ptrdecl(0x744E02, EggmanLargeCannonFix),
		ptrdecl(0x748168, TailsLaserBlasterFix),
		ptrdecl(0x74861A, TailsBazookaFix),
		//ptrdecl(InitSplitscreen, InitSplitscreen_r)
	};

	__declspec(dllexport) PointerList Jumps = { arrayptrandlengthT(jumps, int) };

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };


}
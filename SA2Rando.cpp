// SA2CharSel.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "HelperFuns.h"
#include "KartRando.h"
#include "FogRando.h"
#include "ChaoRando.h"
#include "StageVariants.h"
#include "Subtitles.h"
#include "EnemyRandomizer.h"
#include "TwitchIRC.h"
#include "ModelSwap.h"
namespace fs = std::filesystem;
//#define upgradecheck(chara,name) bool Disable##chara##name = settings->getBool("OnOff", "upmods");
//#define upgradecheck(chara,name) bool Disable##chara##name = false;
//#include "IniFile.hpp"





vector<ModelCredits> modelCreds;
HelperFunctions hf;
vector<short> validCutscenes;
vector<int> ignoreStages;
bool vanillaLives = false;
bool chaoMusic = false;
bool playFromWav = false;
int totalWavFiles = 0;
int game = 1;
int zero = 0;
CharObj2Base* dummy = new CharObj2Base;
TwitchIRC bot;
//vector<TwitchChatter> chatters;
unordered_map<string, int> commandCosts;
unordered_map<string, TwitchChatter> currency;
vector<int> currencyRates;
time_t lastUpdate = 0;
string channelName = "";
vector<string> mods;
int sizeOfAfs = 2727;
bool tag = false;
bool sa2vl = true;
bool sadxvl = true;
bool shvl = true;
bool vanBoss = false;
bool izzyDevMode = false;
bool enemies = false;
LevelCutscene *const stru_173A808 = (LevelCutscene*)0x173A808;
signed int __cdecl sub_458970()
{
	signed int v0; // ecx@3
	unsigned int v1; // eax@6
	if (CurrentLevel == LevelIDs_GreenForest && CurrentCharacter == Characters_Sonic && AltCharacter[0] == 0) return 1;
	else return 0;
	if (CurrentLevel == LevelIDs_BigFoot && CurrentCharacter == Characters_Sonic && AltCharacter[0] == 0) return 1;
	else return 0;
	if (MainCharObj2[0])
		v0 = MainCharObj2[0]->CharID2;
	else
		v0 = -1;
	if (v0 >= Characters_Amy) return 0;
	if (MainCharObj2[1] && MainCharObj2[1]->CharID2 >= Characters_Amy) return 0;
	if (MainCharObj2[1] && AltCostume[1]) return 0;
	if ( *(char*)0x1DEB321 && *(char*)0x1DEB320)
	{
		v1 = 0;
		while ( stru_173A808[v1].Level != (signed __int16)CurrentLevel
			|| stru_173A808[v1].Character )
		{
			v1++;
			if ( v1 >= 15 )
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


int defaultcharacters[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultalts[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultcosts[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int storedPrefs[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };
int defaultcharactersM5[Characters_Amy] = { Characters_Sonic, Characters_Shadow, Characters_Tails, Characters_Eggman, Characters_Knuckles, Characters_Rouge, Characters_MechTails, Characters_MechEggman };


int newCharPerStage[45] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int timeToDelete = -1;


boolean swapOnLoad = false;
bool savedTwitchData = false;
int storeVL[2727];
int storeADX[MusicList_Length];
bool dischaorace = false;
bool dischaokarate = false;

bool crowdControl = false;
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



int charBosses[5];//svs1,svs2,tve1,tve2,kvr
int charBossPlayer[5];//svs1,svs2,tve1,tve2,kvr

bool noQoL = false;
int m2Types[46];
int m2Type = 0;
int m2Req = 100;
int m2Reqs[46];
NJS_VECTOR speedLastFrame = { 1,1,1 };
int subNumber = 0;
string subType = "off";
std::vector<SubtitleQueue> displayMe;
int storeLives = 99;
int vlRandoType = 0;
boolean reloadComplete = true;
boolean rM3Loc = false;
boolean swapChao = false;
//float r = 1;
boolean rSize = false;
bool tPoseFuckery = false;
bool createrMode = false;
int alt;
int cost; 
int choose = 0;
int altncost = 1;
int nocosts = 0;
int heroonly = 0;
int bossInPool = 0;
boolean sehar = false;
int setCharTime = 0;
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
int igtSlot = 30;
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
bool rChaoAnimals = false;
char* chaoN[569] = { "Exant","MainMemory" ,"Mekhialtey02" , "_Gimmick", "_Houston", "0rbis", "1219nekogami", "2D", "44moth", "A_Bowl_Of_Cereal", "a_moustache", "aaaa", "AbsentSR", "acs13123", "Aero_Trigger", "Æzir", "afrogamer2660", "Aggressively Medium", "aguedouf", "AhoyKMS", "aioproject", "Air_iq", "akureikorineko", "Allegro", "Altairan", "AmberCyprian", "Ambloops", "Americanchoirboy", "andzura", "anthonyjuice", "AphexArcade", "Aquova", "AReytoRemember", "Argick", "Armageddun", "ArmorySons", "Aruki", "ASINISTERTACO", "asparcel", "Asterisk254", "Asylix", "Atircerile", "auraace", "Avento128bits", "AxlThunder", "Badlex727", "BarelyFunctional", "Basouification", "Baylee", "bbqsauz", "Bikee", "BillPzc", "Birdy", "Bizkit", "Blatan", "BlazinZzetti", "BlitzBlatt", "Bluelightdimming", "BMW0401_2", "bony", "bonzi77", "Boohead86", "BoostedBandCamp", "bowlercaptain", "brassmonkejr", "Brian_pso", "Brodyzera", "BrokenArthritis", "buckethead222", "Budmin", "BuffaloPrime", "Burningskull123", "Bushiidox", "BUxSteven", "CaitlynMarv", "canariabird", "Captsamerica", "Casusby", "CCNeverender", "Centari", "Cereth", "chainchump", "chanman", "ChaoticChao", "Chaoz163", "CharamelMou", "ChelseyxLynn", "chronoon", "Chucat", "Ckarl_Bobadine", "ClaireSV", "Classic", "Cleekoh", "Clumzy_Chao24", "Lexi", "Condus", "ConkerBandicoot", "Conklestothemax", "cookiepocalypse", "coolcolegamer", "CowTech", "CptPuff", "Cream147", "Cricketdx", "Crispian", "CriticalCyd", "Cryphon", "CrystalChaos", "ctagent", "CuukiesODeath", "CyanideKry", "cybersonicstarzx655", "dabbingjesus", "Dage4", "Daisukemara", "Danidesu", "Darkaria21", "Darkpr0", "Dartanian881", "Dawngaward", "DearmondzFTW", "Deku_sr", "DemotedStaff", "Desura", "Dfesfsfs", "DhrGR", "Diabuk", "DieserFMG", "DiGG3rZ", "dimes", "DirtyDillers", "disconnectoid", "DizzyPrime", "DjShovel", "Dnyceboy", "DolphinDasher", "donniesmithers", "Dorocco", "Draco655", "Drakodan", "drasamii", "Dreamtora", "Drewbiie", "DRGNDrags123", "drminus", "DrPhysic", "Drum", "Drunk_Loli", "DRX-Vector", "drywalleater69", "Dunham", "dusty_pecker", "Eat4thelolz", "EdwardBottle", "ElectricMiles", "EliteCarnage", "Emerauld", "Emerldd", "emerua", "enigma20", "EnPassant", "enu", "Epicfrogskater", "ethmar", "EverlastingSaint", "eXceL", "F_aux", "failgames100", "Failinator", "Faleroth", "FallenFury777", "fastlikesanic", "FierceClash", "FierceFrankie", "FiniteChaos", "Fivavoa", "FloppyDisk", "Flowleyd", "Fomako", "ford373", "foxdra", "Freefall", "FriskyHarambe", "Frokenok", "Frozer", "FuryRising", "g00gly0eyes", "Gailardia", "Gamercal", "Gc4ever4001", "Geno", "Gerp", "Ghoul02", "Ghoulston", "Godly79", "Gold", "Goldenboy", "Goldwolf11", "Gpro", "GrandStarYoshi", "Graphox", "GrayMagicGamma", "Greg", "Grievenomore", "grumblebundle", "Gupply", "Gurdill63", "GuyStreamsStuff", "Gvoltt", "Hawkrex", "Hazel", "Hephlex", "heytallman", "Homes1ck", "Hoopy", "Hoopyhoop1", "Hugasaurus", "Hughmanphist", "HypeMaster2020", "iambpburke", "icedog158", "Iden", "IDGeek121", "iexrrr", "Indextic", "iNeoRetro", "IrregularZero", "Ishmon", "IsleDelfino", "ITLAU", "IvanGS", "Ivegotdatfeel", "Izayoi83", "Jackwitherell", "Jailkat7", "jamception", "Jatenk", "JazzSpeedruns", "jbird", "JBuzzyBee", "Jel", "jellyfishswimmer", "JerKro", "JetSethRadio", "JHobz", "Joedor", "Joeey", "Joerunner", "jolteontrainer", "JonSuperEmerald", "Jordiebee", "Joshifire", "Jpaintrain", "jrk9", "jtnoble321", "Justalot123", "Justgoodpop", "jw13", "Keefyy", "Keeta", "Keewy", "kendallswan", "Keoneon", "Kheartz", "Kimmstaa", "Kimshi", "Kingshadowclock", "kinkycadence", "KinokoJules", "koinu93", "Kurayami", "Kyonexe", "Kytes", "Kyyrie", "Lambo", "LaughTrack", "Leetus", "Leeyuna", "Leif26", "Lergi", "Lewisb99", "Lightning55", "Linkkiro", "Liquid_Bosscelot", "LittleBigness", "Lonewo1f001", "Lordfartamor", "Lotuski24", "LuraxThunder", "Mar", "Markhest", "markusman64ds", "Marshy", "Marumiju", "Mastakirby", "Master-Kuruk", "MasterWaffled", "Matthewfupp", "Mattmurpz", "Mayakanai65", "mcshuggets", "Mecklemisuer", "Matoi", "MelonSpeedruns", "Meltrs", "Menstilo", "MessMyPants", "MetalGlennSolid", "MetroidMaster", "Midboss", "MidnightRambler", "mie_Dax", "Minamiyo", "Mitorequiem", "Mitsuray", "ModifiedMonkee", "Moeter", "Movellandrone", "Mr_Mango", "Mr.Tortellini", "MrDarkIce", "Mrgenericname", "Mrhappyismissing", "MrSanderss", "MrWoofies", "MyPairOfSocks", "MysticRebel", "Napuc", "Nathacsa", "nebbii", "Neptune", "Nerfned2000", "NeroBron", "NEVERDOORS", "Nick902", "Nickireda", "Nightmare47", "NiGHTOPiAN", "Niisoks", "Nimputs", "Nineball", "ninjahenrik", "NiNJaOwNeD", "Ninjembro", "NoThisIsStupider", "Okam", "OnVar", "OSC", "OutrageousJosh", "Oxtane", "Ozzi9816", "Parameter152", "Parkraft123", "Patafoin", "Paulie9990", "Pearstrike", "Pepeye", "Perdonium", "petrie911", "phantoms83", "Phat-Boss", "Phijkchu_tdk", "Pika_choo1", "Pikapals", "piner", "Pixelle", "PKMNtrainerGian", "Pokemanaphy", "Pokestuck33", "Prahaha", "price211066", "Primzi", "PrinceKaro", "Prinny", "PrismaticBlack", "Project", "Proto", "prouds1lver", "Psyknux", "PsyMar", "puchiedarcy", "Puddinghouse", "R3FR4G", "racksblue", "Ragecat", "Raikou", "RaiuPlays", "Rajaxx", "Randomguy55", "RandyBumgardener", "Rapture", "raqibmarvelous", "Ravaildisney", "Ravel", "Razzz", "redsky764", "relik9r", "Renegade522", "RetroRuns", "rezephos", "Rhapsody", "RingEnergy", "Ringrush", "RinKagamine1", "RjassoA", "rodyonce", "SaimeZX", "saintsfighter", "SalmonBuffalo", "Samitian", "SanicSpaceParty", "Savac", "Sayuri", "Sazabi0093", "SB737", "Scamper", "SCT", "Sekanor", "Selphos", "Senzura", "Seraphim", "Shadow2701", "ShadowCero", "ShadowFrost", "Shady_", "shamana", "Shanekilz", "shibakee", "ShiningFace", "SMB", "Silo_Simon", "SimLola661", "simpleton216", "SimplicityWalrus", "Sircharles", "skull_kid_64", "SlickEvan", "Slurm_king", "Snodeca", "Son1cgu1tar", "Sonicku", "Sonikku", "Sora", "SpaceBroJakob", "spades", "Spark3", "Sparkky", "spikevegeta", "spinful", "SpookySpeedruns", "squidtepig", "SqwareEcks", "SSBMstuff", "SSJPichu", "Stevewontleave", "StickFigureVector", "Stirliing", "stllr", "Stonie", "super_alice", "super_sanic123", "SuperDennyBoi", "SuperNerdMiles", "SuperSonic", "Supra", "surfingpikachu", "Suzuru", "Swaaggyy", "SwearImNotAWeeb", "Tallcat", "Talon2461", "Tandom_gamer1", "Tape1", "Techiyo", "TehCherokee", "Tekkie", "Tenacity", "The_Gods", "the0nlykyd", "TheAlphaDolphin", "TheBricktator", "Thecobra931", "TheJokernaut", "theJUICE", "TheKiwiTurtle", "themanual768", "thepuddingfighter", "TheRealMrJangle", "Therio", "TheStrangeMentlegen", "Theunexpected5", "thewaytodawnnn", "Thorn", "Tigerkyle1", "Tikal", "Tikwi", "TiltedStilts", "Timic", "TimpZ", "TJRedeemer", "togain", "tolvengyr", "Tommy", "Tommyspud", "TonesBalones", "toon_rito", "Torpy", "Touch", "ToxicFaker", "Traitor", "Treasure", "Tricolour", "Trix", "trunkynugget", "Ts4ever1201", "TwinkieSWF", "TwoferTuesday", "tyhill111", "Tylenol", "undeadforce22", "Unrealodin", "UnsupervisedFun", "Usiku", "Valioa", "Vark", "Venombyte", "ventiyordle", "Viblosh", "Video2gud", "Vilsol", "Vixuzen", "Vynneve", "WaddleDaisy", "WarpWhistle", "Weegeezv", "welldooder64", "welsar55", "Werey", "Whizzy_the_Elephant", "windssunrise1", "WindsSunrise1", "Wolfii", "Wolfluke", "woofpack", "Wooguy78", "wosige", "Wub", "x10power", "Xallesii", "Xelonious", "xGonzo", "xNose", "Xonos117", "Yes", "Yesjong", "YESR", "Yesthrough", "yoshifan", "yoshipartout", "Yoshis2ndcousin", "yuuutaaaapoonnn", "Zackoon49", "Zeldrak", "ZellnuuEon", "Zeph", "Zodiac92", "Zombiemaster", "Zyldara", "Zync" };
int chaoCNT = 569;


bool shadowBounce = false;
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
int goalRing = 0x0E;
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
boolean disableBS = false;
void* BSptr = (void*)0x0;
int boostTimer = 0;
bool boostMyAss = false;
int boost = 20;
bool replaceMadSpace = false;
bool setESG = false;
bool forceMissionNum = false;
int forcedMissionNum;


int bfPlayers[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter,Characters_Shadow, Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int hsPlayers[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow,Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int eggPlayers[] = {Characters_MechTails,Characters_MechTails|altcharacter, Characters_MechEggman,Characters_MechEggman | altcharacter};
int bioLizard[] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow };

int hunters[4] = { Characters_Knuckles,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter ,Characters_Rouge };
int speedsters[4] = { Characters_Sonic,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter ,Characters_Shadow, };
int mechs[4] = { Characters_MechTails,Characters_MechTails | altcharacter, Characters_MechEggman,Characters_MechEggman | altcharacter };


int* mechAction[2] = {mechs, speedsters};
int* mechHunt[2] = { mechs, hunters};
int* huntAction[2] = { hunters,speedsters };
int * huntMechAct[3] = { hunters,mechs,speedsters };

int vanillaM1Scores[30];
int vanillaM4Scores[30];
int vanillaM5Scores[30];

bool useLastFrameSpeed = false;
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
bool loadedFog = false;
bool rFog = false;
bool rFogColor = false;
bool addedTime = false;
int storeMission;
bool swapOnStage = true;


//int objsSwappedForChao[10] = {0x02,0x01,0x00};


const int shoutCNT = 564;
char* shouts[shoutCNT] = { "DRUMBASHER004", "MEKHIALTEY02" ,"DAGE4", "TRAITOR", "SERAPHIM", "DRAKODAN", "ETHMAR", "IDEN", "BROKENARTHRITIS", "TYLENOL", "DARKPR0", "IDGEEK121", "MODIFIEDMONKEE", "CRYPHON", "SHIBAKEE", "A_MOUSTACHE", "AURAACE", "TALON2461", "JW13", "EMERUA", "VIBLOSH", "COEMPATHY", "EPICFROGSKATER", "JETSETHRADIO", "EDWARDBOTTLE", "SILENTMOTORBOAT", "PINER", "AXLTHUNDER", "TOMMYEASY", "SORA", "METALGLENNSOLID", "NIMPUTS", "AAAA", "MR.TORTELLINI", "MASTER-KURUK", "NINEBALL", "PHANTOMS83", "ETHMAR", "DRYWALLEATER69", "MATTMURPZ", "IRREGULARZERO", "EMERLDD", "PRAHAHA", "BUFFALOPRIME", "SAVAC", "DRUNK_LOLI", "ASINISTERTACO", "SHININGFACE", "JAZZSPEEDRUNS", "CHAINCHUMP", "NICK902", "AGUEDOUF", "CLAIRESV", "PRIMZI", "LITTLEBIGNESS", "RAVEL", "DAISUKEMARA", "THEALPHADOLPHIN", "PRISMATICBLACK", "SPADES", "ZELLNUUEON", "FORD373", "MYSTICREBEL", "KINKYCADENCE", "MRDARKICE", "STLLR", "BLAZINZZETTI", "AREYTOREMEMBER", "SON1CGU1TAR", "JRK9", "BOOSTEDBANDCAMP", "FREEFALL", "PRIMZI", "KOINU93", "TEHCHEROKEE", "DRX-VECTOR", "THEWAYTODAWNNN", "INEORETRO", "JELLYFISHSWIMMER", "SPACEBROJAKOB", "JONSUPEREMERALD", "KINOKOJULES", "REZEPHOS", "NIMPUTS", "MASTER-KURUK", "THEJOKERNAUT", "BIKEE", "BLAZINZZETTI", "FORD373", "NOTHISISSTUPIDER", "DUSTY_PECKER", "ENU", "EMERAULD", "YOSHIFAN", "SUPERDENNYBOI", "SEKANOR", "SIMPLETON216", "OUTRAGEOUSJOSH", "TIKAL", "STIRLIING", "SHADOWFROST", "CRITICALCYD", "ACS13123", "COOKIEPOCALYPSE", "THE0NLYKYD", "CAPTSAMERICA", "GODLY79", "BADLEX727", "PHAT-BOSS", "ENPASSANT", "SWEARIMNOTAWEEB", "PUDDINGHOUSE", "JUSTALOT123", "DIESERFMG", "DIMES", "GRUMBLEBUNDLE", "TONESBALONES", "R3FR4G", "AKUREIKORINEKO", "AMBERCYPRIAN", "MRWOOFIES", "FALLENFURY777", "HUGASAURUS", "MCSHUGGETS", "EXCEL", "ONVAR", "SANICSPACEPARTY", "AIOPROJECT", "SHADOWCERO", "DEMOTEDSTAFF", "ASYLIX", "SNODECA", "AMBLOOPS", "PRISMATICBLACK", "SUPRA", "SHADY_", "OXTANE", "MENSTILO", "PKMNTRAINERGIAN", "DREWBIIE", "MASTAKIRBY", "BAYLEE", "GUYSTREAMSSTUFF", "JOEEY", "VENTIYORDLE", "LONEWO1F001", "1219NEKOGAMI", "WEEGEEZV", "CERETH", "DRAKODAN", "LAUGHTRACK", "TORPY", "PEPEYE", "ZEPH", "MASTAKIRBY", "MECKLEMISUER", "PHIJKCHU_TDK", "MIDBOSS", "HOMES1CK", "DIGG3RZ", "KHEARTZ", "FROKENOK", "CRYSTALCHAOS", "THEPUDDINGFIGHTER", "CAPTSAMERICA", "RENEGADE522", "GRANDSTARYOSHI", "DOLPHINDASHER", "DFESFSFS", "GAMERCAL", "SAMITIAN", "FURYRISING", "CRISPIAN", "LINKKIRO", "THEWAYTODAWNNN", "YUUUTAAAAPOONNN", "NIISOKS", "_GIMMICK", "CAITLYNMARV", "AHOYKMS", "CONKLESTOTHEMAX", "DRMINUS", "SANICSPACEPARTY", "KOINU93", "UNDEADFORCE22", "NERFNED2000", "DUSTY_PECKER", "FURYRISING", "ZYLDARA", "XONOS117", "MRSANDERSS", "JOEDOR", "CHRONOON", "SPARKKY", "LEIF26", "HAZEL", "VIXUZEN", "JORDIEBEE", "IVEGOTDATFEEL", "JERKRO", "TS4EVER1201", "BAYLEE", "WEREY", "CHANMAN", "NEVERDOORS", "BUDMIN", "TAPE1", "MIDNIGHTRAMBLER", "LEWISB99", "AIR_IQ", "MOETER", "DRASAMII", "HUGASAURUS", "MARUMIJU", "RAPTURE", "FLOWLEYD", "PROJECT", "JOERUNNER", "XGONZO", "FALEROTH", "BRIAN_PSO", "CLEEKOH", "TOGAIN", "44MOTH", "RETRORUNS", "MELONSPEEDRUNS", "CUUKIESODEATH", "DJSHOVEL", "KENDALLSWAN", "GHOUL02", "MASTERWAFFLED", "WELSAR55", "PROTO", "CONKERBANDICOOT", "ELECTRICMILES", "TYHILL111", "DABBINGJESUS", "TRIX", "CLAIRESV", "BRODYZERA", "RJASSOA", "NIGHTMARE47", "WELLDOODER64", "GOLDWOLF11", "NEBBII", "THEREALMRJANGLE", "KEONEON", "TWOFERTUESDAY", "ARGICK", "TOLVENGYR", "CANARIABIRD", "AQUOVA", "BIRDY", "GHOULSTON", "THESTRANGEMENTLEGEN", "ALTAIRAN", "DEARMONDZFTW", "IZAYOI83", "TOUCH", "OUTRAGEOUSJOSH", "FIVAVOA", "MAR", "TRICOLOUR", "ELITECARNAGE", "CLUMZY_CHAO24", "KYTES", "CLUMZY_CHAO24", "NEBBII", "YOSHIS2NDCOUSIN", "F_AUX", "SUZURU", "ISHMON", "STONIE", "RAZZZ", "DREAMTORA", "RINGENERGY", "DRPHYSIC", "SCT", "LIQUID_BOSSCELOT", "BARELYFUNCTIONAL", "KINGSHADOWCLOCK", "2D", "PIKAPALS", "SHAMANA", "BURNINGSKULL123", "VYNNEVE", "WADDLEDAISY", "AERO_TRIGGER", "WOSIGE", "DIZZYPRIME", "PRICE211066", "TILTEDSTILTS", "MITSURAY", "WOOGUY78", "THORN", "OKAM", "KURAYAMI", "SLICKEVAN", "SONICKU", "POKESTUCK33", "CONDUS", "THEBRICKTATOR", "JAMCEPTION", "RAGECAT", "MRHAPPYISMISSING", "IAMBPBURKE", "DHRGR", "ASTERISK254", "RAIUPLAYS", "MIE_DAX", "RANDYBUMGARDENER", "PIKA_CHOO1", "DHRGR", "RODYONCE", "SUPERSONIC", "SURFINGPIKACHU", "AVENTO128BITS", "SIRCHARLES", "TECHIYO", "GRAYMAGICGAMMA", "THE_GODS", "MELANCHOLYMATOI", "BOWLERCAPTAIN", "RAJAXX", "GPRO", "CTAGENT", "BLATAN", "DRGNDRAGS123", "BIZKIT", "TIMPZ", "CCNEVERENDER", "DARTANIAN881", "CLASSIC", "INDEXTIC", "WARPWHISTLE", "AMERICANCHOIRBOY", "RINGRUSH", "MESSMYPANTS", "SAYURI", "GOLD", "XALLESII", "KEEFYY", "YES", "BOOHEAD86", "MAR", "DAWNGAWARD", "LEEYUNA", "LEETUS", "BRASSMONKEJR", "APHEXARCADE", "NEROBRON", "TOXICFAKER", "FRISKYHARAMBE", "SCAMPER", "WOLFII", "PROUDS1LVER", "JTNOBLE321", "RHAPSODY", "THEMANUAL768", "MINAMIYO", "TJREDEEMER", "SILO_SIMON", "THECOBRA931", "BUSHIIDOX", "FOXDRA", "DRACO655", "JOSHIFIRE", "STICKFIGUREVECTOR", "CHAOZ163", "FINITECHAOS", "ASPARCEL", "METROIDMASTER", "FLOPPYDISK", "ARMORYSONS", "VALIOA", "PATAFOIN", "FIERCECLASH", "LERGI", "RAQIBMARVELOUS", "TENACITY", "BONZI77", "0RBIS", "PAULIE9990", "GURDILL63", "EVERLASTINGSAINT", "ARUKI", "VARK", "BMW0401_2", "LURAXTHUNDER", "KYYRIE", "SUPERNERDMILES", "ALLEGRO", "LOTUSKI24", "MAYAKANAI65", "ABSENTSR", "YOSHIPARTOUT", "RANDOMGUY55", "LIGHTNING55", "DEKU_SR", "HYPEMASTER2020", "NICKIREDA", "NINJEMBRO", "NEPTUNE", "REDSKY764", "TIKWI", "PARAMETER152", "NINJAOWNED", "SPOOKYSPEEDRUNS", "DIRTYDILLERS", "THERIO", "KEETA", "OSC", "FOMAKO", "DISCONNECTOID", "FASTLIKESANIC", "HOOPYHOOP1", "GUPPLY", "SSJPICHU", "JEL", "FROZER", "CKARL_BOBADINE", "CPTPUFF", "SONIKKU", "MR_MANGO", "DNYCEBOY", "BILLPZC", "JACKWITHERELL", "TALLCAT", "COOLCOLEGAMER", "SAZABI0093", "CREAM147", "ICEDOG158", "EAT4THELOLZ", "SKULL_KID_64", "RAVAILDISNEY", "G00GLY0EYES", "ATIRCERILE", "YESTHROUGH", "SLURM_KING", "TREASURE", "NIGHTMARE47", "DIABUK", "BUCKETHEAD222", "RINGENERGY", "SAINTSFIGHTER", "CENTARI", "DANIDESU", "MAR", "SQUIDTEPIG", "NATHACSA", "WOOFPACK", "MOVELLANDRONE", "TEKKIE", "HUGHMANPHIST", "SHANEKILZ", "MELANCHOLYMATOI", "ZACKOON49", "THEUNEXPECTED5", "ISLEDELFINO", "AGGRESSIVELY MEDIUM", "SENZURA", "TANDOM_GAMER1", "BASOUIFICATION", "CHARAMELMOU", "OZZI9816", "AFROGAMER2660", "STLLR", "COWTECH", "VILSOL", "KIMSHI", "TOMMYSPUD", "TOON_RITO", "HEYTALLMAN", "JBIRD", "TIMIC", "ENIGMA20", "GC4EVER4001", "SIMPLICITYWALRUS", "KIMMSTAA", "GVOLTT", "WOLFLUKE", "MARSHY", "JUSTGOODPOP", "A_BOWL_OF_CEREAL", "JOLTEONTRAINER", "_HOUSTON", "MRGENERICNAME", "SALMONBUFFALO", "VENOMBYTE", "NAPUC", "XNOSE", "HOOPY", "NINJAHENRIK", "JAILKAT7", "MARKUSMAN64DS", "JATENK", "MITOREQUIEM", "USIKU", "GRIEVENOMORE", "HAWKREX", "GREG", "BUXSTEVEN", "PRINNY", "NIGHTOPIAN", "DOROCCO", "IVANGS", "VIDEO2GUD", "WINDSSUNRISE1", "XELONIOUS", "SPARK3", "PSYMAR", "STEVEWONTLEAVE", "TWINKIESWF", "THEKIWITURTLE", "ZODIAC92", "JBUZZYBEE", "KYONEXE", "GAILARDIA", "SIMLOLA661", "DUNHAM", "UNSUPERVISEDFUN", "SB737", "SSBMSTUFF", "SUPER_SANIC123", "CHUCAT", "PIXELLE", "THEJUICE", "BLUELIGHTDIMMING", "CASUSBY", "ARMAGEDDUN", "JPAINTRAIN", "GRAPHOX", "POKEMANAPHY", "RACKSBLUE", "DARKARIA21", "RELIK9R", "CYBERSONICSTARZX655", "JHOBZ", "ZOMBIEMASTER", "SWAAGGYY", "ZYNC", "PRINCEKARO", "PERDONIUM", "MARKHEST", "GENO", "FIERCEFRANKIE", "ANDZURA", "ITLAU", "TRUNKYNUGGET", "LAMBO", "PUCHIEDARCY", "X10POWER", "MATTHEWFUPP", "PARKRAFT123", "GOLDENBOY", "ZELDRAK", "CHELSEYXLYNN", "TIGERKYLE1", "FAILGAMES100", "BONY", "BBQSAUZ", "SPIKEVEGETA", "CRICKETDX", "LORDFARTAMOR" };


int charPool[13] = { Characters_Sonic,Characters_Shadow,Characters_Sonic | altcharacter,Characters_Shadow | altcharacter,
					Characters_Knuckles,Characters_Rouge,Characters_Knuckles | altcharacter,Characters_Rouge | altcharacter,
					Characters_MechTails,Characters_MechEggman,Characters_MechTails|altcharacter, Characters_MechEggman|altcharacter,
					Characters_SuperSonic};
bool inPool[13] = { true,true,true,true,
					true,true,true,true,
					true,true,true,true,
					false};

int useThisPool[13];
int numCharsinPool = 1;

int updateFogCount = 2;
int currentFogCount = 0;
char retName[7];
bool OHKO = false;


int CheckBackRing(int playerNum)
{
	if ((CurrentLevel == LevelIDs_CannonsCoreE || CurrentLevel == LevelIDs_CannonsCoreT) && (MissionNum == 1 || MissionNum == 2))
	{
		int storeRing = RingCount[0];
		RingCount[0] = 0;
		AwardWin(playerNum);
		RingCount[0] = storeRing;
		return 0;
	}
	return 1;
}

void* const sub_43F330 = (void*)0x43F330;
__declspec(naked) void BackRingHook()
{
	__asm
	{
		push ebx
		call CheckBackRing
		pop ebx
		test eax, eax
		jz backringreturn
		jmp sub_43F330
		backringreturn :
		retn
	}
}

boolean credited(ModelCredits m, vector<ModelCredits> v) {
	for (auto md : v) {
		if (m.name.compare(md.name) == 0) return true;
	}
	if (m.name.compare("nothing") == 0) return true;
	return false;
}



char* randomChaoName(int a1, char *a2) {
	string name(chaoN[rand() % chaoCNT]);
	int len = 7;
	if (name.length() < 7) len = name.length();
	for (int i = 0; i < len; i++) {
		retName[i] = encodeLetter(name[i]);
	}
	*a2 = (char)len;
	return retName;
}

void randomPerStage() {
	int r;
	for (int i = 0; i < 45; i++) {
		if (stageToChar(i) != -1) {
			/*if (!noVanillaChars) {
				if (isMech(stageToChar(i))) newCharPerStage[i] = mechAction[rand() % 2][rand() % 4];
				else if (isHunt(stageToChar(i))) newCharPerStage[i] = huntAction[rand() % 2][rand() % 4];
				else newCharPerStage[i] = mechHunt[rand() % 2][rand() % 4];
			}
			else {
				newCharPerStage[i] = huntMechAct[rand() % 3][rand() % 4];
			}*/

			r = useThisPool[rand() % numCharsinPool];
			if (!noVanillaChars) {
				while (sameType(stageToChar(i), r)) {
					r = useThisPool[rand() % numCharsinPool];
				}
			}
			int roll = rand()%2;
			if (roll == 0 && !(r&altcharacter) && nocosts != 1 ) r |= altcostume;
			newCharPerStage[i] = r;
			
		}
	}
	//newCharPerStage[43] = Characters_Knuckles;
	//charPerStage(newCharPerStage, savePath);
}


void setUpCredits() {
	CreditEntry newCredits[Credits_Length];
	vector<CreditEntry> creditVector;
	int count = 0;
	/*for (int i = 0; i < Credits_Length; i++) {
		if (Credits[i].type == 0) newCredits[count++] = Credits[i];
	}
	for (int i = 0; i < Credits_Length; i++) {
		if(Credits[i].type !=0) newCredits[count++] = Credits[i];

	}
	for (int i = 0; i < Credits_Length; i++) {
		Credits[i] = newCredits[i];
	}*/

	for (int i = 0; i < Credits_Length-1; i++) {
		if (Credits[i].type == 0 && (Credits[i+1].type == 1 || Credits[i + 1].type == 2)) creditVector.insert(creditVector.begin(),Credits[i]);
		if (Credits[i].type == 0 && Credits[i+1].type == 0 && (Credits[i + 2].type == 1 || Credits[i + 2].type == 2)) creditVector.insert(creditVector.begin(), Credits[i]);
		else creditVector.push_back(Credits[i]);
	}
	creditVector.push_back(Credits[Credits_Length-1]);
	for (int i = 0; i < Credits_Length; i++) {
		Credits[i] = creditVector[i];
	}


	const int teamSize = 4;
	const int varT = 5;
	const int praT = 1;
	const int tomT = 10;
	const int izzyT = 4;
	char* tommyTitles[tomT] = { "Q&A TESTER", "ONE DAY I'LL BOP CHAINCHUMPER'S SH M4", "LAVA FLOORS HATER", "JR. EMERUA", "BINGO BOARDER", "IGT WAS A MISTAKE",
		"SERAPH1BLESS", "MAYAYA", "SUNGLASSES CLIPPER", "YOU'RE BREATHTAKING!"};


	char* onvarTitles[varT] = { "SCIENCE GUY","BIT-FLIPPER","ONVARPAUSE","ONE DAY I'LL BOP CHAINCHUMPER'S SH M4","SUBSCRIBE TO TWITCH.TV / IDGEEK121"};
	
	
	char* boostedTitles[izzyT] = {"LEVEL DESIGN","STAGE DESIGN" ,"OBJECT MASTER" ,"SET00XX.BIN" };
	
	
	char* praTitles[praT] = { "THANKS FOR PLAYING,"};
	
	
	char** titles[teamSize] = { praTitles,boostedTitles,onvarTitles,tommyTitles };
	const int noTits[teamSize] = { praT,izzyT,varT,tomT };
	char* names[teamSize] = {"Prahaha","BoostedBandCamp","OnVar","TommyeAsY"};

	int start = 1;
	int spacing = 4;


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

	start += 40;
	Credits[start].type = 2;
	Credits[start].text = "Random Shout outs";
	start++;
	Credits[start].type = 1;
	Credits[start].text = "MAINMEMORY";


	int cnt = rand() % 9 + 1;
	for (int i = 0; i < cnt; i++) {
		start++;
		Credits[start].type = 1;
		Credits[start].text = shouts[rand()%shoutCNT];
	}


	/*start += spacing;
	Credits[start].type = 1;
	Credits[start].text = "DISCORD.GG/";
	start++;
	Credits[start].type = 2;
	Credits[start].text = "C24scsy";*/

	start += spacing;
	Credits[start].type = 1;
	Credits[start].text = "PATREON";
	start++;
	Credits[start].type = 2;
	Credits[start].text = "PraModTeam";


	start += spacing;
	Credits[start].type = 1;
	Credits[start].text = "MODELS";
	//for (auto md : modelCreds) {
	for(int i =0; i <modelCreds.size();i++){
		PrintDebug(modelCreds[i].name.c_str());
		PrintDebug(modelCreds[i].creator.c_str());
		start+= 2;
		Credits[start].type = 1;
		Credits[start].red = 69;
		Credits[start].green = 69;
		Credits[start].blue = 69;
		Credits[start].text = modelCreds[i].creator.c_str();
		start++;
		Credits[start].type = 1;
		Credits[start].text = modelCreds[i].name.c_str();
	}


}



const void* jmp_locAwardWin = (const void*)0x43E6ed;
__declspec(naked) void exitStage() {
	__asm {
		push EBX
		xor EDX, EDX
		push EBP
		push EDI
		call setUpCredits
		jmp jmp_locAwardWin

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


void setUpScores() {
	int factor = 2;
	for (int i = 0; i < 30; i++) {
		//PrintDebug("Before");
		factor = 2;
		//PrintDebug(std::to_string(Mission1Scores[i].ARank).c_str());
		//PrintDebug(std::to_string(vanillaM1Scores[i]).c_str());
		int character = stageToChar(Mission1Scores[i].Level);
		int swapped = defaultcharacters[character];
		if (swapOnStage) swapped = newCharPerStage[i];
		if (Mission1Scores[i].Level == LevelIDs_CosmicWall) factor = 4;
		if (!sameType(character, swapped) || !noVanillaChars) {
			Mission1Scores[i].ARank = vanillaM1Scores[i] / factor;
			Mission1Scores[i].BRank = Mission1Scores[i].ARank - 10;
			Mission1Scores[i].CRank = Mission1Scores[i].BRank - 10;
			Mission1Scores[i].DRank = Mission1Scores[i].CRank - 10;

			Mission4Scores[i].ARank = vanillaM4Scores[i] / factor;
			Mission4Scores[i].BRank = Mission4Scores[i].ARank - 10;
			Mission4Scores[i].CRank = Mission4Scores[i].BRank - 10;
			Mission4Scores[i].DRank = Mission4Scores[i].CRank - 10;

		}
		else {
			Mission1Scores[i].ARank = vanillaM1Scores[i];
			Mission1Scores[i].BRank = Mission1Scores[i].ARank - 10;
			Mission1Scores[i].CRank = Mission1Scores[i].BRank - 10;
			Mission1Scores[i].DRank = Mission1Scores[i].CRank - 10;

			Mission4Scores[i].ARank = vanillaM4Scores[i];
			Mission4Scores[i].BRank = Mission4Scores[i].ARank - 10;
			Mission4Scores[i].CRank = Mission4Scores[i].BRank - 10;
			Mission4Scores[i].DRank = Mission4Scores[i].CRank - 10;

		}
		//PrintDebug("After");
		//PrintDebug(std::to_string(Mission1Scores[i].ARank).c_str());
	}



}


void randomizeCurrentM2() {
	if (MissionNum != 1) return;
	int r;
	int idx;
	int range;
	int i = CurrentLevel;
	if (i == LevelIDs_CannonsCoreE || i == LevelIDs_CannonsCoreT || i == LevelIDs_CannonsCoreK || i == LevelIDs_CannonsCoreR) return;
		r = rand() % 2;
		m2Types[i] = r;
		if (r == 0) {
			m2Reqs[i] = rand() % 126 + 25;

		}
		else if (r == 1) {
			for (int j = 0; j < Mission1Scores_Length; j++) {
				if (Mission1Scores[j].Level == i) {
					range = Mission1Scores[j].BRank - Mission1Scores[j].DRank;
					if(i == LevelIDs_LostColony || i == LevelIDs_EternalEngine || i == LevelIDs_WeaponsBed)range = Mission1Scores[j].CRank - Mission1Scores[j].DRank;

					m2Reqs[i] = rand() % range + Mission1Scores[j].DRank;
					m2Reqs[i] *= 100;
				}
			}
			if (isHuntingStagei(i)) {
				m2Reqs[i] /= 3;
			}
		}
		//m2Req = m2Reqs[i];
	
	m2Types[LevelIDs_CannonsCoreE] = m2Types[LevelIDs_CannonsCoreS];
	m2Reqs[LevelIDs_CannonsCoreE] = m2Reqs[LevelIDs_CannonsCoreS];
	m2Types[LevelIDs_CannonsCoreT] = m2Types[LevelIDs_CannonsCoreS];
	m2Reqs[LevelIDs_CannonsCoreT] = m2Reqs[LevelIDs_CannonsCoreS];
	m2Types[LevelIDs_CannonsCoreR] = m2Types[LevelIDs_CannonsCoreS];
	m2Reqs[LevelIDs_CannonsCoreR] = m2Reqs[LevelIDs_CannonsCoreS];
	m2Types[LevelIDs_CannonsCoreK] = m2Types[LevelIDs_CannonsCoreS];
	m2Reqs[LevelIDs_CannonsCoreK] = m2Reqs[LevelIDs_CannonsCoreS];
}



void Randomize(int seeda) {


	srand(seeda);

	if(!dischaokarate) for (int i = 0; i < ChaoKarateOpponents_Length; i++) ChaoKarateOpponentsR[i] = randomKarateChao(40, ChaoKarateOpponentsR[i]);
	if(!dischaorace) for (int i = 1; i < ChaoRaceOpponents_Length;i++) ChaoRaceOpponents[i] = randomRaceChao(8, ChaoRaceOpponents[i]);



	bigFootSwap = bfPlayers[rand() % 8];
	hotShotSwap = hsPlayers[rand() % 8];
	flyDogSwap = hsPlayers[rand() % 8];
	KBBSwap = hsPlayers[rand() % 4+4];
	EGESwap = eggPlayers[rand() % 4];
	biolizSwap = bioLizard[rand() % 4];
	EGSSwap = bioLizard[rand() % 4];
	CCSonicSwap = bioLizard[rand() % 4];

	int r;
	RmissionNum = rand() % 5 + 0;
	if (cADX) {
		for (int j = 0; j < 55; j++) {
			nonloopingMap[nonlooping[j]] = rand() % 55;
		}
		for (int j = 0; j < 102; j++) {
			loopingMap[looping[j]] = rand() % 102;
		}
	}
	if (cVoices) {
		for (int j = 0; j < 2727; j++) {
			storeVL[j] = randVoiceC(j, vlRandoType);
		}
	}


	for (int i = 0; i < Characters_Amy; i++) {

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


		if (!noVanillaChars) {
			while(sameType(i,r)){ 
				//PrintDebug("Char1");
				//PrintDebug(std::to_string(i).c_str());
				//PrintDebug("Char2");
				//PrintDebug(std::to_string(r).c_str());

				//PrintDebug(std::to_string(sameType(i, r)).c_str());
				r = useThisPool[rand() % numCharsinPool];
			}
		}

		/*if (i == Characters_Rouge) {
			if (noVanillaChars) {
				int canBePicked[2] = { Characters_Sonic, Characters_Shadow };
				r = canBePicked[rand() % 2];
				if (alt == 1) r |= altcharacter;
			}
			else {
				int canBePicked[4] = { Characters_Sonic, Characters_Shadow,Characters_Knuckles,Characters_Rouge };
				r = canBePicked[rand() % 4];
				if (alt == 1) r |= altcharacter;
			}
		}*/
		
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
		int roll = rand() % 2;
		if (roll == 0 && !(r&altcharacter) && nocosts != 1) r |= altcostume;

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

	for (int j = 0; j < cutoff; j++) {
		for (int i = 0; i < 4; i++) {
			if (randoMeDaddy[j].cutscene_events[i] != -1) validCutscenes.push_back(randoMeDaddy[j].cutscene_events[i]);
		}
	}


	//LogThis("PreShuffle.txt");
	if (!disRL) {
		for (int j = 0; j < cutoff; j++) {

				for (int i = 0; i < 4; i++) {
					if (randoMeDaddy[j].cutscene_events[i] != -1) validCutscenes.push_back(randoMeDaddy[j].cutscene_events[i]);
				}
	


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

	if (replaceMadSpace) {
		for (int j = 0; j < cutoff; j++) {
			if (randoMeDaddy[j].level_id == LevelIDs_MadSpace && randoMeDaddy[j].entry_type == 1) {
				randoMeDaddy[j].level_id = LevelIDs_GreenHill;
				randoMeDaddy[j].character_id = Characters_Sonic;
			}
		}
	}
	//randoMeDaddy[0] = randoMeDaddy[87];

		if (sehar) {
			for (int i = 0; i < Characters_Amy; i++) {
				if(storedPrefs[i] != 69) {
				defaultalts[i] = 0;
				defaultcosts[i] = 0;
				if(setCharTime == 1) defaultcharacters[i] = storedPrefs[i];
				else if (setCharTime == 2) defaultcharacters[i] = storedPrefs[defaultcharacters[i]];
				}
			}
			swapOnStage = false;
		}
	

	//int repper[8] = {0,1,2,3,4,5,6};
	//for (int i = 0; i < StageSelectLevels_Length; i++) 
	//	StageSelectLevels[i].Character = defaultcharacters[repper[StageSelectLevels[i].Character]];

		if (seed == 69) {
			for (int i = 0; i < Characters_Amy; i++) {
				defaultcharacters[i] = Characters_Rouge | altcostume;
			}
		}


		if (false) {
			if (true) stageV(defaultcharacters, savePath);
			else resetStageV();

		}
			if (swapOnStage) randomPerStage();
		

		int c;
		unsigned int timer = 15 * 60;
		if (swapOnStage) c = newCharPerStage[10] & charmask;
		else c = defaultcharacters[0] & charmask;
		if (isMech(c)) timer = 30 * 60;
		if (isHunt(c)) timer = 20 * 60;
		WriteData<int>(&MHTimer1, timer);
		WriteData<int>(&MHTimer2, timer);
		WriteData<int>(&MHTimer3, timer);
		WriteData<int>(&MHTimer4, timer);
		WriteData<int>(&MHTimerMinus660, timer-660);

		for (int j = 0; j < cutoff; j++) {
			for (int i = 0; i < ignoreStages.size(); i++) {
				if (randoMeDaddy[j].level_id == ignoreStages[i]) {
					randoMeDaddy[j].character_id = 0;
					randoMeDaddy[j].cutscene_events[0] = validCutscenes[rand()%validCutscenes.size()];
					randoMeDaddy[j].cutscene_events[1] = -1;
					randoMeDaddy[j].cutscene_events[2] = -1;
					randoMeDaddy[j].cutscene_events[3] = -1;
					randoMeDaddy[j].entry_type = 0;
					randoMeDaddy[j].level_id = 0;
				}
			}
		}

		for (int i = 0; i < 44; i++) {

			if (isHuntingStagei(i)) {
				for (int j = 0; j < 30; j++) {
					if (m4timers[j].level == i) m4timers[j].min += 1;
				}
			}
			if (isMech(defaultcharacters[stageToChar(i)])) {
				for (int j = 0; j < 30; j++) {
					if (m4timers[j].level == i) m4timers[j].min += 1;
				}
				if (i == LevelIDs_SecurityHall) SHTimer += 2;
			}
		}
		for (int j = 0; j < 30; j++) {
			m4timers[j].min += 1;
		}

		setUpScores();

		if(story.compare("Hero") == 0)
			createSplits(0,45, "Hero Story",showN);
		if (story.compare("Dark") == 0)
			createSplits(46, 89, "Dark Story",showN);
		if (story.compare("All") == 0)
			createSplits(0, 98, "All Stories", showN);
		if (story.compare("173") == 0)
			createSplits(0, 98, "173 Emblems", showN);

		/*
		//Sonic V Shadow 1
		charBosses[0] = speedsters[2*(rand() % 2)];
		charBossPlayer[0] = huntMechAct[rand() % 3][2 * (rand() % 2)];
		

		//Sonic V Shadow 2
		charBosses[1] = huntMechAct[rand() % 3][2 * (rand() % 2)];
		charBossPlayer[1] = huntMechAct[rand() % 3][2 * (rand() % 2)];
		
		//Tails v eggman 1
		charBosses[2] = mechs[2 * (rand() % 2)];
		charBossPlayer[2] = huntMechAct[rand() % 3][2 * (rand() % 2)];
		
		//tails v eggman 2
		charBosses[3] = mechs[2 * (rand() % 2)];
		charBossPlayer[3] = huntMechAct[rand() % 3][2 * (rand() % 2)];


		//knux v rouge
		charBosses[4] = hunters[2 * (rand() % 2)];
		charBossPlayer[4] = huntMechAct[rand() % 3][2 * (rand() % 2)];
		*/




}


static inline BOOL WriteJNZ(void *writeaddress, void *funcaddress)
{
	uint8_t data[6];
	data[0] = 0x0F;
	data[1] = 0x84;
	*(int32_t*)(data + 2) = (uint32_t)funcaddress - ((uint32_t)writeaddress + 6);
	return WriteData(writeaddress, data);
}



int RandomMissionText_i()
{
	int result = rand();
	switch (CurrentLevel)
	{
	case LevelIDs_PyramidRace:
	case LevelIDs_PoolQuest:
	case LevelIDs_PlanetQuest:
	case LevelIDs_DeckRace:
	case LevelIDs_DowntownRace:
	case LevelIDs_GrindRace:
		return result % 35;
	default:
		return result % 250;
	}
}

const void* loc_496570 = (const void*)0x496570;
__declspec(naked) void RandomMissionText()
{
	__asm
	{
		call RandomMissionText_i
		mov ecx, eax
		jmp loc_496570
	}
}


void Omochao_RandomMessage(ObjectMaster *obj)
{
	obj->Data1.Entity->Scale.x = (float)(rand() % StageMessageCount); // select a random hint from the level's hint message file
	obj->MainSub = sub_6BE2E0;
	sub_6BE2E0(obj);
}

int LoadMessageLists_All(const char *filename)
{
	if (!StageMessageList && !SysMessageList)
	{
		if (!strcmp("mh0066", filename) || !strcmp("mh0068", filename)) // keep the FinalHazard and tutorial message files
			StageMessageList = LoadMessageFile(filename, &StageMessageCount);
		else
			StageMessageList = LoadMessageFile("mhall", &StageMessageCount);
		SysMessageList = LoadMessageFile("mhsys", &SysMessageCount);
		if (StageMessageList && SysMessageList)
			return SysMessageCount + StageMessageCount;
		ReleaseMessageLists();
	}
	return -1;
}

__declspec(naked) void LoadMessageLists_r()
{
	__asm
	{
		push eax
		call LoadMessageLists_All
		add esp, 4
		retn
	}
}


static char* __cdecl randMusic(char* song) {
	srand(rand() *time(NULL));
	PrintDebug(song);
	//cADX = true;
	//t1_shadow
	//e210_sn1
	//t1_sonic
	if (strstr(song, "t1_shado") != NULL || strstr(song, "t1_sonic") != NULL || strstr(song, "e210_sn1") != NULL) {
		PrintDebug("In Credits");
		//return looping[rand() % 102];
	}

	else {
		for (int i = 0; i < 55; i++) {
			if (strcmp(song, nonlooping[i]) == 0) {
				if (!cADX)	return nonlooping[rand() % 55];
				else	return nonlooping[nonloopingMap[song]];
			}
		}
	}
	if (chaoMusic) {
		char* temp = looping[rand() % 102];
		while (strstr(temp,"CHAO") != NULL || strstr(temp, "chao") != NULL) {
		temp = looping[rand() % 102];
		}
		return temp;
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

__declspec(naked) void PlayMusicOnce_r()
{
	__asm
	{
		push edi
		call randMusic
		add esp, 4
		mov edi, eax
		jmp PlayMusicOncePtr
	}
}




void giveOmochaoLine() {
	int temp = sizeOfAfs;
	int r = rand() % temp;
	if (voiceLineLang == 1)  temp = 2727;
	while(!isOmochaoLine(r)) r = rand() % temp;
	PlayVoice(0, r);
}


const void* sub_443560 = (const void*)0x443560;
const void* loc_443487 = (const void*)0x443487;
__declspec(naked) void PlayJingle_r()
{
	__asm
	{
		push ebx
		call randMusic
		add esp, 4
		mov ebx, eax
		call sub_443560
		jmp loc_443487
	}
}

int pickFromRange() {
	int r = rand() % sizeOfAfs;
	if (voiceLineLang == 1) return rand()%2727;
	return r;
}


static int __cdecl randVoice(int a) {
	srand(rand() *time(NULL));


	int r = pickFromRange();



	if (cVoices) {
		r = storeVL[a];
		//r = r;				TODO
	}
	else if (vlRandoType == 1) {
		while (isOmochaoLine(r)) { r = pickFromRange(); }
		//return r;
	}
	else if (vlRandoType == 2) r = returnSameCharLine(a);
	else if (vlRandoType == 3) r = returnMainCharLine(a);
	else if (vlRandoType == 4) r = vlBasedOnTime(a,0.2);
	else if (vlRandoType == 5) r = returnSameCharALLGAMELine(a);
	else if (vlRandoType == 72 || vlRandoType == 73) {
		while (lineReferencesMaria(r) || (vlRandoType == 73 && isOmochaoLine(r))) { r = pickFromRange(); }
	}
	if ((subNumber == 2) || (subNumber == 1 && GameState == 0)) {
		int temp = 0;
		

		if (game != 1 && voiceLineLang == 0) {
			if (game == 0) temp = 2727;
			else if (game == 2) temp = 2727 + 2049;
		}

		displayMe = displaySub(r+temp, 3, tag);
	}
	PrintInt(r);
	if (game != 1 && GameMode != 8 && CurrentMenu != Menus_StorySelect && !isOmochaoLine(a)) voiceLineLang = rand() % 2;


	if (playFromWav) {
		string number = "";
		if (r < 10) number += "0";
		if (r < 100) number += "0";
		if (r < 1000) number += "0";
		number += std::to_string(r);
		string fn = savePath + "\\Wav\\" + number + ".wav";
		std::wstring fnw(fn.begin(), fn.end());
		LPCWSTR fnl = fnw.c_str();
		PlaySound(fnl, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
		return -1;
	}
	return r;//4734 both or 2727 SA2 Only 9591 all
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


static int __cdecl randWav(int a) {
	srand(rand() * time(NULL));


	int r = rand()%totalWavFiles;



	if (cVoices) {
		r = storeVL[a];
		//r = r;				TODO
	}
	else if (vlRandoType == 1) {
		while (isOmochaoLine(r)) { r = rand() % totalWavFiles; }
		//return r;
	}
	else if (vlRandoType == 2) r = returnSameCharLine(a);
	else if (vlRandoType == 3) r = returnMainCharLine(a);
	else if (vlRandoType == 4) r = vlBasedOnTime(a, 0.2);
	else if (vlRandoType == 5) r = returnSameCharALLGAMELine(a);
	else if (vlRandoType == 72 || vlRandoType == 73) {
		while (lineReferencesMaria(r) || (vlRandoType == 73 && isOmochaoLine(r))) { r = pickFromRange(); }
	}
	if ((subNumber == 2) || (subNumber == 1 && GameState == 0)) {
		int temp = 0;


		if (game != 1 && voiceLineLang == 0) {
			if (game == 0) temp = 2727;
			else if (game == 2) temp = 2727 + 2049;
		}

		if(r <9592) displayMe = displaySub(r + temp, 3, tag);
	}
	PrintInt(r);
	string number = "";
	if (r < 10) number += "0";
	if (r < 100) number += "0";
	if (r < 1000) number += "0";
	number += std::to_string(r);
	string fn = savePath + "\\Wav\\" + number + ".wav";
	std::wstring fnw(fn.begin(), fn.end());
	LPCWSTR fnl = fnw.c_str();
	PlaySound(fnl, GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
	return -1;

}


static const int loc_jmpbackw = 0x44313D;
__declspec(naked) void PlayWav_r() {
	__asm
	{
		mov eax, [esp + 4]
		push eax
		call randWav
		add esp, 4
		mov[esp + 0x04], eax
		jmp loc_jmpbackw
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
	int vanillaChar = CurrentCharacter;
	randomizeCurrentM2();
	m2Req = m2Reqs[CurrentLevel];
	
	swapChao = false;
	if(randomMissions || forceMissionNum) storeMission = MissionNum;
	if (setESG) ESG = 1;
	/*WriteData<1>((void*)0x4ecb04, 0x90);
	WriteData<1>((void*)0x4ecb05, 0x90);
	WriteData<1>((void*)0x4ecb06, 0x90);
	WriteData<1>((void*)0x4ecb07, 0x90);
	WriteData<1>((void*)0x4ecb08, 0x90);
	WriteData<1>((void*)0x4ecb09, 0x90);
	WriteData<1>((void*)0x4ecb0a, 0x90);
	WriteData<1>((void*)0x4ecb0b, 0x90);
	WriteData<1>((void*)0x4ecb0c, 0x90);
	WriteData<1>((void*)0x4ecb0d, 0x90);*/
	loadedFog = false;
	boostTimer = 0;
	createCount = 3000;
	if (CurrentLevel != LevelIDs_ChaoWorld)
	{
		if ((CurrentCharacter & ~1) == Characters_Tails)
			CurrentCharacter += Characters_MechTails - Characters_Tails;
	}
	else
	{
		if (disChaoReload) {
			srand(time(NULL));
			seed = rand();
			Randomize(seed);
			if (rkart) randomizeKartStats();
			if (true) LogThis("LevelLists.txt",seed,cutoff);
		}
		if ((CurrentCharacter & ~1) == Characters_MechTails)
			CurrentCharacter -= Characters_MechTails - Characters_Tails;
	}
	if (!TwoPlayerMode && CurrentLevel != LevelIDs_FinalHazard && CurrentLevel != LevelIDs_ChaoWorld)
	{
		if (randomMissions && CurrentLevel != LevelIDs_CannonsCoreE && CurrentLevel != LevelIDs_CannonsCoreR && CurrentLevel != LevelIDs_CannonsCoreK && CurrentLevel != LevelIDs_CannonsCoreS) MissionNum = rand() % 5;
		if (forceMissionNum && MissionNum == 0) MissionNum = forcedMissionNum;
		else if (forceMissionNum && MissionNum == forcedMissionNum) MissionNum = 0;
		int ch = defaultcharacters[CurrentCharacter];
		if (swapOnStage) if(stageToChar(CurrentLevel) != -1) ch = newCharPerStage[CurrentLevel];
		if(MissionNum == 4 && !sehar) ch = defaultcharactersM5[CurrentCharacter];
		CurrentCharacter = ch & charmask;
		AltCostume[1] = AltCostume[0] = ch & altcostume ? 1 : 0;
		AltCharacter[1] = AltCharacter[0] = ch & altcharacter ? 1 : 0;
	}
	int playerNum = 0;
	int *character = &CurrentCharacter;
	int buttons = MenuButtons_Held[0];
	int allUps = 1;
	int canPick[6] = { Characters_Sonic,Characters_Shadow,Characters_Tails,Characters_Eggman,Characters_Knuckles,Characters_Rouge };
	if (CurrentLevel == LevelIDs_ChaoWorld) {
		
		*character = canPick[rand()%6];
		AltCostume[0] = 0;
		AltCharacter[0] = 0;
	}

LoopStart:

	///STUFF//////////
	
	

	






	//////////////////////////////////////////////////////////////////////////////////

	//if (rSize) r = (rand() % 200) / 100.0;
	objPlacedInStage = false;
	//if (randomMissions) MissionNum = rand() % 5;
	if(!vanillaLives) Life_Count[0] = storeLives;
	TimeStopped = 0;
	//Chao_Display(CreateChao(ChaoDataArray[0], CurrentChaoArea, GetCurrentChaoStage_ptr, (0, 0, 0), (0, 0, 0)));

	if (swapOnLoad && CurrentLevel != LevelIDs_ChaoWorld && MissionNum != 4 && CurrentLevel != LevelIDs_FinalHazard) {
		int r = useThisPool[rand() % numCharsinPool];
		if (!noVanillaChars) {
			while (sameType(stageToChar(CurrentLevel), r)) {
				r = useThisPool[rand() % numCharsinPool];
			}
		}
		int roll = rand() % 3;
		if (roll == 0 && !(r & altcharacter) && nocosts != 1) r |= altcostume;
		CurrentCharacter = r & charmask;
		AltCostume[1] = AltCostume[0] = r & altcostume ? 1 : 0;
		AltCharacter[1] = AltCharacter[0] = r & altcharacter ? 1 : 0;

		unsigned int timer = 15 * 60;
		int c = CurrentCharacter;
		if (isMech(c)) timer = 30 * 60;
		if (isHunt(c)) timer = 20 * 60;
		WriteData<int>(&MHTimer1, timer);
		WriteData<int>(&MHTimer2, timer);
		WriteData<int>(&MHTimer3, timer);
		WriteData<int>(&MHTimer4, timer);
		WriteData<int>(&MHTimerMinus660, timer - 660);
		for (int j = 0; j < 30; j++) {
			if (m4timers[j].level == CurrentLevel) m4timers[j].min += 1;
		}


		int factor = 2;
		for (int i = 0; i < 30; i++) {
			//PrintDebug("Before");
			factor = 2;
			//PrintDebug(std::to_string(Mission1Scores[i].ARank).c_str());
			//PrintDebug(std::to_string(vanillaM1Scores[i]).c_str());
			int character = stageToChar(Mission1Scores[i].Level);
			int swapped = defaultcharacters[character];
			if (swapOnStage) swapped = newCharPerStage[i];
			if (Mission1Scores[i].Level == LevelIDs_CosmicWall) factor = 4;
			if (!sameType(character, swapped) || !noVanillaChars) {
				Mission1Scores[i].ARank = vanillaM1Scores[i] / factor;
				Mission1Scores[i].BRank = Mission1Scores[i].ARank - 10;
				Mission1Scores[i].CRank = Mission1Scores[i].BRank - 10;
				Mission1Scores[i].DRank = Mission1Scores[i].CRank - 10;

				Mission4Scores[i].ARank = vanillaM4Scores[i] / factor;
				Mission4Scores[i].BRank = Mission4Scores[i].ARank - 10;
				Mission4Scores[i].CRank = Mission4Scores[i].BRank - 10;
				Mission4Scores[i].DRank = Mission4Scores[i].CRank - 10;

			}
			else {
				Mission1Scores[i].ARank = vanillaM1Scores[i];
				Mission1Scores[i].BRank = Mission1Scores[i].ARank - 10;
				Mission1Scores[i].CRank = Mission1Scores[i].BRank - 10;
				Mission1Scores[i].DRank = Mission1Scores[i].CRank - 10;

				Mission4Scores[i].ARank = vanillaM4Scores[i];
				Mission4Scores[i].BRank = Mission4Scores[i].ARank - 10;
				Mission4Scores[i].CRank = Mission4Scores[i].BRank - 10;
				Mission4Scores[i].DRank = Mission4Scores[i].CRank - 10;

			}
			//PrintDebug("After");
			//PrintDebug(std::to_string(Mission1Scores[i].ARank).c_str());
		}



	}

	if (!izzyDevMode) {
		int ctype = 2;
		if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow) ctype = 0;
		if (CurrentCharacter == Characters_Rouge || CurrentCharacter == Characters_Knuckles) ctype = 1;
		if (CurrentCharacter == Characters_SuperSonic) {
			ctype = 1;
			if (isHuntingStagei(CurrentLevel)) ctype = 0;

		}
		string cfb = "set00";
		if (CurrentLevel < 10) cfb += "0";
		cfb += std::to_string(CurrentLevel);
		string scfb = cfb + "_s";
		string ucfb = cfb + "_u";
		if (CurrentLevel == LevelIDs_EggGolemS) scfb = "set_b_Golem_s";
		PrintDebug(scfb.c_str());
		PrintInt(ctype);

		copyFileBin(scfb.c_str(), std::to_string(ctype).c_str(), savePath);
		copyFileBin(ucfb.c_str(), std::to_string(ctype).c_str(), savePath);
		if (isHuntingStagei(CurrentLevel) && CurrentLevel != 44) {
			if (ctype == 0) moveHint(savePath, "SOMessage\\", CurrentLevel, "e");
			else if (ctype == 2) moveHint(savePath, "MechMessage\\", CurrentLevel, "e");
			else moveHint(savePath, "VanillaMessage\\", CurrentLevel, "e");
		}
		if (enemies || rM3Loc) if (stageToChar(CurrentLevel) != -1) randomizeEnemies(savePath, CurrentLevel, rM3Loc, enemies);
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
	goalRing = 0x0E;
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
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_HotShot) {
			int ch = hotShotSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_FlyingDog) {
			int ch = flyDogSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_KingBoomBoo) {
			int ch = KBBSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_EggGolemE) {
			int ch = EGESwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_Biolizard){
			int ch = biolizSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}
		
		if (CurrentLevel == LevelIDs_CannonsCoreS) {
			int ch = CCSonicSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}

		if (CurrentLevel == LevelIDs_EggGolemS) {
			int ch = EGSSwap;
			CurrentCharacter = ch & charmask;
			AltCostume[0] = 0;
			AltCharacter[0] = ch & altcharacter ? 1 : 0;
			character = &CurrentCharacter;
			if (vanBoss) CurrentCharacter = vanillaChar;
		}
		
		switch (CurrentLevel) {
			int cha;
		case LevelIDs_TailsVsEggman1:
			*character = Characters_MechTails + rand() % 2;
			if (vanBoss) CurrentCharacter = vanillaChar;
			//*character = charBossPlayer[2];
			break;
		case LevelIDs_TailsVsEggman2:
			*character = Characters_MechTails;
			if (vanBoss) CurrentCharacter = vanillaChar;
			//*character = charBossPlayer[3];
			break;
		case LevelIDs_KnucklesVsRouge:
			*character = Characters_Knuckles + rand() % 2;
			if (vanBoss) CurrentCharacter = vanillaChar;
			//*character = charBossPlayer[4];
			break;
		case LevelIDs_SonicVsShadow1:
			*character = Characters_Sonic + rand() % 2;
			if (vanBoss) CurrentCharacter = vanillaChar;
			//*character = charBossPlayer[0];
			AltCostume[1] = AltCostume[0] = 0;
			break;
		case LevelIDs_SonicVsShadow2:
			if (CurrentCharacter == Characters_MechEggman) *character = Characters_MechTails;
			if (vanBoss) CurrentCharacter = vanillaChar;
			//*character = charBossPlayer[1];
			AltCostume[1] = AltCostume[0] = 0;
			break;
		case LevelIDs_WhiteJungle:
			if (CurrentCharacter == Characters_MechTails)	*character = Characters_Tails;
			if (CurrentCharacter == Characters_MechEggman)	*character = Characters_Eggman;
			springID = 1;
			itemBoxID = 6;
			MMID = 49;
			goalRing = 0x1C;
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
			if (CurrentCharacter == Characters_MechTails) AltCostume[0] = 0;
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
			goalRing = 0x0D;
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
			goalRing = 0x0D;
			break;
		case LevelIDs_GreenForest:
			if (CurrentCharacter == Characters_Sonic) AltCostume[0] = 0;
			if (CurrentCharacter == Characters_MechTails)	*character = Characters_Tails;
			if (CurrentCharacter == Characters_MechEggman)	*character = Characters_Eggman;
			springID = 1;
			itemBoxID = 6;
			MMID = 51;
			goalRing = 0x1F;
			break;
		case LevelIDs_HiddenBase:
			if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Shadow || CurrentCharacter == Characters_MechEggman) WriteData<1>((void*)0x46AD50, 0xC3); //C3
			break;
		case LevelIDs_MadSpace:
			if (noVanillaChars) {
				if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_MechTails || CurrentCharacter == Characters_SuperSonic) *character = Characters_Knuckles;
				if (CurrentCharacter == Characters_Shadow || CurrentCharacter == Characters_MechEggman) *character = Characters_Rouge;
			}
			if (!noVanillaChars) {
				*character = Characters_Knuckles;
			}
			if (vanBoss) CurrentCharacter = vanillaChar;
			break;

		case LevelIDs_FinalHazard:
			
			break;
		case LevelIDs_CrazyGadget:
			if (CurrentCharacter == Characters_MechTails) AltCostume[0] = 0;
			MMID = 35;
			break;
		case LevelIDs_SecurityHall:
			break;
		case LevelIDs_DryLagoon:
			break;
		case LevelIDs_EggQuarters:
			if (CurrentCharacter == Characters_MechTails) *character = Characters_Tails;
			if (CurrentCharacter == Characters_MechEggman) *character = Characters_Eggman;
			break;
		case LevelIDs_CannonsCoreR:
			//if (CurrentCharacter == Characters_MechTails) *character = Characters_Knuckles;
			//if (CurrentCharacter == Characters_MechEggman) *character = Characters_Rouge;
			break;
		}


	}

	if (CurrentLevel != LevelIDs_CosmicWall) {
		SonicAncientLightGot = 1;
		ShadowAncientLightGot = 1;
	}

	if (CurrentCharacter == Characters_MechEggman && randoSV) AltCostume[0] = 0;
	if (vanBoss) {
		AltCharacter[0] = 0;
		AltCostume[0] = 0;
	}
	if (vanBoss && MissionNum == 4) CurrentCharacter = vanillaChar;
	if (setRNG) {
		if (isHuntingStage()) {
			FrameCount = seed % 1023 + 1;
			FrameCountIngame = seed % 1023 + 1;
		}
	}

	ModelCredits md;
	md = swapModel(CurrentCharacter, savePath, hf);

	//if (!credited(md, modelCreds)) modelCreds.push_back(md);



	if(inPool[12]) fixSuper(); //if SS enabled, will crash
	int repcnt;
	pair<short, short> *replst;
	switch (*character)
	{
	case Characters_SuperSonic:
		if( CurrentLevel != LevelIDs_FinalHazard && !TwoPlayerMode) setUpSuper();
		LoadSuperSonic();
		repcnt = (int)LengthOfArray(OthersAnimReplacements);
		replst = OthersAnimReplacements;
		break;
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
	for (int i = 0; i < repcnt; i++) {
		/*if (CurrentLevel == LevelIDs_TailsVsEggman2) {
			if (!CharacterAnimations[anilst[replst[i].key].AnimNum].Animation)
				anilst[replst[i].key] = anilst[replst[i].value];
		}
		else */
			anilst[replst[i].key] = anilst[replst[i].value];

	}
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
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },
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
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },
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
    { LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },
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
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },
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
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
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
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
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
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },

	{ LevelIDs_Invalid }
};

StartPosition SuperSonicStart[] = {
	{ LevelIDs_BasicTest },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, {20,-1000,1520}, {20,-1000,1520}, {20,-1000,1520} },

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

	//swapChao = false;

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
			if (rSize) if (MainCharObj1[playerNum]) {
				float r1 = (rand() % 20) / 10.0;
				float r2 = (rand() % 20) / 10.0;
				float r3 = (rand() % 20) / 10.0;
				MainCharObj1[playerNum]->Scale = { r1,r2,r3 };

			}
			//if (rSize) if (MainCharObj2[0]) MainCharObj2[0]->PhysData.CollisionSize *= pow(3*pow(r,2),0.5);
			//if (!isMech(CurrentCharacter)) MainCharObj2[0]->MechHP = 1.0;
			if(CurrentLevel == LevelIDs_PumpkinHill || CurrentLevel == LevelIDs_EggQuarters) v4->Upgrades = v4->Upgrades | 0x2002400;
			switch ( v4->CharID )
			{
			case Characters_Sonic:
				list = SonicStartList;
				break;
			case Characters_Shadow:
				list = ShadowStartList;
				if (shadowBounce) v4->Upgrades = v4->Upgrades | 16;
				if (AltCharacter[0] == 1 && !noQoL) {
					
					v4->PhysData.BrakeSpeed = -0.07;
					v4->PhysData.GroundDecel = -0.03;
				}
				break;
			case Characters_Knuckles:
				list = KnucklesStartList;
				break;
			case Characters_Rouge:
				list = RougeStartList;
				if (!noQoL) {
					v4->UnderwaterTime = 32000;
					if (AltCharacter[0] == 1) v4->PhysData.BaseSpeed = 1.9;
				}
				break;
			case Characters_Tails:
				list = TailsStartList;
				if(!noQoL) v4->PhysData.BaseSpeed = 2.4;
				break;
			case Characters_Eggman:
				list = EggmanStartList;
				v4->PhysData.InitialJumpSpeed = 2.2;
				v4->PhysData.HangTime = 10;
				break;
			case Characters_MechEggman:
				list = MechEggmanStartList;
				if (AltCharacter[0] == 1 && !noQoL) {
					v4->PhysData.BaseSpeed = 1.3;
				}
				break;
			case Characters_MechTails:
				list = MechTailsStartList;
				break;
			case Characters_SuperSonic:
				list = SuperSonicStartList;
				if (CurrentLevel != LevelIDs_FinalHazard) {
						v4->UnderwaterTime = 32000;
					if (!noQoL) {
						v4->PhysData.BaseSpeed = 8;
						v4->PhysData.HSpeedCap = 30;
						v4->PhysData.VSpeedCap = 30;
					}
				}
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
	if(randomMissions) MissionNum = storeMission;

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
		*(float *)&MainCharObj2[v1]->idk6 = v11;
		MainCharObj2[v1]->field_144[0] = 0;
		sub_46DC70(v1, &v4->Position, 0);
		v4->Collision->CollisionArray->field_2 |= 0x70u;
		*(int*)&MainCharObj2[v1]->gap70[24] = 0;
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
						*(float *)&MainCharObj2[v1]->idk6 = v10;
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
		*(int*)&MainCharObj2[v1]->gap70[24] = 0;
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
						*(float *)&MainCharObj2[v2]->idk6 = v13;
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
		*(int*)&MainCharObj2[v2]->gap70[24] = 0;
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
	ESG = 0;
	if (CurrentCharacter == Characters_SuperSonic) CurrentCharacter = Characters_Sonic;
	int character = CurrentCharacter ^ 1;



	AltCharacter[1] = rand() % 2;
	if (vanBoss) {
		AltCharacter[1] = 0;
		AltCostume[1] = 0;
	}
	/*if (CurrentCharacter == Characters_SuperSonic) {
		AltCharacter[1] = 0;
		LoadSuperShadow();
		return;
	}*/
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

int sub_46EE00() {
	if (CurrentCharacter == Characters_SuperSonic) return 0;
	else return 0;
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


int BSFix() { 
	return 0; 
}



void __cdecl RandomizeItemBoxAir(EntityData1 *obj)
{
	obj->Index = rand() % 11; // the item is stored in field_3 and can range from 0 to 10
}

// for some reason MSVC can't jmp to an address directly, it has to be a variable/constant
static const int loc_6C9044 = 0x6C9044;
// this function is a pure ASM wrapper for RandomizeItemBoxAir
__declspec(naked) void loc_6C903D()
{
	__asm
	{
		push eax // save eax
		push ecx // save ecx
		push edx // save edx
		push ebp // takes the pointer to the current object stored in ebp and pushes it onto the stack where RandomizeItemBoxAir will see it as 'obj'
		call RandomizeItemBoxAir
		pop ebp // restore ebp
		pop edx // restore edx
		pop ecx // restore ecx
		pop eax // restore eax
		jmp loc_6C9044 // jump back into SA2's code
	}
}

void __cdecl RandomizeItemBox(ObjectMaster *obj)
{
	obj->UnknownA_ptr = (ObjUnknownA*)(rand() % 11); // the item is stored in field_3C for some reason
}

static const int loc_6DB15B = 0x6DB15B;
__declspec(naked) void loc_6DB136()
{
	__asm
	{
		push eax // save eax
		push ecx // save ecx
		push edx // save edx
		push esi
		call RandomizeItemBox
		pop esi
		pop edx // restore edx
		pop ecx // restore ecx
		pop eax // restore eax
		jmp loc_6DB15B
	}
}

static const int loc_6C7DED = 0x6C7DED;
__declspec(naked) void loc_6C7DC8()
{
	__asm
	{
		push eax // save eax
		push ecx // save ecx
		push edx // save edx
		push edi
		call RandomizeItemBox
		pop edi
		pop edx // restore edx
		pop ecx // restore ecx
		pop eax // restore eax
		jmp loc_6C7DED
	}
}






static int loc_jmpbackFH = 0x49CA8B;
static int loc_jmpbackFH2 = 0x49CD3D;
static int loc_jmpbackFH3 = 0x49CA7D;
int FHCheck() {
	if (CurrentLevel == LevelIDs_FinalHazard) return 1;
	return 0;
}


int LevelCompCheck() {
	if(LevelComplete==1) return 1;
	return 0;
}


__declspec(naked) void FinalHazardFix() {
	__asm {
			call FHCheck
			cmp eax,0x0
			jz label
			cmp[ECX], AL
			jz label
			call LevelCompCheck
			cmp eax, 0x1
			jnz label
			jmp loc_jmpbackFH2
		label:
			jmp loc_jmpbackFH
	}

}


/*			cmp [ECX],AL
			jz label
			call LevelCompCheck
			cmp eax, 0x1
			jz label
			jmp loc_jmpbackFH2*/



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
	if (s.compare("random") == 0) return 69;
	auto ch = charnamemap.find(s);
	if (ch != charnamemap.end())
		return ch->second;
	return def;
}

void sendChat(string msg) {
	bot.sendChat(msg.c_str(), channelName.c_str());
}


bool isModerator(string s) {
	if (s.compare(channelName) == 0) return true;
	for (auto m : mods) {
		if (s.compare(m) == 0) return true;
	}
	return false;
}



void reactToString(string s) {
	if (TwoPlayerMode) return;
	float f = 1.2;
	TwitchMsg msg = parseChat(s);
	s = msg.msg;

	int cost = 0;
	if (s.compare("bread") != 0 && s.find(" ") == std::string::npos) {
		cost = commandCosts[msg.msg];
		currency[msg.user].active = true;
		currency[msg.user].lastActive = time(NULL);
		if (currency[msg.user].currency < cost) return;
	}
	if (cost == -1) return;



	if (!savedTwitchData) {
		if (s.compare("bread") != 0) {
			CopyFileA((savePath + "\\loginTwitch.txt").c_str(), "loginTwitch-save.txt", false);
			savedTwitchData = true;
		}
		sendChat("SA2R-TCI Active! Use !info for more information.");

	}

	string 	retMsg = msg.user + " used " + s + "!";



	if (s.compare("bread") == 0) return;
	else if (s.find(".") != string::npos) {


		string sub1 = "";
		string sub2 = "";
		string sub3 = "0";

		sub1 = s.substr(0, s.find("."));
		sub2 = s.substr(s.find(".") + 1);
		if (sub2.find(".") != string::npos) {
			string temp = sub2;
			sub2 = temp.substr(0,temp.find("."));
			sub3 = temp.substr(temp.find(".") + 1);
		}
		
		if (sub1.compare("!points") == 0 && isModerator(msg.user)) {
			currency[sub2].currency += stoi(sub3);
			retMsg = msg.user + " gave " + sub2 + " " +  sub3 + " points!";
			sendChat(retMsg);
			return;
		}
		else if (sub1.compare("!pointsall") == 0 && isModerator(msg.user)) {
			for (auto x : currency) {
				currency[x.first].currency += stoi(sub2);
			}
			retMsg = msg.user + " gave everyone " + sub2 + " points!";
			sendChat(retMsg);
			return;
		}
		else if (sub1.compare("!pointsactive") == 0 && isModerator(msg.user)) {
			for (auto x : currency) {
				if (x.second.active) currency[x.first].currency += stoi(sub2);
			}
			retMsg = msg.user + " gave all active chatters " + sub2 + " points!";
			sendChat(retMsg);
			return;
		}


		return;
	}
	else {

		if (currency[msg.user].currency == 0) {
			currency[msg.user] = FirstCurrency(currency[msg.user], currencyRates);
		}


		if (s.compare("!points") == 0) {
			retMsg = msg.user + ": " + std::to_string(currency[msg.user].currency) + " points!";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!info") == 0) {
			retMsg = "Use !commandinfo to learn about commands or !pointinfo to learn about the currency system. SA2R-TCI Mods can use !modinfo for their specific tools.";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!pointinfo") == 0) {
			retMsg = "You will earn " + std::to_string(currencyRates[2]) + " points every " + std::to_string(currencyRates[1]) + " seconds, and become inactive after " + std::to_string(currencyRates[0]) + " seconds! Use !points to view your points!";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!commandinfo") == 0) {
			retMsg = "";
			for (auto x : commandCosts) {
				retMsg += x.first + "(" + std::to_string(x.second) + "), ";
			}
			retMsg.pop_back();
			retMsg.pop_back();
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!modinfo") == 0) {
			retMsg = "Use !points.user.X to give user X points, !pointsall.X to give everyone X, or !pointsactive.X to give active chatters X points.";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!pointsall") == 0 && isModerator(msg.user)) {
			for (auto x : currency) {
				currency[x.first].currency += currencyRates[3];
			}
			retMsg = msg.user + " gave everyone " + std::to_string(currencyRates[3]) + " points!";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!pointsactive") == 0 && isModerator(msg.user)) {
			for (auto x : currency) {
				if (x.second.active) currency[x.first].currency += currencyRates[3];
			}
			retMsg = msg.user + " gave all active chatters " + std::to_string(currencyRates[3]) + " points!";
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!win") == 0) {
			if (GameState == 16) {
				AwardWin(0);
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!ring+") == 0) {
			if (GameState == 16 && RingCount[0] < 989) {
				RingCount[0] += 10;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!ring-") == 0) {
			if (GameState == 16 && RingCount[0] > 10) {
				RingCount[0] -= 10;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!life+") == 0) {
			if (GameState == 16 && Life_Count[0] < 99) {
				Life_Count[0]++;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!life-") == 0) {
			if (GameState == 16 && Life_Count[0] < 999) {
				Life_Count[0]--;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!vert") == 0) {
			if (GameState == 16 && MainCharObj1[0]) {
				MainCharObj1[0]->Position.y += 500;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!speed") == 0) {
			if (GameState == 16 && MainCharObj2[0]) {
				MainCharObj2[0]->PhysData.GroundAccel *= f;
				MainCharObj2[0]->PhysData.AirAccel *= f;
				MainCharObj2[0]->PhysData.HSpeedCap *= f;
				MainCharObj2[0]->PhysData.VSpeedCap *= f;
				MainCharObj2[0]->Speed.x *= f;
				MainCharObj2[0]->Speed.y *= f;
				MainCharObj2[0]->Speed.z *= f;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!magnet") == 0) {
			if (GameState == 16) {
				AwardMagneticBarrier(0);
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!barrier") == 0) {
			if (GameState == 16) {
				AwardBarrier(0);
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!jump") == 0) {
			if (GameState == 16 && MainCharObj2[0]) {
				MainCharObj2[0]->PhysData.InitialJumpSpeed *= f;
				MainCharObj2[0]->PhysData.HangTime *= f;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!score+") == 0) {
			if (GameState == 16) {
				ScoreP1 += 1000;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!score-") == 0) {
			if (GameState == 16 && ScoreP1 > 1000) {
				ScoreP1 -= 1000;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!hp+") == 0) {
			if (GameState == 16 && MainCharObj2[0] && isMech(CurrentCharacter)) {
				MainCharObj2[0]->MechHP += 10;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!dmg") == 0) {
			if (GameState == 16 && MainCharObj1[0]) {
				MainCharObj1[0]->Status |= Status_Hurt;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!chaokey") == 0) {
		if (GameState == 16 && MainCharObj1[0] && HaveChaoKey == 0) {
			HaveChaoKey = 1;
			currency[msg.user].currency -= cost;
			sendChat(retMsg);
		}
		return;
		}
		else if (s.compare("!song") == 0) {
			StopMusic();
			PlayMusic(looping[0]);
			ResetMusic();
			currency[msg.user].currency -= cost;
			sendChat(retMsg);
			return;
		}
		else if (s.compare("!bosshp+") == 0) {
			if (GameState == 16) {
				AddHP(1, 4);
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!bosshp-") == 0) {
			if (GameState == 16) {
				AddHP(1, -4);
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!chaoscontrol") == 0) {
			if (GameState == 16) {
				Sonic2PTimeStopMan_Load(dummy);
				if (!isSpeed(CurrentCharacter)) timeToDelete = 400;
				currency[msg.user].currency -= cost;
				sendChat(retMsg);
			}
			return;
		}
		else if (s.compare("!voiceline") == 0) {
			PlayVoice(0, 123);
			currency[msg.user].currency -= cost;
			sendChat(retMsg);
			return;
		}
	}
}



void reactToFlag() {
	if (TwoPlayerMode) return;
	float f = 1.2;
	switch (CCFlag) {
	case(1):
		AwardWin(0);
		break;
	case(2):
		if (RingCount[0] < 999) RingCount[0]++;
		break;
	case(3):
		if (RingCount[0] > 0) RingCount[0]--;
		break;
	case(4):
		if (Life_Count[0] < 99) Life_Count[0]++;
		break;
	case(5):
		if (Life_Count[0] > 0) Life_Count[0]--;
		break;
	case(6):
		MainCharObj1[0]->Position.y += 500;
		break;
	case(7):

		MainCharObj2[0]->PhysData.GroundAccel *= f;
		MainCharObj2[0]->PhysData.AirAccel *= f;
		MainCharObj2[0]->PhysData.AirAccel *= f;
		MainCharObj2[0]->PhysData.HSpeedCap *= f;
		MainCharObj2[0]->PhysData.VSpeedCap *= f;
		MainCharObj2[0]->Speed.x *= f;
		MainCharObj2[0]->Speed.y *= f;
		MainCharObj2[0]->Speed.z *= f;
		break;
	case(8):
		AwardMagneticBarrier(0);
		break;
	case(9):
		AwardBarrier(0);
		break;
	case(10):
		//AwardSpeedShoes(0);
		break;
	case(11):
		MainCharObj2[0]->PhysData.InitialJumpSpeed *= f;
		MainCharObj2[0]->PhysData.HangTime *= f;
		break;
	case(12):
		ScoreP1 += 100;
		break;
	case(13):
		if(ScoreP1 > 100) ScoreP1 -= 100;
		break;
	case(14):
		if (isMech(CurrentCharacter)) MainCharObj2[0]->MechHP += 10;
		break;
	case(15):
		MainCharObj1[0]->Status |= Status_Hurt;
		break;
	case(16):
		StopMusic();
		PlayMusic(looping[0]);
		ResetMusic();
		break;
	case(17):
		Gravity.y *= 1.01;
		break;
	case(18):
		Gravity.y /= 1.01;
		break;
	case(19):
		AddHP(1, 4);
		break;
	case(20):
		AddHP(1, -4);
		break;
	case(21):
			Sonic2PTimeStopMan_Load(dummy);
			if(!isSpeed(CurrentCharacter)) timeToDelete = 400;
		break;


	}



	CCFlag = 0;
}


const char* GetMissionText()
{
	string s = "Collect " + std::to_string(m2Req);
	if(m2Types[CurrentLevel] == 0) s += " Rings";
	else if (m2Types[CurrentLevel] == 1) s += " Points";

	if (MissionNum == 1) return s.c_str();
	return nullptr;
}

const void* loc_4966B7 = (const void*)0x4966BB;
__declspec(naked) void MissionTextHook()
{
	__asm
	{
		call GetMissionText
		test eax, eax
		jz notxt
		mov esi, eax
	notxt :
		mov eax, [0x1A5A3F4]
		jmp loc_4966B7
	}
}





const string charnames[Characters_Amy] = { "Sonic", "Shadow", "Tails", "Eggman", "Knuckles", "Rouge", "MechTails", "MechEggman" };

extern "C"
{

	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		

		hf = helperFunctions;

		//WriteJump((void*)0x43E6D0, exitStage); //AwardWin DONT USE
		InitBossTitles();
		InitRankVoice();
		std::ifstream afsFile;
		string tempPath = path;
		tempPath += "\\gd_PC\\event_adx.afs";
		afsFile.open(tempPath.c_str(),std::ios::binary);
		afsFile.read(reinterpret_cast<char*>(&sizeOfAfs),4);
		afsFile.read(reinterpret_cast<char*>(&sizeOfAfs),4);
		afsFile.close();
		PrintInt(sizeOfAfs);
		//if(sizeOfAfs > 2727) WriteData<2>((char*)0x44267F, 0x90i8);
		if (sizeOfAfs < 2600) game = 0;
		else if (sizeOfAfs > 3000) game = 2;


		bool dev = false;

		for (int i = 0; i < 46; i++) {
			m2Reqs[i] = 100;
			m2Types[i] = 0;
		}



		HaveBattleDLC = 1;
		HaveBattleDLC2 = 1;
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
		storeLives = settings->getInt("OnOff", "lives",99)%100;
		//if (RandoSeed == 122) RandoSeed = 123;
		randomMissions = settings->getBool("rando", "rmissions");
		RmissionNum = rand() % 5 + 1;
		//sehar = settings->getBool("OnOff", "setchars");
		tag = settings->getBool("OnOffVL", "tag");
		sa2vl = settings->getBool("OnOffVL", "sa2vl",true);
		sadxvl = settings->getBool("OnOffVL", "sadxvl",true);
		shvl = settings->getBool("OnOffVL", "shvl",true);
		playFromWav = settings->getBool("OnOffVL", "wav", false);


		if (playFromWav) {
			WriteJump((void*)0x443130, PlayWav_r);  /// VOICES
			for (const auto& f : fs::directory_iterator(savePath+"\\Wav\\")) {
				totalWavFiles++;
			}

		}



		string t = settings->getString("OnOff", "setchars");
		if (t.compare("before") == 0) {
			sehar = true;
			setCharTime = 1;
		}
		else if (t.compare("after") == 0) {
			sehar = true;
			setCharTime = 2;
		}
		subType = settings->getString("OnOffVL", "subtitles");
		if (subType.compare("cuts") == 0) subNumber = 1;
		else if (subType.compare("on") == 0) subNumber = 2;

		story = settings->getString("OnOff", "story");

		if (settings->getString("OnOff", "swap").compare("character") == 0) swapOnStage = false;
		else if (settings->getString("OnOff", "swap").compare("load") == 0) {
			swapOnLoad = true;
			swapOnStage = false;
		}

		string s = settings->getString("OnOffVL", "vlType");
		
		if(s.compare("orand") == 0) vlRandoType = 1;
		else if(s.compare("samerand") == 0) vlRandoType = 2;
		else if(s.compare("mainrand") == 0) vlRandoType = 3;
		else if (s.compare("time") == 0) vlRandoType = 4;
		else if (s.compare("sameAll") == 0) vlRandoType = 5;
		else if (s.compare("saferand") == 0) vlRandoType = 72;
		else if (s.compare("safeorand") == 0) vlRandoType = 73;
		showN = settings->getBool("OnOff", "showNames");


		if (settings->getInt("Izzy", "loadSet",1) == 0) izzyDevMode = true;
		if (settings->getBool("OnOff", "r2pc")) altncost = 0;
		if (settings->getBool("OnOff", "rAltCost")) nocosts = 1;
		//rchar = settings->getBool("OnOff", "rChar");
		setRNG = settings->getBool("OnOff", "setRNG");
		crowdControl = settings->getBool("OnOff", "crowdControl");

		//randoSV = settings->getBool("OnOff", "rVers");
		randoSV = true;
		rVoices = settings->getBool("OnOffVL", "rVL");
		cVoices = settings->getBool("OnOffVL", "cVL");
		cADX = settings->getBool("rando", "cADX");
		noVanillaChars = settings->getBool("OnOff", "noVanilla");
		boostMyAss = settings->getBool("OnOffDEV", "boostActive");
		boost = settings->getInt("OnOffDEV", "boostSpeed");
		
		noQoL = settings->getBool("OnOffDEV", "noQoL");
		OHKO = settings->getBool("OnOffDEV", "OHKO");
		vanBoss = settings->getBool("OnOffDEV", "vanBoss");
		vanillaLives = settings->getBool("OnOffDEV", "vanillaLives");
		shadowBounce = settings->getBool("OnOff", "shadowBounce");
		MetalSonicAnimList[30] = MetalSonicAnimList[11]; 

		for (int i = 0; i < 71; i++) if (settings->getBool("stages", std::to_string(i))) ignoreStages.push_back(i);
		




		forcedMissionNum = settings->getInt("OnOffDEV", "forceMission",1);
		if (forcedMissionNum > 1 && forcedMissionNum <=5 ) {
			forcedMissionNum = (forcedMissionNum - 1) % 5;
			forceMissionNum = true;
		}

		rFog = settings->getBool("OnOffDEV", "rFog");
		rFogColor = settings->getBool("OnOffDEV", "rFogColor");

		if(!playFromWav) if (!rVoices) WriteJump((void*)0x443130, PlayVoice_r);  /// VOICES

		if (RandoSeed != 0)
			seed = RandoSeed;
		else {
			srand(seed);
			seed = rand();
		}

		srand(seed);

		if (!settings->getBool("OnOffKart", "rTrack")) {
			createTrack(0, savePath);
			createTrack(1, savePath);
		}
		if (!settings->getBool("OnOffKart", "rTrackKart")) {
			createTrack(2, savePath);
			createTrack(3, savePath);
			createTrack(4, savePath);
		}

		if (crowdControl) {
			currency = startUpScores(savePath);
			commandCosts = GetCommandCosts(savePath);
			currencyRates = setUpRates(savePath);
			mods = setUpMods(savePath);

			std::ifstream twitchlog;
			string ptl = path;
			ptl += "\\loginTwitch.txt";
			twitchlog.open(ptl);
			string n;
			string u;
			string p;
			string c;
			string temp;
			getline(twitchlog, temp);
			temp = lowerCase(temp);

			if (temp.compare("channel") == 0) {
				twitchlog.close();
				CopyFileA("loginTwitch-save.txt", (savePath + "\\loginTwitch.txt").c_str(), false);
				twitchlog.open(ptl);
				getline(twitchlog, temp);
			}

			bot.channelSave = temp.c_str();
			channelName = temp;
			n = "NICK " + temp + "\r\n";

			//std::cout << n;

			//twitchlog >> temp;
			u = "USER " + temp + "\r\n";
			c = "JOIN #" + temp + "\r\n";
			twitchlog >> temp;
			p = "PASS " + temp + "\r\n";
			//twitchlog >> temp;
			//c = "JOIN #" + temp + "\r\n";

			twitchlog.close();

			bot.nick = n.c_str();
			bot.usr = u.c_str();
			bot.password = p.c_str();
			bot.channel = c.c_str();
			bot.start();


			dummy->PlayerNum = 1;

			WriteJump((void*)0x724B40, (void*)0x724BB8);//2p free chaos control
			//WriteJump((void*)0x724A6F, (void*)0x724A7D);
			WriteData((short*)0x724745, (short)0x9090);//2p free chaos control
		}


		chaoMusic = settings->getBool("rando", "chaoMusic", false);

		if (!settings->getBool("rando", "rMusic")) {
			WriteJump((void*)0x442CF0, PlayMusic_r);
			WriteCall((void*)0x44F8AB, PlayMusicOnce_r);
			WriteCall((void*)0x45085D, PlayMusicOnce_r);
			WriteCall((void*)0x451026, PlayMusicOnce_r);
			WriteCall((void*)0x4510BE, PlayMusicOnce_r);
			WriteCall((void*)0x542AAE, PlayMusicOnce_r);
			WriteCall((void*)0x542B41, PlayMusicOnce_r);
			WriteCall((void*)0x542B90, PlayMusicOnce_r);
			WriteCall((void*)0x586025, PlayMusicOnce_r);
			WriteCall((void*)0x6D8940, PlayMusicOnce_r);
			WriteCall((void*)0x793211, PlayMusicOnce_r);
			WriteJump((void*)0x443480, PlayJingle_r);
		}

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

		if (settings->getBool("OnOffDEV", "enableSS")) inPool[12] = true;

		numCharsinPool = 0;
		for (int i = 0; i < 13; i++) {
			if (inPool[i]) {
				//PrintDebug("here");
				useThisPool[numCharsinPool] = charPool[i];
				//PrintDebug(std::to_string(numCharsinPool).c_str());
				numCharsinPool++;
				//PrintDebug(std::to_string(numCharsinPool).c_str());
			}
		}


		for (int i = 0; i < 30; i++) {
			vanillaM1Scores[i] = Mission1Scores[i].ARank;
			vanillaM4Scores[i] = Mission4Scores[i].ARank;
			vanillaM5Scores[i] = Mission5Scores[i].ARank;

		}


		//inplaceCut = settings->getBool("OnOff", "cuts");
		disRL = settings->getBool("rando", "disRandL");
		replaceMadSpace = settings->getBool("OnOff", "madSwap");

		dischaokarate = settings->getBool("chaoSets", "disChaoKarate");
		dischaorace = settings->getBool("chaoSets", "disChaoRace");
		Randomize(seed);

		rM3Loc = settings->getBool("rando", "rM3Loc");
		enemies = settings->getBool("rando", "rEnemy");
		


		/*for (int j = 0; j < cutoff; j++) {
			if (Levellist[j].entry_type == 1)
				Levellist[j].character_id = defaultcharacters[Levellist[j].character_id];
		}*/



		if (settings->getBool("OnOff", "upmods")) {
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

		if (true) LogThis("LevelLists.txt",seed,cutoff);
		logThisV = settings->getBool("OnOff", "llg");
		//boolean logs = false;

		//WriteData<2>((void*)0x459110, 0x90);
		//WriteData<2>((void*)0x45913B, 0x90);


		if (settings->getBool("OnOffDEV", "fastLoad")) WriteData<1>((void*)0x43A889, 0x03);
		disKill = settings->getBool("OnOffDEV", "disKill");
		if (disKill) WriteData<1>((void*)0x46AD50, 0xC3);
		

		rkart = settings->getBool("OnOffKart", "rKart");
		if (!rkart) randomizeKartStats();

		rChaoAnimals = settings->getBool("chaoSets", "rChaoAnimals");
		rChao = settings->getBool("chaoSets", "rChao");
		maxChaoStats = settings->getBool("chaoSets", "maxChao");
		//colorChao = settings->getBool("chaoSets", "colorChao");
		disChaoReload = settings->getBool("chaoSets", "disChaoRR");
		disTempChaoFile = settings->getBool("chaoSets", "disChaoTemp");



		string baseFrom = savePath + "\\Options\\SAVEDATA\\";
		string baseTo = savePath + "\\gd_PC\\SAVEDATA\\";
		string f = "SONIC2B__ALF";
		baseFrom += f;
		baseTo += f;
		if (true) CopyFileA(baseFrom.c_str(), baseTo.c_str(), false);


		if (settings->getBool("OnOff", "setESG")) setESG = true;
		disableBS = settings->getBool("OnOff", "disBS");
		tPoseFuckery = settings->getBool("OnOff", "tPose");
		rSize = settings->getBool("OnOffDEV", "rSize");


		if (settings->getBool("rando", "rMisText")) {
			WriteJump((void*)0x49656A, RandomMissionText);
			WriteJNZ((void*)0x4965DC, RandomMissionText);
			WriteJump((void*)0x6BD650, LoadMessageLists_r);//omochao text stuff
			WriteData((ObjectFuncPtr*)0x6C0879, Omochao_RandomMessage);

		}
		if (settings->getBool("rando", "rM2")) {
			WriteJump((void*)0x4966B2, MissionTextHook);

			for (int i = 0; i < Mission2Times_Length;i++) {
				Mission2Times[i].ARank.Minutes += 1;
				Mission2Times[i].BRank.Minutes += 1;
				Mission2Times[i].CRank.Minutes += 1;
				Mission2Times[i].DRank.Minutes += 1;
			}


			int r;
			int idx;
			int range;
			for (int i = 0; i < 45; i++) {
				r = rand() % 2;
				m2Types[i] = r;
				if (r == 0) {
					m2Reqs[i] = rand() % 126 + 25;

				}
				else if (r == 1) {
					for (int j = 0; j < Mission1Scores_Length; j++) {
						if (Mission1Scores[j].Level == i) {
							range = Mission1Scores[j].BRank - Mission1Scores[j].DRank;
							m2Reqs[i] = rand() % range + Mission1Scores[j].DRank;
							m2Reqs[i] *= 100;
						}
					}
					if (isHuntingStagei(i)) {
						m2Reqs[i] /= 3;
					}
				}

			}
			m2Types[LevelIDs_CannonsCoreE] = m2Types[LevelIDs_CannonsCoreS];
			m2Reqs[LevelIDs_CannonsCoreE] = m2Reqs[LevelIDs_CannonsCoreS];
			m2Types[LevelIDs_CannonsCoreT] = m2Types[LevelIDs_CannonsCoreS];
			m2Reqs[LevelIDs_CannonsCoreT] = m2Reqs[LevelIDs_CannonsCoreS];
			m2Types[LevelIDs_CannonsCoreR] = m2Types[LevelIDs_CannonsCoreS];
			m2Reqs[LevelIDs_CannonsCoreR] = m2Reqs[LevelIDs_CannonsCoreS];
			m2Types[LevelIDs_CannonsCoreK] = m2Types[LevelIDs_CannonsCoreS];
			m2Reqs[LevelIDs_CannonsCoreK] = m2Reqs[LevelIDs_CannonsCoreS];

		}
		if (settings->getBool("rando", "rItems")) {
			WriteJump((void*)0x6C903D, loc_6C903D); // inserts a jump to the function loc_6C903D at address 6C903D
			WriteJump((void*)0x6DB136, loc_6DB136); // for item balloons
			WriteJump((void*)0x6C7DC8, loc_6C7DC8); // for item boxes on the ground
		}



		if (subNumber > 0) {
			WriteData((char*)0x60221D, (char)0xEB); //Disable cutscene subs
			if (subNumber == 2) WriteCall((void*)0x6BEA92, giveOmochaoLine);
		}
		

		delete settings;


		if (dev) {
			if (swapOnStage) {
				for (int i = 0; i < StageSelectLevels_Length; i++) {
					if (StageSelectLevels[i].Level < 45) {
						StageSelectLevels[i].Character = newCharPerStage[StageSelectLevels[i].Level] & charmask;
					}
				}
			}
			else {
				for (int i = 0; i < StageSelectLevels_Length; i++) {
					int s = StageSelectLevels[i].Character;
					StageSelectLevels[i].Character = defaultcharacters[s] & charmask;
				}
			}
		}
		for (int i = 0; i < 8; i++) 
			for (auto c : getAllInfo(i, savePath)) 
				if (!credited(c, modelCreds))
					modelCreds.push_back(c);
			
		setUpCredits();

		WriteJump((void*)0x43cf16, (void*)0x43cf54);
		WriteCall((void*)0x6C6A3A, BackRingHook);//CC back ring fix
		WriteJump((void*)0x543280, randomChaoName);//chao karate names
		WriteJump(BrokenDownSmokeExec, DeleteObject_); //delete mech smoke
		hiddenGlitchChao = rand() % 100;
		
		//for(int i = 0; i < 4;i++) PrintDebug(std::to_string(EggmanActionWindowTextIndexes[i]).c_str());
		//WriteJump((void*)0x459110, SFX_r);//Work on SFX here

//////////////////////END OF RANDO STUFF
	}

	unsigned __int8 nop[] = { 0x90 };
	unsigned __int8 twobytenop[] = { 0x66, 0x90 };
	unsigned __int8 fivebytenop[] = { 0x66, 0x90, 0x66, 0x90, 0x90 };
	unsigned __int8 shortjmp[] = { 0xEB };
	unsigned __int8 twobyteshortjump[] = { 0x90,0xEB };
	unsigned __int8 supersonicstuff[] = { 0x88, 0x7C,0x71,0x00 };

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
		patchdecl(0x061f19d,shortjmp),//r101/r280 respawn
		patchdecl(0x6653c1,shortjmp)
		//patchdecl(0x4ecb04, fivebytenop),
		//patchdecl(0x4ecb09, fivebytenop)

	};



	__declspec(dllexport) void OnFrame()
	{

		//voiceLineLang = rand()%2;
		if (crowdControl) {
			commandCosts = GetCommandCosts(savePath);
			currencyRates = setUpRates(savePath);
			mods = setUpMods(savePath);
			if (lastUpdate+currencyRates[1] < time(NULL)) {
				for (auto x : currency) {
					//Update Currency
					currency[x.first] = UpdateCurrency(x.second, currencyRates);
				}
				std::ofstream in;
				in.open((savePath + "\\Twitch\\chatCurrency.txt").c_str());
				for (auto x : currency)
					in << x.first << " " << x.second.currency << std::endl;
				in.close();
				lastUpdate = time(NULL);
			}
			if (bot.msg.compare("bread") == 0) {
				bot.checkOnce();
				reactToString(bot.msg);
				//PrintDebug(bot.msg.c_str());
				bot.msg = "bread";
			}

			if (timeToDelete >= 0) {
				MainCharObj1[0]->Action = Action_None;
				MainCharObj2[0]->Speed.x = 0.0;
				MainCharObj2[0]->Speed.y = 0.0;
				MainCharObj2[0]->Speed.z = 0.0;
				timeToDelete--;
			}
		}


		//if (GameState == 16 && CCFlag != 0) {
		//	reactToFlag();
		//}

		if (OHKO && GameState == 16 && MainCharObj2[0] != NULL) {
			if (isMech(CurrentCharacter) && MainCharObj2[0]->MechHP > 1) MainCharObj2[0]->MechHP = 1;
			else {
				if (MainCharObj1[0]->Status & Status_Hurt) RingCount[0] = 0;
			}
		}

		if (subNumber == 2 || (subNumber == 1 && GameState == 0)) {
			SubtitleQueue sq;
			if (!displayMe.empty()) {
				sq = displayMe.back();
				if (sq.time <= FrameCount) {
					displayText(3, sq.text.c_str(), timeOfVl(sq.text,sq.ogID), 1);
					displayMe.pop_back();
				}
			}
		}

		if(GameState == 16) if(ScoreP1 %10 == 0) 	ScoreP1 += MissionNum + 1;

		if (MissionNum == 1 && TwoPlayerMode == 0) {
			if(m2Types[CurrentLevel] == 0 && RingCount[0] >= m2Req)	AwardWin(0);
			if (m2Types[CurrentLevel] == 1 && ScoreP1 >= m2Req) AwardWin(0);
		}
		if (CurrentLevel == LevelIDs_Route101280) {
			KartTimer = 99;
		}
		if(StageSelectLocked == 1)StageSelectLocked = 0;
		if (CurrentLevel == LevelIDs_ChaoWorld) ChaoGardensUnlocked |= SA2BLobbyUnlocks_NeutralGarden | SA2BLobbyUnlocks_DarkGarden | SA2BLobbyUnlocks_HeroGarden;

		if (CurrentLevel != LevelIDs_CannonsCoreT && CurrentLevel != LevelIDs_CannonsCoreE && CurrentLevel != LevelIDs_CannonsCoreK && CurrentLevel != LevelIDs_CannonsCoreR && CurrentLevel != LevelIDs_CannonsCoreS)
		if (myFogData != NULL && levelTimer > 0) {
				if(rFog && !loadedFog) randomizeFog();
				if(rFogColor && !loadedFog) randomizeFogColor();
				if ((rFogColor || rFog) && currentFogCount == updateFogCount) {
					loadedFog = true;
					updateFog();
					currentFogCount = 0;
				}
				currentFogCount++;
		}
	
		//WriteData<1>((void*)0x49b6e0, 0x88);
		//WriteData<1>((void*)0x49b6e1, 0x7C);
		//WriteData<1>((void*)0x49b6e2, 0x71);
		//WriteData<1>((void*)0x49b6e3, 0x00);


		//CameraMode = 1;

		if (MenuButtons_Pressed[0] & Buttons_A) Acount++;
		if (MenuButtons_Pressed[0] & Buttons_B) Bcount++;
		if (MenuButtons_Pressed[0] & Buttons_X) Xcount++;
		if (MenuButtons_Pressed[0] & Buttons_Y) {
			Ycount++;
			AwardWin(0);

		}

		if (MenuButtons_Pressed[0] & Buttons_Start) {
			Startcount++;
			
		}

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
				boostTimer = 0;
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

		if (!rChao) {
			if (CurrentLevel == LevelIDs_ChaoWorld) {

				

				//if(hiddenGlitchChao == 69 )
				if(!maxChaoStats) Chao1Data.EggColor = rand() % 55;
				if (Chao1Data.Type == 2) {
					Chao1Data = randomizeChao(Chao1Data);
					if (!maxChaoStats) Chao1Data = maxChao(Chao1Data);
					if (rChaoAnimals) ChaoDataAll[0] = animalChao(ChaoDataAll[0]);
				}
				//if (Chao2Data.Type == 2) {
				//	Chao2Data = randomizeChao(Chao2Data);
				//}				
				for (int i = 1; i < 24; i++) {
					if (ChaoDataAll[i].Type == 2) {
						ChaoDataAll[i] = randomizeChao(ChaoDataAll[i]);
						if (rChaoAnimals) ChaoDataAll[i] = animalChao(ChaoDataAll[i]);
					}
				}

			}
		}
		
		/*if (CurrentLevel == LevelIDs_CannonsCoreS) {
			if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Sonic) {
				if(MainCharObj1[0] != NULL) if (MainCharObj1[0]->Action == 72) MainCharObj1[0]->Action = Action_None;
			}
		}*/

		/*if (CurrentLevel == LevelIDs_CannonsCoreT && GameState == GameStates_ReturnRing && (MissionNum == 1 || MissionNum == 2)) {
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
		}*/


		if (MainCharObj2[0] != NULL && MainCharObj1[0] !=NULL) {

		
			if (useLastFrameSpeed) {
				MainCharObj1[0]->Action = 10;
				MainCharObj2[0]->Speed = speedLastFrame;
				useLastFrameSpeed = false;
			}



			if (MainCharObj1[0]->Action == 18  && MainCharObj2[0]->Speed.x != 0 && MainCharObj2[0]->Speed.y != 0 && MainCharObj2[0]->Speed.z != 0 &&
				speedLastFrame.x == 0 && speedLastFrame.y == 0 && speedLastFrame.z == 0) {
				
				if (isHunt(CurrentCharacter) && (CurrentLevel == LevelIDs_MetalHarbor || CurrentLevel == LevelIDs_GreenForest || CurrentLevel == LevelIDs_WhiteJungle)) {
					MainCharObj1[0]->NextAction = 10;
					MainCharObj1[0]->Status |= Status_DoNextAction;
					speedLastFrame = MainCharObj2[0]->Speed;
					useLastFrameSpeed = true;
				}
				if (isMech(CurrentCharacter) && CurrentLevel == LevelIDs_MetalHarbor) {
					MainCharObj1[0]->NextAction = 10;
					MainCharObj1[0]->Status |= Status_DoNextAction;
					speedLastFrame = MainCharObj2[0]->Speed;
					useLastFrameSpeed = true;
				}
			

			}


			//CameraX = MainCharObj1[0]->Position.x;
			//CameraY = MainCharObj1[0]->Position.y;
			//CameraZ = MainCharObj1[0]->Position.z;

			if (tPoseFuckery) {
				//MainCharObj2[0]->AnimInfo.Animation = 0;
				//MainCharObj2[0]->AnimInfo.Animation2 = 0;
				MainCharObj2[0]->AnimInfo.Animation3 = 0;
				MainCharObj2[0]->AnimInfo.Animations->AnimNum = 0;
				MainCharObj2[0]->AnimInfo.Animations->NextAnimation = 0;
				MainCharObj2[0]->AnimInfo.Animations->TransitionSpeed = 0;
				MainCharObj2[0]->AnimInfo.Animations->AnimationSpeed = 0;
			}

			if (boostMyAss) {
				if ((MenuButtons_Held[0] & Buttons_Y) && RingCount[0] > 1) {
					RingCount[0]--;
					boostTimer += 10;
				}
				if (boostTimer > 0 && (MainCharObj1[0]->Action == Action_SpinRelease || MainCharObj1[0]->Action == Action_Run || MainCharObj1[0]->Action == Action_Glide || MainCharObj1[0]->Action == Action_BounceUp || MainCharObj1[0]->Action == Action_BounceDown || MainCharObj1[0]->Action == Action_Board || MainCharObj1[0]->Action == Action_BoardTrick || MainCharObj1[0]->Action == Action_MechHover)) {
					double power = 1.0 + boost / 100.0;
					MainCharObj2[0]->Speed.x *= power;
					MainCharObj2[0]->Speed.y *= power;
					MainCharObj2[0]->Speed.z *= power;
					boostTimer--;
				}
			}

			if (CurrentCharacter == Characters_SuperSonic) {
				MainCharObj2[0]->Speed.y -= 0.08;
				if (MainCharObj1[0]->Action == 45) MainCharObj1[0]->Action = Action_None;
				//if ((MenuButtons_Pressed[0] & Buttons_L) && (MenuButtons_Pressed[0] & Buttons_Y) && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run)) {
				//	MainCharObj1[0]->Action = 45;
				//}
				if ((MenuButtons_Pressed[0] & Buttons_B) || ((MenuButtons_Pressed[0] & Buttons_X)) ) {
					if (findClosestMM(MMID) < 50) {
						MainCharObj1[0]->Action = 45;
					}
				}
			}

			if (CurrentCharacter == Characters_Eggman || CurrentCharacter == Characters_Tails) {
				if (MainCharObj1[0]->Action == 45) MainCharObj1[0]->Action = Action_None;
				//if ((MenuButtons_Pressed[0] & Buttons_L) && (MenuButtons_Pressed[0] & Buttons_Y) && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run)) {
				//	MainCharObj1[0]->Action = 45;
				//}
				if (((MenuButtons_Pressed[0] & Buttons_B) || (MenuButtons_Pressed[0] & Buttons_X)) && (MainCharObj1[0]->Action == Action_None || MainCharObj1[0]->Action == Action_Run)) {
					if (findClosestMM(MMID) < 50) {
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


			if(!useLastFrameSpeed) speedLastFrame = MainCharObj2[0]->Speed;
		}


		/*if (rM3Loc) {
			if (MissionNum == 2 && !swapChao && CurrentLevel < 70) {
				int usableObjs = 0;
				vector<int> objsThatWork;
				for (int i = 0; i < SETObjectCount; i++) {
					if (SETObjects->SETEntry[i].ID < 0x09 && SETObjects->SETEntry[i].ID!= 0x02) {
						usableObjs++;
						objsThatWork.push_back(i);
					}
				}
				if (usableObjs > 0) {
					int r = objsThatWork[rand() % usableObjs];
					SETObjects->SETEntry[r].XRot = 1;
					SETObjects->SETEntry[r].ID = goalRing;
					for (int i = 0; i < SETObjectCount; i++) if (SETObjects->SETEntry[i].ID == goalRing && SETObjects->SETEntry[i].XRot == 1) SETObjects->SETEntry[i].Position = SETObjects->SETEntry[r].Position;
					swapChao = true;
					reloadComplete = false;
					PrintPos(SETObjects->SETEntry[r].Position);
					//GameState = 2;
				}
				for (int i = 0; i < SETObjectCount; i++) {
					if (SETObjects->SETEntry[i].ID == goalRing && SETObjects->SETEntry[i].XRot == 1) {
						SETObjects->SETEntry[i].Position = KnucklesStart[4].Position1P;
					}
				}

			}
		}*/


		if (lastUse > 0 && controlActive && GameState != GameStates_Pause) lastUse--;
	}



	__declspec(dllexport) PatchList Patches = { arrayptrandlengthT(patches, int) };

	PointerInfo jumps[] = {
		ptrdecl(0x6220CE,0x6220E5),//billboards
		ptrdecl(0x622353,0x62235F),//expert kart track fix
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
		//ptrdecl(0x532029, loc_532029), // Chao World sounds
		//ptrdecl(0x459236, loc_2800440), // Chao World voices
		ptrdecl(0x72F4D6, KnucklesSunglassesFix),
		ptrdecl(0x72F531, KnucklesAirNecklaceFix),
		ptrdecl(0x744914, EggmanLaserBlasterFix),
		ptrdecl(0x744E02, EggmanLargeCannonFix),
		ptrdecl(0x748168, TailsLaserBlasterFix),
		ptrdecl(0x74861A, TailsBazookaFix),
		//ptrdecl(0x46EE00, sub_46EE00),
		//ptrdecl(0x49CA7A, 0x49CA8B)//will crash at final hazard
		ptrdecl(0x49CA7A, FinalHazardFix),
		//ptrdecl(0x723790, BSFix)//Disable Black Shield
		//ptrdecl(InitSplitscreen, InitSplitscreen_r)
	};

	__declspec(dllexport) PointerList Jumps = { arrayptrandlengthT(jumps, int) };

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };


}
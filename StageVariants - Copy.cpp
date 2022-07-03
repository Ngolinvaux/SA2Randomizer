#include "stdafx.h"
#include "StageVariants.h"



const int TOTALSTAGEOPTIONS = 44;
char stageOptionS[TOTALSTAGEOPTIONS][14] = { "set0013_s","set0003_s","set0004_s","set0009_s" ,"set0011_s","set0010_s","set0012_s" ,"set0017_s" ,"set0017_u" ,"set0021_s" ,"set0021_u",
"set0022_s","set0023_s" ,"set0024_s" ,"set0027_s","set0028_s" ,"set0030_s" ,"set0043_s" ,"set0043_u","set0014_s" ,"set0005_s","set0005_u",
"set0007_s","set0007_u","set0008_s","set0008_u" ,"set0016_s","set0016_u" ,"set0018_s" ,"set0025_s" ,"set0026_s","set0026_u","set0032_s","set0037_s" ,"set0038_s",
"set0009_u", "set0011_u", "set0012_u", "set0023_u" , "set0035_s", "set0035_u" , "set0040_s","set_b_Golem_s","set0006_s" }; //file
int stageOptionT[TOTALSTAGEOPTIONS];  //0 = speed  1 = hunt   2 = mech  3 = mechless
//int stageOptionReset[TOTALSTAGEOPTIONS] = { 1 ,1 , 1,1,1}; //rando vanilla version number

const int SonicVersions = 7;
int SonicStages[SonicVersions] = { 0,1,5,11,15,16,42 };

const int ShadowVersions = 4;
int ShadowStages[ShadowVersions] = { 2,19,41,43 };

const int KnuxVersions = 9;
int KnuxStages[KnuxVersions] = { 20,21,22,23,26,27,29,32,34 };

const int RougeVersions = 6;
int RougeStages[RougeVersions] = { 24,25,28,30,31,33 };

const int EggmanVersions = 11;
int EggmanStages[EggmanVersions] = { 4,6,9,10,14,17,18,36,37,39,40 };

const int TailsVersions = 7;
int TailsStages[TailsVersions] = { 3,7,8,12,13,35,38 };


void moveMessage(string from, string to, string file) {
	string f = from + file;
	string t = to + file;
	CopyFileA(f.c_str(), t.c_str(), FALSE);
}

void soHints(int i,string savePath) {
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

void vanHints(int i, string savePath) {
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

void mechHints(int i, string savePath) {
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


void copyFileBin(const char* f, const char* num, string savePath) {
	string from = savePath + "\\Options\\" + f + "\\" + num + ".bin";
	string to = savePath + "\\gd_PC\\" + f + ".bin";
	//CopyFileA(strcat(strcat(strcat(strcat(strcat(getcwd(), "\\mods\\SA2Rando\\Options\\"),f),"\\"),num),".bin"), strcat(strcat(strcat(getcwd(), "\\mods\\SA2Rando\\gd_PC\\"),f),".bin"), false);
	CopyFileA(from.c_str(), to.c_str(), FALSE);
	return;
}

void setSonicStages(int defaultcharacters[]) {
	int type = defaultcharacters[0] & charmask;
	if (type == Characters_SuperSonic) type = 1;
	else if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < SonicVersions; i++) {
		stageOptionT[SonicStages[i]] = type;
	}

}

void setShadowStages(int defaultcharacters[]) {
	int type = defaultcharacters[1] & charmask;
	if (type == Characters_SuperSonic) type = 1;
	else if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < ShadowVersions; i++) {
		stageOptionT[ShadowStages[i]] = type;
	}

}

void setKnuxStages(int defaultcharacters[], string savePath) {
	int type = defaultcharacters[4] & charmask;
	if (type == Characters_SuperSonic) {
		type = 0;
		soHints(0, savePath);
	}
	else if (type == Characters_Sonic || type == Characters_Shadow) {
		type = 0;
		soHints(0, savePath);
	}
	else if (type == Characters_Knuckles || type == Characters_Rouge) {
		type = 1;
		vanHints(0, savePath);
	}
	else {
		type = 2;
		mechHints(0, savePath);
	}
	for (int i = 0; i < KnuxVersions; i++) {
		stageOptionT[KnuxStages[i]] = type;
	}

}

void setRougeStages(int defaultcharacters[], string savePath) {
	int type = defaultcharacters[5] & charmask;
	if (type == Characters_SuperSonic) {
		type = 0;
		soHints(1,savePath);
	}
	else if (type == Characters_Sonic || type == Characters_Shadow) {
		type = 0;
		soHints(1, savePath);
	}
	else if (type == Characters_Knuckles || type == Characters_Rouge) {
		type = 1;
		vanHints(1, savePath);
	}
	else {
		type = 2;
		mechHints(1, savePath);
	}
	for (int i = 0; i < RougeVersions; i++) {
		stageOptionT[RougeStages[i]] = type;
	}

}

void setEggmanStages(int defaultcharacters[]) {
	int type = defaultcharacters[7] & charmask;
	if (type == Characters_SuperSonic) type = 0;
	else if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < EggmanVersions; i++) {
		stageOptionT[EggmanStages[i]] = type;
	}

}

void setTailsStages(int defaultcharacters[]) {
	int type = defaultcharacters[6] & charmask;
	if (type == Characters_SuperSonic) type = 0;
	else if (type == Characters_Sonic || type == Characters_Shadow) type = 0;
	else if (type == Characters_Knuckles || type == Characters_Rouge) type = 1;
	else  type = 2;
	for (int i = 0; i < TailsVersions; i++) {
		stageOptionT[TailsStages[i]] = type;
	}

}

void setStages(int defaultcharacters[],string savePath) {
	setSonicStages(defaultcharacters);
	setShadowStages(defaultcharacters);
	setKnuxStages(defaultcharacters, savePath);
	setRougeStages(defaultcharacters, savePath);
	setEggmanStages(defaultcharacters);
	setTailsStages(defaultcharacters);
}

void stageV(int defaultcharacters[], string savePath) {
	setStages(defaultcharacters, savePath);
	for (int q = 0; q < TOTALSTAGEOPTIONS; q++) {
		char num[2];
		itoa(stageOptionT[q], num, 10);
		copyFileBin(stageOptionS[q], num,savePath);
	}
}

void resetStageV() {
	for (int q = 0; q < TOTALSTAGEOPTIONS; q++) {
		//char num[2];
		//itoa(stageOptionReset[q], num, 10);
		//copyFileBin(stageOptionS[q], num);
		copyFileBin(stageOptionS[q], "1","");
	}
}




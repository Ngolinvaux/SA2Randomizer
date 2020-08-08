#include "stdafx.h"
#include "StageVariants.h"



const int TOTALSTAGEOPTIONS = 49;
char stageOptionS[TOTALSTAGEOPTIONS][14] = { "set0013_s","set0003_s","set0004_s","set0009_s" ,"set0011_s","set0010_s","set0012_s" ,"set0017_s" ,"set0017_u" ,"set0021_s" ,"set0021_u",
"set0022_s","set0023_s" ,"set0024_s" ,"set0027_s","set0028_s" ,"set0030_s" ,"set0043_s" ,"set0043_u","set0014_s" ,"set0005_s","set0005_u",
"set0007_s","set0007_u","set0008_s","set0008_u" ,"set0016_s","set0016_u" ,"set0018_s" ,"set0025_s" ,"set0026_s","set0026_u","set0032_s","set0037_s" ,"set0038_s",
"set0009_u", "set0011_u", "set0012_u", "set0023_u" , "set0035_s", "set0035_u" , "set0040_s","set_b_Golem_s","set0006_s","set0034_s","set0036_s","set0036_u",
"set0044_s","set0031_s"}; //file
int stageOptionT[TOTALSTAGEOPTIONS];  //0 = speed  1 = hunt   2 = mech  3 = mechless
//int stageOptionReset[TOTALSTAGEOPTIONS] = { 1 ,1 , 1,1,1}; //rando vanilla version number

int hasVariant[TOTALSTAGEOPTIONS] = {13,3,4,9,11,10,12,17,-17,21,-21,22,23,24,27,28,30,43,-43,14,5,-5,7,-7,8,-8,16,-16,18,25,
										26,-26,32,37,38,-9,-11,-12,-23,35,-35,40,64,6,34,36,-36,44,31};

const int SonicVersions = 9;
int SonicStages[SonicVersions] = { 0,1,5,11,15,16,42,44,48};

const int ShadowVersions = 4;
int ShadowStages[ShadowVersions] = { 2,19,41,43 };

const int KnuxVersions = 9;
int KnuxStages[KnuxVersions] = { 20,21,22,23,26,27,29,32,34 };

const int RougeVersions = 7;
int RougeStages[RougeVersions] = { 24,25,28,30,31,33,47 };

const int EggmanVersions = 11;
int EggmanStages[EggmanVersions] = { 4,6,9,10,14,17,18,36,37,39,40 };

const int TailsVersions = 9;
int TailsStages[TailsVersions] = { 3,7,8,12,13,35,38,45,46 };


int zeggStages[5] = { 43,11,12,21,27 };
int zsonicStages[8] = { 3,10,13,22,28,30,31,34 };
int zshadowStages[4] = { 4,6,14,40 };
int ztailsStages[5] = { 9,17,23,24,36 };
int zknuxStages[5] = { 5,7,16,25,32 };
int zrougeStages[4] = { 44,26,18,8 };


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
		_itoa(stageOptionT[q], num, 10);
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


void moveHint(string savePath, string folder, int stage, string lang) {
	string baseFrom = savePath + "\\Options\\"+folder;
	string baseTo = savePath + "\\gd_PC\\Message\\";
	string file = "eh00";
	if (stage < 10) file += "0" + std::to_string(stage);
	else file += std::to_string(stage);
	file += lang + ".prs";
	//PrintDebug(file.c_str());
	moveMessage(baseFrom, baseTo, file);
}



void charPerStage(int chars[], string savePath) {
	for (int i = 0; i < 45; i++) {
		//int type = chars[i] & charmask;
		int type = chars[i] & charmask;
	
		if (type == Characters_SuperSonic) {
			type = 0;
			if (isIn(i, zshadowStages, 4) != -1 || isIn(i, zsonicStages, 8) != -1) type = 1;
		}
		else if (isSpeed(type)) type = 0;
		else if (isHunt(type)) type = 1;
		else  type = 2;
		


		if (isIn(i, hasVariant, TOTALSTAGEOPTIONS) != -1) {
			copyFileBin(stageOptionS[isIn(i, hasVariant, TOTALSTAGEOPTIONS)], std::to_string(type).c_str() , savePath);
			//PrintInt(i);
		}
		if (isIn(-i, hasVariant, TOTALSTAGEOPTIONS) != -1) {
			copyFileBin(stageOptionS[isIn(-i, hasVariant, TOTALSTAGEOPTIONS)], std::to_string(type).c_str(), savePath);
			//PrintInt(-i);
		}

		//TODO: HINTS
		if (isHuntingStagei(i)&&i!=44) {
			if (type == 0) moveHint(savePath, "SOMessage\\", i, "e");
			else if (type == 2) moveHint(savePath, "MechMessage\\", i, "e");
			else moveHint(savePath, "VanillaMessage\\", i, "e");
		}

	}
	return;
}

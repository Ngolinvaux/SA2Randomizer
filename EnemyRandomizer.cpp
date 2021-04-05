#include "stdafx.h"
#include "EnemyRandomizer.h"
#include "KartRando.h"


vector<ObjectFuncPtr> FlyingEnemyFunctionsAddress = {(ObjectFuncPtr)0x501530,(ObjectFuncPtr)0x7A0D10,(ObjectFuncPtr)0x7A21C0,(ObjectFuncPtr)0x4FC700,(ObjectFuncPtr)0x4F8F90};
vector<ObjectFuncPtr> GroundEnemyFunctionsAddress = {(ObjectFuncPtr)0x4FF990,(ObjectFuncPtr)0x50D790,(ObjectFuncPtr)0x7A1600,(ObjectFuncPtr)0x50A850,(ObjectFuncPtr)0x4FDD00,(ObjectFuncPtr)0x503140,(ObjectFuncPtr)0x50E4D0,(ObjectFuncPtr)0x50F150 };
vector<ObjectFuncPtr> MovingEnemyFunctionsAddress = {(ObjectFuncPtr)0x505C20,(ObjectFuncPtr)0x50C3F0 };

vector<ObjectFuncPtr> ValidChaoObjs = {};//TODO


vector<char*> EnemyNames = {"E KUMI","E AI"};

vector<ObjectListEntry*> StageObjLists = {
	{},
	{},
	{},
	GreenForestObjs,
	WhiteJungleObjs,
	PumpkinHillObjs,
	SkyRailObjs,
	AquaticMineObjs,
	SecurityHallObjs,
	PrisonLaneObjs,
	MetalHarborObjs,
	IronGateObjs,
	WeaponsBedObjs,
	CityEscapeObjs,
	RadicalHighwayObjs,
	{},
	WildCanyonObjs,
	MissionStreetObjs,
	DryLagoonObjs,
	{},
	{},
	SandOceanObjs,
	CrazyGadgetObjs,
	HiddenBaseObjs,
	EternalEngineObjs,
	DeathChamberObjs,
	EggQuartersObjs,
	LostColonyObjs,
	PyramidCaveObjs,
	{},
	FinalRushObjs,
	GreenHillZoneObjs,
	MeteorHerdObjs,
	{},
	CCSonicObjs,
	CCEggmanObjs,
	CCTailsObjs,
	CCRougeObjs,
	CCKnuxObjs,
	{},
	FinalChaseObjs,
	{},
	{},
	CosmicWallObjs,
	MadSpaceObjs
};


vector<int> StageObjListsLength = {
	0,
	0,
	0,
	GreenForestObjs_Length,
	WhiteJungleObjs_Length,
	PumpkinHillObjs_Length,
	SkyRailObjs_Length,
	AquaticMineObjs_Length,
	SecurityHallObjs_Length,
	PrisonLaneObjs_Length,
	MetalHarborObjs_Length,
	IronGateObjs_Length,
	WeaponsBedObjs_Length,
	CityEscapeObjs_Length,
	RadicalHighwayObjs_Length,
	0,
	WildCanyonObjs_Length,
	MissionStreetObjs_Length,
	DryLagoonObjs_Length,
	0,
	0,
	SandOceanObjs_Length,
	CrazyGadgetObjs_Length,
	HiddenBaseObjs_Length,
	EternalEngineObjs_Length,
	DeathChamberObjs_Length,
	EggQuartersObjs_Length,
	LostColonyObjs_Length,
	PyramidCaveObjs_Length,
	0,
	FinalRushObjs_Length,
	GreenHillZoneObjs_Length,
	MeteorHerdObjs_Length,
	0,
	CCSonicObjs_Length,
	CCEggmanObjs_Length,
	CCTailsObjs_Length,
	CCRougeObjs_Length,
	CCKnuxObjs_Length,
	0,
	FinalChaseObjs_Length,
	0,
	0,
	CosmicWallObjs_Length,
	MadSpaceObjs_Length
};






vector<int> stage0Chao = {};
vector<int> stage1Chao = {};
vector<int> stage2Chao = {};
vector<int> stage3Chao = {0,1,2,3,4,5,6,7,0x27};
vector<int> stage4Chao = {0,1,2,3,4,5,6,7,0xa,0xb};
vector<int> stage5Chao = {0,2,3,4,5,6,8,9,0xa};
vector<int> stage6Chao = {0,1,2,3,4,5,6,7,9,0xa,0x16};
vector<int> stage7Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xc,0xd };
vector<int> stage8Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage9Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage10Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage11Chao = {0,1,2,3,4,5,6,7,9,0xa};
vector<int> stage12Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage13Chao = {0,1,3,4,5,6,7,8,9,0xa,0xc,0xd};
vector<int> stage14Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage15Chao = {};
vector<int> stage16Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage17Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage18Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage19Chao = {};
vector<int> stage20Chao = {};
vector<int> stage21Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage22Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage23Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage24Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage25Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage26Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage27Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage28Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage29Chao = {};
vector<int> stage30Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage31Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage32Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage33Chao = {};
vector<int> stage34Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage35Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage36Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage37Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage38Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage39Chao = {};
vector<int> stage40Chao = { 0,1,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage41Chao = {};
vector<int> stage42Chao = {};
vector<int> stage43Chao = { 0,1,3,4,5,6,7,8,9,0xa,0xb,0xc,0xd };
vector<int> stage44Chao = { 0,1,3,4,5 };

vector < vector<int>>  stageAllChao = {

stage0Chao,
stage1Chao,
stage2Chao,
stage3Chao,
stage4Chao,
stage5Chao,
stage6Chao,
stage7Chao,
stage8Chao,
stage9Chao,
stage10Chao,
stage11Chao,
stage12Chao,
stage13Chao,
stage14Chao,
stage15Chao,
stage16Chao,
stage17Chao,
stage18Chao,
stage19Chao,
stage20Chao,
stage21Chao,
stage22Chao,
stage23Chao,
stage24Chao,
stage25Chao,
stage26Chao,
stage27Chao,
stage28Chao,
stage29Chao,
stage30Chao,
stage31Chao,
stage32Chao,
stage33Chao,
stage34Chao,
stage35Chao,
stage36Chao,
stage37Chao,
stage38Chao,
stage39Chao,
stage40Chao,
stage41Chao,
stage42Chao,
stage43Chao,
stage44Chao,
};

vector < int>  stageAllChaoID = {0,0,0,0x1f,0x1c,0xe,0xe,0xd,0xe,
	0xe,0xe,0xd,0xe,0xe,0xe,0,0xe,0xe,0xe,0,0,0xe,0xe,0xe,0xe,
	0xe,0xe,0xe,0xe,0,0xe,0xe,0xe,0,0xe,0xe,0xe,0xe,0xe,0,0xe,0,0,0xe,0xe
};


vector<int> stage0E = {};
vector<int> stage1E = {};
vector<int> stage2E = {};
vector<int> stage3E = {0x1c,0x1d,0x4b};
vector<int> stage4E = {0x2b,0x2c,0x47,0x48,};
vector<int> stage5E = {0x1d,0x1e,0x51,0x52};
vector<int> stage6E = {0x1d,0x1e,0xb,0x27,0x53};
vector<int> stage7E = {0x20,0x21,0x22};
vector<int> stage8E = { 0x38,0x39,0x3a,0x3b ,0x4b,0x4c};
vector<int> stage9E = { 0x38,0x39,0x3a,0x3b,0x50,0x51,0x52 ,0x53 ,0x54 ,0x55 ,0x56 ,0x57 ,0x58 ,0x59 ,0x5A,0x5F ,0x61 };
vector<int> stage10E = { 0x38,0x39,0x3A,0x3B };
vector<int> stage11E = {0x20,0x21,0x22,0x47,0x48,0x4c,0x4d,0x4e,0x4f,0x50,0x51,0x52,0x53,0x58};
vector<int> stage12E = { 0x38,0x39,0x3a,0x3b};
vector<int> stage13E = {0x38,0x39,0x5b,0x5d};
vector<int> stage14E = {0x38,0x39,0x58,};
vector<int> stage15E = {};
vector<int> stage16E = { 0x38,0x39,0x49 };
vector<int> stage17E = {0x37,0x38,0x3d,0x3e};
vector<int> stage18E = { 0x38,0x39,0x3a,0x3b};
vector<int> stage19E = {};
vector<int> stage20E = {};
vector<int> stage21E = { 0x38,0x39,0x3a,0x3b,0x55};
vector<int> stage22E = {0x3e,0x3f,0x40};
vector<int> stage23E = { 0x38,0x39,0x3A,0x3B,0x4d,0x4e,0x52};
vector<int> stage24E = { 0x38,0x39,0x3A,0x3B ,0x3c,0x56};
vector<int> stage25E = {0x37,0x38,0x3b,0x3d,0x52,0x53};
vector<int> stage26E = { 0x38,0x39,0x37,0x3b,0x4f,0x50,0x51 };
vector<int> stage27E = { 0x38,0x39,0x3a,0x3b,0x3c};
vector<int> stage28E = {0x38,0x39,0x3a,0x3b,0x3c};
vector<int> stage29E = {};
vector<int> stage30E = { 0x38,0x39,0x3a,0x3b,0x3c ,0x56 };
vector<int> stage31E = { 0x38,0x39,0x3a,0x3b,0x3c };
vector<int> stage32E = { 0x38,0x39,0x3a,0x3b,0x3c ,0x5c };
vector<int> stage33E = {};
vector<int> stage34E = { 0x38,0x39,0x3a,0x3b,0x3c ,0x4e,0x4f,0x50,0x51};
vector<int> stage35E = { 0x38,0x39,0x3a,0x3b,0x3f,0x4d,0x4e,0x4f };
vector<int> stage36E = { 0x38,0x39,0x3A,0x3B ,0x4c,0x4d,0x4e,0x4f};
vector<int> stage37E = { 0x38,0x39,0x47,0x49,0x4a};
vector<int> stage38E = { 0x38,0x39,0x3a,0x3c,0x4a,0x4b,0x4c,0x4d};
vector<int> stage39E = {};
vector<int> stage40E = { 0x38,0x39,0x3a,0x3b,0x3c,0x51};
vector<int> stage41E = {};
vector<int> stage42E = {};
vector<int> stage43E = { 0x38,0x39,0x3a,0x3b,0x36 ,0x37,0x3f };
vector<int> stage44E = { 0x38,0x39,0x3a,0x37,0x3d,0x3e,0x59,0x5a,0x5b };

vector < vector<int>>  stageAllE = {

stage0E,
stage1E,
stage2E,
stage3E,
stage4E,
stage5E,
stage6E,
stage7E,
stage8E,
stage9E,
stage10E,
stage11E,
stage12E,
stage13E,
stage14E,
stage15E,
stage16E,
stage17E,
stage18E,
stage19E,
stage20E,
stage21E,
stage22E,
stage23E,
stage24E,
stage25E,
stage26E,
stage27E,
stage28E,
stage29E,
stage30E,
stage31E,
stage32E,
stage33E,
stage34E,
stage35E,
stage36E,
stage37E,
stage38E,
stage39E,
stage40E,
stage41E,
stage42E,
stage43E,
stage44E
};


setObj swapObj(setObj o) {
	o.id = swap(o.id);
	o.xRot = swap(o.xRot);
	o.yRot = swap(o.yRot);
	o.zRot = swap(o.zRot);
	o.x = swap(o.x);
	o.y = swap(o.y);
	o.z = swap(o.z);
	o.v1 = swap(o.v1);
	o.v2 = swap(o.v2);
	o.v3 = swap(o.v3);
	return o;
}

int convertIntSwapped(char* num) {
	return ((unsigned char)num[0] << 24) | ((unsigned char)num[1] << 16) | ((unsigned char)num[2] << 8) | ((unsigned char)num[3]);
}
short convertShort(char* num) {
	return ((unsigned char)num[1] << 8) | ((unsigned char)num[0]);
}

vector<setObj> readSetObjs(string f) {
	vector<setObj> objects;

	char numObjs[4];
	char header[28];
	char id[2];
	char rotX[2];
	char rotY[2];
	char rotZ[2];
	char X[4];
	char Y[4];
	char Z[4];
	char v1[4];
	char v2[4];
	char v3[4];
	setObj obj;

	std::ifstream is2(f.c_str(), std::ios::binary | std::ios::in);
	if (is2.is_open()) {
		is2.read(numObjs, 4); 
		is2.ignore(28);
		int n = convertIntSwapped(numObjs);

		for (int i = 0; i < n; i++) {
			is2.read(id, 2);
			obj.id = convertShort(id);
			
			is2.read(rotX, 2);
			obj.xRot = convertShort(rotX);
			is2.read(rotY, 2);
			obj.yRot = convertShort(rotY);
			is2.read(rotZ, 2);
			obj.zRot = convertShort(rotZ);

			is2.read(X, 4);
			memcpy(&obj.x, &X, 4);
			is2.read(Y, 4);
			memcpy(&obj.y, &Y, 4);
			is2.read(Z, 4);
			memcpy(&obj.z, &Z, 4);


			is2.read(v1, 4);
			memcpy(&obj.v1, &v1, 4);
			is2.read(v2, 4);
			memcpy(&obj.v2, &v2, 4);
			is2.read(v3, 4);
			memcpy(&obj.v3, &v3, 4);

			obj = swapObj(obj);
			objects.push_back(obj);
		}


		is2.close();
	}

		
	return objects;
}

void writeOBJ2(setObj o, std::ofstream& bin) {
	writeOBJ(o.id, o.xRot, o.yRot, o.zRot, o.x, o.y, o.z, o.v1, o.v2, o.v3, bin);
}


bool inVector(int a, vector<int> v) {
	if (std::find(v.begin(), v.end(), a) != v.end()) return true;
	return false;
}


vector<setObj> randomizeChao(vector<setObj> objects, int stage) {

	int l = objects.size();
	int r = rand() % l;
	while(!inVector(objects[r].id, stageAllChao[stage])) r = rand() % l;
	



	for (int i = 0; i < l; i++) {
		if (objects[i].id == stageAllChaoID[stage] && objects[i].xRot == 1) {
			objects[i].x = objects[r].x + 1;
			objects[i].y = objects[r].y+15;
			if (objects[r].id == 0) objects[i].y -= 15;
			objects[i].z = objects[r].z + 1;
			return objects;
		}
	}





	return objects;
}




NJS_VECTOR randomizeEnemies(string savePath, int stage, bool chao,bool enemies, bool chaos) {

	NJS_VECTOR chaoLocation = { 0,0,0 };
	if (stage > 44) return chaoLocation;
	string folder = savePath + "\\gd_PC\\set00";
	if (stage < 10) folder += "0";
	if(MissionNum == 4) folder += std::to_string(stage) + "_hd_s.bin";
	else folder += std::to_string(stage) + "_s.bin";

	vector<setObj> objects = readSetObjs(folder);
	int len = objects.size();

	if (chao) objects = randomizeChao(objects, stage);
	for (int i = 0; i < len; i++) {
		if (objects[i].id == stageAllChaoID[stage] && objects[i].xRot == 1) {
			chaoLocation = { objects[i].x,objects[i].y,objects[i].z };
		}
	}

	unsigned short doorID = 0;
	for (int i = 0; i < StageObjListsLength[stage]; i++) {
		if (StageObjLists[stage][i].Function == (ObjectFuncPtr)0x778700 || StageObjLists[stage][i].Function == (ObjectFuncPtr)0x4D01C0 || StageObjLists[stage][i].Function == (ObjectFuncPtr)0x769930 || StageObjLists[stage][i].Function == (ObjectFuncPtr)0x788460) {
			doorID = i;
			PrintInt(doorID);
			//PrintDebug("^^^^\n\n\n\n");
		}
	}
	

	int subLen = 0;
	for (int i = 0; i < len; i++) {
		if (inVector(objects[i].id, stageAllE[stage])) {
			if (enemies && !isHuntingStagei(stage) && CurrentLevel != LevelIDs_MetalHarbor && CurrentLevel != LevelIDs_CannonsCoreS && CurrentLevel != LevelIDs_CrazyGadget) {
				subLen = stageAllE[stage].size();
				objects[i].id = stageAllE[stage][rand() % subLen];
			}
			if (isHuntingStagei(stage) && (enemies || chaos)) {
				objects[i].xRot &= 0x00FF;
				//objects[i].xRot &= 0x0011;
				objects[i].xRot |= 0xFF00;
			}
		}
		if (objects[i].id == doorID && ((enemies || chaos) || (isMechless(CurrentCharacter)&&CurrentLevel!=LevelIDs_LostColony))) {
			objects[i].zRot = 3;

		}
		if (CurrentLevel == LevelIDs_EternalEngine) {
			if (objects[i].id == 0x49 && ((enemies || chaos) || isMechless(CurrentCharacter))) {
				objects[i].zRot = 3;

			}
		}
		if (CurrentLevel == LevelIDs_PrisonLane) {
			if ((objects[i].id == 0x4A || objects[i].id == 0x4B)&& (enemies || chaos)) {
				objects[i].xRot = -1;

			}
		}
		if (objects[i].id == 0x38 &&  CurrentLevel == LevelIDs_CosmicWall && MissionNum == 4) {
			objects[i].zRot *= 3;
			objects[i].v3 /= 3;

		}
	}
	



	std::ofstream bin(folder, std::ios::binary);
	writeToBin((unsigned int)len, bin);
	for (int i = 0; i < 7; i++) writeToBin((unsigned int)0, bin);
	for (int i = 0; i < len; i++) {
		writeOBJ2(objects[i], bin);
	}
	bin.close();

	if ((enemies || chaos) && !isHuntingStagei(stage)) {
		for (int i = 0; i < StageObjListsLength[CurrentLevel]; i++) {
			//PrintDebug("I LOVE BABE\n");
			if(!isSpeed(CurrentCharacter) || (CurrentLevel != LevelIDs_MetalHarbor && CurrentLevel != LevelIDs_CannonsCoreS && CurrentLevel != LevelIDs_CrazyGadget))
				if (find(FlyingEnemyFunctionsAddress.begin(), FlyingEnemyFunctionsAddress.end(), StageObjLists[CurrentLevel][i].Function) != FlyingEnemyFunctionsAddress.end())
				StageObjLists[CurrentLevel][i].Function = FlyingEnemyFunctionsAddress[rand() % FlyingEnemyFunctionsAddress.size()];

			if (find(GroundEnemyFunctionsAddress.begin(), GroundEnemyFunctionsAddress.end(), StageObjLists[CurrentLevel][i].Function) != GroundEnemyFunctionsAddress.end())
				StageObjLists[CurrentLevel][i].Function = GroundEnemyFunctionsAddress[rand() % GroundEnemyFunctionsAddress.size()];

			if (!isSpeed(CurrentCharacter) || (CurrentLevel != LevelIDs_MetalHarbor && CurrentLevel != LevelIDs_CannonsCoreS && CurrentLevel != LevelIDs_CrazyGadget))
				if (find(MovingEnemyFunctionsAddress.begin(), MovingEnemyFunctionsAddress.end(), StageObjLists[CurrentLevel][i].Function) != MovingEnemyFunctionsAddress.end())
				StageObjLists[CurrentLevel][i].Function = MovingEnemyFunctionsAddress[rand() % MovingEnemyFunctionsAddress.size()];
			
			

		}
		
	}


	return chaoLocation;

}

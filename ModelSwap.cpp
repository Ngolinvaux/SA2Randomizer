#include "stdafx.h"
#include "ModelSwap.h"


vector<string> files;
vector<string> filesToBeDeleted;

std::vector<std::string> get_directories(const std::string& s)
{
	std::vector<std::string> r;
	for (auto& p : std::filesystem::recursive_directory_iterator(s))
		if (p.is_directory() && p.path().string().find("gd_PC") == string::npos) {
			r.push_back(p.path().string());
			//PrintDebug(p.path().string().c_str());
		}
	return r;
}



void get_files(const std::string& s)
{
	for (auto& p : std::filesystem::recursive_directory_iterator(s))
		if (p.is_regular_file())
			files.push_back(p.path().string());
}


const void* const loc_717028 = (const void*)0x717028;
__declspec(naked) void thing() {
	__asm {
		mov esi, [esp +0Ch]
		sub esp, 4
		jmp loc_717028
	}
}
const void* const loc_7287c0 = (const void*)0x7287c0;
__declspec(naked) void thingRouge() {
	__asm {
		mov esi, [esp +0Ch]
		sub esp, 4
		jmp loc_7287c0
	}
}
const void* const loc_717588 = (const void*)0x717588;
__declspec(naked) void thingShadow() {
	__asm {
		mov esi, [esp +0Ch]
		sub esp, 4
		jmp loc_717588
	}
}
const void* const loc_728399 = (const void*)0x728399;
__declspec(naked) void thingKnux() {
	__asm {
		mov esi, [esp +0Ch]
		sub esp, 4
		jmp loc_728399
	}
}
const void* const loc_49ab13 = (const void*)0x49ab13;
__declspec(naked) void thingSuperSonic() {
	__asm {
		
		sub esp, 4
		jmp loc_49ab13
	}
}


vector<ModelCredits> getAllInfo(int c, string path, int alt) {
	vector<string> dirs;
	//vector<string> files;
	vector<string> locs;
	string name;
	vector<ModelCredits> v;
	ModelCredits thisCred;
	thisCred.name = "nothing";
	thisCred.creator = "noone";
	switch (c) {
	case Characters_Shadow:
		if (alt ==  1) {
			name = "Metal";
			break;
		}
		name = "Shadow";
		break;
	case Characters_MechEggman:
		if (alt == 1) {
			name = "DChao";
			break;
		}
		name = "MechEgg";
		break;
	case Characters_Sonic:
		if (alt == 1) {
			name = "Amy";
			break;
		}
		name = "Sonic";
		break;
	case Characters_MechTails:
		if (alt == 1) {
			name = "Chao";
			break;
		}
		name = "MechTails";
		break;
	case Characters_Rouge:
		if (alt == 1) {
			name = "Chaos";
			break;
		}
		name = "Rouge";
		break;
	case Characters_Knuckles:
		if (alt == 1) {
			name = "Tikal";
			break;
		}
		name = "Knux";
		break;
	case Characters_Eggman:
		name = "Egg";
		break;
	case Characters_Tails:
		name = "Tails";
		break;
	case Characters_SuperSonic:
		name = "Super";
		break;
	default:
		return v;
	}
	dirs = get_directories(path + "\\Models\\" + name + "\\");
	if (dirs.empty()) return v;
	for (int i = 0; i < dirs.size(); i++) {
		string modelPath = dirs[i];
		//PrintDebug(modelPath.c_str());
		std::ifstream info;
		info.open((modelPath + "\\info.txt").c_str());
		if (info.is_open()) {
			getline(info, name);
			getline(info, thisCred.name);
			getline(info, thisCred.creator);
			
			transform(thisCred.name.begin(), thisCred.name.end(), thisCred.name.begin(), ::toupper);
			transform(thisCred.creator.begin(), thisCred.creator.end(), thisCred.creator.begin(), ::toupper);

			info.close();
		}

		v.push_back(thisCred);
	}
	return v;
}


void swapYoshi(string path, HelperFunctions& hf) {
	vector<string> dirs;
	string name;
	dirs = get_directories(path + "\\Models\\YoshiColors\\");
	//if (dirs.empty()) return thisCred;
	srand(time(NULL));
	string modelPath = dirs[rand() % dirs.size()];

	PrintDebug(modelPath.c_str());
	std::ifstream info;

	get_files(modelPath);
	for (auto f : files) {
		if (f.find("info.txt") == string::npos) {
			hf.ReplaceFile(("resource\\" + f.substr(f.find("gd_PC"))).c_str(), f.c_str());
			PrintDebug(("Replacing " + f).c_str());
		}

	}
	while (!files.empty()) {
		files.pop_back();
	}


}




int swapModel(int c, string path, HelperFunctions& hf) {
	string name;
	ModelCredits thisCred;
	thisCred.name = "nothing";
	thisCred.creator = "noone";
	string req;
	bool require = false;
	vector<string> dirs;
	//vector<string> files;
	vector<string> locs;
	switch (c) {
	case Characters_Shadow:
		if (AltCharacter[0] == 1) {
			name = "Metal";
			break;
		}
		name = "Shadow";
		break;
	case Characters_MechEggman:
		if (AltCharacter[0] == 1) {
			name = "DChao";
			break;
		}
		name = "MechEgg";
		break;
	case Characters_Sonic:
		if (AltCharacter[0] == 1) {
			name = "Amy";
			break;
		}
		name = "Sonic";
		break;
	case Characters_MechTails:
		if (AltCharacter[0] == 1) {
			name = "Chao";
			break;
		}
		name = "MechTails";
		break;
	case Characters_Rouge:
		if (AltCharacter[0] == 1) {
			name = "Chaos";
			break;
		}
		name = "Rouge";
		break;
	case Characters_Knuckles:
		if (AltCharacter[0] == 1) {
			name = "Tikal";
			break;
		}
		name = "Knux";
		break;
	case Characters_Eggman:
		name = "Egg";
		break;
	case Characters_Tails:
		name = "Tails";
		break;
	case Characters_SuperSonic:
		name = "Super";
		break;
	default:
		name = "Sonic";
		break;
	}
	dirs = get_directories(path + "\\Models\\" + name+"\\");
	//if (dirs.empty()) return thisCred;
	if (dirs.empty()) return 0;
	srand(time(NULL));
	string modelPath = dirs[rand() % dirs.size()];

	PrintDebug(modelPath.c_str());
	std::ifstream info;
	int alt = 1;

	info.open((modelPath+"\\info.txt").c_str());
	if (info.is_open()) {
		getline(info, req);
		if (req.compare("yes") == 0) require = true;
		else require = false;
		getline(info, thisCred.name);
		getline(info, thisCred.creator);
		getline(info, req);
		alt = stoi(req);
		//PrintInt(alt);
		info.close();
	}


	//WriteJump((void*)0x716FDD, thing);
	//WriteJump((void*)0x71753d, thingShadow);
	//WriteJump((void*)0x728346, thingKnux);
	//WriteJump((void*)0x728696, thingRouge);
	//WriteJump((void*)0x49aacb, thingSuperSonic);
	if (c == Characters_Sonic) {
		if(require) WriteJump((void*)0x716FDD, thing);
		else {
			WriteData<1>((void*)0x716FDD, 0xa1);
			WriteData<1>((void*)0x716FDE, 0xcc);
			WriteData<1>((void*)0x716FDF, 0x96);
			WriteData<1>((void*)0x716FE0, 0xde);
			WriteData<1>((void*)0x716FE1, 0x01);
		}
	}
	else if (c == Characters_SuperSonic) {
		if (require) WriteJump((void*)0x49aacb, thingSuperSonic);
		else {
			WriteData<1>((void*)0x49aacb, 0x8b);
			WriteData<1>((void*)0x49aacc, 0x15);
			WriteData<1>((void*)0x49aacd, 0x0c);
			WriteData<1>((void*)0x49aace, 0xa1);
			WriteData<1>((void*)0x49aacf, 0xde);
		}
	}
	else if (c == Characters_Knuckles) {
		if (require) WriteJump((void*)0x728346, thingKnux);
		else {
			WriteData<1>((void*)0x728346, 0xa1);
			WriteData<1>((void*)0x728347, 0x04);
			WriteData<1>((void*)0x728348, 0x9b);
			WriteData<1>((void*)0x728349, 0xde);
			WriteData<1>((void*)0x72834a, 0x01);
		}
	}

	//PrintDebug(modelPath.c_str());
	get_files(modelPath);
	for (auto f : files) {
		if (f.find("info.txt") == string::npos) {
			hf.ReplaceFile(("resource\\" + f.substr(f.find("gd_PC"))).c_str(), f.c_str());
			PrintDebug(("Replacing " + f).c_str());
		}
		
	}
	while (!files.empty()) {
		files.pop_back();
	}

	if (modelPath.find("Yoshi") != string::npos) {
		swapYoshi(path, hf);
	}


	//return thisCred;
	if (alt) PrintDebug("Skin Available");

	return alt;
}
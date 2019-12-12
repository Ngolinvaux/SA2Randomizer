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

vector<ModelCredits> getAllInfo(int c, string path) {
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



ModelCredits swapModel(int c, string path, HelperFunctions& hf) {
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
		name = "Shadow";
		break;
	case Characters_MechEggman:
		name = "MechEgg";
		break;
	case Characters_Sonic:
		name = "Sonic";
		break;
	case Characters_MechTails:
		name = "MechTails";
		break;
	case Characters_Rouge:
		name = "Rouge";
		break;
	case Characters_Knuckles:
		if (AltCharacter[0] == 1) {
			name = "Tikal";
			break;
		}
		name = "Knux";
		break;
	default:
		return thisCred;
	}
	dirs = get_directories(path + "\\Models\\" + name+"\\");
	if (dirs.empty()) return thisCred;
	srand(time(NULL));
	string modelPath = dirs[rand() % dirs.size()];

	PrintDebug(modelPath.c_str());
	std::ifstream info;
	info.open((modelPath+"\\info.txt").c_str());
	if (info.is_open()) {
		info >> req;
		if (req.compare("yes") == 0) require = true;
		else require = false;
		info >> thisCred.name;
		info >> thisCred.creator;

		info.close();
	}


	if(require) WriteJump((void*)0x716FDD, thing);


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
	return thisCred;
}
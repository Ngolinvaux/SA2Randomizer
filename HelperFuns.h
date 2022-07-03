
#ifndef HELPERFUNS_H_
#define HELPERFUNS_H_


#include "stdafx.h"
#include "SA2Rando.h"
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
#include "BossTitles.h"
#include "RankVoices.h"


#define altcostume 0x80u
#define altcharacter 0x40
#define charmask ~(altcostume|altcharacter)

using std::vector;
using std::string;
using std::unordered_map;
using std::transform;
using std::shuffle;

TwitchChatter FirstCurrency(TwitchChatter tc, vector<int> rates);
vector<string> setUpMods(string path);
vector<int> setUpRates(string path);
TwitchChatter UpdateCurrency(TwitchChatter tc, vector<int> rates);
unordered_map<string, TwitchChatter> startUpScores(string path);
unordered_map<string, int> GetCommandCosts(string path);
TwitchMsg parseChat(string s);
string lowerCase(string data);
int returnSameCharLine(int line);

int isAttacking();
int returnMainCharLine(int line);
int sizeOfArray(int* a);
int returnSameCharALLGAMELine(int line);
bool isOmochaoLine(int i);
bool isMariaLine(int i);
void PrintPos(NJS_VECTOR a);
void PrintInt(int a);
void PrintF(float a);
int isIn(int a, int* b,int size);
bool isMech(int i);
bool isMechless(int i);
bool isSpeed(int i);
bool isHunt(int i);
bool sameType(int i, int r);
bool isBoss();
double dist(NJS_VECTOR a, NJS_VECTOR b);
float findClosestMM(int MMID);
boolean isHuntingStage();
int isHuntingStageInt();
boolean isHuntingStagei(int CurrentLevel);
void setUpSuper();
void fixSuper();
void createSplits(vector<StoryEntry>& stages, std::string category, bool showN);
std::string stageNumToName(int num);
void LogThis(std::string file, int seed, vector<StoryEntry>** stories);
int stageToChar(int stage);


#endif
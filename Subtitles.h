#ifndef SUBTITLES_H_
#define SUBTITLES_H_


#include "stdafx.h"
#include "HelperFuns.h"

vector<SubtitleQueue>  formatStr(string s, int charLineLimit, int a);
int timeOfVl(string s, int id);
vector<SubtitleQueue>  vl2Text(int a,bool tag);
std::vector<SubtitleQueue> displaySub(int r, int style,bool tag);
int vlBasedOnTime(int idx, double tolerance);
int randVoiceC(int a, int vlRandoType);
#endif

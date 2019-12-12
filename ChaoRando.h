#ifndef CHAORANDO_H
#define CHAORANDO_H
#include "HelperFuns.h"


byte encodeLetter(char a);

ChaoDataBaseGap randomizeChao(ChaoDataBaseGap cdb);
ChaoDataBaseGap animalChao(ChaoDataBaseGap cdb);
ChaoDataBaseGap maxChao(ChaoDataBaseGap cdb);
struct_a1R randomKarateChao(int idx, struct_a1R kChao);
RaceBotData randomRaceChao(int idx, RaceBotData rChao);
#endif
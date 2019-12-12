#ifndef STAGEVARIANTS_H
#define STAGEVARIANTS_H
#include "HelperFuns.h"

void moveMessage(string from, string to, string file);
void soHints(int i, string savePath);
void vanHints(int i, string savePath);
void mechHints(int i, string savePath);
void copyFileBin(const char* f, const char* num, string savePath);
void setSonicStages(int defaultcharacters[]);
void setShadowStages(int defaultcharacters[]);
void setKnuxStages(int defaultcharacters[], string savePath);
void setRougeStages(int defaultcharacters[], string savePath);
void setEggmanStages(int defaultcharacters[]);
void setTailsStages(int defaultcharacters[]);
void setStages(int defaultcharacters[], string savePath);
void stageV(int defaultcharacters[], string savePath);
void resetStageV();
void moveHint(string savePath, string folder, int stage, string lang);
void charPerStage(int chars[], string savePath);

#endif






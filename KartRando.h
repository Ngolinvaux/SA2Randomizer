#ifndef KartRando_H_
#define KartRando_H_


#include "stdafx.h"
#include "HelperFuns.h"

template<typename T>
T swap(T d);


template<typename T>
void writeToBin(T a, std::ofstream& b);
void writeOBJ(unsigned short id, unsigned short xRot, unsigned short yRot, unsigned short zRot, float x, float y, float z, float v1, float v2, float v3, std::ofstream& bin);
void placeObjects(string savepath, int idx, int length);
void PrintTrack(vector<KartSegment> t, int length, int idx);
void randomizeKartStats();
float distance(NJS_VECTOR a, NJS_VECTOR b);
bool checkCollision(vector<KartSegment> trackSoFar, KartSegment current);
int getSize(byte* arr);
void setTrack(vector<byte> tra, vector<KartSegment> tr, int idx, int length);
float radiusCalc(NJS_VECTOR a);
NJS_VECTOR rotatePiece(NJS_VECTOR a, unsigned short rot);
void createTrack(int t, string savepath,int min,int max);

#endif
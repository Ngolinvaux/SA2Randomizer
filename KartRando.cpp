#include "stdafx.h"
#include "KartRando.h"



vector<KartSegment> track;
vector<byte> trackIDs;

vector<KartSegment> track280;
vector<byte> trackIDs280;

vector<KartSegment> trackEasy;
vector<byte> trackIDsEasy;

vector<KartSegment> trackMed;
vector<byte> trackIDsMed;

vector<KartSegment> trackHard;
vector<byte> trackIDsHard;

byte straight_next[45] = {
	0x01, 0x02, 0x03, 0x05, 0x07, 0x08, 0x32, 0x0a,
		0x0b, 0x0e, 0x0f, 0x11, 0x12, 0x13, 0x15, 0x17,
		0x1a, 0x1c, 0x1d, 0x20, 0x21, 0x22,
		0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
		0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x09,
		0x48, 0x4b, 0x51, 0x52, 0x53, 0x54, 0x00
};


byte straight_next_noTunnelStart[44] = {
	0x01, 0x02, 0x03, 0x05, 0x07, 0x08, 0x0a,
		0x0b, 0x0e, 0x0f, 0x11, 0x12, 0x13, 0x15, 0x17,
		0x1a, 0x1c, 0x1d, 0x20, 0x21, 0x22,
		0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
		0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x09,
		0x48, 0x4b, 0x51, 0x52, 0x53, 0x54, 0x00
};

byte tunnel_next[8] = {
	0x33, 0x34, 0x35, 0x36, 0x37, 0x3c, 0x3f,0x00
};

byte tunnel_narrow_next[9] = {
	0x38, 0x39, 0x3a, 0x3b, 0x42, 0x45, 0x38, 0x00
};

byte arrray0406[3] = { 0x04, 0x06 ,0x00 };
byte arrray50[2] = { 0x50,0x00 };
byte arrray0c14[3] = { 0x0c, 0x14 ,0x00 };
byte arrray0d16[3] = { 0x0d, 0x16 ,0x00 };
byte arrray1018[3] = { 0x10, 0x18 ,0x00 };
byte arrray3d3e[3] = { 0x3d, 0x3e ,0x00 };
byte arrray4041[3] = { 0x40, 0x41 ,0x00 };
byte arrray4344[3] = { 0x43, 0x44 ,0x00 };
byte arrray4647[3] = { 0x46, 0x47 ,0x00 };
byte arrray49af[4] = { 0x49,0x4a,0x4f,0x00 };
byte arrray4cde[4] = { 0x4c,0x4d,0x4e ,0x00 };

byte* next_map[85] = {
		{},
		straight_next,
		straight_next,
		straight_next,
		arrray0406,
		arrray0406,
		straight_next,
		straight_next,
		straight_next,
		arrray50,
		straight_next,
		straight_next,
		arrray0c14,
		arrray0d16,
		straight_next,
		straight_next,
		arrray1018,
		straight_next,
		straight_next,
		arrray0c14,
		straight_next,
		arrray0d16,
		straight_next,
		arrray1018,
		straight_next,
		{},
		straight_next_noTunnelStart,
		{},
		straight_next,
		straight_next,
		arrray0406,
		arrray0406,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		tunnel_next,
		straight_next_noTunnelStart,
		tunnel_next,
		tunnel_next,
		tunnel_next,
		tunnel_narrow_next,
		tunnel_next,
		tunnel_narrow_next,
		tunnel_narrow_next,
		tunnel_narrow_next,
		arrray3d3e,
		arrray3d3e,
		tunnel_next,
		arrray4041,
		arrray4041,
		tunnel_next,
		arrray4344,
		arrray4344,
		tunnel_narrow_next,
		arrray4647,
		arrray4647,
		tunnel_narrow_next,
		arrray49af,
		arrray49af,
		straight_next,
		arrray4cde,
		arrray4cde,
		straight_next,
		arrray4cde,
		arrray49af,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
		straight_next,
};

DataArray(KartCourseModel, offsetTable, GetProcAddress(**datadllhandle, "CartCourseModels"), 0x55);

template<typename T>
T swap(T d)
{
	T a;
	unsigned char *dst = (unsigned char *)&a;
	unsigned char *src = (unsigned char *)&d;

	for (int i = 0; i < sizeof(d); i++)
		dst[i] = src[sizeof(d) - 1 - i];

	return a;
}


template<typename T>
void writeToBin(T a, std::ofstream& b) {
	a = swap(a);
	b.write(reinterpret_cast <const char*>(&a), sizeof(a));
}


void writeOBJ(unsigned short id, unsigned short xRot, unsigned short yRot, unsigned short zRot, float x, float y, float z, float v1, float v2, float v3, std::ofstream& bin) {
	writeToBin(id, bin);
	writeToBin(xRot, bin);
	writeToBin(yRot, bin);
	writeToBin(zRot, bin);
	writeToBin(x, bin);
	writeToBin(y, bin);
	writeToBin(z, bin);
	writeToBin(v1, bin);
	writeToBin(v2, bin);
	writeToBin(v3, bin);
}



void placeObjects(string savepath,int idx,int length) {
	string folder = savepath + "\\gd_PC\\";
	vector<KartSegment>* temp;
	switch (idx) {
	case 0:
		folder += "setCartTails.bin";
		temp = &track;
		break;
	case 1:
		folder += "setCartRouge.bin";
		temp = &track280;
		break;
	case 2:
		folder += "setCartMini1.bin";
		temp = &trackEasy;
		break;
	case 3:
		folder += "setCartMini2.bin";
		temp = &trackMed;
		break;
	case 4:
		folder += "setCartMini3.bin";
		temp = &trackHard;
		break;
	default:
		return;
	}
	std::ofstream bin(folder, std::ios::binary);

	int balloons = std::round(length / 20);
	

	if(idx < 2) writeToBin((unsigned int) 3+balloons, bin);
	else writeToBin((unsigned int)4 + balloons, bin);

	for(int i = 0; i < 7; i++) writeToBin((unsigned int) 0,bin);
	writeOBJ(4, 0, temp->at(length / 3).yRot, 0, temp->at(length / 3).endPos.x, temp->at(length / 3).endPos.y, temp->at(length / 3).endPos.z, 0, 80, 0, bin);

	writeOBJ(4, 0, temp->at(2* length / 3).yRot, 0, temp->at(2 * length / 3).endPos.x, temp->at(2 * length / 3).endPos.y, temp->at(2 * length / 3).endPos.z, 0, 80, 0, bin);
	if(idx > 1)	writeOBJ(4, 0, temp->at(length - 1).yRot, 0, temp->at(length - 1).endPos.x, temp->at(length -1).endPos.y, temp->at(length - 1).endPos.z, 0, 80, 0, bin);

	
	writeOBJ(6, 0, 0, 0, 0, 0, 0, 0, 0, 0, bin);
	for (int i = 0; i < balloons; i++) writeOBJ(0x9, 3, 0, 0,temp->at(length*i/balloons).endPos.x, temp->at(length*i / balloons).endPos.y+25, temp->at(length*i / balloons).endPos.z,70,0,0,bin);
	bin.close();
	
	
	if (idx < 2) {
		folder = savepath;
		if (idx == 0) {
			folder += "\\gd_PC\\setCartTails_hd.bin";
			temp = &track;
		}
		if (idx == 1) {
			folder += "\\gd_PC\\setCartRouge_hd.bin";
			temp = &track280;
		}
		std::ofstream bin(folder, std::ios::binary);

		int balloons = std::round(length / 20);


		if (idx < 2) writeToBin((unsigned int)3 + balloons, bin);
		else writeToBin((unsigned int)4 + balloons, bin);

		for (int i = 0; i < 7; i++) writeToBin((unsigned int)0, bin);
		writeOBJ(4, 0, temp->at(length / 3).yRot, 0, temp->at(length / 3).endPos.x, temp->at(length / 3).endPos.y, temp->at(length / 3).endPos.z, 0, 80, 0, bin);

		writeOBJ(4, 0, temp->at(2 * length / 3).yRot, 0, temp->at(2 * length / 3).endPos.x, temp->at(2 * length / 3).endPos.y, temp->at(2 * length / 3).endPos.z, 0, 80, 0, bin);
		if (idx > 1)	writeOBJ(4, 0, temp->at(length - 1).yRot, 0, temp->at(length - 1).endPos.x, temp->at(length - 1).endPos.y, temp->at(length - 1).endPos.z, 0, 80, 0, bin);


		writeOBJ(6, 0, 0, 0, 0, 0, 0, 0, 0, 0, bin);
		for (int i = 0; i < balloons; i++) writeOBJ(0x9, 3, 0, 0, temp->at(length * i / balloons).endPos.x, temp->at(length * i / balloons).endPos.y + 25, temp->at(length * i / balloons).endPos.z, 70, 0, 0, bin);
		bin.close();
	}


}


void PrintTrack(vector<KartSegment> t,int length,int idx) {
	FILE* pfile;
	string name;
	switch (idx) {
	case 0:
		name = "ZZZr101.txt";
		break;
	case 1:
		name = "ZZZr280.txt";
		break;
	case 2:
		name = "ZZZkartEasy.txt";
		break;
	case 3:
		name = "ZZZkartMed.txt";
		break;
	case 4:
		name = "ZZZkartHard.txt";
		break;
	}
	pfile = fopen(name.c_str(), "w");
	for (int i = 0; i < length; i++) {
		fprintf(pfile,"Piece %i\n", i);
		fprintf(pfile, "----ID %x\n",t[i].segmentID);
		fprintf(pfile, "----yRot %d\n", t[i].yRot);
		fprintf(pfile, "----End %0.2f , %0.2f , %0.2f\n",t[i].endPos.x, t[i].endPos.y, t[i].endPos.z);
		fprintf(pfile, "----Center %0.2f , %0.2f , %0.2f\n", t[i].center.x, t[i].center.y, t[i].center.z);
		fprintf(pfile, "----Radius %0.2f\n\n", t[i].radius);
	}
	fclose(pfile);
}


void randomizeKartStats() {
	for (int i = 0; i < karts_Length; i++) {
		karts[i].accel *= float((rand() % 300 + 100) / 100.0);
		karts[i].speed_cap *= float((rand() % 400 + 100) / 100.0);
		karts[i].maxDriveSpeed *= float((rand() % 500 + 100) / 100.0);
	}
	for (int i = 0; i < kartAlts_Length; i++) {
		kartAlts[i].accel *= float((rand() % 300 + 100) / 100.0);
		kartAlts[i].speed_cap *= float((rand() % 400 + 100) / 100.0);
		kartAlts[i].maxDriveSpeed *= float((rand() % 500 + 100) / 100.0);
	}

}


float distance(NJS_VECTOR a, NJS_VECTOR b) {
	return pow(pow(a.x - b.x, 2) + pow(0.5*(a.y - b.y), 2) + pow(a.z - b.z, 2), 0.5);
}


bool checkCollision(vector<KartSegment> trackSoFar, KartSegment current) {
	for (int i = 0; i < trackSoFar.size() - 2; i++) {
		if (distance(current.center, trackSoFar[i].center) < (current.radius + trackSoFar[i].radius)) return true;
		if (distance(current.endPos, trackSoFar[i].endPos) < (current.radius + trackSoFar[i].radius)) return true;
	}
	return false;
}



int getSize(byte* arr) {
	int s = 0;
	while (*arr != NULL) {
		arr++;
		s++;
	}
	return s;
}

void setTrack(vector<byte> tra, vector<KartSegment> tr, int idx, int length) {
	PrintTrack(tr, length,idx);
	for (int i = 0; i < length; i++) {
		//tra.push_back(tr[i].segmentID);
		if(idx == 0) trackIDs.push_back(tr[i].segmentID);
		else if (idx == 1) trackIDs280.push_back(tr[i].segmentID);
		else if(idx == 2) trackIDsEasy.push_back(tr[i].segmentID);
		else if (idx == 3) trackIDsMed.push_back(tr[i].segmentID);
		else if (idx == 4) trackIDsHard.push_back(tr[i].segmentID);
	}
	tracks[idx].len = length;
	//tracks[idx].ptr = &tra[0];
	if (idx == 0) tracks[idx].ptr = &trackIDs[0];
	else if (idx == 1) tracks[idx].ptr = &trackIDs280[0];
	else if (idx == 2) tracks[idx].ptr = &trackIDsEasy[0];
	else if (idx == 3) tracks[idx].ptr = &trackIDsMed[0];
	else if (idx == 4) tracks[idx].ptr = &trackIDsHard[0];

}


float radiusCalc(NJS_VECTOR a) {
	return pow(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2), 0.5) / 2.0;
}

NJS_VECTOR rotatePiece(NJS_VECTOR a, unsigned short rot) {
	double pi = 3.14159265359;
	double rad = ((2.0 * pi) / (double)0x10000)*rot;
	float newX = a.z*sin(rad) + a.x*cos(rad);
	float newZ = a.z*cos(rad) - a.x*sin(rad);
	return { newX,a.y,newZ };
}

void createTrack(int t,string savepath,int min,int max) {
	//int length = rand() % 162 + 100;
	if (min < 30) min = 30;
	if (max <= min) max = min+1;
	int length = rand() % (max-min) + min;
	int current = 0;
	byte currentPiece;

	KartSegment currentSegment;

	int nextLen;
	unsigned short totalRot = 0;
	float X = 0;
	float Y = 0;
	float Z = 0;
	int N = 4;
	int tempN = N;
	byte endingPieces[8] = { 0x03,0x03,0x03,0x03,0x03,0x03,0x09,0x03 };
	vector<KartSegment>* tempTrack;
	vector<byte>* tempIDs;

	switch(t){
	case 0:
		tempTrack = &track;
		tempIDs = &trackIDs;
		break;
	case 1:
		tempTrack = &track280;
		tempIDs = &trackIDs280;
		break;
	case 2:
		tempTrack = &trackEasy;
		tempIDs = &trackIDsEasy;
		break;
	case 3:
		tempTrack = &trackMed;
		tempIDs = &trackIDsMed;
		break;
	case 4:
		tempTrack = &trackHard;
		tempIDs = &trackIDsHard;
		break;
	}

	std::ifstream info;
	vector<int> disabledPieces;
	info.open((savepath + "\\disableSegments.txt").c_str());
	if (info.is_open()) {
		string s;
		while (info >> s) {
			disabledPieces.push_back(std::stoi(s, 0, 16));
			//PrintInt(std::stoi(s,0,16));
			//PrintDebug(s.c_str());
		}
		

		info.close();
	}




	while (current < length) {
		if (current < 5) currentPiece = 0x03;
		else if (current > length - 25 && t < 2) {
			if (currentPiece == 0x09) currentPiece = 0x50;
			else currentPiece = endingPieces[rand() % 8];
		}
		else if (current > length - 28 && t < 2) {
			if (totalRot == 0xE000) currentPiece = 0x23; //45 right
			else if (totalRot == 0xA000) currentPiece = 0x22; //45 left
			else if (totalRot == 0x0000) currentPiece = 0x21; //90 right
			else if (totalRot == 0x2000)currentPiece = 0x23; //45 right
			else if (totalRot == 0x4000)currentPiece = 0x20; //90 left
			else if (totalRot == 0x6000)currentPiece = 0x22; //45 left
			else if (totalRot == 0x8000)currentPiece = 0x20; //90 left
			else currentPiece = 0x01; //straight
			//if (current == length - 25) PrintInt(totalRot);
		}
		else if (current > length - 2 && t > 1) {
			currentPiece = 0x01;
		}
		else {
			//PrintDebug("Piece:");
			//PrintInt(currentPiece);
			//PrintDebug("Array Size:");
			//PrintInt(getSize(next_map[currentPiece]));
			byte op = currentPiece;
			currentPiece = next_map[currentPiece][rand() % getSize(next_map[currentPiece])];
			while(std::find(disabledPieces.begin(), disabledPieces.end(),currentPiece) != disabledPieces.end()) currentPiece = next_map[op][rand() % getSize(next_map[op])];
		}
		{//following stuff
			//if (t == 4 && current == 122) {
			//	totalRot = 1;
			//}
			NJS_VECTOR newOffset = rotatePiece(offsetTable[currentPiece].end_point, totalRot);

			totalRot += offsetTable[currentPiece].y_rot;
			totalRot %= 0x10000;

			currentSegment.center.x = (X + X + newOffset.x) / 2;
			currentSegment.center.y = (Y + Y + newOffset.y) / 2;
			currentSegment.center.z = (Z + Z + newOffset.z) / 2;


			X += newOffset.x;
			Y += newOffset.y;
			Z += newOffset.z;

			currentSegment.segmentID = currentPiece;
			currentSegment.yRot = totalRot;
			currentSegment.endPos.x = X;
			currentSegment.endPos.y = Y;
			currentSegment.endPos.z = Z;
			currentSegment.radius = radiusCalc(offsetTable[currentPiece].end_point);
			if (currentPiece >= 0x50 || currentPiece == 0x09) currentSegment.radius *= 1;

			//PrintInt(currentPiece);

			if (current > length - 28) N = 28+tempN;
			else N = tempN;


			if (current < N + 1) tempTrack->push_back(currentSegment);
			if (current > N) {
				if (!checkCollision(*tempTrack, currentSegment)) tempTrack->push_back(currentSegment);
				else {
					current -= (N + 1);
					for (int i = 0; i < N; i++) tempTrack->pop_back();
					currentPiece = tempTrack->back().segmentID;
					totalRot = tempTrack->back().yRot;
					X = tempTrack->back().endPos.x;
					Y = tempTrack->back().endPos.y;
					Z = tempTrack->back().endPos.z;
				}

			}

		}
		//PrintInt(currentPiece);
		current++;
	}

	setTrack(*tempIDs,*tempTrack, t, length);
	placeObjects(savepath,t,length);
}

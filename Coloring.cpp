#include "stdafx.h"
#include "Coloring.h"







DataPointer(NJS_ARGB, constMaterial, 0x25effd0);
DataPointer(int, njControl3D, 0x25F02D8);
int storenjControl;
NJS_ARGB color;
float increment = 0.0;
bool up = true;
bool set = false;

void pickColor() {
	color.a = 1.0;
	color.r = (rand() % 1001) / 1000.0;
	color.g = (rand() % 1001) / 1000.0;
	color.b = (rand() % 1001) / 1000.0;

}
void setEColor(int r, int g, int b) {
	color.a = 1.0;
	color.r = r / 255.0;
	color.g = g / 255.0;
	color.b = b / 255.0;
	set = true;
}

void setColor() {
	//PrintDebug("set");
		
		constMaterial = color;
		if (isHuntingStage()) {
			OnControl3D(0x10);
			increment += 0.000008;

		}
		if ((isHuntingStage() && !set) || !isHuntingStage()) {
			increment += 0.00000001;
			if (up) {
				if (color.r < 1) color.r += increment;
				else if (color.g < 1) color.g += increment;
				else if (color.b < 1) color.b += increment;
				else {
					up = false;
					increment = 0.0;
				}
			}
			else {
				if (color.r > 0.1) color.r -= increment;
				else if (color.g > 0.1) color.g -= increment;
				else if (color.b > 0.1) color.b -= increment;
				else {
					up = true;
					increment = 0.0;
				}
			}
		}
	
}

void resetColor() {
	OffControl3D(0x10);
	//PrintDebug("resret");
	
}


static void __declspec(naked) setEmeraldColoring() {
	__asm {
		pushad
		pushfd
		call setColor
		popfd
		popad
		
		sub esp,0x10
		xor eax,eax

		push 0x6d02f5
		ret

	}
}

static void __declspec(naked) resetEmeraldColoring() {
	__asm {
		pushad
		pushfd
		call resetColor
		popfd
		popad
		ret
	}
}


DataPointer(int, d, 0x1a4a918);
static void __declspec(naked) setBallColoring() {
	__asm {
		pushad
		pushfd
		call setColor
		popfd
		popad

		cmp esi,d

		push 0x66fc32
		ret

	}
}



void initColoring() {
	pickColor();
	WriteJump((void*)0x6d02f0, setEmeraldColoring);
	WriteJump((void*)0x6d0314, resetEmeraldColoring);
	//WriteData<2>((void*)0x73b4b3, 0x90); //remove emerald get sign
	WriteData<1>((void*)0x6d26f4, 0x0f); // slow down strobe
	//WriteData<5>((void*)0x6d0282, 0x90); // remove strobe
	//WriteData<5>((void*)0x66fc1b, 0x90); // remove menu balls
	


	//WriteJump((void*)0x66f5fb, setBallColoring);
	WriteJump((void*)0x66fc2c, setBallColoring);
	//WriteJump((void*)0x6bf610, setOmochaoColoring);

}
void onFrameColoring() {
}
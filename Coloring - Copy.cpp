#include "stdafx.h"
#include "Coloring.h"







DataPointer(NJS_ARGB, constMaterial, 0x25effd0);
DataPointer(int, njControl3D, 0x25F02D8);
int storenjControl;

void setColor() {
	njControl3D_Add(0x10);
	constMaterial.a = 1.0;
	constMaterial.r = 1.0;
	constMaterial.g = 1.0;
	constMaterial.b = 0.0;

}

void resetColor() {
	PrintDebug("reset");
	njControl3D_Remove(0x10);
}


static void __declspec(naked) setEmeraldColor() {
	__asm {
		pushad
		pushfd
		call setColor
		popfd
		popad
		mov ecx, dword ptr [ebx + 0x40]
		mov eax, dword ptr [ebx + 0x34]
		push 0x6d265b
		ret
	}
}





static void __declspec(naked) resetEmeraldColor() {
	__asm {
		pushad
		pushfd
		call resetColor
		popfd
		popad

		ret
	}
}

static void __declspec(naked) resetEmeraldColor2() {
	__asm {
		pushad
		pushfd
		call resetColor
		popfd
		popad

		add esp, 0x10
		ret
	}
}

DataPointer(int, DAT_01a5a3d0, 0x1a5a3d0);
static void __declspec(naked) resetEmeraldColor3() {
	__asm {
		pushad
		pushfd
		call resetColor
		popfd
		popad

		cmp dword ptr [DAT_01a5a3d0], 0x0
		push 0x6d00f4
		ret
	}
}


void initColoring() {
	WriteJump((void*)0x6d2655, setEmeraldColor);
	WriteJump((void*)0x6d0314, resetEmeraldColor); // reset when not on screen
	WriteJump((void*)0x4931e6, resetEmeraldColor2);
	WriteJump((void*)0x6d00ed, resetEmeraldColor3);
}
void onFrameColoring() {
}
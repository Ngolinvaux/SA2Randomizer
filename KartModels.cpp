#include "stdafx.h"
#include "KartModels.h"



#include <random>


struct KartObjData
{
	int a1;
	int CharID;
	int var_1C;
	float var_18;
	float var_14;
	float var_10;
	int var_C;
	int var_8;
	int var_4;
};

int kartchars[6];
void __cdecl sub_61AE20(int a1)
{
	signed int v1; // ebp
	int v2; // esi
	char v3; // cl
	int v5; // eax
	double v6; // st7
	ObjectMaster* v7; // eax
	KartObjData a1a; // [esp+2Ch] [ebp-24h]
	ObjectMaster** v10; // [esp+54h] [ebp+4h]

	*(int*)0x1D96D20 = 0;
	*(int*)0x1D96D24 = 0;
	*(int*)0x1D96D28 = 0;
	*(int*)0x1D96D2C = 0;
	*(int*)0x1D96D30 = 0;
	*(int*)0x1D96D34 = 0;
	if (a1)
	{
		v1 = 1;
		*(int*)0x1D96F40 = 1;
		*(int*)0xEF5AA0 = 0;
	}
	else
	{
		v1 = 6;
		*(int*)0x1D96F40 = 0;
		*(int*)0xEF5AA0 = 1;
	}
	v2 = 0;
	*(int*)0x1D96F48 = 0;
	*(int*)0x1D96F4C = 0;
	if (v1 > 0)
	{
		v10 = (ObjectMaster * *)0x1D9443C;
		do
		{
			v3 = TwoPlayerMode;
			a1a.CharID = kartchars[v2];
			a1a.var_1C = v2;
			a1a.var_18 = (float)((v2 % 2) * -80.0 + 30.0);
			a1a.var_14 = 6.0;
			if (v3 && v2 < 2)
			{
				v6 = -100.0;
			}
			else
			{
				v6 = -100.0 - (40.0 * v2);
			}
			a1a.var_10 = (float)v6;
			a1a.var_C = 0;
			a1a.var_8 = 0;
			a1a.var_4 = 0;
			a1a.a1 = v2 < SplitscreenMode;
			v7 = LoadCartExecuter(&a1a);
			((ObjectMaster * *)0x1D96D20)[v2] = v7;
			if (a1a.a1)
			{
				*v10 = v7;
				v10 += 4;
			}
			++v2;
		} while (v2 < v1);
	}
	memset((int*)0x1A36650, 0, 0x5A0u);
	memset((int*)0x1A35EC8, 0, 0x5A0u);
	*(int*)0x1A36C18 = 0;
	*(int*)0x1A36C1C = 0;
	memset((int*)0x1A36468, 0, 0x1E0u);
	*(int*)0x1A36648 = 0;
	*(int*)0x1A3664C = 0;
}

// void __usercall(signed int a1@<ebx>)
static const void* const sub_61D3F0Ptr = (void*)0x61D3F0;
static inline void sub_61D3F0(signed int a1)
{
	__asm
	{
		mov ebx, [a1]
		call sub_61D3F0Ptr
	}
}

DataArray(KartSpecialInfo, kartSpecialInfo, 0x1D96F70, 8);
void __cdecl LoadKartTexturesAndExModels_r()
{
	HMODULE** v0; // ecx
	HMODULE v1; // edx
	NJS_OBJECT** v2; // eax
	NJS_OBJECT** v3; // esi
	NJS_TEXLIST* v4; // eax
	HMODULE v5; // ecx
	HMODULE v6; // ecx
	NJS_TEXLIST* v7; // eax
	int i; // edi
	NJS_OBJECT* v9; // edx
	int v10; // ebx
	HMODULE v11; // ecx
	NJS_TEXLIST* v12; // eax
	NJS_OBJECT* v13; // ecx
	NJS_OBJECT* v14; // eax
	NJS_OBJECT* v15; // edx
	HMODULE v16; // ecx
	NJS_TEXLIST* v17; // eax
	NJS_OBJECT* v18; // ecx
	NJS_OBJECT* v19; // eax
	NJS_TEXLIST* v20; // eax
	HMODULE v21; // ecx
	NJS_TEXLIST* v22; // eax
	HMODULE v23; // ecx

	v0 = datadllhandle;
	if (datadllhandle)
	{
		v1 = **datadllhandle;
		v2 = 0;
		if (v1)
		{
			v2 = (NJS_OBJECT * *)GetProcAddress(v1, "exModels");
			v0 = datadllhandle;
		}
		v3 = v2;
	}
	else
	{
		v3 = 0;
	}
	*(int*)0x1AEDECC = 1;
	v22 = 0;
	if (v0)
	{
		v23 = **v0;
		if (v23)
		{
			v22 = (NJS_TEXLIST*)GetProcAddress(v23, "texlist_tailsBig");
		}
	}
	LoadTextureList("tailsBig", v22);
	v20 = 0;
	if (v0)
	{
		v21 = **v0;
		if (v21)
		{
			v20 = (NJS_TEXLIST*)GetProcAddress(v21, "texlist_rougeBig");
		}
	}
	LoadTextureList("rougeBig", v20);
	v4 = 0;
	if (v0)
	{
		v5 = **v0;
		if (v5)
		{
			v4 = (NJS_TEXLIST*)GetProcAddress(v5, "texlist_cartData_cartSpecial");
		}
	}
	LoadTextureList("cartData", v4);
	if (datadllhandle)
	{
		v6 = **datadllhandle;
		v7 = 0;
		if (v6)
		{
			v7 = (NJS_TEXLIST*)GetProcAddress(v6, "texlist_kartExModel_cartSpecial");
		}
	}
	else
	{
		v7 = 0;
	}
	LoadTextureList("kartExModel", v7);
	char usedchars[8];
	memset(usedchars, 0, 8);
	for (i = 0; i < 6; ++i)
	{
		int ch, ch2;
		do
		{
			ch = rand() % 14;
			if (ch > 7)
				ch2 = ch - 6;
			else
				ch2 = ch;
		} while (usedchars[ch2]);
		kartchars[i] = ch2;
		usedchars[ch2] = 1;
		if (ch > 7)
		{
			switch (ch2)
			{
			case 2:
				kartSpecialInfo[2].TexList = (NJS_TEXLIST*)GetDllData("texlist_kartExModel_cartSpecial");
				kartSpecialInfo[2].Model = *v3;
				v9 = *v3;
				kartSpecialInfo[2].Unknown3 = 0;
				kartSpecialInfo[2].LowModel = v9;
				v10 = 2;
				goto LABEL_31;
			case 3:
				kartSpecialInfo[6].TexList = (NJS_TEXLIST*)GetDllData("texlist_kartExModel_cartSpecial");
				kartSpecialInfo[6].Model = v3[3];
				v15 = v3[3];
				kartSpecialInfo[6].Unknown3 = 0;
				kartSpecialInfo[6].LowModel = v15;
				v10 = 6;
				goto LABEL_31;
			case 4:
				if (datadllhandle)
				{
					v11 = **datadllhandle;
					v12 = 0;
					if (v11)
					{
						v12 = (NJS_TEXLIST*)GetProcAddress(v11, "texlist_kartExModel_cartSpecial");
					}
				}
				else
				{
					v12 = 0;
				}
				kartSpecialInfo[4].TexList = v12;
				kartSpecialInfo[4].Model = v3[1];
				v13 = v3[1];
				kartSpecialInfo[4].Unknown3 = 0;
				kartSpecialInfo[4].LowModel = v13;
				v10 = 4;
				goto LABEL_31;
			case 5:
				if (datadllhandle)
				{
					v16 = **datadllhandle;
					v17 = 0;
					if (v16)
					{
						v17 = (NJS_TEXLIST*)GetProcAddress(v16, "texlist_kartExModel_cartSpecial");
					}
				}
				else
				{
					v17 = 0;
				}
				kartSpecialInfo[5].TexList = v17;
				kartSpecialInfo[5].Model = v3[4];
				v18 = v3[4];
				kartSpecialInfo[5].Unknown3 = 0;
				kartSpecialInfo[5].LowModel = v18;
				v10 = 5;
				goto LABEL_31;
			case 6:
				kartSpecialInfo[3].TexList = (NJS_TEXLIST*)GetDllData("texlist_kartExModel_cartSpecial");
				kartSpecialInfo[3].Model = v3[2];
				v14 = v3[2];
				kartSpecialInfo[3].Unknown3 = 0;
				kartSpecialInfo[3].LowModel = v14;
				v10 = 3;
				goto LABEL_31;
			case 7:
				kartSpecialInfo[7].TexList = (NJS_TEXLIST*)GetDllData("texlist_kartExModel_cartSpecial");
				kartSpecialInfo[7].Model = v3[5];
				v19 = v3[5];
				kartSpecialInfo[7].Unknown3 = 0;
				kartSpecialInfo[7].LowModel = v19;
				v10 = 7;
			LABEL_31:
				sub_61D3F0(v10);
				break;
			}
		}
	}
}



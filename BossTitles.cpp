#include "stdafx.h"
#include "HelperFuns.h"
#include "BossTitles.h"

DataPointer(BossTitleData, KnucklesBossTitle, 0xDCF434);
DataPointer(BossTitleData, RougeBossTitle, 0xDCF530);
DataPointer(BossTitleData, TailsBossTitle, 0xEF3084);
DataPointer(BossTitleData, EggmanBossTitle, 0xEF3190);
DataPointer(BossTitleData, SonicBossTitle, 0x1646524);
DataPointer(BossTitleData, ShadowBossTitle, 0x1647C24);

enum BossTitleLetterIDs
{
	space,
	_A = 1000000,
	_C,
	_D,
	dot,
	_E,
	_G,
	_H,
	_I,
	_L,
	_M,
	_N,
	_O,
	_R,
	_S,
	_T,
	_U,
	_W,
	_Y,
	_K = 1000030
};

NJS_TEXNAME AmyBossTitleTexName[3];

NJS_TEXLIST AmyBossTitleTex{ arrayptrandlengthT(AmyBossTitleTexName, int) };

BossTitleLetterData AmyBossTitleLetters[]
{
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _M, 22, 16, 0, 32, 16, 0 },
	{ _Y, 16, 16, 0, 16, 16, 0 },
};

BossTitleData AmyBossTitle{ arrayptrandlengthT(AmyBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &AmyBossTitleTex, 320, 240, 2, 0xFFFFFF };

NJS_TEXNAME MetalSonicBossTitleTexName[10];

NJS_TEXLIST MetalSonicBossTitleTex{ arrayptrandlengthT(MetalSonicBossTitleTexName, int) };

BossTitleLetterData MetalSonicBossTitleLetters[]
{
	{ _M, 22, 16, 0, 32, 16, 0 },
	{ _E, 16, 16, 0, 16, 16, 0 },
	{ _T, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _L, 16, 16, 0, 16, 16, 0 },
	{ space, 16, 16, 0, 16, 16, 0 },
	{ _S, 16, 16, 0, 16, 16, 0 },
	{ _O, 16, 16, 0, 16, 16, 0 },
	{ _N, 16, 16, 0, 16, 16, 0 },
	{ _I, 8, 16, 0, 8, 16, 0 },
	{ _C, 16, 16, 0, 16, 16, 0 },
};

BossTitleData MetalSonicBossTitle{ arrayptrandlengthT(MetalSonicBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &MetalSonicBossTitleTex, 320, 240, 2, 0xFFFFFF };

NJS_TEXNAME TikalBossTitleTexName[5];

NJS_TEXLIST TikalBossTitleTex{ arrayptrandlengthT(TikalBossTitleTexName, int) };

BossTitleLetterData TikalBossTitleLetters[]
{
	{ _T, 16, 16, 0, 16, 16, 0 },
	{ _I, 8, 16, 0, 8, 16, 0 },
	{ _K, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _L, 16, 16, 0, 16, 16, 0 },
};

BossTitleData TikalBossTitle{ arrayptrandlengthT(TikalBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &TikalBossTitleTex, 320, 240, 2, 0xFFFFFF };

NJS_TEXNAME ChaosBossTitleTexName[5];

NJS_TEXLIST ChaosBossTitleTex{ arrayptrandlengthT(ChaosBossTitleTexName, int) };

BossTitleLetterData ChaosBossTitleLetters[]
{
	{ _C, 16, 16, 0, 16, 16, 0 },
	{ _H, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _O, 16, 16, 0, 16, 16, 0 },
	{ _S, 16, 16, 0, 16, 16, 0 },
};

BossTitleData ChaosBossTitle{ arrayptrandlengthT(ChaosBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &ChaosBossTitleTex, 320, 240, 2, 0xFFFFFF };

NJS_TEXNAME ChaoBossTitleTexName[4];

NJS_TEXLIST ChaoBossTitleTex{ arrayptrandlengthT(ChaoBossTitleTexName, int) };

BossTitleLetterData ChaoBossTitleLetters[]
{
	{ _C, 16, 16, 0, 16, 16, 0 },
	{ _H, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _O, 16, 16, 0, 16, 16, 0 },
};

BossTitleData ChaoBossTitle{ arrayptrandlengthT(ChaoBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &ChaoBossTitleTex, 320, 240, 2, 0xFFFFFF };

NJS_TEXNAME DarkChaoBossTitleTexName[7];

NJS_TEXLIST DarkChaoBossTitleTex{ arrayptrandlengthT(DarkChaoBossTitleTexName, int) };

BossTitleLetterData DarkChaoBossTitleLetters[]
{
	{ _D, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _R, 16, 16, 0, 16, 16, 0 },
	{ _K, 16, 16, 0, 16, 16, 0 },
	{ space, 16, 16, 0, 16, 16, 0 },
	{ _C, 16, 16, 0, 16, 16, 0 },
	{ _H, 16, 16, 0, 16, 16, 0 },
	{ _A, 18, 16, 0, 32, 16, 0 },
	{ _O, 16, 16, 0, 16, 16, 0 },
};

BossTitleData DarkChaoBossTitle{ arrayptrandlengthT(DarkChaoBossTitleLetters, short), 0xC, 0x14, 0, 0x30000, 480, &DarkChaoBossTitleTex, 320, 240, 2, 0xFFFFFF };

void LoadBossTitle(char id)
{
	BossTitleData* title = nullptr;
	switch (id)
	{
	case Characters_Sonic:
		title = &SonicBossTitle;
		break;
	case Characters_Shadow:
		title = &ShadowBossTitle;
		break;
	case Characters_Tails:
	case Characters_MechTails:
		title = &TailsBossTitle;
		break;
	case Characters_Eggman:
	case Characters_MechEggman:
		title = &EggmanBossTitle;
		break;
	case Characters_Knuckles:
		title = &KnucklesBossTitle;
		break;
	case Characters_Rouge:
		title = &RougeBossTitle;
		break;
	case Characters_Amy:
		title = &AmyBossTitle;
		break;
	case Characters_MetalSonic:
		title = &MetalSonicBossTitle;
		break;
	case Characters_Tikal:
		title = &TikalBossTitle;
		break;
	case Characters_Chaos:
		title = &ChaosBossTitle;
		break;
	case Characters_ChaoWalker:
		title = &ChaoBossTitle;
		break;
	case Characters_DarkChaoWalker:
		title = &DarkChaoBossTitle;
		break;
	}
	if (title)
	{
		switch (CurrentLevel)
		{
		case LevelIDs_SonicVsShadow1:
		case LevelIDs_TailsVsEggman1:
		case LevelIDs_SonicVsShadow2:
			title->DisplayTime = 360;
			break;
		case LevelIDs_TailsVsEggman2:
		case LevelIDs_KnucklesVsRouge:
			title->DisplayTime = 480;
			break;
		}
		LoadBossTitleExec(nullptr, title);
	}
}

const void* const loc_4C8142 = (void*)0x4C8142;
__declspec(naked) void LoadShadow2BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_4C8142
	}
}

const void* const loc_619D4C = (void*)0x619D4C;
__declspec(naked) void LoadShadow1BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_619D4C
	}
}

const void* const loc_6273E7 = (void*)0x6273E7;
__declspec(naked) void LoadEggman1BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_6273E7
	}
}

const void* const loc_649C91 = (void*)0x649C91;
__declspec(naked) void LoadRougeBossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_649C91
	}
}

const void* const loc_662A7B = (void*)0x662A7B;
__declspec(naked) void LoadEggman2BossTitle()
{
	__asm
	{
		movzx eax, al
		push eax
		call LoadBossTitle
		pop eax
		jmp loc_662A7B
	}
}

FunctionPointer(void, ReleaseTextureList, (NJS_TEXLIST* a1), 0x77F9F0);
void FreeSonicBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(SonicBossTitle.TexList);
}

void FreeShadowBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(ShadowBossTitle.TexList);
}

void FreeTailsBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(TailsBossTitle.TexList);
}

void FreeEggmanBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(EggmanBossTitle.TexList);
}

void FreeKnucklesBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(KnucklesBossTitle.TexList);
}

void FreeRougeBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(RougeBossTitle.TexList);
}

void FreeAmyBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(AmyBossTitle.TexList);
}

void FreeMetalSonicBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(MetalSonicBossTitle.TexList);
}

void FreeTikalBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(TikalBossTitle.TexList);
}

void FreeChaosBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(ChaosBossTitle.TexList);
}

void FreeChaoBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(ChaoBossTitle.TexList);
}

void FreeDarkChaoBossTitleTex(ObjectMaster* obj)
{
	ReleaseTextureList(DarkChaoBossTitle.TexList);
}

void LoadBossTitleTex(ObjectMaster* obj, char id)
{
	switch (id)
	{
	case Characters_Sonic:
		LoadTextureList("TITLETEX_SONIC", SonicBossTitle.TexList);
		obj->DeleteSub = FreeSonicBossTitleTex;
		break;
	case Characters_Shadow:
		LoadTextureList("TITLETEX_SHADOW", ShadowBossTitle.TexList);
		obj->DeleteSub = FreeShadowBossTitleTex;
		break;
	case Characters_Tails:
	case Characters_MechTails:
		LoadTextureList("TITLETEX_TAILS", TailsBossTitle.TexList);
		obj->DeleteSub = FreeTailsBossTitleTex;
		break;
	case Characters_Eggman:
	case Characters_MechEggman:
		LoadTextureList("TITLETEX_EGGMAN", EggmanBossTitle.TexList);
		obj->DeleteSub = FreeEggmanBossTitleTex;
		break;
	case Characters_Knuckles:
		LoadTextureList("TITLETEX_KNUCKLES", KnucklesBossTitle.TexList);
		obj->DeleteSub = FreeKnucklesBossTitleTex;
		break;
	case Characters_Rouge:
		LoadTextureList("TITLETEX_ROUGE", RougeBossTitle.TexList);
		obj->DeleteSub = FreeRougeBossTitleTex;
		break;
	case Characters_Amy:
		LoadTextureList("TITLETEX_AMY", AmyBossTitle.TexList);
		obj->DeleteSub = FreeAmyBossTitleTex;
		break;
	case Characters_MetalSonic:
		LoadTextureList("TITLETEX_METALSONIC", MetalSonicBossTitle.TexList);
		obj->DeleteSub = FreeMetalSonicBossTitleTex;
		break;
	case Characters_Tikal:
		LoadTextureList("TITLETEX_TIKAL", TikalBossTitle.TexList);
		obj->DeleteSub = FreeTikalBossTitleTex;
		break;
	case Characters_Chaos:
		LoadTextureList("TITLETEX_CHAOS", ChaosBossTitle.TexList);
		obj->DeleteSub = FreeChaosBossTitleTex;
		break;
	case Characters_ChaoWalker:
		LoadTextureList("TITLETEX_CHAO", ChaoBossTitle.TexList);
		obj->DeleteSub = FreeChaoBossTitleTex;
		break;
	case Characters_DarkChaoWalker:
		LoadTextureList("TITLETEX_DARKCHAO", DarkChaoBossTitle.TexList);
		obj->DeleteSub = FreeDarkChaoBossTitleTex;
		break;
	}
}

const void* const loc_4C909C = (void*)0x4C909C;
__declspec(naked) void LoadShadow2BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_4C909C
	}
}

const void* const loc_61A383 = (void*)0x61A383;
__declspec(naked) void LoadShadow1BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_61A383
	}
}

const void* const loc_627D02 = (void*)0x627D02;
__declspec(naked) void LoadEggman1BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_627D02
	}
}

const void* const loc_64B7A0 = (void*)0x64B7A0;
__declspec(naked) void LoadRougeBossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_64B7A0
	}
}

const void* const loc_6639D9 = (void*)0x6639D9;
__declspec(naked) void LoadEggman2BossTitleTex()
{
	__asm
	{
		movzx eax, al
		push eax
		push edi
		call LoadBossTitleTex
		pop edi
		pop eax
		jmp loc_6639D9
	}
}

void InitBossTitles()
{
	WriteJump((void*)0x4C8124, LoadShadow2BossTitle);
	WriteJump((void*)0x4C9061, LoadShadow2BossTitleTex);
	WriteJump((void*)0x619D2E, LoadShadow1BossTitle);
	WriteJump((void*)0x61A348, LoadShadow1BossTitleTex);
	WriteJump((void*)0x6273C9, LoadEggman1BossTitle);
	WriteJump((void*)0x627CC7, LoadEggman1BossTitleTex);
	WriteJump((void*)0x649C73, LoadRougeBossTitle);
	WriteJump((void*)0x64B765, LoadRougeBossTitleTex);
	WriteJump((void*)0x662A5D, LoadEggman2BossTitle);
	WriteJump((void*)0x66399E, LoadEggman2BossTitleTex);
}
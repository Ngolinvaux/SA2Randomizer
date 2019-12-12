#include "stdafx.h"
#include "RankVoices.h"
#include "HelperFuns.h"

DataArray(int, SonicRankVoices, 0x173B7D0, 5);
DataArray(int, TailsRankVoices, 0x173B7E4, 5);
DataArray(int, KnucklesRankVoices, 0x173B7F8, 5);
DataArray(int, EggmanRankVoices, 0x173B80C, 5);
DataArray(int, ShadowRankVoices, 0x173B820, 5);
DataArray(int, RougeRankVoices, 0x173B834, 5);
DataPointer(int, CurrentLevelRank, 0x174B001);
void PlayRankVoice_i(int id)
{
	int v23 = -1;
	switch (id)
	{
	case Characters_Sonic:
	case Characters_SuperSonic:
		v23 = SonicRankVoices[CurrentLevelRank];
		break;
	case Characters_Shadow:
	case Characters_SuperShadow:
		v23 = ShadowRankVoices[CurrentLevelRank];
		break;
	case Characters_Knuckles:
		v23 = KnucklesRankVoices[CurrentLevelRank];
		break;
	case Characters_Rouge:
		v23 = RougeRankVoices[CurrentLevelRank];
		break;
	case Characters_Tails:
	case Characters_MechTails:
		v23 = TailsRankVoices[CurrentLevelRank];
		break;
	case Characters_Eggman:
	case Characters_MechEggman:
		v23 = EggmanRankVoices[CurrentLevelRank];
		break;
	}
	if (v23 != -1)
	{
		PlayVoice(2, v23);
	}
}

const void* const loc_44FD08 = (void*)0x44FD08;
__declspec(naked) void PlayRankVoice()
{
	__asm
	{
		push eax
		call PlayRankVoice_i
		add esp, 4
		jmp loc_44FD08
	}
}

void InitRankVoice()
{
	WriteJump((void*)0x44FC5E, PlayRankVoice);
}
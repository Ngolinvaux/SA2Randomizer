#include "stdafx.h"
#include "Animations.h"
#include "Trampoline.h"
#include "Windows.h"



FunctionPointer(void, sub_45B610, (EntityData1* data, EntityData2* a3, CharObj2Base* data2), 0x45B610);
FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff
DataArray(EntityData2*, EntityData2Ptrs, 0x1DE95E0, 8);
DataPointer(NJS_MATRIX_PTR, nj_current_matrix_ptr_, 0x1A557FC);
FunctionPointer(unsigned int, DoGrindThing, (EntityData1* data, EntityData2* data2, CharObj2Base* co2, CharObj2Base* co2Miles), 0x725F30);

FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2* a2, CharObj2Base* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2* a2, CharObj2Base* a3), 0x46D6D0);

vector<float> vanillaSizes = { 9.0,15.5 };
NJS_VECTOR lastPos = { 0,0,0 };

Trampoline* CheckBreakObject_t;
//Trampoline* chaoStats_t;
bool onLoopPath = false;
int loopIDX = 0;

Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{
	
	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];

	if ((MainCharObj1[0]->Action == Action_MechlessAttack) && GetCollidingPlayer(obj) && isMechless(CurrentCharacter))
		return 1;

	FunctionPointer(Bool, original, (ObjectMaster * obj, ObjectMaster * other), CheckBreakObject_t->Target());
	return original(obj, other);
}

static const void* const sub_45B2C0Ptr = (void*)0x45B2C0;
static inline int sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3)
{

	int result;

	__asm
	{
		mov esi, [a3]
		mov ecx, [a2]
		mov edx, [a1]

		call sub_45B2C0Ptr
		mov result, edx
	}

	return result;

}


void idk(CharObj2Base* co2) {
	if (co2->PhysData.RunSpeed > co2->Speed.x) {
		co2->Speed.x = co2->PhysData.RunSpeed;
	}

	//v77 = __OFSUB__(HIWORD(co2->field_12), 12);
	//v76 = (HIWORD(co2->field_12) - 12) < 0;
	
	co2->Speed.y = 0.449999988079071 - njScalor(&co2->Speed) * 0.0260000005364418 + co2->Speed.y;

	/*if (v76 ^ v77) {
		HIWORD(co2->field_12) = 12;
	}*/
	if (co2->field_12 < 0xc) co2->field_12 = 0xc;
	co2->AnimInfo.Current = 15; // Falling
}

static const void* const CheckGrindPtr = (void*)0x726D00;
static inline signed int CheckTrickASM(CharObj2Base* a1, CharObj2Base* a2, EntityData1* a3)
{

	signed int result;

	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [a1]

		call CheckGrindPtr
		add esp, 8 // a2
		mov result, eax
	}
	return result;
}

void CheckGrindThing(EntityData1* data1, EntityData2* data2, CharObj2Base* co2) {
	if (data1->NextAction != 0 || data1->Status & Status_DoNextAction) {
		
		return;
	}

	if ((data1->Status & Status_OnPath) == 0) {
		
		co2->AnimInfo.Next = 15;
		data1->Action = 10; //SA2Action_LaunchJumpOrFalling
		co2->AnimInfo.Current = 15; //Falling
		data1->Status &= 0xDFFFu;
		return;
	}

	//if (CheckTrickASM(co2, co2, data1))
	//{
	//	return;
	//}

	if (data1->Status & Status_DisableControl || !Jump_Pressed[co2->PlayerNum] || !sub_45B2C0(co2, co2->PlayerNum, data1) || sub_45B2C0(co2, co2->PlayerNum, data1) > 3) {
		//if (data1->NextAction == 10) {
			//data1->Status &= 0xDFFFu;
		//}
		//else {
			//data2->field_1C = data1->Rotation.y;
			//if (co2->PhysData.RunSpeed > co2->Speed.x) {
			//	co2->Speed.x = co2->PhysData.RunSpeed;
			//}
			//PrintDebug("here");
			//data1->Action = 10; //SA2Action_LaunchJumpOrFalling
			//co2->AnimInfo.Current = 15; //Falling
			//data1->Status &= 0xDFFFu;

		//}

		return;
	}

	data1->Status &= 0xDFFFu;
	data1->Action = 10; //SA2Action_LaunchJumpOrFalling
	//PlaySoundProbably(8193, 0, 0, 0);

	Angle analog_angle;
	Float analog_mag;

	GetAnalog(data1, co2, &analog_angle, &analog_mag);

	analog_mag *= njSin((analog_angle - LOWORD(data1->Rotation.y)));

	if (analog_mag < 0) {
		data1->Rotation.y = data1->Rotation.y - (12288.0 - njScalor(&co2->Speed) * 800.0);
	}
	else {
		data1->Rotation.y = 12288.0 - njScalor(&co2->Speed) * 800.0 + data1->Rotation.y;
	}

}

static const void* jmploc = (void*)0x751cb5;
static const void* jmplocGrind = (void*)0x717840;

static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static inline char PlaySound3DThingMaybe(int id, NJS_VECTOR* pos, int a3, char a4, char a5)
{
	char result;
	__asm
	{
		push[a5]
		push[a4]
		push[a3]
		mov esi, [pos]
		mov edi, [id]
		call Sub4372E0Ptr
		mov result, al
		add esp, 12
	}
	return result;
}



static const void* const sub_46D140Ptr = (void*)0x46D140;
int inline getRailAccel(CharObj2Base* a1, EntityData1* a2, EntityData2* a3)
{
	int result;

	__asm
	{

		push[a3]
		push[a2]
		mov eax, [a1]

		// Call your __cdecl function here:
		call sub_46D140Ptr
		add esp, 8 // a2

	}
	return result;
}


static const void* const sub_46D040Ptr = (void*)0x46D040;
int inline sub_46D040(EntityData1* a1, CharObj2Base* a2, EntityData2* a3)
{
	__asm
	{
		push[a3]
		mov ebx, [a2]
		mov eax, [a1]

		call sub_46D040Ptr

		add esp, 4 // a3        
	}
}

void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2* a3) {
	sub_46D040(a1, a2, a3);
	if (a1->Action != 72)
		getRailAccel(a2, a1, a3);
	return;
}

void goingDown() {
	NJS_VECTOR result;
	int v8 = 0;
	float* v21;
	signed int v37 = 0;
	int a2a = 0;
	int v20 = 0;
	double v22 = 0.0;
	double v23 = 0.0;
	double v24 = 0.0;
	int v25 = 0;
	float v39 = 0.0;
	float v40 = 0.0;
	float v41 = 0.0;



	MainCharObj1[0]->Status = MainCharObj1[0]->Status & 0xFAFF | 0x2000;
	//(EntityData2Ptrs[0][13].field_28) = 0;
	//(EntityData2Ptrs[0][13].field_2C) = 0;
	result = { 1, 0, 0 };
	sub_429710();
	v21 = nj_current_matrix_ptr_;
	if (nj_current_matrix_ptr_)
	{
		memset(nj_current_matrix_ptr_, v20, 0x30u);
		*v21 = 1.0;
		v21[5] = 1.0;
		v21[10] = 1.0;
	}
	if (v37)
	{
		njRotateZ(v21, v37);
	}
	if (a2a)
	{
		njRotateX(v21, a2a);
	}
	if (MainCharObj1[0]->Rotation.y)
	{
		njRotateY((float*)v21, -MainCharObj1[0]->Rotation.y);
	}
	//njCalcPoint(&result, &result, v21);
	njCalcPoint(v21,&result, &result,1);
	v39 = fabs(MainCharObj2[0]->Speed.y);
	if (MainCharObj2[0]->Speed.x < 0.0)
	{
		v24 = v39;
		v41 = fabs(result.y);
		v23 = MainCharObj2[0]->Speed.x - v24 * v41;
	}
	else
	{
		v22 = v39;
		v40 = fabs(result.y);
		v23 = v22 * v40 + MainCharObj2[0]->Speed.x;
	}
	MainCharObj2[0]->Speed.x = v23;
	MainCharObj1[0]->Action = 71;
	if ((double)rand() * 0.000030517578125 <= 0.5)
	{
		MainCharObj2[0]->AnimInfo.Next = 207;
	}
	else
	{
		MainCharObj2[0]->AnimInfo.Next = 203;
	}
	if (CurrentLevel == LevelIDs_GreenForest)
	{
		v25 = 6;
	}
	else
	{
		v25 = 2;
		if (CurrentLevel != LevelIDs_WhiteJungle)
		{
			v25 = 4103;
		}
	}
	PlaySound3DThingMaybe(v25, &MainCharObj1[0]->Position, 0, 0, 127);
	//sub_438E70(0, 15, 0, 6); //Vibe thing 
	sub_429000();
	v8 = 1;
	
	MainCharObj2[0]->Speed.y = 0.0;
	return;
}

//////////////////
///Hand Grinding///
/////////////


void sub_4273B0(NJS_VECTOR* a1, NJS_VECTOR* a2, float* a3)
{
	Float v3; // ST00_4
	Float v4; // ST04_4

	v3 = a3[4] * a1->x + a3[5] * a1->y + a3[6] * a1->z;
	v4 = a3[8] * a1->x + a3[9] * a1->y + a3[10] * a1->z;
	a2->x = a3[1] * a1->y + *a3 * a1->x + a3[2] * a1->z;
	a2->y = v3;
	a2->z = v4;
}


static const void* const sub_7274F0Ptr = (void*)0x7274F0;
float* sub_7274F0(EntityData1* a1)
{
	float* result;
	__asm
	{
		mov eax, [a1] // eax0
		// Call your __cdecl function here:
		call sub_7274F0Ptr
		mov result, eax
	}
	return result;
}

static const void* const Sub468E70Ptr = (void*)0x468E70;
float* sub_468E70(EntityData1* a1, NJS_VECTOR* a2)
{
	float* result;

	__asm
	{
		mov esi, [a2] // a4
		mov edi, [a1] // a3
		// Call your __cdecl function here:		
		call Sub468E70Ptr
		mov result, edi
	}
	return result;
}


void SetHandGrinding(EntityData2* data2, CharObj2Base* co2Miles, CharObj2Base* co2, EntityData1* data1) {

	//void* v26 = *(void**)co2Miles->field_1BC[16];
	//float v40 = co2Miles->field_3BC[4];
	int a2a = 0;
	NJS_VECTOR v37;
	int result = 0;
	float v35;
	float v36;
	signed int v39 = 0;
	float v45 = 0;
	double v28 = 0.0;
	float v46 = 0.0;


	data1->Status = data1->Status & 0xFAFF | 0x2000;
	//data2[13].field_28 = 0;
	//data2[13].field_2C = 0;
	data2[13].SpeedAngle.x = 0;
	data2[13].SpeedAngle.y = 0;

	//*(float*)& co2Miles->field_3BC[16] = 0.0;
	v37.x = 1.0;
	v37.y = 0.0;
	v37.z = 0.0;
	sub_468E70(data1, &v37);
	*(float*)& result = 0.0;
	v35 = 1.0;
	v36 = 0.0;
	sub_429710();
	float* v27 = (float*)nj_current_matrix_ptr_;
	if (nj_current_matrix_ptr_)
	{
		memset(nj_current_matrix_ptr_, 0, 0x30u);
		*v27 = 1.0;
		v27[5] = 1.0;
		v27[10] = 1.0;
	}
	if (v39)
	{
		njRotateZ(v27, v39);
	}
	if (a2a)
	{
		njRotateX(v27, a2a);
	}
	sub_4273B0((NJS_VECTOR*)& result, (NJS_VECTOR*)& result, v27);
	sub_429000();
	v45 = asin(-v36);
	v28 = -*(float*)& result;
	data1->Rotation.x = (signed int)(v45 * 10430.38043493439);
	v46 = atan2(-v35, v28);
	data1->Rotation.z = (signed int)(v46 * -10430.38043493439);
	sub_429710();
	float* v29 = (float*)nj_current_matrix_ptr_;
	if (nj_current_matrix_ptr_)
	{
		memset(nj_current_matrix_ptr_, 0, 0x30u);
		*v29 = 1.0;
		v29[5] = 1.0;
		v29[10] = 1.0;
	}
	if (data1->Rotation.x)
	{
		njRotateX(v29, -data1->Rotation.x);
	}
	if (data1->Rotation.z)
	{
		njRotateZ(v29, -data1->Rotation.z);
	}
	sub_4273B0(&v37, (NJS_VECTOR*)& result, v29);
	sub_429000();
	float v47 = (*(float*)& result, v36);
	int v30 = (signed int)(v47 * 10430.38043493439);
	data1->Rotation.y = v30;
	//*(DWORD*)& co2Miles->base.gap1C[2] = v30;
	//data1->Action = 72;
	//co2->AnimInfo.Next = 200;
	co2->Speed.y = 0.0;
}

static const void* const sub45FEF0ptr = (void*)0x45FEF0;
inline double sub_45FEF0(EntityData1* data, CharObj2Base* co2, EntityData2* data2)
{

	double  result;
	__asm
	{
		push[data2]
		mov eax, [co2]
		mov ecx, [data]
		call sub45FEF0ptr
		fstp result
	}
	return result;
}

void fuckTHisShit() {



	switch (MainCharObj1[0]->NextAction)
	{
		//if(isMechless(CurrentCharacter))
		//	if (MainCharObj2[0]->AnimInfo.Current == 76 || MainCharObj2[0]->AnimInfo.Current == 77) {
		//		MainCharObj2[0]->AnimInfo.Current = 10;
		//		break;
		//	}

		

	default:
		break;





	case 17:

		if (CurrentCharacter == Characters_SuperSonic) {
			MainCharObj1[0]->Action = 60;
			MainCharObj1[0]->Status = 8193;
			onLoopPath = true;
			loopIDX = 0;
		}
		break;


	case 61://dig on ground
	case 62:
		if (isHunt(CurrentCharacter)) {
			MainCharObj2[0]->AnimInfo.Next = 89;
			MainCharObj2[0]->AnimInfo.Current = 89;
		}

		break;
	case 65://dig on wall
		if (isHunt(CurrentCharacter)) {
			MainCharObj2[0]->AnimInfo.Next = 94;
			MainCharObj2[0]->AnimInfo.Current = 94;
		}

		break;
	case 66:
		if (isHunt(CurrentCharacter)) {
			MainCharObj2[0]->AnimInfo.Current = 98;
		}

		break;

	case 18:
		if (isMechless(CurrentCharacter)) {
			MainCharObj2[0]->AnimInfo.Next = 10;
		}
		break;

	case 45:
		if (isMechless(CurrentCharacter)) {
			MainCharObj1[0]->Status &= 0xDAFFu;
			MainCharObj2[0]->Speed = { 0, 0, 0 };
			MainCharObj1[0]->Action = Action_Launch;
			MainCharObj2[0]->AnimInfo.Next = 10;
		}
		break;

	case 20: //Pulley
		//if (isMechless(CurrentCharacter)) {
			MainCharObj1[0]->Status &= 0xDAFFu;
			MainCharObj2[0]->Speed = { 0, 0, 0 };
			MainCharObj1[0]->Action = Action_Pulley;
			MainCharObj2[0]->AnimInfo.Next = 75;
		//}
		break;

	case 0x20:
		if (CurrentLevel != 22  && CurrentLevel != 34) break;
		SetHandGrinding(EntityData2Ptrs[0], MainCharObj2[0], MainCharObj2[0], MainCharObj1[0]);
	case 0x1F: //Grind
		goingDown();
		MainCharObj1[0]->Action = Action_Grind;
		if (isHunt(CurrentCharacter) || CurrentCharacter == Characters_SuperSonic)MainCharObj1[0]->Action = 100;
		MainCharObj2[0]->AnimInfo.Next = 10;

		break;


		//case 0x20:
			//if (CurrentLevel == 22) SetHandGrinding(EntityData2Ptrs[0], MainCharObj2[0], MainCharObj2[0], MainCharObj1[0]);
			//MainCharObj1[0]->Action = 101;
			//MainCharObj2[0]->AnimInfo.Next = 10;
			//break;


	}
}


static void __declspec(naked) switchAnimationsH() {
	jmploc = (void*)0x732e11;
	__asm {
		pushad
		pushfd
		push eax
		call fuckTHisShit
		pop eax
		popfd
		popad
		test eax, 0x1000
		jmp jmploc
	}

}
static void __declspec(naked) switchAnimationsM() {
	jmploc = (void*)0x74943a;
	__asm {
		pushad
		pushfd
		push eax
		call fuckTHisShit
		pop eax
		popfd
		popad
		test eax, 0x1000
		jmp jmploc
	}

}

static void __declspec(naked) switchAnimationsEgg() {
	jmploc = (void*)0x73f8b1;
	__asm {
		pushad
		pushfd
		
		call fuckTHisShit
		
		popfd
		popad

		push esi
		push edi
		test edx, 0x1000
		jmp jmploc
	}

}

static void __declspec(naked) switchAnimationsTails() {
	jmploc = (void*)0x751cb5;
	__asm {
		pushad
		pushfd
		push eax
		call fuckTHisShit
		pop eax
		popfd
		popad
		push ecx
		movzx edx, word ptr[esi + 0x4]
		jmp jmploc
	}

}

static void __declspec(naked) switchAnimationsSuper() {
	jmploc = (void*)0x49ae16;
	__asm {
		pushad
		pushfd
		push eax
		call fuckTHisShit
		pop eax
		popfd
		popad
		push ebp
		mov ebp, esp
		and esp, 0xfffffff8
		jmp jmploc
	}

}

////////////////////////
static void __declspec(naked) switchAnimations() {


	__asm {
		pushad
		pushfd
		call fuckTHisShit
		popfd
		popad
	}



	if (CurrentCharacter == Characters_Tails) {
		jmploc = (void*)0x751cb5;
		__asm {
			push ecx
			movzx edx, word ptr[esi + 0x4]
			jmp jmploc
		}
	}
	else if (CurrentCharacter == Characters_Eggman) {
		//jmploc = (void*)0x73f8a5;
		//__asm {
		//	movzx edx, word ptr[ebx + 0x4]
		//	push ebp
		//	jmp jmploc
		//}
		jmploc = (void*)0x73f8b1;
		__asm {
			push esi
			push edi
			test edx,0x1000
			jmp jmploc
		}

	}
	else if (isMech(CurrentCharacter)) {
		jmploc = (void*)0x74943a;
		__asm {
			test eax, 0x1000
			jmp jmploc
		}

	}
	else if (isHunt(CurrentCharacter)) {
		jmploc = (void*)0x732e11;


		__asm {
			test eax, 0x1000
			jmp jmploc
		}

	}
	else {
		jmploc = (void*)0x49ae16;
		__asm {
			push ebp
			mov ebp,esp
			and esp, 0xfffffff8
			jmp jmploc
		}
	}


}



static const void* lab_00776d5f = (void*)0x776d5f;
static const void* lab_00776d23 = (void*)0x776d23;
static void __declspec(naked) gravSwitch() {
	if ((MenuButtons_Held[0]&Buttons_B) || (MenuButtons_Held[0] & Buttons_X) || MainCharObj1[0]->Action == 0x53) {
		__asm {
			jmp lab_00776d23
		}
	}
	else {
		__asm {
			jmp lab_00776d5f
		}
	}


}




static const void* const loc_6d6934 = (void*)0x6d6934;
__declspec(naked) void  CheckBreakIronBox() {

	//if (isMechless(CurrentCharacter) || CurrentCharacter == Characters_SuperSonic || (MainCharObj2[0]->Upgrades & Upgrades_SonicFlameRing) != 0)
	if (isMechless(CurrentCharacter) || CurrentCharacter == Characters_SuperSonic || isSpeed(CurrentCharacter))
	{
		_asm jmp loc_6d6934
	}
}


static const void* const loc_46ee89 = (void*)0x46ee89;
static const void* const loc_46ee9b = (void*)0x46ee9b;
__declspec(naked) void CheckUpgradeBox() {

	if (MainCharObj2[0]->CharID == Characters_Rouge && (MainCharObj2[0]->Upgrades & Upgrades_RougeIronBoots) != 0 || (MainCharObj1[0]->Action == Action_MechlessAttack && isMechless(CurrentCharacter)) || CurrentCharacter == Characters_SuperSonic) {
		_asm jmp loc_46ee89
	}
	else {
		_asm jmp loc_46ee9b
	}
}

static void __declspec(naked) sub_46EE00()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call CheckUpgradeBox

		add esp, 4 // a1<eax> is also used for return value
		retn
	}
}

//Sparkles Rail thing
//void __usercall sub_754EC0(int playernum@<ebx>)
static const void* const sub_754EC0Ptr = (void*)0x754EC0;
int inline sub_754EC0(int playernum)
{
	__asm {
		mov ebx, [playernum]
		call sub_754EC0Ptr
	}
}

void PowderExecute_Rails(TailsCharObj2* sco2, NJS_VECTOR* dir) {
	float idk = static_cast<float>(rand()) * 0.00003f * 3.0f;
	if (idk > 0.0f) {
		PowderExecute(dir, idk, (NJS_VECTOR*)& sco2->field_1BC[68], 0);
	}
}

void LoadRailParticules(CharObj2Base* co2, EntityData2* data2) {
	if (fabs(co2->Speed.x) >= 3.7f) {
		NJS_VECTOR speed;
		speed.x = data2->Velocity.x * 0.9f;
		speed.y = data2->Velocity.y * 0.9f;
		speed.z = data2->Velocity.z * 0.9f;
			
		PowderExecute_Rails((TailsCharObj2 * )co2, &speed);
		PowderExecute_Rails((TailsCharObj2 * )co2, &speed);
		sub_754EC0(0);
	}
}




void fixRocket() {
	int item = 5;
	if (MainCharObj2[0] && !(MainCharObj2[0]->Powerups & Powerups_Dead) && CurrentLevel < LevelIDs_Route101280)
	{
		DisplayItemBoxItem(0, ItemBox_Items[item].Texture);
		ItemBox_Items[item].Code(MainCharacter[0], 0);
	}

}


static const void* fdss = (void*)0x47e6c0;
static void __declspec(naked) rocketStuff() {

	
		__asm {
			
			mov eax,esi
			call fdss

			push  0x6d6329
			ret
		}



}


int checkShadow(int i) {

	if (CurrentCharacter == Characters_SuperShadow || CurrentCharacter == Characters_SuperSonic) {		
		return 0;
	}
	return i;
}


static const void* lab_004599eb = (void*)0x4599eb;
static void __declspec(naked) fixSuperShadow() {

	__asm {

		push eax
		push ecx
		call checkShadow
		pop ecx
		mov ecx, eax
		pop eax

		
		push 0x88
		jmp lab_004599eb
	}



}


static void __declspec(naked) birdBox() {

	__asm {
		call isAttacking
		retn
	}
}

int speedCheck() {
	return (int)isSpeed(CurrentCharacter);
}

static const void* notSpeed = (void*)0x5217ca;
static const void* speed = (void*)0x521842;
VoidFunc(fun_5209f0, 0x5209f0);
static void __declspec(naked) biolizardBalls() {

	__asm {
		pushad
		push eax
		call speedCheck
		cmp eax, 0x0
		pop eax
		popad
		je nsc
		mov eax,edi
		call fun_5209f0
		jmp speed
	nsc:
		jmp notSpeed
	}
}


///////////Roll//////////

void SetPhysicRoll() {
	MainCharObj2[0]->PhysData.Height = PhysicsArray[0].Height * 0.4000000059604645;
	MainCharObj2[0]->PhysData.Radius = PhysicsArray[0].Radius * 0.4000000059604645;
	MainCharObj2[0]->PhysData.FloorGrip = PhysicsArray[0].FloorGrip * 0.4000000059604645;
	MainCharObj2[0]->PhysData.CenterHeight = PhysicsArray[0].CenterHeight * 0.4000000059604645;
	MainCharObj1[0]->Collision->CollisionArray->push &= ~0x4000u;
	return;
}

////////////////////////////////////////////

void Test() {
	if(MainCharacter[1])
	DeleteObject_(MainCharacter[1]);
	LoadMetalSonic(1);
	InitPlayer(1);
	
	if (MainCharacter[0])
		DeleteObject_(MainCharacter[0]);
	LoadAmy(0);
	//TailsCharObj2* co2Miles = (TailsCharObj2*)MainCharObj2[0];
	MainCharObj1[0]->NextAction = 0;
	MainCharObj1[0]->Action = 0;
	//co2Miles->base.AnimInfo.Animations = SuperSonicAnimList;
	//co2Miles->base.Upgrades = Upgrades_SuperSonic;
	//MainCharacter[0]->SomethingSub = Super_Something;
	LastBossPlayerManager_Load();
	InitPlayer(0);
}


ObjectMaster* getCollidingObj() {
	if (MainCharObj1[0]) {
		CollisionInfo* info = (CollisionInfo*)MainCharObj1[0]->Collision->CollidingObject;
		if (info) return info->Object;
	}
	return nullptr;
}

void collideWithObj()
{
	
	if (getCollidingObj() != nullptr) {
		//PrintInt((int)getCollidingObj()->MainSub);


		string name = "";
		if (getCollidingObj()->Name) {
			string s = getCollidingObj()->Name;
			name = getCollidingObj()->Name;
			s += " at : dec ";
			s += std::to_string((int)getCollidingObj()->MainSub);
			PrintDebug(s.c_str());
			
		}
		else {
			PrintInt((int)getCollidingObj()->MainSub);
		}


		switch ((int)getCollidingObj()->MainSub) {
			
		case 7242336://Hint monitors
			if(CurrentCharacter == Characters_SuperSonic && !EfMsgWnd0 && getCollidingObj()->Data1.Entity->Action == 1) getCollidingObj()->Data1.Entity->Action = 2;
			break;

		case 5967568:
			if(isAttacking())getCollidingObj()->Data1.Entity->NextAction = 1;
			break;

		
		case 0x609E80: //PL Elevator
		case 0x69B300://IG
			//PrintInt(getCollidingObj()->Data1.Entity->Action);
			//getCollidingObj()->Data1.Entity->Action = 3;
			

			break;

		case 0x77BB90://cg iron
			if (isAttacking()) {
				
			}
			break;

		case 7030576: //DC treasure
			if (isAttacking()) {
				
			}
			break;

		case 0x6D5D90://rocket
			getCollidingObj()->Data1.Entity->Collision->CollisionArray->center.y += 10;
			break;
		case 0x6a10a0 ://IG MISSILE
			getCollidingObj()->Data1.Entity->Action = 6;
			break;
		case 0x0069d1d0://IG DOORS
		case 0x0069f460:
			if (!isMech(CurrentCharacter) && isAttacking()) {
				//getCollidingObj()->Data1.Entity->Action = 1;
				//getCollidingObj()->Data1.Entity->Scale.x = -3;
				//getCollidingObj()->Data1.Entity->field_6 = getCollidingObj()->Data1.Entity->Rotation.z;
				getCollidingObj()->Data1.Entity->NextAction = 15;
			}
			break;
		case 0x769C30:// lc
		case 0x714610: // hb dynamite
			getCollidingObj()->Data1.Entity->Timer = 0;
			getCollidingObj()->Data1.Entity->NextAction = 7;
			break;
		case 7409856: //hb red things
			getCollidingObj()->Data1.Entity->NextAction = 3;
			break;


		case 0x65AEA0: //so dynamite
		case 0x6da880://dynamite
			if (!isMech(CurrentCharacter)) {
				getCollidingObj()->Data1.Entity->Status |= 4u;
				getCollidingObj()->EntityData2->gap_44[0] = 0;

			}
			break;

			
		case 0x6A5810: //WC bird box
			if (((MenuButtons_Held[0] & Buttons_B)|| (MenuButtons_Held[0] & Buttons_X)) && !isHunt(CurrentCharacter)) {
				//MainCharObj1[0]->Action = Action_Punch;
				
			}
			//PrintDebug("hitdfoor");
			break;

		case 0x715560: //HB door
		case 7415328: //HB block
		case 0x715170: //hb pots
		case 0x79afb0: //CC door
		
			//PrintInt(MainCharObj1[0]->field_2);
			if (isAttacking() && !isMech(CurrentCharacter)) {
				MainCharObj1[0]->field_2 = 6;
				MainCharObj1[0]->Action = 102;
				MainCharObj2[0]->AnimInfo.Next = 21;
			}
			//PrintDebug("hitdfoor");
			break;


		case 0x5ea0f0:
			PrintDebug("here at board\n\n\n");
			break;

		case 0x640db0://DC warps
		case 0x6a4db0://WC warps


			if (CurrentCharacter != Characters_SuperSonic) {
				if (!isHunt(CurrentCharacter) && MainCharObj1[0]->Action != Action_Fall) {
					getCollidingObj()->field_4C = (void*)(((int)getCollidingObj()->field_4C) + 2);
					MainCharObj1[0]->Action = Action_Fall;
				}
			}
			else {
				if (MainCharObj1[0]->Action != Action_SuperStand) {
					getCollidingObj()->field_4C = (void*)(((int)getCollidingObj()->field_4C) + 2);
					MainCharObj1[0]->Action = Action_SuperStand;
				}
			}
			break;


		case 7336480: //pc hourglass
		case 6997408: //dc hourglass
			//getCollidingObj()->Data1.Entity->Action = 0xf;
			//getCollidingObj()->Data1.Entity->Status = 32;
			//dead this is the collision not the hourglass
			break;

		case 0x527D60:
			RoundsWon[0] = 0;
			RoundsWon[1] = 0;
			getCollidingObj()->Data1.Entity->Action = 1;
			break;


		default:
			

			break;


		}
	}
}

/*  Failed attempt to make ss use sonic
FunctionPointer(int, speed_state_transition, (EntityData1* a1, EntityData2* a2, CharObj2Base* a3, CharObj2Base* a4), 0x719920);

void makeTheCall() {
	speed_state_transition(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0], MainCharObj2[0]);
}


static void __declspec(naked) superToSonic() {
	
	__asm {
		pushad
		pushfd
		call makeTheCall
		popfd
		popad
		ret
	}
}*/

bool canlockOn() {
	return CurrentLevel != LevelIDs_BigFoot && CurrentLevel != LevelIDs_HotShot && CurrentLevel != LevelIDs_FlyingDog;
}


static void __declspec(naked) canLockOn() {
	
	__asm {
		pushad
		call canlockOn
		test eax,eax
		popad

		push 0x74186d
		ret
	}
}


int hunterCheck() {
	return (int)isHunt(CurrentCharacter);
}
static void __declspec(naked) bigbogy() {
	
	__asm {
	
		pushad
		push eax
		call hunterCheck
		cmp eax, 0x0
		pop eax
		popad
		
		je notHunt
		push 0x6107ec
		ret

		notHunt:
		push 0x610b33
		ret
	}
}




int setMeter(int n) {
	int a = 0xff000000;
	byte g; 
	byte b;
	byte r;
	//PrintInt(n);
	if (n > 24) {
		r = 0;
		b = (n-24) * 10;
		g = (47 - n) *5;

	}

	if (n <= 24) {
		b = 0;
		g = (47 - n) * 5;
		r = (24 - n) * 10;


	}
	return a | r << 16 | g << 8 | b;
}
static void __declspec(naked) chaoMeter() {
	
	__asm {
		push edi
		call setMeter
		pop edi
		push 0x5977ec
		ret
	}
}


FunctionPointer(void, setDisp, (float, float, float, float), 0x559fa0);

//FunctionPointer(void, writeChar, (int*, float, float, float,float,int,int), 0x558be0);
DataPointer(int, dat_13128b0, 0x13128b0);
static const void* const writeCharPtr = (void*)0x558be0;
static inline void writeChar(int* a, float b, float c)
{
	__asm
	{
		pushad
		pushfd
		push -1
		push -1
		push 0x3f800000
		push 0x3f800000
		push 0xbf99999a
		push [c]
		push [b]
		mov eax, [a]
		call writeCharPtr
		add esp, 0x1c
		popfd
		popad
	}
}



void statFix(unsigned int p1, float x, float y,float opacity) {
	setDisp(opacity, 1.0, 1.0, 1.0);
	
	writeChar((int*)(0x13128b0 + ((p1 % 100000) / 10000) * 0x24), x-14, y);
	writeChar((int*)(0x13128b0 + ((p1 % 10000) / 1000) * 0x24), x, y);
	writeChar((int*)(0x13128b0 + ((p1 % 1000) / 100) * 0x24), x+14, y);
	writeChar((int*)(0x13128b0 + ((p1 % 100) / 10) * 0x24), x+28, y);
	writeChar((int*)(0x13128b0 + (p1 % 10) * 0x24), x+42, y);
}
__declspec(naked) void statFixCaller()
{
	__asm
	{
		
		push[esp + 0xc]
		push[esp + 0xc]
		push[esp + 0xc]
		push eax
		call statFix
		add esp, 0x10
	
		ret
	}
}

int mechCheck() {
	return (int)isMech(CurrentCharacter);
}


static void __declspec(naked) gravSwitchMech() {
	__asm {
		
		fld dword ptr[esp + 0x34]
		fstp dword ptr[esp]

		pushad
		push eax
		call mechCheck
		cmp eax, 0x0
		pop eax
		popad
		je notMech
		push 0x776eab
		ret


		notMech :
			push 0x776ea6
			ret

	}


}






void* fun = (void*)0x45b610;
__declspec(naked) void ssRun()
{
	__asm
	{

		push edi
		push ebx
		push esi
		call fun
		add esp,0xC
		push 0x49b0ae
		ret
	}
}//action,global,physics

float CWASSpeed = 14.0;
float CWASSpeedMech = 10.0;



__declspec(naked) void CWAutoScroller() {

	__asm {
		pushad
		push eax
		call mechCheck
		cmp eax, 0x0
		pop eax
		popad
		je notMech
		mov eax, dword ptr[esi +0x38]
		//fld dword ptr[eax +0x40]
		fld CWASSpeedMech
		push 0x62bacc
		ret


	notMech:
		mov eax, dword ptr[esi + 0x38]
		fld CWASSpeed


		push 0x62bacc
		ret
	}
}

void* addToList = (void*)0x6b9c30;
__declspec(naked) void cgIron() {
	__asm {
		pushad
		pushfd
		mov edx, edi
		push edx
		call addToList
		pop edx
		popad
		popfd
		
		mov ecx,dword ptr[edi+0x40]
		mov dword ptr[esp+0xc],eax



		push 0x77b8d3
		ret
	}
}

void initAnimations() {



	WriteJump((void*)0x62bac6, CWAutoScroller);
	//WriteData<2>((void*)0x60a0e0, 0x90);
	//WriteData<5>((void*)0x62bd8e, 0x90); // CW autoscrollerthing
	
	
	WriteData<1>((void*)0x46bc60, 0xc3); //underwater
	
	//WriteData<2>((void*)0x6c63f1, 0x90); // Goal ring stuff





	WriteJump((void*)0x751cb0, switchAnimationsTails);//tails
	WriteJump((void*)0x73f8a9, switchAnimationsEgg);//eggman using this one
	//WriteJump((void*)0x73f8a0, switchAnimations);//eggman
	WriteJump((void*)0x749435, switchAnimationsM);//mech
	
	WriteJump((void*)0x732e0c, switchAnimationsH);//hunters
	WriteJump((void*)0x49ae10, switchAnimationsSuper);//supersonic
	//WriteJump((void*)0x6d6906, (void*)0x6d6934);//fix for iron box

	WriteJump((void*)0x726bd5, (void*)0x726bc8);//fix for eggman grinding


	//WriteJump((void*)0x61a195, (void*)0x61a1ab);//fix for svs1 ai
	//WriteData<5>((void*)0x61a1b0, 0x90); // removes svs1 ai
	

	//WriteData<1>((void*)0x64b6d0, 0x70); // removes svs1 ai
	//WriteData<1>((void*)0x64b6d1, 0x9c); // removes svs1 ai
	//WriteData<1>((void*)0x64b6d2, 0x61); // removes svs1 ai

	//speed updte is at 719920
	//WriteCall((void*)0x49ae59, superToSonic);

	//WriteJump((void*)0x60ff58, (void*)0x610b33); // shadow to evade
	WriteJump((void*)0x60ff58, bigbogy); // shadow to evade
	//WriteJump((void*)0x6107ec, (void*)0x610b33); // shadow to evade
	//WriteJump((void*)0x6107ec, (void*)0x6107fe); // shadow to evade


	WriteJump((void*)0x776d1e, gravSwitch);
	WriteJump((void*)0x776e9f, gravSwitchMech);
	WriteJump((void*)0x6a82ab, birdBox);


	//WriteJump((void*)0x77b8cc, cgIron);

	WriteData<5>((void*)0x7899e8, 0x90); // removes EE ending

	
	//WriteData<7>((void*)0x5b9aa0, 0x90); // BG Stuff 0x5b9efo sr BG
	

	WriteJump((void*)0x741863, canLockOn); //   
	
	

	//WriteData<5>((void*)0x5837d2, 0x90); // chao fortune teller
	
	 
	
	WriteData<6>((void*)0x59778a, 0x90);// chao stamina now appears
	WriteJump((void*)0x5977e7, chaoMeter);// chao stamina now fades



	//WriteJump((void*)0x597908, (void*)0x597a47);// chao stamina border
	
	WriteCall((void*)0x5655e8, statFixCaller);// chao stats window



	
	//WriteData<10>((void*)0x5837f8, 0x90);//


	if (false) {
		//WriteData<5>((void*)0x498a90, 0x90); // this one
		//WriteData<5>((void*)0x498a98, 0x90);	// this one
		//WriteData<5>((void*)0x498a9f, 0x90);
		//WriteData<5>((void*)0x498aae, 0x90);	//this one
		//WriteData<5>((void*)0x498ab6, 0x90);	//this one
		//WriteData<5>((void*)0x498ac5, 0x90);
		//WriteData<5>((void*)0x498acf, 0x90);
		//WriteData<5>((void*)0x498ae0, 0x90);
		//WriteJump((void*)0x498a8b, (void*)0x498aee);
		//WriteCall((void*)0x498a98, LoadCharacters);
		//WriteCall((void*)0x498ab6, LoadCharacters);
		//super shadow stuff//////////////////////////////////
		//WriteJump((void*)0x4599e6, fixSuperShadow);
		//WriteCall((void*)0x498A9F, Test);
		//WriteData<6>((void*)0x49cf7f, 0x90);
		//WriteData<1>((void*)0x49ac21, 0x02);
		//WriteData<1>((void*)0x49ac20, 0x57);

		//WriteData<1>((void*)0x49aa3a, 0xd2);
		//WriteData<1>((void*)0x49aa39, 0x28);


		//WriteData<1>((void*)0x49ad31, 0x0c);

		//WriteData<1>((void*)0x49ac66, 0x00);

		//WriteData<1>((void*)0x49ac5a, 0x9);
		//WriteData<1>((void*)0x49ad4c, 0x12);

		//WriteData<1>((void*)0x49aa73, 0x3c);//sonic model to shadow
		//WriteData<1>((void*)0x49aa74, 0xaa);//sonic model to shadow


		//WriteData<1>((void*)0x49aa4f, 0x30);//sonic text to shadow
		//WriteData<1>((void*)0x49aa50, 0xaa);//sonic text to shadow

		//WriteData<1>((void*)0x49ece0, 0xc3);//laod into FH



		//WriteData<1>((void*)0x49aa83, 0x4c);//sonic mtn to shadow
		//WriteData<1>((void*)0x49aa84, 0xaa);//sonic mtn to shadow

		/////////////////////////
	}
	
	//rocket dmg
	//WriteJump((void*)0x6d56d5, rocketStuff);
	//WriteData<5>((void*)0x6d6324, 0x90);// FIX timing
	WriteJump((void*)0x6d6324, rocketStuff);// FIX timing
	
	
	
	//WriteData<5>((void*)0x49b109, 0x90);// MOVE SS FUNC
	
	WriteData<5>((void*)0x49b12e, 0x90);// MOVE SS FUNC On angle
	WriteData<6>((void*)0x49bf8b, 0x90);// ss rot reset


	
	
	
	//WriteData<5>((void*)0x49b3b7, 0x90);// ss unskewgrav



	//////biolizard ball phase
	//case 1 & 4 spawn animation
	//case  a b is dmg
	// 8 is exhaust
	//7 is dark balls?
	//WriteJump((void*)0x5217e2, (void*)0x5217ca);// 9 to 8 skipps all balls
	WriteJump((void*)0x5217e2, biolizardBalls);// 9 to 8 skipps all balls


	




	

	/////////////////AI /////////////////////////
	//WriteData<5>((void*)0x661d3a, 0x90);// Tails v Eggman 2 AI Stuff
	//WriteData<5>((void*)0x6266ca, 0x90);// Tails v Eggman 1 AI Stuff
	//WriteData<5>((void*)0x6486d5, 0x90);// Knux v Bat 1 AI Stuff
	//WriteData<5>((void*)0x4c7143, 0x90);// svs2 AI Stuff
	//WriteData<5>((void*)0x619416, 0x90);// svs1 AI Stuff
	//WriteData<1>((void*)0x6199e0, 0xc3); // removes ai not landing stuff


	//upright rocket stuff?
	//WriteData<5>((void*)0x6d5c69, 0x90);
	//WriteData<5>((void*)0x6d5fe8, 0x90);

	//WriteJump((void*)0x6d5c3b, (void*)0x6d5c50);//fix for rocket rotation


	WriteJump(reinterpret_cast<void*>(0x6d6911), CheckBreakIronBox);
	WriteJump(reinterpret_cast<void*>(0x46ee7c), CheckUpgradeBox);

	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);// break objects
	//chaoStats_t = new Trampoline(0x5369f0, 0x536b98, statFixCaller);// 

	//WriteData<4>((void*)0x49BBB9, 0x90);
	//WriteData<5>((void*)0x72631f, 0x90);
	

}
float mini = 999;
int iStore = -1;
float miniDif = 0;
bool updated = false;
void onFrameAnimations() {




	if (MainCharObj1[0] && MainCharObj2[0]) {
	
		if (CurrentCharacter == Characters_SuperSonic && MainCharacter[0] && CurrentLevel != LevelIDs_FinalHazard) {
			if (MainCharObj1[0]->Action != Action_Grind) {
				GlobalMetricStruct* gbs = (GlobalMetricStruct*)MainCharacter[0]->EntityData2;
				//if (!onLoopPath) {
					gbs->applied_force.y += Gravity_Direction.y * 0.065;
					gbs->applied_force.x += Gravity_Direction.x * 0.1;
					gbs->applied_force.z += Gravity_Direction.z * 0.1;
				//}
				if (CurrentLevel == 22) {
					MainCharObj1[0]->Rotation.z = GravityRotZ;
					MainCharObj1[0]->Rotation.x = GravityRotX;
				}
				if (sqrtf(MainCharObj2[0]->Speed.x* MainCharObj2[0]->Speed.x + MainCharObj2[0]->Speed.z* MainCharObj2[0]->Speed.z) < 5 && MainCharObj2[0]->Speed.y < 4) {
					MainCharObj1[0]->Rotation.z = GravityRotZ;
					MainCharObj1[0]->Rotation.x = GravityRotX;

					//PrintInt(MainCharObj1[0]->Action);
				}
				if (MainCharObj1[0]->Action == Action_SuperBoostUp || MainCharObj1[0]->Action == Action_SuperBoostDown) {
					MainCharObj1[0]->Rotation.z = GravityRotZ;
					MainCharObj1[0]->Rotation.x = GravityRotX;
				}

			}
		}
		if (CurrentCharacter == Characters_SuperSonic && onLoopPath) {
			mini = 9999;
			for (int i = iStore+1; i < ((MCO2*)MainCharObj2[0])->path->Count; i++) {
				
				//PrintF(dist(MainCharObj1[0]->Position, ((MCO2*)MainCharObj2[0])->path->Points[i].Position));
				if (mini > dist(MainCharObj1[0]->Position, ((MCO2*)MainCharObj2[0])->path->Points[i].Position)) {
					mini = dist(MainCharObj1[0]->Position, ((MCO2*)MainCharObj2[0])->path->Points[i].Position);
					iStore = i;
				}
			}
			PrintF(mini);
			if (mini < 30) {
				MainCharObj1[0]->Action = 60;
				MainCharObj1[0]->Position = ((MCO2*)MainCharObj2[0])->path->Points[iStore].Position;
				
				MainCharObj1[0]->Rotation.x = ((MCO2*)MainCharObj2[0])->path->Points[iStore].XRot;
				MainCharObj1[0]->Rotation.y = ((MCO2*)MainCharObj2[0])->path->Points[iStore].YRot;
			}
			else onLoopPath = false;
			//if (loopIDX < ((MCO2*)MainCharObj2[0])->path->Count) {
			///	MainCharObj1[0]->Action = 60;
			//	MainCharObj1[0]->Position = ((MCO2*)MainCharObj2[0])->path->Points[loopIDX].Position;
			///	MainCharObj1[0]->Rotation.x = ((MCO2*)MainCharObj2[0])->path->Points[loopIDX].XRot;
			//	MainCharObj1[0]->Rotation.y = ((MCO2*)MainCharObj2[0])->path->Points[loopIDX].YRot;
			//	loopIDX++;
			//}
			//else {
			//	loopIDX = 0;
			//	onLoopPath = false;
			//}
			if (MainCharObj1[0]->Action == Action_SuperBoostUp || MainCharObj1[0]->Action == Action_SuperBoostDown) {
				onLoopPath = false;

			}

		}





		//TODO
		if (CurrentCharacter == Characters_MechTails && AltCostume[0] == 1 && AltCharacter[0] == 0 && CurrentLevel == 22) {
			//MainCharObj1[0]->Rotation.z = GravityRotZ;
			//MainCharObj1[0]->Rotation.x = GravityRotX;
		}


		if (MainCharObj1[0]->Action == 102) {
			MainCharObj1[0]->Action = 0;
			MainCharObj1[0]->field_2 = 1;
		}
		collideWithObj();

		//getting off rails and pulleys
		if (true) {
			if ((MainCharObj1[0]->Action == Action_Pulley || MainCharObj1[0]->Action == Action_Grind || MainCharObj1[0]->Action == 100 || MainCharObj1[0]->Action == 101) && Jump_Pressed[0]) {

				MainCharObj1[0]->Action = Action_Jump;
				MainCharObj1[0]->NextAction = Action_Jump;
				MainCharObj1[0]->Status = 0;
				MainCharObj2[0]->AnimInfo.Next = 65;

				//GlobalMetricStruct* gbs = (GlobalMetricStruct*)MainCharacter[0]->EntityData2;
				//gbs->global_speed.y = 1;
				MainCharObj2[0]->Speed.y = MainCharObj2[0]->PhysData.JumpSpeed;

				//njRotateY((float*)nj_current_matrix_ptr_, -MainCharObj1[0]->Rotation.y);

				//njCalcPoint(&MainCharObj2[0]->Speed, &MainCharObj2[0]->Speed, nj_current_matrix_ptr_);




			}
		}

		//increase mechless hitbox	TODO
		if (isMechless(CurrentCharacter) ){
		
		}

		//PrintInt((int)MainCharObj1[0]->Collision->CollisionArray[1].attr);
		////////// dmg on black shield and mechles jump TODO
		if ((CurrentCharacter == Characters_Shadow && AltCharacter[0] == 1 && MainCharObj1[0]->Action == Action_BlackShield) || 
			(isMechless(CurrentCharacter) && MainCharObj1[0]->Action == Action_Jump)) {
			//MainCharObj2[0]->AnimInfo.Current = 65;
			MainCharObj1[0]->Status |= Status_Attack;
			MainCharObj1[0]->Status |= Status_Ball;
			

			//MainCharObj1[0]->Collision->CollisionArray[0].damage = 0x1 * 0x4 | 1 | MainCharObj1[0]->Collision->CollisionArray[0].damage & 0xf0;

			MainCharObj1[0]->Collision->CollisionArray[0].damage &= 0xFCu;
			MainCharObj1[0]->Collision->CollisionArray[0].damage |= 0xCu;
			MainCharObj1[0]->Collision->CollisionArray[0].damage |= 0xEF;


			MainCharObj1[0]->Collision->CollisionArray[1].center = MainCharObj1[0]->Position;
			MainCharObj1[0]->Collision->CollisionArray[1].attr &= 0xFFFFFFEF;
			
		}

		if (((MainCharObj1[0]->Action == Action_Grind && (isMech(CurrentCharacter) || isMechless(CurrentCharacter))) ||
			MainCharObj1[0]->Action == 100 && (isHunt(CurrentCharacter) || CurrentCharacter == Characters_SuperSonic))
			&& GameState != GameStates_Pause) {


			//CheckGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);
		}

		//rails
		if (((MainCharObj1[0]->Action == Action_Grind && (isMech(CurrentCharacter) || isMechless(CurrentCharacter))) ||
			MainCharObj1[0]->Action == 100 && (isHunt(CurrentCharacter)|| CurrentCharacter == Characters_SuperSonic))
			&& GameState != GameStates_Pause) {

		
			//CheckGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);
			DoGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0], MainCharObj2[0]);
			//sub_46D040(MainCharObj1[0], MainCharObj2[0], EntityData2Ptrs[0]);
			MoveCharacterOnRail(MainCharObj1[0], MainCharObj2[0], EntityData2Ptrs[0]);
			LoadRailParticules(MainCharObj2[0], EntityData2Ptrs[0]);
			CheckGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);
			
			//grinding up stuff
			if (MainCharObj1[0]->Position.y > lastPos.y && MainCharObj2[0]->Speed.x < MainCharObj2[0]->PhysData.RunSpeed*2 && CurrentLevel == LevelIDs_FinalRush) {
				//for (int i = 0; i < 5; i++) getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
				MainCharObj2[0]->Speed.x += 0.1;
				//PrintDebug("DOing this");
			}
			//PrintInt((int)MainCharObj2[0]->Speed.y);


			//biolizard help
			int item = 10;
			if (CurrentLevel == LevelIDs_Biolizard && isHunt(CurrentCharacter)) {
				if (!(MainCharObj2[0]->Powerups & Powerups_Invincibility)) {
					DisplayItemBoxItem(0, ItemBox_Items[item].Texture);
					ItemBox_Items[item].Code(MainCharacter[0], 0);
				}
				for(int i = 0; i < 2; i++) getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
			}
			else if (CurrentLevel == LevelIDs_Biolizard && isMech(CurrentCharacter)) {
				if (!(MainCharObj2[0]->Powerups & Powerups_Invincibility)) {
					DisplayItemBoxItem(0, ItemBox_Items[item].Texture);
					ItemBox_Items[item].Code(MainCharacter[0], 0);
					DisplayItemBoxItem(0, ItemBox_Items[7].Texture);
					ItemBox_Items[7].Code(MainCharacter[0], 0);

				}
				for (int i = 0; i < 1; i++) getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
			}
			else if (CurrentLevel == LevelIDs_Biolizard && isMechless(CurrentCharacter)) {
				
				if (!(MainCharObj2[0]->Powerups & Powerups_Invincibility)) {
					DisplayItemBoxItem(0, ItemBox_Items[item].Texture);
					ItemBox_Items[item].Code(MainCharacter[0], 0);
				}
				for (int i = 0; i < 1; i++) getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
			}
			/////

		}




		if (MainCharObj1[0]->Action == 101 && GameState != GameStates_Pause) {
			
			DoGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0], MainCharObj2[0]);
			sub_46D040(MainCharObj1[0], MainCharObj2[0], EntityData2Ptrs[0]);
			getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
			getRailAccel(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
			CheckGrindThing(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);;
			SomethingAboutHandGrind(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);
			SomethingAboutHandGrind2(MainCharObj1[0], EntityData2Ptrs[0], MainCharObj2[0]);
			
		}


		if (CurrentCharacter == Characters_SuperSonic && MainCharObj1[0]->Action == Action_Jump) {
			MainCharObj1[0]->Action = 59;
			MainCharObj1[0]->NextAction = 59;
			MainCharObj1[0]->Status = 0;
			MainCharObj2[0]->AnimInfo.Next = 65;
			MainCharObj2[0]->Speed.y = MainCharObj2[0]->PhysData.JumpSpeed;
		}
		if (CurrentCharacter == Characters_SuperSonic && MainCharObj1[0]->Action == Action_Fall) {
				MainCharObj1[0]->Action = 59;
				MainCharObj1[0]->NextAction = 59;
				MainCharObj1[0]->Status = 0;
				MainCharObj2[0]->AnimInfo.Next = 65;
		}
		lastPos = MainCharObj1[0]->Position;
	


	}




}

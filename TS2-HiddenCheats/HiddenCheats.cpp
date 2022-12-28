#include "HiddenCheats.h"
#include "pch.h"
#include <Psapi.h>
#include "LDLibraries/LDHooking/hooking.h"

#define ADDEFFECTCHEATS_HOOK1_ADDR 0xffaceb
#define ADDEFFECTCHEATS_HOOK2_ADDR 0xffad18

#define ADDEFFECTCHEATS_HOOK1_RETURN_ADDR (ADDEFFECTCHEATS_HOOK1_ADDR + 5)
#define ADDEFFECTCHEATS_HOOK2_RETURN_ADDR (ADDEFFECTCHEATS_HOOK2_ADDR + 5)

typedef void(__thiscall* thiseffectfunction_t)(void *effectsManager);
thiseffectfunction_t cTSEffectCheat = (thiseffectfunction_t)0xFFAA10;
thiseffectfunction_t cTSEffectsManagerCheat = (thiseffectfunction_t)0xFFA870;

typedef void(__stdcall* function_t)(void* cheat);
function_t TSRegisterTestingCheat = (function_t)0xD0DAA0;

namespace HiddenCheats {

	char* returnAddEffectCheatsHook1 = (char*)ADDEFFECTCHEATS_HOOK1_RETURN_ADDR;
	char* returnAddEffectCheatsHook2 = (char*)ADDEFFECTCHEATS_HOOK2_RETURN_ADDR;

	__declspec(naked) void AddEffectCheats_Hook1()
	{
		__asm {
			// command = cTSEffectCheat::cTSEffectCheat(this [ecx],effectsManager);
			call cTSEffectCheat

			// Custom code below
			push eax
			// TSRegisterTestingCheat(command)
			call TSRegisterTestingCheat
			pop eax

			jmp returnAddEffectCheatsHook1
		}
	}

	__declspec(naked) void AddEffectCheats_Hook2()
	{
		__asm {
			// command = cTSEffectsManagerCheat::cTSEffectsManagerCheat(this [ecx],effectsManager);
			call cTSEffectsManagerCheat

			// Custom code below
			push eax
			// TSRegisterTestingCheat(command)
			call TSRegisterTestingCheat
			pop eax

			jmp returnAddEffectCheatsHook2
		}
	}

	void Run() {
		returnAddEffectCheatsHook1 = (char*)((BYTE*)ADDEFFECTCHEATS_HOOK1_ADDR + 5);
		Hooking::MakeJMP((BYTE*)ADDEFFECTCHEATS_HOOK1_ADDR, (DWORD)AddEffectCheats_Hook1, 5);

		returnAddEffectCheatsHook2 = (char*)((BYTE*)ADDEFFECTCHEATS_HOOK2_ADDR + 5);
		Hooking::MakeJMP((BYTE*)ADDEFFECTCHEATS_HOOK2_ADDR, (DWORD)AddEffectCheats_Hook2, 5);
	}
}
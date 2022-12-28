#include "HiddenCheats.h"
#include "pch.h"
#include <Psapi.h>
#include "LDLibraries/LDHooking/hooking.h"

// Hook "CALL cTSEffectCheat::cTSEffectCheat" ASM line in AddEffectCheats.
#define ADDEFFECTCHEATS_HOOK1_ADDR 0xffaceb

// Hook "CALL cTSEffectsManagerCheat::cTSEffectsManagerCheat" ASM line in AddEffectCheats.
#define ADDEFFECTCHEATS_HOOK2_ADDR 0xffad18

// Addresses to jump back to when done hooking.

#define ADDEFFECTCHEATS_HOOK1_RETURN_ADDR (ADDEFFECTCHEATS_HOOK1_ADDR + 5)
#define ADDEFFECTCHEATS_HOOK2_RETURN_ADDR (ADDEFFECTCHEATS_HOOK2_ADDR + 5)

// Typedefs for functions to call.

typedef void(__thiscall* thiseffectfunction_t)(void *effectsManager);
typedef void(__stdcall* cheatfunction_t)(void* cheat);

thiseffectfunction_t cTSEffectCheat = (thiseffectfunction_t)0xFFAA10;
thiseffectfunction_t cTSEffectsManagerCheat = (thiseffectfunction_t)0xFFA870;

cheatfunction_t TSRegisterTestingCheat = (cheatfunction_t)0xD0DAA0;

namespace HiddenCheats {

	char* returnAddEffectCheatsHook1 = (char*)ADDEFFECTCHEATS_HOOK1_RETURN_ADDR;
	char* returnAddEffectCheatsHook2 = (char*)ADDEFFECTCHEATS_HOOK2_RETURN_ADDR;

	__declspec(naked) void AddEffectCheats_Hook1()
	{
		__asm {
			// effectsManager is already pushed onto the stack at this point.

			// command = cTSEffectCheat::cTSEffectCheat(this [ecx],effectsManager);
			call cTSEffectCheat

			// Custom code below.
			// TSRegisterTestingCheat(command);
			push eax
			call TSRegisterTestingCheat
			pop eax

			// Return to original code.
			jmp returnAddEffectCheatsHook1
		}
	}

	__declspec(naked) void AddEffectCheats_Hook2()
	{
		__asm {
			// effectsManager is already pushed onto the stack at this point.

			// command = cTSEffectsManagerCheat::cTSEffectsManagerCheat(this [ecx],effectsManager);
			call cTSEffectsManagerCheat

			// Custom code below.
			// TSRegisterTestingCheat(command);
			push eax
			call TSRegisterTestingCheat
			pop eax

			// Return to original code.
			jmp returnAddEffectCheatsHook2
		}
	}

	/// <summary>
	/// Run hooks.
	/// </summary>
	void Run() {
		Hooking::MakeJMP((BYTE*)ADDEFFECTCHEATS_HOOK1_ADDR, (DWORD)AddEffectCheats_Hook1, 5);
		Hooking::MakeJMP((BYTE*)ADDEFFECTCHEATS_HOOK2_ADDR, (DWORD)AddEffectCheats_Hook2, 5);
	}
}
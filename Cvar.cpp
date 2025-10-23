#include "Cvar.h"
#include "..\Utils\PatternScan\PatternScan.h"

using namespace Weight;
extern DWORD g_Pid;

float __stdcall CarriedWeightFloat(int* pp)
{
	__asm push ecx
	int idx = GetPlayerIdx(pp);
	
	if (idx >= 64 || idx < 1)
	{
		__asm pop ecx
		return 0.0f;
	}
	__asm pop ecx
	return MaxCarryArr[idx];
}
int __stdcall CarriedWeightInt(int* pp)
{
	__asm push ecx
	int idx = GetPlayerIdx(pp);
	if (idx >= 64 || idx < 1)
	{
		__asm pop ecx
		return 0;
	}
	__asm pop ecx
	return (int)MaxCarryArr[idx];
}

void __declspec(naked) GetMaxCarriedWeight_ecx::Hook()
{
	__asm
	{
		push ecx //carredweightfloat->ecx = pp
		call CarriedWeightFloat
		jmp GetMaxCarriedWeight_ecx::jmpBack
	}
}

void __declspec(naked) CItem_InventoryBox_CreateAmmoForPlayer::Hook()//31C67D-31C683 
{
	__asm
	{
		push ecx//pp
		call CarriedWeightInt//pop
		mov edi,eax
		jmp CItem_InventoryBox_CreateAmmoForPlayer::jmpBack
	}
}

void __declspec(naked)CreateItemForPlayer::Hook()//31C8D5-31C8CE
{
	__asm
	{
		push ebx
		call CarriedWeightInt//pop
		mov ecx,ebx
		mov esi,eax
		jmp CreateItemForPlayer::jmpBack
	}
}

void __declspec(naked)AddCarriedWeight::Hook()//3772A2-37729A
{
	__asm
	{
		push ebx
		call CarriedWeightInt
		mov edi,eax
		jmp AddCarriedWeight::jmpBack
	}
}

void __declspec(naked)PlayerWpnPickedUp::Hook()//37B3C7-37B3BE
{
	__asm
	{
		lea edx, dword ptr ds:[ebx+0x131c]
		push ebx
		call CarriedWeightInt
		jmp PlayerWpnPickedUp::jmpBack
	}
}

void __declspec(naked)PlayerBumpWpn::Hook()//37B8B4-37B8AE
{
	__asm
	{
		add edi,dword ptr ds:[ebx+0x131c]
		push ebx
		call CarriedWeightInt
		mov esi,eax
		jmp PlayerBumpWpn::jmpBack
	}
}

void __declspec(naked)GetWeightSpeedFactor::Hook()//37BDBD -37BDB8
{
	__asm
	{
		push ebx
		call CarriedWeightInt
		mov edi,eax
		jmp GetWeightSpeedFactor::jmpBack
	}
}

void __declspec(naked)HasEnoughInventoryRoomForWeapon::Hook()//37BE24-37BE2A
{
	__asm
	{
		add edi, [esi + 0x131c]
		push esi
		call CarriedWeightInt
		mov esi,eax
		jmp HasEnoughInventoryRoomForWeapon::jmpBack
	}
}

void __declspec(naked)HasLeftoverWeight::Hook()//37BE6C-37BE71
{
	__asm
	{
		push esi
		call CarriedWeightFloat
		fstp  [ebp-0x4]//xmm0
		jmp HasLeftoverWeight::jmpBack
	}
}

void __declspec(naked)CAmmoDef_MaxCarry_::Hook()
{
	__asm
	{
		push edi
		call CarriedWeightInt
		jmp CAmmoDef_MaxCarry_::jmpBack
	}
}



void Weight::CvarInit()
{
	using namespace Utils::PatternScan;
	INIT_HK(GetMaxCarriedWeight_ecx);
	INIT_HK(CAmmoDef_MaxCarry_);
	INIT_HK(CItem_InventoryBox_CreateAmmoForPlayer);
	INIT_HK(CreateItemForPlayer);
	INIT_HK(AddCarriedWeight);
	INIT_HK(PlayerWpnPickedUp);
	INIT_HK(PlayerBumpWpn);
	INIT_HK(GetWeightSpeedFactor);
	INIT_HK(HasEnoughInventoryRoomForWeapon);
	INIT_HK(HasLeftoverWeight);
}
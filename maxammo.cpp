#include "maxammo.h"
#include "..\Utils\PatternScan\PatternScan.h"

using namespace Weight;

void __declspec(naked) GiveAmmo::Hook()
{
	__asm
	{
		push ebx
		push edi
		push esi
		call FN::callAddrAMMO
		mov ecx,eax
		call FN::callAddrMAX
		pop edi
		jmp GiveAmmo::jmpBack
	}
}

void __declspec(naked) GetAmmoCount::Hook()
{
	__asm
	{
		push edi
		push esi
		call FN::callAddrAMMO
		mov ecx,eax
		call FN::callAddrMAX
		pop edi
		cmp eax,-2
		jmp GetAmmoCount::jmpBack
	}
}

void __declspec(naked) RemoveAmmo::Hook()
{
	__asm
	{
		push esi//存esi,esi没有使用，可以拿来保存参数 
		mov esi,edi//原EDI参数放进esi
		mov edi,ebx//把玩家pp放进edi
		push esi//替代edi入参
		call FN::callAddrAMMO
		mov ecx,eax
		call FN::callAddrMAX//会代替我们清栈，会执行一次pop
		mov edi,esi
		pop esi
		jmp RemoveAmmo::jmpBack
	}
}

void __declspec(naked) CanHaveAmmo::Hook()
{
	__asm
	{
		push eax//存eax,eax没有使用，可以拿来保存参数 
		mov eax,edi
		mov edi,[esp+0x8]//pp
		push eax
		call FN::callAddrAMMO
		mov ecx, eax
		call FN::callAddrMAX//会代替我们清栈，会执行一次pop
		mov edi, eax//还原edi之前的参数!!!!
		pop eax
		jmp CanHaveAmmo::jmpBack
	}
}

void __declspec(naked) CC_GiveCurrentAmmo1::Hook()
{
	__asm
	{
		mov ecx,eax
		call FN::callAddrMAX
	}
}

void __declspec(naked) CC_GiveCurrentAmmo2::Hook()
{
	__asm
	{

	}
}

void Weight::MaxammoInit()
{
	using namespace Utils::PatternScan;
	FN::callAddrAMMO = (FnGetAmmoData)((DWORD)(FN::callAddrAMMO)+ Find("server.dll", FN::AMMODATAPAT));
	FN::callAddrMAX = (FnCAmmoDef_MaxCarry_)((DWORD)(FN::callAddrMAX)+Find("server.dll", FN::MAXDEFPAT));
	//INIT_HK(GiveAmmo); other funcs's player pointer is edi itself,we don't need hk them....
	//INIT_HK(GetAmmoCount);
	INIT_HK(RemoveAmmo);
	INIT_HK(CanHaveAmmo);
	//INIT_HK(CC_GiveCurrentAmmo1);
	//INIT_HK(CC_GiveCurrentAmmo2);
}
#pragma once
#include "..\base.h"
#include "..\Utils\Myhook\Hook.h"

namespace Weight
{
	/*
	float __fastcall GetPlayerMaxCarriedWeight(void* ecx, void* edx)
	{
		int* ptr_ = nullptr;
		__asm
		{mov ptr_, ecx}
		int idx = GetPlayerIdx(ptr_);
		return MaxCarryArr[idx];
	}*/
	namespace GetMaxCarriedWeight_ecx//ecx == pp 
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? D9 40 2C C3 CC CC CC CC CC CC CC A1 ? ? ? ? D9 40 2C C3 CC CC CC CC CC CC CC A1 ? ? ? ? 56 57";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x8;//retn is ok
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CAmmoDef_MaxCarry_
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? 8B 40 30 99 F7 F9";//edi没有在这个函数内使用，可以用来传参playerpointer！！！
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x8;//99 cdq
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CItem_InventoryBox_CreateAmmoForPlayer//a2参数=玩家，EDI是保存重量的，ecx/ESP+4 == PP
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? 8B 78 30 E8 ? ? ? ? 0F AF DE";//57 8B 7A 30 8B 15 ? ? ? ? 8B 5A 30
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x8;//call
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CreateItemForPlayer//ebx == pp,esi == weights
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? 8B CB 8B 70 30";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0xA;//call
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace AddCarriedWeight//edi == weights ebx == pp
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? 8B 78 30 39 3E";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace PlayerWpnPickedUp//eax == weights ebx == pp
	{
		constexpr const char* PATTERN = "8D 93 1C 13 00 00 8B 40 30";//8D 93 50 13 00 00 8B 40 30 89 45 FC
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x9;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace PlayerBumpWpn//esi == weights  pp == ebx
	{
		constexpr const char* PATTERN = "03 BB 1C 13 00 00 8B 72 30";//50 13->1c 13
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x9;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace GetWeightSpeedFactor//ebx == pp edi == weights
	{
		constexpr const char* PATTERN = "A1 ? ? ? ? 8B 78 30 E8 ? ? ? ? 8B C8";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x8;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace HasEnoughInventoryRoomForWeapon//esi == pp,esi == weights
	{
		constexpr const char* PATTERN = "03 BE 1C 13 00 00 8B 71 30";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0x9;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace HasLeftoverWeight//ESI == PP XMM0 == WEIGHTS
	{
		constexpr const char* PATTERN = "8B F1 F3 0F 10 40 2C F3 0F 11 45 FC E8";
		inline DWORD jmpAddr = 0x2;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	void CvarInit();
}

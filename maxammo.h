#pragma once
#include "..\base.h"
#include "..\Utils\Myhook\Hook.h"

typedef int(__thiscall* FnCAmmoDef_MaxCarry_)(void* ecx, int a2);
typedef int(__fastcall* FnGetAmmoData)(void* ecx, void* edx);
extern DWORD g_Pid;

namespace Weight
{
	namespace FN
	{
		constexpr const char* AMMODATAPAT = "6A 08 6A 04 6A 00 51 D9 1C 24 6A 3C 68 2C 01 00 00 6A 19";
		inline FnGetAmmoData callAddrAMMO = (FnGetAmmoData)-59;//new number
		constexpr const char* MAXDEFPAT = "55 8B EC 8B 55 08 83 FA 01 7C 46 3B 91 84 07";
		inline FnCAmmoDef_MaxCarry_ callAddrMAX = 0x0;
	}
	namespace GiveAmmo//no
	{
		constexpr const char* PATTERN = "53 56 E8 ? ? ? ? 8B C8 E8 ? ? ? ?";
		inline DWORD jmpAddr = 0x2;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace GetAmmoCount//no
	{
		constexpr const char* PATTERN = "56 E8 ? ? ? ? 8B C8 E8 ? ? ? ? 83 F8 FE";
		inline DWORD jmpAddr = 0x2;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace RemoveAmmo
	{
		constexpr const char* PATTERN = "57 E8 ? ? ? ? 8B C8 E8 ? ? ? ? 83 F8 FE 74 3E";//使用EBX或者ESP+8构造。
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0xD;//cmp 
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CanHaveAmmo
	{
		constexpr const char* PATTERN = "57 E8 ? ? ? ? 8B C8 E8 ? ? ? ? 8B 4D 08 8B F0 57 8B 11 FF";
		inline DWORD jmpAddr = 0x0;
		inline DWORD jmpBack = 0xD;//mov
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CC_GiveCurrentAmmo1
	{
		constexpr const char* PATTERN = "8B C8 E8 ? ? ? ? FF 75 F8 8B 3F";
		inline DWORD jmpAddr = 0x2;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	namespace CC_GiveCurrentAmmo2
	{
		constexpr const char* PATTERN = "8B C8 E8 ? ? ? ? 8B 3F 8B F0";
		inline DWORD jmpAddr = 0x2;
		inline DWORD jmpBack = 0xA;
		void Hook();
		inline InlineHook* hook = nullptr;
	}
	void MaxammoInit();
}
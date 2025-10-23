#pragma once
#include "base.h"
//https://github.com/Lak3/l4d2-internal-base/blob/main/src/Util/Pattern/Pattern.h
#define INRANGE(x,a,b)	(x >= a && x <= b)
#define GetBits(x)		(INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetBytes(x)		(GetBits(x[0]) << 4 | GetBits(x[1]))
namespace Utils
{
	namespace PatternScan
	{
        

		DWORD FindPattern(const DWORD dwAddress, const DWORD dwLen, const char* const szPattern);
   
        DWORD Find(const char* const szModule, const char* const szPattern);

		DWORD GetProcModuleAddr(DWORD pid, const char* moduleName);
		
	}
}
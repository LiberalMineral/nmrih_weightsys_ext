#include "PatternScan.h"

using namespace Utils;

DWORD PatternScan::FindPattern(const DWORD dwAddress, const DWORD dwLen, const char* const szPattern)
{
    const char* szPatt = szPattern;
    DWORD dwFirstMatch = 0x0;

    for (DWORD dwCur = dwAddress; dwCur < dwLen; dwCur++)
    {
        if (!szPatt)
            return dwFirstMatch;

        const BYTE pCurByte = *(BYTE*)dwCur;
        const BYTE pBytePatt = *(BYTE*)szPatt;

        if (pBytePatt == '\?' || pCurByte == GetBytes(szPatt))
        {
            if (!dwFirstMatch)
                dwFirstMatch = dwCur;

            if (!szPatt[2])
                return dwFirstMatch;

            szPatt += (pBytePatt == '\?\?' || pBytePatt != '\?') ? 3 : 2;
        }
        else
        {
            szPatt = szPattern;
            dwFirstMatch = 0x0;
        }
    }

    return 0x0;
}

DWORD PatternScan::Find(const char* const szModule, const char* const szPattern)
{
    const DWORD dwMod = reinterpret_cast<DWORD>(GetModuleHandleA(szModule));

    if (!dwMod)
        return 0x0;

    const PIMAGE_NT_HEADERS32 pNTH = reinterpret_cast<PIMAGE_NT_HEADERS32>(dwMod + reinterpret_cast<PIMAGE_DOS_HEADER>(dwMod)->e_lfanew);

    if (!pNTH)
        return 0x0;

    return PatternScan::FindPattern(dwMod + pNTH->OptionalHeader.BaseOfCode, dwMod + pNTH->OptionalHeader.SizeOfCode, szPattern);
}

DWORD PatternScan::GetProcModuleAddr(DWORD pid, const char* moduleName)
{
	{
		HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
		MODULEENTRY32 module32;
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		if (hModuleSnap == INVALID_HANDLE_VALUE)
		{
			printf("[ERROR]Could not Get The Module Snap Enum!\n");
			return ERROR;
		}
		module32.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(hModuleSnap, &module32))
		{
			printf("[ERROR]There is no more FirstModule!\n");
			return ERROR;
		}
		do
		{
			if (strcmp(module32.szModule, moduleName) == 0)
			{
				CloseHandle(hModuleSnap);
				//MessageBox(NULL, L"GEEEEEEEEEEEETTTTTTT!", L"yes", MB_OK);
				printf("get is :%p\n", module32.modBaseAddr);
				//g_std = (DWORD)module32.modBaseAddr;
				return (DWORD)module32.modBaseAddr;
			}
#ifdef _DEBUG
			wprintf(L"wprintf szWchar = %s\n", module32.szModule);
#endif
		} while (Module32Next(hModuleSnap, &module32));
		//MessageBox(NULL, L"NOT!!GEEEEEEEEEEEETTTTTTT!", L"yes", MB_OK);
		CloseHandle(hModuleSnap);
		return ERROR;
	}
}

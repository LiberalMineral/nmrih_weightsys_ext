#include "base.h"

__declspec(noinline) int __cdecl GetPlayerIdx(const int* pp)
{
    int* v1 = (int*)*(int*)(pp + 6);
    int result = 0;
    if (v1)
        result = *(char*)((char*)v1 + 6);
    else
        result = 0;
    return result;
}
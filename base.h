#pragma once
#include <iostream>
#include <cstdint>
#include <memory>
#include <Windows.h>
#include <TlHelp32.h>


__declspec(noinline)  int __cdecl GetPlayerIdx(const int* pp);

inline float MaxCarryArr[64] = {};
#define INIT_HK(names)\
					names::jmpAddr+=Find("server.dll",names::PATTERN);\
					names::jmpBack+=names::jmpAddr;\
					names::hook = new InlineHook(names::jmpAddr,names::Hook);\
					names::hook->Hook()
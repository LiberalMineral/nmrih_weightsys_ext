#pragma once
#include "base.h"

//from internet.
class VMTHook
{
private:
	std::uintptr_t** baseclass = nullptr;
	std::unique_ptr<std::uintptr_t[]> current_vft = nullptr;
	std::uintptr_t* original_vft = nullptr;
	std::size_t total_functions = 0;
public:

	VMTHook(void) = default;
	VMTHook(const VMTHook&) = delete;
	//构造函数：传递基址，记录v函数数量，获取原地址，分配新vft的函数表并重新赋给baseclass;
	VMTHook(void* baseclass, int idx = 0) {
		this->baseclass = static_cast<std::uintptr_t**>(baseclass);

		while (static_cast<std::uintptr_t*>(*(this->baseclass + idx))[this->total_functions])
			++this->total_functions;

		const std::size_t table_size = this->total_functions * sizeof(std::uintptr_t);

		this->original_vft = *(this->baseclass + idx);
		this->current_vft = std::make_unique<std::uintptr_t[]>(this->total_functions + 1);

		std::memcpy((this->current_vft.get() + 1), this->original_vft, table_size);
		//extern DWORD g_mat;
		int rtti_info_ptr = (int)(*(this->baseclass)) - 4;
		std::memcpy(this->current_vft.get(), (void*)rtti_info_ptr, 4);
		*(this->baseclass + idx) = (this->current_vft.get() + 1);
	};
	//还原vft
	~VMTHook() {
		//*(this->baseclass + idx) = this->original_vft;
	};
	//取原函数
	template <typename Fn = void*> inline const Fn GetOriginalFunction(std::size_t function_index) {
		return reinterpret_cast<Fn>(this->original_vft[function_index]);
	}
	//hook
	inline bool HookFunction(void* new_function, const std::size_t function_index) {
		if (function_index > this->total_functions)
			return false;

		this->current_vft[function_index + 1] = reinterpret_cast<std::uintptr_t>(new_function);

		return true;
	}
	//还原hook
	inline bool UnhookFunction(const std::size_t function_index) {
		if (function_index > this->total_functions)
			return false;

		this->current_vft[function_index + 1] = this->original_vft[function_index];

		return true;
	}
	//返回全部数量。
	inline std::size_t GetTotalFunctions() {
		return this->total_functions;
	}
};
extern DWORD g_Pid;
class InlineHook
{
public:
	InlineHook(const InlineHook&) = delete;
	InlineHook() = delete;
	InlineHook(DWORD addr, void* func)
	{
		hookaddr = addr;
		pFunc = func;
	}
	bool Hook()
	{
		DWORD jmpAddr = (DWORD)pFunc - (hookaddr + 5);
		//UINT offset = 1 + (m_nCodeLen - m_nCodeLen);
		BYTE jmpCode[5];
		*(jmpCode + 0) = 0xE9;
		*(DWORD*)(jmpCode + 1) = jmpAddr;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, g_Pid);
		if (ReadProcessMemory(hProcess, (LPVOID)hookaddr, retoredcodes, 5, NULL) == 0) {
			goto RETURN_AND_CLOSE;
		}
		if (WriteProcessMemory(hProcess, (LPVOID)hookaddr, jmpCode, 5, NULL) == 0) {
			//delete jmpCode;
			goto RETURN_AND_CLOSE;
		}
		ishooking = true;
		RETURN_AND_CLOSE:
		CloseHandle(hProcess);
		return ishooking;
	}
	void Unhook()
	{
		if (!ishooking)return;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, g_Pid);
		WriteProcessMemory(hProcess, (LPVOID)hookaddr, retoredcodes, 5, NULL);
		CloseHandle(hProcess);
		ishooking = false;
	}
	bool IsHooking()
	{
		return ishooking;
	}
private:
	BYTE retoredcodes[5];
	DWORD hookaddr;
	void* pFunc = nullptr;
	bool ishooking = false;
};
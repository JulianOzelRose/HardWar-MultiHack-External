#pragma once
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <TlHelp32.h>

DWORD GetProcessId(const wchar_t* processName);
uintptr_t GetModuleBaseAddress(DWORD processId, const wchar_t* moduleName);
uintptr_t FindDmaAddress(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
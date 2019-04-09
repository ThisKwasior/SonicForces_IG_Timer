#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

#include <string>

DWORD GetProcId(const std::string* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const std::string* modName);

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);
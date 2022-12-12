#pragma once
//	Windows API
#include <Windows.h>
#include <atomic>
#include <chrono>
#include <vector>

namespace InternalOverlayBase {
	using namespace std::chrono_literals;
	inline HMODULE g_hModule{};
	inline LPCWSTR g_ModuleName{};
	static HANDLE g_moduleHandle = GetModuleHandle(g_ModuleName);
	static DWORD g_processID = GetCurrentProcessId();
	static HWND g_WindowHandle{};
	static uintptr_t dwEntryPoint{ 0 };
	static uintptr_t dwGameBase = (uintptr_t)g_moduleHandle;
}
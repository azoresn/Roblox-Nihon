#include "Hooking.hpp"

Hooking::Hooking()
{
	MH_Initialize();
#if CONSOLE_OUTPUT
	g_Console->printdbg("Hooking::Initialized\n", Console::Colors::pink);
#endif
	return;
}

Hooking::~Hooking()
{
	MH_RemoveHook(MH_ALL_HOOKS);
}

void Hooking::Hook()
{
	g_GameVariables->Init();
	g_D3D11Window->Hook();
	MH_EnableHook(MH_ALL_HOOKS);
#if CONSOLE_OUTPUT
	g_Console->printdbg("Hooking::Hook Initialized\n", Console::Colors::pink);
#endif
	return;
}

void Hooking::Unhook()
{
	g_D3D11Window->Unhook();
	MH_RemoveHook(MH_ALL_HOOKS);
	g_Console->DestroyConsole();
	return;
}

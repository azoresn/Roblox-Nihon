#pragma once
#include "helper.h"
#include "Overlay.hpp"

void BackgroundWorker()
{
    while (g_Running) {
        g_Menu->Loops();
        std::this_thread::sleep_for(1ms);
    }
    return;
}

void InitializeFramework()
{
    /// INIT INFO
    g_Engine = std::make_unique<PS2>();
    g_Console = std::make_unique<Console>();
    g_Console->InitializeConsole("SOCOM 1 - INTERNAL DEBUG");
    g_Console->printdbg("[+] SOCOM INTERNAL\n[+] BUILD VERSION: v1.0\n[+] BUILD DATE: 11/9/22\n[+] Created by NightFyre\n\n", Console::Colors::yellow);
    g_Console->printdbg("[!] THIS IS ONLY FOR SOCOM 1 (black edition)\n[!] THIS IS A PREVIEW BUILD\n[!] PLEASE DON'T INJECT UNTIL YOU HAVE LAUNCHED THE GAME [INSERT]\n\n", Console::Colors::red);
    g_Console->printdbg("PCSX2 LAUNCHED\n", Console::Colors::green);
    g_Console->printdbg("[!] PLEASE LAUNCH SOCOM & TOGGLE FULLSCREEN\n\n", Console::Colors::yellow);


    // WAIT FOR USER INPUT
    while (GetAsyncKeyState(VK_INSERT) == 0)
        Sleep(60);

    g_Console->printdbg("Initializing NightFyre Framework\n", Console::Colors::yellow);

    /// ESTABLISH GAME DATA   
    g_GameVariables = std::make_unique<GameVariables>();
    g_GameData = std::make_unique<GameData>();

    /// CREATE WINDOW AND ESTABLISH HOOKS
    g_D3D11Window = std::make_unique<D3D11Window>();
    g_Hooking = std::make_unique<Hooking>();

    /// INITIALIZE HOOK
    g_Menu = std::make_unique<Menu>();
    g_Hooking->Hook();

    g_Console->printdbg("NightFyreFramework::Initialized\n\n", Console::Colors::green);
}

DWORD WINAPI MainThread()
{
    InitializeFramework();

    //  INIT UPDATE THREAD
    std::thread UPDATE(BackgroundWorker);

    while (g_Running)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1) g_GameVariables->m_ShowMenu = !g_GameVariables->m_ShowMenu;
    }

    ///  EXIT
    UPDATE.join();
    FreeLibraryAndExitThread(g_hModule, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
#pragma once
#include <windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

// Include Dear ImGui & D3D11
#include "../../libs/ImGui/imgui.h"
#include "../../libs/ImGui/imgui_internal.h"
#include "../../libs/ImGui/imgui_Impl_dx11.h"
#include "../../libs/ImGui/imgui_Impl_Win32.h"
#include "../../libs/SDK/engine.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// Minhook
#include "../../libs/MinHook/MinHook.h"
#include "../../include/Overlay.hpp"
#pragma once

//	External Libraries
#include "../libs/FrameWork/Console.hpp"
#include "../libs/FrameWork/Game.hpp"
#include "../libs/FrameWork/Hooking.hpp"
#include "../libs/SDK/SOCOM1.h"


using namespace SOCOM1;
using namespace std::chrono_literals;
inline std::atomic_bool g_Running = TRUE;
inline std::atomic_bool g_Killswitch = FALSE;
#pragma once
//Windows Includes (SDKs)
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <winternl.h>
#include <d3d11.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <map>
#include <unordered_map>
#include <vector>
#include <array>
#include <wrl/client.h>
#include <random>
#include <filesystem>
#include <timeapi.h>
#pragma comment(lib, "winmm")
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "wldap32")
#pragma comment(lib, "crypt32")
#pragma disable(warning : 4996)
//Namespace Defines
using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
//ImGui Includes
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
//ImGui Defines
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//DirectX Includes
#include <dxgi.h>
#include <d3d11.h>
//MinHook Includes
#include "MinHook.h"
//StackWalker Includes
#include "StackWalker.h"
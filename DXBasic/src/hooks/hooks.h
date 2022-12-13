#pragma once
#include "pch/pch.h"
#include "memory/pointers.h"
#include "hooks/vmt_hooks/vmt_hooks.h"
#include "hooks/detour_hooks/detour_hooks.h"

struct hooks {
public:
	static int64_t scriptVirtualMachine(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* threadContext);
	static BOOL getThreadContext(HANDLE hThread, LPCONTEXT lpContext);
	static LPVOID convertThreadToFiber(LPVOID param);
	static HRESULT present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
	static HRESULT resizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
};
class hooking {
public:
	friend struct hooks;
public:
	hooking();
public:
	void hook();
	void unhook();
public:
	MinHook m_mhKeepalive;
	detour m_scriptVirtualMachine;
	detour m_getThreadContext;
	detour m_convertThreadToFiber;
	hookVFT m_swapchainVft;
};
inline std::unique_ptr<hooking> g_hooking;
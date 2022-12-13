#include "hooks.h"

auto g_kernelModuleHandle{ GetModuleHandleA("kernel32.dll") };
hooking::hooking() :
	m_mhKeepalive(),
	m_scriptVirtualMachine("SVM", g_pointers.m_scriptVirtualMachine, &hooks::scriptVirtualMachine),
	m_convertThreadToFiber("CTTF", GetProcAddress(g_kernelModuleHandle, "ConvertThreadToFiber"), &hooks::convertThreadToFiber),
	m_getThreadContext("GTC", GetProcAddress(g_kernelModuleHandle, "GetThreadContext"), &hooks::getThreadContext),
	m_swapchainVft(VFT(*g_pointers.m_swapchain, 19), VFT({ vft_FunctionData(&hooks::present, 8), vft_FunctionData(&hooks::resizeBuffers, 13) }))
{}
void hooking::hook() {
	m_swapchainVft.enable();
	detour::enableAll();
}
void hooking::unhook() {
	m_swapchainVft.disable();
	detour::disableAll();
}
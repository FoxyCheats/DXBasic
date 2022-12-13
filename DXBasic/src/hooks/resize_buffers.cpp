#include "hooks.h"
#include "imgui_impl_dx11.h"

HRESULT hooks::resizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_InvalidateDeviceObjects();
	auto hr = g_hooking->m_swapchainVft.getOg<decltype(&resizeBuffers)>(13)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	if (SUCCEEDED(hr))
		ImGui_ImplDX11_CreateDeviceObjects();
	return hr;
}
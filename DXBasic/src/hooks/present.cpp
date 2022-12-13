#include "hooks.h"
#include "renderer/renderer.h"

HRESULT hooks::present(IDXGISwapChain* dis, UINT syncInterval, UINT flags) {
	g_renderer->present();
	return g_hooking->m_swapchainVft.getOg<decltype(&present)>(8)(dis, syncInterval, flags);
}
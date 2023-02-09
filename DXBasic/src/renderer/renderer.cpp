#include "renderer/renderer.h"
#include "renderer/fonts/icon_font.h"
#include "renderer/fonts/icon_font.h"
#include "memory/pointers.h"
#include "gui/gui.h"


renderer::renderer() : m_swapchain(*g_pointers.m_swapchain) {
	m_wndProc = WNDPROC(SetWindowLongPtrA(g_pointers.m_hwnd, GWLP_WNDPROC, LONG_PTR(wndProc)));
	if (FAILED(m_swapchain->GetDevice(__uuidof(ID3D11Device), (void**)m_device.GetAddressOf())))
		logNow(fatal, "Failed to create SwapChain device")
	m_device->GetImmediateContext(m_context.GetAddressOf());
	ImGui::CreateContext();
	ImGui::StyleColorsClassic();
	ImGui_ImplDX11_Init(m_device.Get(), m_context.Get());
	ImGui_ImplWin32_Init(g_pointers.m_hwnd);
	m_fontCfg.FontDataOwnedByAtlas = false;
	m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 20.f, &m_fontCfg);
	m_headerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\AriBLK.ttf", gui::sizes::fonts::g_header, &m_fontCfg);
	m_subtitleFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", gui::sizes::fonts::g_subtitle, &m_fontCfg);
	m_optionFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", gui::sizes::fonts::g_option, &m_fontCfg);
	m_footerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", gui::sizes::fonts::g_footer, &m_fontCfg);
	m_descriptionFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", gui::sizes::fonts::g_description, &m_fontCfg);
	m_smallIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), gui::sizes::fonts::icon::g_small, &m_fontCfg);
	m_mediumIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), gui::sizes::fonts::icon::g_medium, &m_fontCfg);
	m_largeIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), gui::sizes::fonts::icon::g_large, &m_fontCfg);
}
renderer::~renderer() {
	SetWindowLongPtrA(g_pointers.m_hwnd, GWLP_WNDPROC, LONG_PTR(m_wndProc));
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
void renderer::present() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	gui::drawing::draw();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
LRESULT renderer::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_renderer.get()) {
		switch (msg) {
		default: {
			ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		} break;
		}
		return CallWindowProcA(g_renderer->m_wndProc, hWnd, msg, wParam, lParam);
	}
	return LRESULT();
}
#include "renderer/renderer.h"
#include "renderer/fonts/icon_font.h"
#include "renderer/fonts/icon_font.h"
#include "memory/pointers.h"
#include "gui/gui.h"

void setColors() {
	auto&& style = ImGui::GetStyle();
	auto&& colors = style.Colors;
	style.Alpha = 1.f;
	style.WindowPadding = ImVec2(8, 8);
	style.PopupRounding = 0.f;
	style.FramePadding = { 8.f, 4.f };
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = { 0.f, 0.f };
	style.IndentSpacing = 21.f;
	style.ScrollbarSize = 8.f;
	style.ScrollbarRounding = 8.f;
	style.GrabMinSize = 6.f;
	style.GrabRounding = 4.25f;
	style.WindowBorderSize = 0.f;
	style.ChildBorderSize = 0.f;
	style.PopupBorderSize = 0.f;
	style.FrameBorderSize = 0.f;
	style.TabBorderSize = 0.f;
	style.WindowRounding = 0.f;
	style.ChildRounding = 3.f;
	style.FrameRounding = 5.f;
	style.TabRounding = 7.f;
	style.WindowTitleAlign = { 0.5f, 0.5f };
	style.ButtonTextAlign = { 0.5f, 0.5f };
	style.DisplaySafeAreaPadding = { 3.f, 3.f };
	colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.f);
	colors[ImGuiCol_Border] = ImVec4(1.f, 1.f, 1.f, 0.88f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.15f, 0.15f, 0.75f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.f, 1.f, 1.f, 1.f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
	colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
	colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
	colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
	colors[ImGuiCol_Separator] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.f, 0.00f, 1.f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.f, 0.00f, 1.f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.f, 0.00f, 0.43f);
}
renderer::renderer() : m_swapchain(*g_pointers.m_swapchain) {
	m_wndProc = WNDPROC(SetWindowLongPtrA(g_pointers.m_hwnd, GWLP_WNDPROC, LONG_PTR(wndProc)));
	if (FAILED(m_swapchain->GetDevice(__uuidof(ID3D11Device), (void**)m_device.GetAddressOf())))
		logNow(fatal, "Failed to create SwapChain device")
	m_device->GetImmediateContext(m_context.GetAddressOf());
	ImGui::CreateContext();
	setColors();
	ImGui_ImplDX11_Init(m_device.Get(), m_context.Get());
	ImGui_ImplWin32_Init(g_pointers.m_hwnd);
	m_fontCfg.FontDataOwnedByAtlas = false;
	m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 20.f, &m_fontCfg);
	m_headerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\AriBLK.ttf", 40.f, &m_fontCfg);
	m_subtitleFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_fontCfg);
	m_optionFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 17.f, &m_fontCfg);
	m_footerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_fontCfg);
	m_descriptionFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 19.f, &m_fontCfg);
	m_smallIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), 10.f, &m_fontCfg);
	m_mediumIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), 15.f, &m_fontCfg);
	m_largeIconFont = ImGui::GetIO().Fonts->AddFontFromMemoryTTF((void*)iconFont, sizeof(iconFont), 20.f, &m_fontCfg);
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
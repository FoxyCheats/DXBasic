#pragma once
#include "pch/pch.h"

class renderer {
public:
	renderer();
	~renderer();
public:
	static LRESULT wndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	WNDPROC m_wndProc;
public:
	void present();
public:
	comPtr<IDXGISwapChain> m_swapchain{};
	comPtr<ID3D11Device> m_device{};
	comPtr<ID3D11DeviceContext> m_context{};
public:
	ImFont* m_font{};
	ImFont* m_headerFont{};
	ImFont* m_subtitleFont{};
	ImFont* m_optionFont{};
	ImFont* m_footerFont{};
	ImFont* m_descriptionFont{};
	ImFont* m_smallIconFont{};
	ImFont* m_mediumIconFont{};
	ImFont* m_largeIconFont{};
	ImFontConfig m_fontCfg{};
};
inline std::unique_ptr<renderer> g_renderer{};
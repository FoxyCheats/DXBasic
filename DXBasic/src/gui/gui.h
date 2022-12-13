#pragma once
#include "pch/pch.h"
#include "gui/submenu_types/submenu.h"

namespace gui {
	inline bool g_isOpen{};
	namespace keys {
		namespace delays {
			inline size_t g_open{ 20 };
			inline size_t g_enter{ 20 };
			inline size_t g_back{ 20 };
			inline size_t g_up{ 10 };
			inline size_t g_down{ 10 };
			inline size_t g_left{ 10 };
			inline size_t g_right{ 10 };
		}
		namespace pressed {
			inline bool g_open{};
			inline bool g_enter{};
			inline bool g_back{};
			inline bool g_up{};
			inline bool g_down{};
			inline bool g_left{};
			inline bool g_right{};
			extern void reset();
		}
		inline int8_t g_open{ VK_INSERT };
		inline int8_t g_enter{ VK_RETURN };
		inline int8_t g_back{ VK_BACK };
		inline int8_t g_up{ VK_UP };
		inline int8_t g_down{ VK_DOWN };
		inline int8_t g_left{ VK_LEFT };
		inline int8_t g_right{ VK_RIGHT };
	}
	inline bool g_pushMenu{ true };
	inline std::stack<menu::types::submenu> g_menus{};
	inline menu::types::submenu g_menuToPush{};
	inline ImVec2 g_pos{ 25.f, 5.f };
	namespace sizes {
		namespace rects {
			inline float g_width{ 350.f };
			inline ImVec2 g_header{ g_width, 100.f };
			inline ImVec2 g_subtitle{ g_width, 37.f };
			inline ImVec2 g_option{ g_width, 35.f };
			inline ImVec2 g_footer{ g_width, 37.f };
			inline ImVec2 g_description{ g_width, 40.f };
		}
		namespace fonts {
			inline float g_header{ 40.f };
			inline float g_subtitle{ 19.f };
			inline float g_option{ 17.f };
			inline float g_footer{ 19.f };
			inline float g_description{ 19.f };
			namespace icon {
				inline float g_small{ 10.f };
				inline float g_medium{ 15.f };
				inline float g_large{ 20.f };
			}
		}
	}
	namespace colors {
		namespace rects {
			inline ImU32 g_header{ IM_COL32(14, 14, 14, 255) };
			inline ImU32 g_subtitle{ IM_COL32(10, 10, 10, 210) };
			inline ImU32 g_option{ IM_COL32(0, 0, 0, 160) };
			inline ImU32 g_optionSelected{ IM_COL32(255, 255, 255, 255) };
			inline ImU32 g_footer{ IM_COL32(10, 10, 10, 210) };
			inline ImU32 g_description{ IM_COL32(20, 20, 20, 255) };
		}
		namespace texts {
			inline ImU32 g_header{ IM_COL32(255, 255, 255, 255) };
			inline ImU32 g_subtitle{ IM_COL32(255, 255, 255, 255) };
			inline ImU32 g_option{ IM_COL32(255, 255, 255, 255) };
			inline ImU32 g_optionSelected{ IM_COL32(10, 10, 10, 255) };
			inline ImU32 g_footer{ IM_COL32(255, 255, 255, 255) };
			inline ImU32 g_description{ IM_COL32(255, 255, 255, 255) };
		}
	}
	namespace menu {
		#define CURRENT_MENU g_menus.top()
		#define MENU_NAME CURRENT_MENU.m_name
		#define MAX_VISIBLE_OPTIONS CURRENT_MENU.m_maxOptions
		#define OPTION_COUNT CURRENT_MENU.m_options.size()
		#define CURRENT_OPTION CURRENT_MENU.m_currentOption
		#define IS_STACK_VALID !g_menus.empty() && g_menus.size() > NULL
		#define GET_OPT(idx) CURRENT_MENU.get(idx)
		namespace options {
			inline size_t g_currentOption{};
		}
		extern void push(menu::types::submenu menu);
		extern void init(menu::types::submenu menu);
		extern void pop();
	}
	namespace drawing {
		namespace menuSections {
			extern void header();
			extern void subtitle();
			extern void option(menu::options::types::abstractOption* opt, bool selected);
			extern void options();
			extern void footer();
			extern void description();
			extern void handleXValues();
		}
		namespace math {
			extern ImRect getRect(ImVec2 pos, ImVec2 size);
			extern ImVec2 getResolution();
			inline ImVec2 g_resolution{};
		}
		extern void rect(ImVec2 pos, ImVec2 size, ImU32 color, ImDrawList* drawList = ImGui::GetBackgroundDrawList());
		extern void line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness = 1.f, ImDrawList* drawList = ImGui::GetForegroundDrawList());
		extern void sprite(ImTextureID* resource, ImVec2 pos, ImVec2 size, ImU32 color, ImDrawList* drawList = ImGui::GetForegroundDrawList());
		extern void text(std::string text, ImVec2 pos, ImU32 color, ImFont* font, ImDrawList* drawList = ImGui::GetForegroundDrawList());
		extern void draw();
	}
	namespace keyHandlers {
		namespace sounds {
			struct soundData {
				bool m_active{};
				std::string_view m_id{};
				std::string_view m_set{ "HUD_FRONTEND_DEFAULT_SOUNDSET" };
			};
			inline soundData g_open{ true, "SELECT" };
			inline soundData g_close{ true, "BACK" };
			inline soundData g_enter{ true, "SELECT" };
			inline soundData g_back{ true, "BACK" };
			inline soundData g_left({ true, "NAV_LEFT_RIGHT" });
			inline soundData g_right{ g_left };
			inline soundData g_up{ true, "NAV_UP_DOWN" };
			inline soundData g_down{ g_up };
			extern void soundQueue(soundData& sound);
		}
		extern void keyPress(bool& isPressed, int8_t key, size_t delay);
		extern void check();
		extern void handle();
	}
}
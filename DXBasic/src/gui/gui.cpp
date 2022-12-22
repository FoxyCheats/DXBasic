#include "gui/gui.h"
#include "gui/option_types/boolean_option.h"
#include "gui/option_types/number_option.h"
#include "fiber/fiber.h"
#include "fiber/manager.h"
#include "fiber/queue.h"
#include "memory/pointers.h"
#include "rage/classes.h"
#include "natives/natives.h"
#include "renderer/renderer.h"
#include "util/timer.h"

namespace gui {
	namespace keys::pressed {
		void reset() {
			g_open = false;
			g_enter = false;
			g_back = false;
			g_up = false;
			g_down = false;
			g_left = false;
			g_right = false;
		}
	}
	namespace sizes {
		ImVec2 getTextSize(strung text) {
			return ImGui::CalcTextSize(text.c_str(), NULL, false, rects::g_width);
		}
	}
	namespace menu {
		void push(menu::types::submenu menu) {
			if (!menu.m_maxOptions) {
				menu.m_maxOptions = 12;
			}
			g_menuToPush = menu;
			g_pushMenu = true;
		}
		void init(menu::types::submenu menu) {
			menu.m_maxOptions = 12;
			push(menu);
		}
		void pop() {
			if (g_menus.size() > 1 && g_menus.top().m_id != "Home"_joaat)
				g_menus.pop();
			else
				g_isOpen = false;
		}
	}
	namespace drawing {
		namespace menuSections {
			void header() {
				auto headerTextOffset = ImGui::CalcTextSize(BRANDING_NAME).x;
				auto offset = g_pos.x + (sizes::rects::g_width / 2.f) - headerTextOffset - 25.f;
				rect(g_pos, sizes::rects::g_header, colors::rects::g_header);
				text(BRANDING_NAME, ImVec2(g_pos.x + offset, (g_pos.y + (sizes::rects::g_header.y / 2.f)) - 20.f), colors::texts::g_header, g_renderer->m_headerFont);
			}
			void subtitle() {
				auto optionText = std::format("{}/{}", CURRENT_OPTION + 1, OPTION_COUNT);
				auto rightAlignOffset = sizes::rects::g_width - ImGui::CalcTextSize(optionText.c_str()).x - 5.25f;
				rect(ImVec2(g_pos.x, g_pos.y + sizes::rects::g_header.y), sizes::rects::g_subtitle, colors::rects::g_subtitle);
				text(MENU_NAME, ImVec2(g_pos.x + 7.f, g_pos.y + sizes::rects::g_header.y + 5.f), colors::texts::g_subtitle, g_renderer->m_subtitleFont);
				text(optionText.c_str(), ImVec2(g_pos.x + rightAlignOffset, g_pos.y + sizes::rects::g_header.y + 5.f), colors::texts::g_subtitle, g_renderer->m_subtitleFont);
			}
			void option(menu::options::types::abstractOption* opt, int count, bool selected) {
				auto offset = 7.f;
				rect(ImVec2(g_pos.x, g_pos.y + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), sizes::rects::g_option, colors::rects::g_option);
				if (selected)
					rect(ImVec2(g_pos.x, g_pos.y + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), sizes::rects::g_option, colors::rects::g_optionSelected);
				text(opt->m_name, ImVec2(g_pos.x + offset, g_pos.y + 9.f + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), selected ? colors::texts::g_optionSelected : colors::texts::g_option, g_renderer->m_optionFont);
				switch (opt->m_type) {
				case menu::options::types::eOptionTypes::SubmenuOption: {
					text(opt->getRightText(), ImVec2(g_pos.x + ((sizes::rects::g_option.x - sizes::getTextSize(opt->getRightText()).x) - 12.f) + 1.f, g_pos.y + 9.3f + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)) , selected ? colors::texts::g_optionSelected : colors::texts::g_option, g_renderer->m_mediumIconFont);
				} break;
				case menu::options::types::eOptionTypes::BooleanOption: {
					text(opt->getRightText(), ImVec2(g_pos.x + ((sizes::rects::g_option.x - sizes::getTextSize(opt->getRightText()).x) - 12.f), g_pos.y + 9.3f + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)) , selected ? colors::texts::g_optionSelected : colors::texts::g_option, g_renderer->m_mediumIconFont);
				} break;
				case menu::options::types::eOptionTypes::NumberOption: {
					text(opt->getRightText(), ImVec2(g_pos.x + ((sizes::rects::g_option.x - sizes::getTextSize(opt->getRightText()).x) - 12.f), g_pos.y + 9.3f + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)) , selected ? colors::texts::g_optionSelected : colors::texts::g_option, g_renderer->m_mediumIconFont);
				} break;
				default: {
					text(opt->getRightText(), ImVec2(g_pos.x + ((sizes::rects::g_option.x - sizes::getTextSize(opt->getRightText()).x) - 5.f) + 1.f, g_pos.y + 9.f + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)) , selected ? colors::texts::g_optionSelected : colors::texts::g_option, g_renderer->m_optionFont);
				} break;
				}
			}
			void options() {
				auto& menu = g_menus.top();
				menu.clearOptions();
				menu.executeOptionAdding();
				if (OPTION_COUNT != 0) {	
					size_t startPoint{}, endPoint{ OPTION_COUNT > MAX_VISIBLE_OPTIONS ? MAX_VISIBLE_OPTIONS : OPTION_COUNT };
					if (OPTION_COUNT > MAX_VISIBLE_OPTIONS && CURRENT_OPTION >= MAX_VISIBLE_OPTIONS - 1)
						startPoint = CURRENT_OPTION - MAX_VISIBLE_OPTIONS, endPoint = CURRENT_OPTION;
					for (size_t i{ startPoint }; i != endPoint; ++i)
						option(GET_OPT(i), i, i == CURRENT_OPTION);
				}
			}
			void footer() {
				auto arrowOffset = sizes::rects::g_width / 2.f - 10.f;
				auto centerArrowOffset = (sizes::rects::g_footer.y / 2.f) - 10.f;
				auto count = MAX_VISIBLE_OPTIONS < OPTION_COUNT ? MAX_VISIBLE_OPTIONS : OPTION_COUNT;
				rect(ImVec2(g_pos.x, g_pos.y + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), sizes::rects::g_footer, colors::rects::g_footer);
				text(CURRENT_OPTION + 1 == OPTION_COUNT ? "u" : (CURRENT_OPTION + 1 == 1 ? "" : "u"), ImVec2(g_pos.x + arrowOffset, g_pos.y + (((CURRENT_OPTION + 1 != 1) && (CURRENT_OPTION + 1 != OPTION_COUNT)) ? 3.f : centerArrowOffset) + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), colors::texts::g_footer, g_renderer->m_mediumIconFont);
				text(CURRENT_OPTION + 1 == 1 ? "d" : (CURRENT_OPTION + 1 == OPTION_COUNT ? "" : "d"), ImVec2(g_pos.x + arrowOffset, g_pos.y + (((CURRENT_OPTION + 1 != 1) && (CURRENT_OPTION + 1 != OPTION_COUNT)) ? 12.5f : centerArrowOffset) + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count)), colors::texts::g_footer, g_renderer->m_mediumIconFont);
			}
			void description() {
				if (auto opt = GET_OPT(CURRENT_OPTION); opt && !opt->m_description.empty()) {
					const auto iconOffset = 7.f;
					const auto iconOffsetFromRight = 8.f;
					const auto textOffset = iconOffset + 24.f;
					const auto textOffsetFromRight = 10.f;
					auto count = MAX_VISIBLE_OPTIONS < OPTION_COUNT ? MAX_VISIBLE_OPTIONS : OPTION_COUNT;
					rect(ImVec2(g_pos.x, g_pos.y + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count) + sizes::rects::g_footer.y), sizes::rects::g_description, colors::rects::g_description);
					text("i", ImVec2(g_pos.x + iconOffset, g_pos.y + textOffsetFromRight + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count) + sizes::rects::g_footer.y), colors::texts::g_description, g_renderer->m_mediumIconFont);
					text(opt->m_description, ImVec2(g_pos.x + textOffset, g_pos.y + textOffsetFromRight + sizes::rects::g_header.y + sizes::rects::g_subtitle.y + (sizes::rects::g_option.y * count) + sizes::rects::g_footer.y), colors::texts::g_description, g_renderer->m_descriptionFont);
				}
			}
			void handleXValues() {
				sizes::rects::g_header.x = sizes::rects::g_subtitle.x = sizes::rects::g_option.x = sizes::rects::g_footer.x = sizes::rects::g_description.x = sizes::rects::g_width;
			}
		}
		namespace math {
			ImRect getRect(ImVec2 pos, ImVec2 size) {
				const auto itemSize = ImGui::CalcItemSize(ImVec2(size.x, size.y), 0.0f, 0.0f);
				return ImRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + itemSize.x, pos.y + itemSize.y));
			}
			ImVec2 getResolution() {
				return ImGui::GetIO().DisplaySize;
			}
		}
		void rect(ImVec2 pos, ImVec2 size, ImU32 color, ImDrawList* drawList) {
			const ImRect rect = math::getRect(pos, size);
			drawList->AddRectFilled(rect.Max, rect.Min, color);
		}
		void line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness, ImDrawList* drawList) {
			const ImRect rect = math::getRect(pos, size);
			drawList->AddRect(rect.Min, rect.Max, color, 0.f, 15, thickness);
		}
		void sprite(ImTextureID* resource, ImVec2 pos, ImVec2 size, ImU32 color, ImDrawList* drawList) {
			const ImRect rect = math::getRect(pos, size);
			drawList->AddImage(resource, rect.Min, rect.Max, ImVec2(0, 0), ImVec2(1, 1), color);
		}
		void text(strung text, ImVec2 pos, ImU32 color, ImFont* font, ImDrawList* drawList) {
			ImGui::PushFont(font);
			drawList->AddText(pos, color, text.c_str());
			ImGui::PopFont();
		}
		void draw() {
			keyHandlers::check();
			if (IS_STACK_VALID) {
				keyHandlers::handle();
				if (g_isOpen) {
					menuSections::header();
					menuSections::subtitle();
					menuSections::options();
					menuSections::footer();
					menuSections::description();
					menuSections::handleXValues();
				}
				keys::pressed::reset();
			}
			if (g_pushMenu) {
				g_menus.push(g_menuToPush);
				g_pushMenu = false;
			}
		}
	}
	namespace keyHandlers {
		namespace sounds {
			void soundQueue(soundData& sound) {
				if (sound.m_active) {
					fibers::queue::g_queue.add([&] {
						AUDIO::PLAY_SOUND_FRONTEND(-1, sound.m_id.data(), sound.m_set.data(), NULL);
					});
				}
			}
		}
		void keyPress(bool& isPressed, int8_t key, size_t delay) {
			if (GetForegroundWindow() == g_pointers.m_hwnd) {
				static simpleTimer t{};
				if (GetAsyncKeyState(key) & 1) {
					isPressed = true;
				}
				else if (GetAsyncKeyState(key) & 0x8000) {
					t.start(delay * 100);
					if (t.isReady())
						isPressed = true;
				}
				else {
					t.reset();
				}
			}
		}
		void check() {
			keyPress(keys::pressed::g_open, keys::g_open, keys::delays::g_open);
			keyPress(keys::pressed::g_enter, keys::g_enter, keys::delays::g_enter);
			keyPress(keys::pressed::g_back, keys::g_back, keys::delays::g_back);
			keyPress(keys::pressed::g_up, keys::g_up, keys::delays::g_up);
			keyPress(keys::pressed::g_down, keys::g_down, keys::delays::g_down);
			keyPress(keys::pressed::g_left, keys::g_left, keys::delays::g_left);
			keyPress(keys::pressed::g_right, keys::g_right, keys::delays::g_right);
		}
		void handle() {
			if (keys::pressed::g_open) {
				soundQueue(g_isOpen ? sounds::g_open : sounds::g_close);
				g_isOpen ^= true;
			}
			if (g_isOpen) {
				if (keys::pressed::g_enter) {
					soundQueue(sounds::g_enter);
					CURRENT_MENU.action(menu::types::eActionType::Enter);
				}
				if (keys::pressed::g_back) {
					soundQueue(sounds::g_back);
					menu::pop();
				}
				if (keys::pressed::g_up) {
					soundQueue(sounds::g_up);
					CURRENT_MENU.action(menu::types::eActionType::Up);
				}
				if (keys::pressed::g_down) {
					soundQueue(sounds::g_down);
					CURRENT_MENU.action(menu::types::eActionType::Down);
				}
				if (keys::pressed::g_left) {
					soundQueue(sounds::g_left);
					CURRENT_MENU.action(menu::types::eActionType::Left);
				}
				if (keys::pressed::g_right) {
					soundQueue(sounds::g_right);
					CURRENT_MENU.action(menu::types::eActionType::Right);
				}
			}
		}
	}
}
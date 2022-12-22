#pragma once
#include <functional>
#include "abstract_option.h"
#include "gui/submenu_types/submenu.h"
#include "gui/gui.h"

namespace gui::menu::options::types {
	class submenuOption : public abstractOption {
	public:
		submenuOption(strung name, strung description, menu::types::submenu submenu, std::function<void()> action) :
			abstractOption(name, description, eOptionTypes::SubmenuOption),
			m_submenu(submenu),
			m_action(std::move(action))
		{}
		submenuOption(strung name, strung description, menu::types::submenu submenu) :
			submenuOption(name, description, submenu, nullptr)
		{}
		submenuOption(strung name, menu::types::submenu submenu, std::function<void()> action) :
			submenuOption(name, strung(), submenu, std::move(action))
		{}
		submenuOption(strung name, menu::types::submenu submenu) :
			submenuOption(name, submenu, nullptr)
		{}
	public:
		void action(eActionType type) {
			switch (type) {
			case eActionType::Enter: {
				if (m_action)
					m_action();
				gui::menu::push(m_submenu);
			} break;
			}
		}
		strung getRightText() {
			return "r";
		}
	public:
		std::function<void()> m_action{};
		menu::types::submenu m_submenu{};
	};
}
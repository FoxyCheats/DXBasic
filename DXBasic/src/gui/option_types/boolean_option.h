#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	class booleanOption : public abstractOption {
	public:
		booleanOption(strung name, strung description, bool* boolean, std::function<void()> action) :
			m_action(std::move(action)),
			m_boolean(boolean),
			abstractOption(name, description, eOptionTypes::BooleanOption)
		{}
		booleanOption(strung name, strung description, bool* boolean) :
			booleanOption(name, description, boolean, nullptr)
		{}
		booleanOption(strung name, bool* boolean, std::function<void()> action) :
			booleanOption(name, strung(), boolean, std::move(action))
		{}
		booleanOption(strung name, bool* boolean) :
			booleanOption(name, boolean, std::function<void()>(nullptr))
		{}
	public:
		void action(eActionType type) {
			switch (type) {
			case eActionType::Enter: {
				if (m_boolean)
					*m_boolean ^= true;
				if (m_action)
					m_action();
			} break;
			}
		}
		strung getRightText() {
			return m_boolean ? (*m_boolean ? "g" : "b") : "";
		}
	public:
		std::function<void()> m_action{};
		bool* m_boolean{};
	};
}
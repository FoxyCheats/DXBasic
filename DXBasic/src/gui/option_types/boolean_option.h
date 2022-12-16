#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	class booleanOption : public abstractOption {
	public:
		booleanOption(std::string name, std::string description, bool& boolean, std::function<void()> action) :
			abstractOption(name, m_right.empty() ? getRight() : m_right, description, eOptionTypes::BooleanOption),
			m_boolean(&boolean),
			m_right(getRight()),
			m_action(std::move(action))
		{}
		booleanOption(std::string name, std::string description, bool& boolean) : booleanOption(name, description, boolean, nullptr)
		{}
		booleanOption(std::string name, bool& boolean, std::function<void()> action) :
			booleanOption(name, std::string(), boolean, std::move(action))
		{}
		booleanOption(std::string name, bool& boolean) :
			booleanOption(name, boolean, nullptr)
		{}
	public:
		std::string getRight() {
			return *m_boolean ? "g" : "b";
		}
		void action(eActionType type) {
			switch (type) {
			case eActionType::Enter: {
				if (m_action)
					m_action();
			} break;
			}
		}
	public:
		std::function<void()> m_action{};
		bool* m_boolean{};
		std::string m_right{};
	};
}
#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	class numberOption : public abstractOption {
	public:
		numberOption(std::string name, std::string description, std::function<void()> action) : abstractOption(name, "", description, eOptionTypes::RegularOption), m_action(std::move(action)) {}
		numberOption(std::string name, std::string description) : numberOption(name, description, nullptr) {}
		numberOption(std::string name, std::function<void()> action) : numberOption(name, std::string(), std::move(action)) {}
		numberOption(std::string name) : numberOption(name, std::function<void()>(nullptr)) {}
	public:
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
	};
}
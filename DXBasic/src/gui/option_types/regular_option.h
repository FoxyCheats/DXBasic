#pragma once
#include "abstract_option.h"
#include <functional>

namespace gui::menu::options::types {
	class regularOption : public abstractOption {
	public:
		regularOption(std::string name, std::string description, std::function<void()> action) : abstractOption(name, description, eOptionTypes::RegularOption), m_action(action) {}
		regularOption(std::string name, std::string description) : regularOption(name, description, nullptr) {}
		regularOption(std::string name, std::function<void()> action) : regularOption(name, std::string(), action) {}
		regularOption(std::string name) : regularOption(name, std::string(), nullptr) {}
		virtual void callAction() override {
			if (m_action)
				m_action();
		}
	public:
		std::function<void()> m_action{};
	};
}
#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	class regularOption : public abstractOption {
	public:
		regularOption(std::string name, std::string description, std::function<void()> action) :
			abstractOption(name, "", description, eOptionTypes::RegularOption),
			m_action(std::move(action))
		{}
		regularOption(std::string name, std::string description) :
			regularOption(name, description, nullptr)
		{}
		regularOption(std::string name, std::function<void()> action) :
			regularOption(name, std::string(), std::move(action))
		{}
		regularOption(std::string name) :
			regularOption(name, std::function<void()>(nullptr))
		{}
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
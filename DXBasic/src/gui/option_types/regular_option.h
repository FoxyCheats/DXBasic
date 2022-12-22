#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	class regularOption : public abstractOption {
	public:
		regularOption(strung name, strung description, std::function<void()> action) :
			abstractOption(name, description, eOptionTypes::RegularOption),
			m_action(std::move(action))
		{}
		regularOption(strung name, strung description) :
			regularOption(name, description, nullptr)
		{}
		regularOption(strung name, std::function<void()> action) :
			regularOption(name, strung(), std::move(action))
		{}
		regularOption(strung name) :
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
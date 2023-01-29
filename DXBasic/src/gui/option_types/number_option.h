#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	template <typename type>
	class numberOption : public abstractOption {
	public:
		numberOption(strung name, strung description, type* number, type increment, type minimum, type maximum, std::function<void()> action) :
			abstractOption(name, description, eOptionTypes::NumberOption),
			m_number(number), m_increment(increment), m_minimum(minimum), m_maximum(maximum),
			m_action(std::move(action))
		{}
		numberOption(strung name, strung description, type* number) : numberOption(name, description, number, nullptr)
		{}
		numberOption(strung name, type* number, std::function<void()> action) :
			numberOption(name, strung(), number, std::move(action))
		{}
		numberOption(strung name, type* number) :
			numberOption(name, number, nullptr)
		{}
	public:
		void action(eActionType type) {
			switch (type) {
			case eActionType::Enter: {
				if (m_action)
					m_action();
			} break;
			case eActionType::Left: {
				if (*m_number > m_minimum)
					*m_number -= m_increment;
				else
					*m_number = m_maximum;
			} break;
			case eActionType::Right: {
				if (*m_number < m_maximum)
					*m_number += m_increment;
				else
					*m_number = m_minimum;
			} break;
			}
		}
		strung getRightText() {
			//Cursed
			if (std::is_same_v<std::remove_pointer_t<decltype(m_number)>, float>::value) {
				std::ostringstream ss;
				ss << float(*m_number);
				return ss.str();
			}
			else if (std::is_same_v<std::remove_pointer_t<decltype(m_number)>, double>::value) {
				std::ostringstream ss;
				ss << double(*m_number);
				return ss.str();
			}
			else {
				return std::format("{}", *m_number);
			}
			return "";
		}
	public:
		std::function<void()> m_action{};
		type* m_number{};
		type m_increment{};
		type m_minimum{};
		type m_maximum{};
	};
}
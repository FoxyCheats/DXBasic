#pragma once
#include <functional>
#include "abstract_option.h"

namespace gui::menu::options::types {
	template <typename type>
	class numberOption : public abstractOption {
	public:
		numberOption(std::string name, std::string description, type& number, type increment, type minimum, type maximum, std::function<void()> action) :
			abstractOption(name, m_right.empty() ? getRight() : m_right, description, eOptionTypes::NumberOption),
			m_number(&number), m_increment(increment), m_minimum(minimum), m_maximum(maximum),
			m_action(std::move(action))
		{}
		numberOption(std::string name, std::string description, type& number) : numberOption(name, description, number, nullptr)
		{}
		numberOption(std::string name, type& number, std::function<void()> action) :
			numberOption(name, std::string(), number, std::move(action))
		{}
		numberOption(std::string name, type& number) :
			numberOption(name, number, nullptr)
		{}
	public:
		std::string getRight() {
			if (std::is_same_v<std::remove_pointer_t<decltype(m_number)>, float>::value) {
				std::ostringstream ss;
				ss << float(*m_number);
				m_right = ss.str();
			}
			else if (std::is_same_v<std::remove_pointer_t<decltype(m_number)>, double>::value) {
				std::ostringstream ss;
				ss << double(*m_number);
				m_right = ss.str();
			}
			else {
				m_right = std::format("{}", *m_number);
			}
			return m_right;
		}
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
	public:
		std::function<void()> m_action{};
		type* m_number{};
		type m_increment{};
		type m_minimum{};
		type m_maximum{};
		std::string m_right{};
	};
}
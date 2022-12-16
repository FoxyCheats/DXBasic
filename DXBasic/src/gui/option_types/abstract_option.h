#pragma once
#include "pch/pch.h"

namespace gui::menu::options::types {
	enum class eOptionTypes : int32_t {
		InvalidOption = -1,
		RegularOption,
		SubmenuOption,
		BooleanOption,
		NumberOption,
	};
	enum class eActionType : uint8_t {
		Enter,
		Up,
		Down,
		Left,
		Right
	};
	class abstractOption {
	public:
		abstractOption(std::string name, std::string right, std::string description, eOptionTypes type) :
			m_name{ name }, m_right{ right }, m_description{ description }, m_type{ type }
		{}
	public:
		virtual ~abstractOption() = default;
		virtual void action(eActionType type) = 0;
	public:
		std::string m_name{};
		std::string m_right{};
		std::string m_description{};
		eOptionTypes m_type{};
	};
}
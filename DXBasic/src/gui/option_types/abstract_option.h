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
		abstractOption(strung name, strung description, eOptionTypes type) :
			m_name{ name }, m_description{ description }, m_type{ type }
		{}
	public:
		virtual ~abstractOption() {};
		virtual void action(eActionType type) {};
		virtual strung getRightText() { return strung(); } //Because bool options and other shit dies without a function for it. ffs
	public:
		strung m_name{};
		strung m_description{};
		eOptionTypes m_type{};
	};
}
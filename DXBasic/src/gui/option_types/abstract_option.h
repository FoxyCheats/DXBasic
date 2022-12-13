#pragma once
#include "pch/pch.h"

namespace gui::menu::options::types {
	enum class eOptionTypes : int32_t {
		InvalidOption = -1,
		RegularOption,
		SubOption,
		BoolOption,
	};
	class abstractOption {
	public:
		abstractOption(std::string name, std::string description, eOptionTypes type) : m_name{ name }, m_description{ description }, m_type{ type } {}
		virtual ~abstractOption() = default;
		virtual void callAction() { return; }
		std::string m_name{};
		std::string m_description{};
		eOptionTypes m_type{};
	};
}
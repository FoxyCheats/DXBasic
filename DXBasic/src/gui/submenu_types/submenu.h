#pragma once
#include "pch/pch.h"
#include "gui/option_types/abstract_option.h"
#include <exceptions/exception_handler.h>

namespace gui::menu::types {
	inline void exceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
		if (!exceptions::onExceptionCallback_TryExcept(exceptionInfo))
			return;
	}
	class submenu {
	public:
		submenu(std::string name, uint32_t id, std::function<void(submenu&)> action) : m_name(name), m_id(id), m_action(action) {}
		submenu(std::string name, uint32_t id) : submenu(name, id, nullptr) {}
		submenu(std::string name) : submenu(name, name.empty() ? NULL : joaat(name)) {}
		submenu() : submenu("") {}
	public:
		void add(options::types::abstractOption option) {
			m_options.emplace_back(new options::types::abstractOption(option));
		}
		options::types::abstractOption* get(size_t idx) {
			if (idx > m_options.size())
				return nullptr;
			return m_options[idx].get();
		}
		void callAction() {
			if (m_action)
				m_action(static_cast<submenu&>(*this));
		}
		void setAction(fnptr<void(submenu&)> action) {
			m_action = action;
		}
		void executeOptionAdding() {
			std::thread thr([=] {
				__try {
					if (const auto& act = m_action; act) {
						act(static_cast<submenu&>(*this));
					}
				}
				__except (exceptionHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) {}
				if (m_currentOption >= m_options.size())
					m_currentOption = 0;
			});
			if (thr.joinable())
				thr.join();
		}
		void clearOptions() {
			m_options.clear();
		}
	public:
		int m_maxOptions{};
		int m_currentOption{};
	public:
		std::string m_name{};
		uint32_t m_id{};
		std::vector<std::shared_ptr<options::types::abstractOption>> m_options{};
		std::function<void(submenu&)> m_action{};
	};
}
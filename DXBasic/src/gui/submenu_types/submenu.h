#pragma once
#include "pch/pch.h"
#include "gui/option_types/abstract_option.h"
#include <exceptions/exception_handler.h>

namespace gui::menu::types {
	using namespace options::types;
	inline void exceptionHandler(PEXCEPTION_POINTERS exceptionInfo) {
		if (!exceptions::onExceptionCallback_TryExcept(exceptionInfo))
			return;
	}
	class submenu {
	public:
		submenu(std::string name, uint32_t id, std::function<void(submenu&)> action) : m_name(name), m_id(id), m_action(std::move(action)) {}
		submenu(std::string name, uint32_t id) : submenu(name, id, nullptr) {}
		submenu(std::string name, std::function<void(submenu&)> action) : submenu(name, name.empty() ? NULL : joaat(name), action) {}
		submenu(std::string name) : submenu(name, nullptr) {}
		submenu() : submenu("") {}
	public:
		template <typename type>
		void add(type option) {
			m_options.emplace_back(new type(option));
		}
		options::types::abstractOption* get(size_t idx) {
			if (idx > m_options.size())
				return nullptr;
			return m_options[idx].get();
		}
	public:
		void callAction() {
			if (m_action)
				m_action(static_cast<submenu&>(*this));
		}
		void setAction(fnptr<void(submenu&)> action) {
			m_action = std::move(action);
		}
	public:
		void setCurrentOption(size_t position) {
			m_currentOption = position;
		}
		size_t getCurrentOption() {
			return m_currentOption;
		}
	public:
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
		void action(eActionType type) {
			switch (type) {
			case eActionType::Up: {
				if (getCurrentOption() > 0)
					setCurrentOption(getCurrentOption() - 1);
				else
					setCurrentOption(m_options.size() - 1);
			} break;
			case eActionType::Down: {
				if (getCurrentOption() < m_options.size() - 1)
					setCurrentOption(getCurrentOption() + 1);
				else
					setCurrentOption(0);
			} break;
			default: {
				get(m_currentOption)->action(type);
			} break;
			}
		}
	public:
		int m_maxOptions{};
		size_t m_currentOption{};
	public:
		std::string m_name{};
		uint32_t m_id{};
		std::vector<std::shared_ptr<options::types::abstractOption>> m_options{};
		std::function<void(submenu&)> m_action{};
	};
}
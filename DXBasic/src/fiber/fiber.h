#pragma once
#include "pch/pch.h"
#include <functional>

namespace fibers {
	class fiber;
	class fiber {
	public:
		fiber(strung name, std::function<void()> func, std::optional<std::size_t> statckSize = std::nullopt) : m_name(name), m_func(func), m_secondary(nullptr), m_primary(nullptr) {
			m_secondary = CreateFiber(statckSize.has_value() ? statckSize.value() : 0, [](void* param) { static_cast<fiber*>(param)->fn(); }, this);
		}
		~fiber() {
			if (m_secondary)
				DeleteFiber(m_secondary);
		}
	public:
		void tick() {
			m_primary = GetCurrentFiber();
			if (!m_time.has_value() || m_time.value() <= std::chrono::high_resolution_clock::now())
				SwitchToFiber(m_secondary);
		}
		void wait(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt) {
			if (time.has_value())
				m_time = std::chrono::high_resolution_clock::now() + time.value();
			else
				m_time = std::nullopt;
			SwitchToFiber(m_primary);
		}
		static fiber* cur() {
			return static_cast<fiber*>(GetFiberData());
		}
	public:
		void fn() {
			try {
				m_func();
			}
			catch (...) {
				std::cout << "Caught an exception in fiber '" << m_name << "'." << '\n';
			}
			while (true) {
				wait();
			}
		}
	public:
		strung m_name{};
		std::function<void()> m_func{};
	public:
		void* m_primary{};
		void* m_secondary{};
		std::optional<std::chrono::high_resolution_clock::time_point> m_time{};
	};
}
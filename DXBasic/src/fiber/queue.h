#pragma once
#include "pch/pch.h"
#include <map>
#include <functional>
#include "rage/classes.h"
#include "manager.h"

namespace fibers::queue {
	class queue {
	public:
		void createScripts() {
			for (auto i = 0; i < 8; i++) {
				manager::g_manager->push(("fiber_" + std::to_string(i)).c_str(), [=] {
					while (true) {
						this->tick();
						fiber::cur()->wait();
					}
				});
			}
		}
	public:
		void tick() {
			std::unique_lock lck(m_mutex);
			if (!m_jobs.empty()) {
				auto job = std::move(m_jobs.top());
				m_jobs.pop();
				lck.unlock();
				std::invoke(std::move(job));
			}
		}
		void add(std::function<void()> func) {
			std::lock_guard lck(m_mutex);
			m_jobs.push(std::move(func));
		}
	public:
		std::recursive_mutex m_mutex{};
		std::stack<std::function<void()>> m_jobs{};
	};
	inline queue g_queue{};
}

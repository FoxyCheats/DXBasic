#pragma once
#include "pch/pch.h"
#include "fiber/fiber.h"
#include "rage/classes.h"

namespace fibers::manager {
	namespace util {
		inline auto get_scrThread = [=](uint32_t hash) -> GtaThread* {
			for (auto& thr : *g_pointers.m_gtaThreads) {
				if (thr->m_script_hash == hash)
					return thr;
			}
			return nullptr;
		};
		inline auto getViaId_scrThread = [=](uint32_t id) -> GtaThread* {
			for (auto& thr : *g_pointers.m_gtaThreads) {
				if (thr->m_context.m_thread_id == id)
					return thr;
			}
			return nullptr;
		};
		template <typename call, typename ...arguments>
		inline bool executeUnderScr(GtaThread* scr, call&& callback, arguments&&... args) {
			auto tlsCtx = rage::tlsContext::get();
			if (!scr || !scr->m_context.m_thread_id)
				return false;
			auto ogThr = tlsCtx->m_script_thread;
			tlsCtx->m_script_thread = scr;
			tlsCtx->m_is_script_thread_active = true;
			std::invoke(std::forward<call>(callback), std::forward<arguments>(args)...);
			tlsCtx->m_script_thread = ogThr;
			tlsCtx->m_is_script_thread_active = ogThr != nullptr;
			return true;
		}
	}
	class manager {
	public:
		manager() : m_maxNumOfFibers(20) {}
		~manager() {
			for (auto& element : m_fibers) {
				this->erase(element.first);
			}
		}
	public:
		bool push(strung name, std::function<void()> func, std::optional<std::size_t> stackSize = std::nullopt) {
			if (m_fibers.size() == m_maxNumOfFibers)
				return false;
			m_fibers.insert(std::make_pair(name.c_str(), std::make_unique<fiber>(name, func, stackSize)));
			return true;
		}
		bool erase(char const* name) {
			return m_fibers.erase(name);
		}
	public:
		void onTick() {
			static bool ensure = (ConvertThreadToFiber(nullptr), true);
			if (!ensure)
				return;
			for (auto& element : m_fibers) {
				auto& fbr = element.second;
				fbr->onTick();
			}
		}
		void onScriptTick(uint32_t hash) {
			util::executeUnderScr(util::get_scrThread(hash), std::mem_fn(&manager::onTick), this);
		}
	public:
		std::map<char const*, std::unique_ptr<fiber>> m_fibers{};
		int m_maxNumOfFibers{ 20 };
	};
	inline std::unique_ptr<manager> g_manager{};
}

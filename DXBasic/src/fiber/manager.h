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
	inline std::vector<fiber*> g_fibers;
	inline void handler() {
		static bool ensureMainFbr = (ConvertThreadToFiber(nullptr), true);
		if (!ensureMainFbr)
			return;
		for (auto& scr : g_fibers)
			scr->tick();
	}
	inline void scriptTick(uint32_t hash) {
		util::executeUnderScr(util::get_scrThread(hash), &handler);
	}
}
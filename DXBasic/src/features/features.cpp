#include "features.h"
#include "memory/pointers.h"
#include "config/config.h"

namespace features {
	namespace self {
		void godMode() {
			auto cPed = (*g_pointers.m_pedFactory)->m_local_ped;
			cPed->m_godmode = g_config.get()["self"]["godMode"].get<bool>();
		}
		void neverWanted() {
			auto cPed = (*g_pointers.m_pedFactory)->m_local_ped;
			auto cPlayerInfo = cPed->m_player_info;
			cPlayerInfo->m_is_wanted = g_config.get()["self"]["neverWanted"].get<bool>();
			cPlayerInfo->m_wanted_level_display = cPlayerInfo->m_wanted_level;
			if (g_config.get()["self"]["neverWanted"].get<bool>())
				cPlayerInfo->m_wanted_level = 0;
		}
	}
	void tick() {
		while (true) {
			self::godMode();
			self::neverWanted();
			fibers::fiber::cur()->wait();
		}
	}
}
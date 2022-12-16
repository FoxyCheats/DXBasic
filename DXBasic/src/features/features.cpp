#include "features.h"
#include "memory/pointers.h"
#include "config/config.h"
#include "../util/util.h"

namespace features {
	namespace self {
		auto& s_cfg = g_config.get()["self"];
		namespace movement {
			auto& s_m_cfg = g_config.get()["self"]["movement"];
			void superRun() {
				if (s_m_cfg["superRun"].get<bool>() && (PAD::IS_DISABLED_CONTROL_PRESSED(2, 32) && PAD::IS_DISABLED_CONTROL_PRESSED(2, 21))) {
					ENTITY::APPLY_FORCE_TO_ENTITY(util::ped::g_entityHandle, 1, Vector3(0.f, 1.3, 0.f), Vector3(), 0, true, true, true, false, false);
					PLAYER::SET_PLAYER_SPRINT(util::ped::g_entityHandle, true);
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(util::ped::g_entityHandle, 5.f);
				}
			}
			void superJump() {
				if (s_m_cfg["superJump"].get<bool>() && !PED::IS_PED_IN_ANY_VEHICLE(util::ped::g_entityHandle, false) && !ENTITY::IS_ENTITY_IN_AIR(util::ped::g_entityHandle) && !PED::IS_PED_DOING_A_BEAST_JUMP(util::ped::g_entityHandle)) {
					if (PAD::IS_CONTROL_JUST_PRESSED(2, 22))
						TASK::TASK_JUMP(util::ped::g_entityHandle, true, true, true);
				}
			}
		}
		void godMode() {
			*reinterpret_cast<uint8_t*>(uint64_t(util::ped::g_handle) + (offsetof(CPed, m_damage_bits) + 0x1)) = s_cfg["godMode"].get<bool>();
		}
		void neverWanted() {
			util::player::g_handle->m_is_wanted = s_cfg["neverWanted"].get<bool>();
			util::player::g_handle->m_wanted_level_display = util::player::g_handle->m_wanted_level;
			if (s_cfg["neverWanted"].get<bool>())
				util::player::g_handle->m_wanted_level = 0;
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
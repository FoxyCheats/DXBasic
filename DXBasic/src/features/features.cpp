#include "features.h"
#include "memory/pointers.h"
#include "config/config.h"
#include "util/util.h"

namespace features {
	namespace self {
		namespace movement {
			void superRun() {
				if (superRunBool && (PAD::IS_DISABLED_CONTROL_PRESSED(2, 32) && PAD::IS_DISABLED_CONTROL_PRESSED(2, 21))) {
					ENTITY::APPLY_FORCE_TO_ENTITY(util::ped::g_entityHandle, 1, Vector3(0.f, 1.3, 0.f), Vector3(), 0, true, true, true, false, false);
					PLAYER::SET_PLAYER_SPRINT(util::ped::g_entityHandle, true);
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(util::ped::g_entityHandle, 5.f);
				}
			}
			void superJump() {
				if (superJumpBool && !PED::IS_PED_IN_ANY_VEHICLE(util::ped::g_entityHandle, false) && !ENTITY::IS_ENTITY_IN_AIR(util::ped::g_entityHandle) && !PED::IS_PED_DOING_A_BEAST_JUMP(util::ped::g_entityHandle)) {
					if (PAD::IS_CONTROL_JUST_PRESSED(2, 22))
						TASK::TASK_JUMP(util::ped::g_entityHandle, true, true, true);
				}
			}
			void run() {
				util::player::g_handle->m_run_speed = runBool ? runSpeed : 1.f;
			}
			void swim() {
				util::player::g_handle->m_swim_speed = swimBool ? swimSpeed : 1.f;
			}
		}
		void godMode() {
			*reinterpret_cast<uint8_t*>(uint64_t(util::ped::g_handle) + (offsetof(CPed, m_damage_bits) + 0x1)) = godModeBool;
		}
		void neverWanted() {
			util::player::g_handle->m_is_wanted = neverWantedBool ? false : true;
			if (neverWantedBool) {
				util::player::g_handle->m_wanted_level = 0;
				util::player::g_handle->m_wanted_level_display = util::player::g_handle->m_wanted_level;
			}
		}
		void tick() {
			movement::superRun();
			movement::superJump();
			movement::run();
			movement::swim();
			godMode();
			neverWanted();
		}
	}
	void onTick() {
		while (true) {
			if (util::player::g_handle && util::ped::g_handle)
				self::tick();
			fibers::fiber::cur()->wait();
		}
	}
}

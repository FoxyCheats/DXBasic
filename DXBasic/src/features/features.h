#include "pch/pch.h"
#include "natives/natives.h"
#include "fiber/fiber.h"
#include "fiber/manager.h"
#include "fiber/queue.h"
#include "rage/classes.h"
#include "rage/enums.h"

namespace features {
	namespace self {
		namespace movement {
			inline bool superRunBool{};
			extern void superRun();
			inline bool superJumpBool{};
			extern void superJump();
			extern void run();
			extern void swim();
		}
		inline bool godModeBool{};
		extern void godMode();
		inline bool neverWantedBool{};
		extern void neverWanted();
		extern void tick();
	}
	extern void onTick();
}

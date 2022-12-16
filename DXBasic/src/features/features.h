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
			extern void superRun();
			extern void superJump();
			extern void run();
			extern void swim();
		}
		extern void godMode();
		extern void neverWanted();
		extern void tick();
	}
	extern void tick();
}
#include "pch/pch.h"
#include "natives/natives.h"
#include "fiber/fiber.h"
#include "fiber/manager.h"
#include "fiber/queue.h"
#include "rage/classes.h"
#include "rage/enums.h"

namespace features {
	namespace self {
		extern void godMode();
		extern void neverWanted();
	}
	extern void tick();
}
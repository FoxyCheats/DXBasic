#include "script/self/movement/movement.h"
#include "features/features.h"

namespace script {
	movement::movement() : submenu("Movement", &movement::call) {}
	void movement::call(submenu& sub) {
		sub.add(booleanOption("Super Run", &features::self::movement::superRunBool));
		sub.add(booleanOption("Super Jump", &features::self::movement::superJumpBool));
	}
}

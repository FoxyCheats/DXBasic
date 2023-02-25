#include "script/self/self.h"
#include "script/self/movement/movement.h"

namespace script {
	self::self() : submenu("Self", &self::call) {}
	bool toggle{};
	void self::call(submenu& sub) {
		sub.add(submenuOption("Movement", movement()));
		sub.add(booleanOption("God Mode", &features::self::godModeBool));
		sub.add(booleanOption("Never Wanted", &features::self::neverWantedBool));
	}
}

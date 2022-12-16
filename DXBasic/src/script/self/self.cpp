#include "script/self/self.h"

namespace script {
	auto cfg = g_config.get()["self"];
	self::self() : submenu("Self", &self::call) {}
	void self::call(submenu& sub) {
		sub.add(submenuOption("Movement", self()));
		sub.add(booleanOption("God Mode", cfg["godMode"].get_ref<bool&>()));
		sub.add(booleanOption("Never Wanted", cfg["neverWanted"].get_ref<bool&>()));
	}
}
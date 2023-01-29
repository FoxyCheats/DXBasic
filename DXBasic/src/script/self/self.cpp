#include "script/self/self.h"
#include "script/self/movement/movement.h"

namespace script {
	auto s_cfg = g_config.get()["self"];
	self::self() : submenu("Self", &self::call) {}
	bool toggle{};
	void self::call(submenu& sub) {
		sub.add(submenuOption("Movement", movement()));
		sub.add(booleanOption("God Mode", s_cfg["godMode"].get<bool*>()));
		sub.add(booleanOption("Never Wanted", s_cfg["neverWanted"].get<bool*>()));
	}
}
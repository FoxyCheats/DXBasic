#include "script/self/self.h"
#include "script/self/movement/movement.h"

namespace script {
	auto s_cfg = g_config.get()["self"];
	self::self() : submenu("Self", &self::call) {}
	bool toggle{};
	void self::call(submenu& sub) {
		sub.add(submenuOption("Movement", movement()));
		sub.add(booleanOption("Test", "Hello World", toggle));
		sub.add(booleanOption("God Mode", s_cfg["godMode"].get_ref<bool&>()));
		sub.add(booleanOption("Never Wanted", s_cfg["neverWanted"].get_ref<bool&>()));
	}
}
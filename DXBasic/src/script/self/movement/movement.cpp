#include "script/self/movement/movement.h"

namespace script {
	auto cfg = g_config.get()["self"]["movement"];
	movement::movement() : submenu("Movement", &movement::call) {}
	void movement::call(submenu& sub) {
		sub.add(booleanOption("Super Run", cfg["superRun"].get_ref<bool&>()));
		sub.add(booleanOption("Super Jump", cfg["superJump"].get_ref<bool&>()));
	}
}
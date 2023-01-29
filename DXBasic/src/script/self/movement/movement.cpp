#include "script/self/movement/movement.h"

namespace script {
	auto s_m_cfg = g_config.get()["self"]["movement"];
	movement::movement() : submenu("Movement", &movement::call) {}
	void movement::call(submenu& sub) {
		sub.add(booleanOption("Super Run", s_m_cfg["superRun"].get<bool*>()));
		sub.add(booleanOption("Super Jump", s_m_cfg["superJump"].get<bool*>()));
	}
}
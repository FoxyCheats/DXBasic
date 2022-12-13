#include "home.h"

namespace script {
	home::home() : submenu("Home") {
		setAction(&home::call);
	}
	void home::call(submenu& sub) {
		sub.add(regularOption("Test"));
		sub.add(regularOption("Unload", "Hello World", [=] {
			g_running = false;
		}));
	}
}
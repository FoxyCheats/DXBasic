#include "settings.h"

namespace script {
	settings::settings() : submenu("Settings", &settings::call) {}
	void settings::call(submenu& sub) {
		sub.add(regularOption("Unload", "Unloads the menu", [=] {
			g_running = false;
		}));
	}
}
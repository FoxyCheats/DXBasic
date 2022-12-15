#include "script/home/home.h"
#include "script/self/self.h"
#include "script/settings/settings.h"

namespace script {
	home::home() : submenu("Home", &home::call) {}
	void home::call(submenu& sub) {
		sub.add(submenuOption("Self", self()));
		sub.add(submenuOption("Settings", settings()));
	}
}
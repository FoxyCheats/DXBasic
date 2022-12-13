#include "self.h"

namespace script {
	self::self() : submenu("Self") {
		setAction(&self::call);
	}
	void self::call(submenu& sub) {
		sub.add(regularOption("Unload", [=] {

		}));
	}
}
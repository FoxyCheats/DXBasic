#include "self.h"

namespace script {
	self::self() : submenu("Self", &self::call) {}
	void self::call(submenu& sub) {
		sub.add(regularOption("Nullsub"));
	}
}
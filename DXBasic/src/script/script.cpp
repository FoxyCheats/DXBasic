#include "script.h"
#include "fiber/fiber.h"
#include "fiber/queue.h"
#include "natives/natives.h"
#include "gui/gui.h"
#include "gui/option_types/regular_option.h"
#include "script/home/home.h"

namespace script {
	void init() {
		gui::menu::init(home());
	}
	void tick() {
		script::init();
		while (true) {
			PAD::DISABLE_CONTROL_ACTION(2, 27, true);
			PAD::SET_INPUT_EXCLUSIVE(2, 201);
			PAD::SET_INPUT_EXCLUSIVE(2, 202);
			PAD::SET_INPUT_EXCLUSIVE(2, 187);
			PAD::SET_INPUT_EXCLUSIVE(2, 188);
			PAD::SET_INPUT_EXCLUSIVE(2, 189);
			PAD::SET_INPUT_EXCLUSIVE(2, 190);
			fibers::fiber::cur()->wait();
		}
	}
}
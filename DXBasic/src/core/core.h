#pragma once
#include "pch/pch.h"

namespace core {
	namespace dll {
		extern void attach();
		extern void detach();
		inline bool g_wasDllDetachCalled{ false };
	}
	extern void init();
	extern void uninit();
	extern void createThreadInstance();
}
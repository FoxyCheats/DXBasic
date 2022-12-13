#include "hooks/hooks.h"

LPVOID hooks::convertThreadToFiber(LPVOID param) {
	if (IsThreadAFiber())
		return GetCurrentFiber();
	return g_hooking->m_convertThreadToFiber.getOg<decltype(&convertThreadToFiber)>()(param);
}
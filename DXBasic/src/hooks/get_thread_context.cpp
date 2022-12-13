#include "hooks/hooks.h"

BOOL hooks::getThreadContext(HANDLE hThread, LPCONTEXT lpContext) {
	if (lpContext->ContextFlags && CONTEXT_DEBUG_REGISTERS) {
		lpContext->Dr0 = NULL;
		lpContext->Dr1 = NULL;
		lpContext->Dr2 = NULL;
		lpContext->Dr3 = NULL;
		lpContext->Dr6 = NULL;
		lpContext->Dr7 = NULL;
	}
	return g_hooking->m_getThreadContext.getOg<decltype(&getThreadContext)>()(hThread, lpContext);
}
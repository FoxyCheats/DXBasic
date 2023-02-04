#include "hooks.h"
#include "natives/natives.h"
#include "fiber/manager.h"

uint32_t frameCount{};
int64_t hooks::scriptVirtualMachine(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* threadContext) {
	if ((threadContext->m_script_hash == "freemode"_joaat || threadContext->m_script_hash == "main_persistent"_joaat) && frameCount != MISC::GET_FRAME_COUNT()) {
		fibers::manager::g_manager->onScriptTick(threadContext->m_script_hash);
		frameCount = MISC::GET_FRAME_COUNT();
	}
	return g_hooking->m_scriptVirtualMachine.getOg<funcTypes::scriptVirtualMachineT>()(stack, globals, program, threadContext);
}
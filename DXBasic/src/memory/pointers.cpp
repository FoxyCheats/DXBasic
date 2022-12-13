#include "memory/pointers.h"
#include "memory/pattern_batch.h"
#define STRINGIFY(str) #str
#define printSig(ptr) logNow_Debug(STRINGIFY(ptr) " GTA5.exe+0x{:X}", (uintptr_t)ptr - uintptr_t(GetModuleHandleA(NULL)))
#define printSigModuleSpecific(ptr, moduleName) logNow_Debug(STRINGIFY(ptr) " " moduleName"+0x{:X}", (uintptr_t)ptr - uintptr_t(GetModuleHandleA(moduleName)))
#define printSigNonRelative(ptr) logNow_Debug(STRINGIFY(ptr) " 0x{:X}", (uintptr_t)ptr)

void pointers::scan() {
	stopwatch stopwatch;
	static patternBatch mainBatch;
	mainBatch.add("SVM", "4A 89 3C 39", [=](mem ptr) {
		m_scriptVirtualMachine = ptr.sub(0x26).rip().as<decltype(m_scriptVirtualMachine)>();
		printSig(m_scriptVirtualMachine)
	});
	mainBatch.add("NRT/GNH", "40 B6 01 39 79 2C", [=](mem ptr) {
		m_nativeRegistrationTable = ptr.add(0xF).rip().as<decltype(m_nativeRegistrationTable)>();
		printSig(m_nativeRegistrationTable)
		m_getNativeHandler = ptr.add(0x18).rip().as<decltype(m_getNativeHandler)>();
		printSig(m_getNativeHandler)
	});
	mainBatch.add("GTS", "F5 8B FD 73", [=](mem ptr) {
		m_gtaThreads = ptr.add(8).rip().as<decltype(m_gtaThreads)>();
		printSig(m_gtaThreads)
	});
	mainBatch.add("NPM", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [=](mem ptr) {
		m_networkPlayerMgr = ptr.add(3).rip().as<decltype(m_networkPlayerMgr)>();
		printSig(m_networkPlayerMgr)
	});
	mainBatch.add("PF", "48 8B 05 ? ? ? ? 8A D1", [=](mem ptr) {
		m_pedFactory = ptr.add(3).rip().as<decltype(m_pedFactory)>();
		printSig(m_pedFactory)
	});
	mainBatch.add("G", "48 8B 8D ? ? ? ? 4C 8D 4D 08", [=](mem ptr) {
		m_globals = ptr.add(0xE).rip().as<decltype(m_globals)>();
		printSig(m_globals)
	});
	mainBatch.add("S", "48 8B 3D ? ? ? ? 3B C8", [=](mem ptr) {
		m_swapchain = ptr.add(3).rip().as<decltype(m_swapchain)>();
		printSig(m_swapchain)
	});
	mainBatch.add("JRR", "23 C3 C1 E0 0C", [=](mem ptr) {
		m_jmpRbxRegister = ptr.sub(1).as<decltype(m_jmpRbxRegister)>();
		printSig(m_jmpRbxRegister)
	});
	m_hwnd = FindWindowA("grcWindow", nullptr);
	mainBatch.run("GTA5.exe");
	auto endTime = stopwatch.getAs<float>();
	g_logger.get()->log(eLogColor::Grey, "Signatures", "{} found and {} failed out of {} signatures. Scan time took {:2f}s with a per sig avg. of {:2f}s", g_foundSigCount, g_failedSigCount, g_totalSigCount, endTime, endTime / g_totalSigCount);
}
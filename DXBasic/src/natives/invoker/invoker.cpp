#include "invoker.h"
#include "memory/pointers.h"
#include "stack/call_spoof.h"

void invoker::cache() {
	for (auto& mapping : g_crossmap)
		m_cache.emplace(mapping.u117, g_pointers.m_getNativeHandler(g_pointers.m_nativeRegistrationTable, mapping.u166));
}

void invoker::begin() {
	m_context.reset();
}

void invoker::end(std::uint64_t hash) {
	if (auto val = m_cache.find(hash); val != m_cache.end()) {
		auto handler = rage::scrNativeHandler(val->second);
		if (!val->second) {
			logNow(fatal, "0x{:X} native's handler is NULL", hash)
			return;
		}
		spoofCall(g_pointers.m_jmpRbxRegister, val->second, dynamic_cast<rage::scrNativeCallContext*>(&m_context));
		dynamic_cast<rage::scrNativeCallContext*>(&m_context)->shiftVectorCoords();
	}
	else {
		logNow(fatal, "Failed to find 0x{:X} native's handler.", hash)
	}
}
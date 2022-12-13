#pragma once
#include "pch/pch.h"
#include "core/logger.h"

class MinHook {
public:
	MinHook() { MH_Initialize(); }
	~MinHook() { MH_Uninitialize(); }
};
class detour {
public:
	detour(char const* name, void* ptr, void* dtr, bool creationShouldBeStopped = false) : m_name(name), m_ptr(ptr), m_dtr(dtr), m_wasCreationShouldBeStoppedSet(creationShouldBeStopped) {
		if (!m_wasCreationShouldBeStoppedSet) {
			if (auto st = MH_CreateHook(m_ptr, m_dtr, &m_og); st != MH_OK && m_name != "")
				logNow(detours, "Failed to create hook {}.", m_name);
		}
	}
	~detour() {
		if (!m_wasCreationShouldBeStoppedSet) {
			if (auto st = MH_RemoveHook(m_ptr); st != MH_OK && m_name != "")
				logNow(detours, "Failed to remove hook {}.", m_name);
		}
	}
public:
	void enable() {
		if (!m_wasCreationShouldBeStoppedSet) {
			if (auto st = MH_QueueEnableHook(m_ptr); st != MH_OK && m_name != "")
				logNow(detours, "Failed to enable hook {}.", m_name);
		}
	}
	void disable() {
		if (!m_wasCreationShouldBeStoppedSet) {
			if (auto st = MH_QueueDisableHook(m_ptr); st != MH_OK && m_name != "")
				logNow(detours, "Failed to disable hook {}.", m_name);
		}
	}
public:
	inline static void enableAll() {
		MH_EnableHook(MH_ALL_HOOKS);
	}
	inline static void disableAll() {
		MH_DisableHook(MH_ALL_HOOKS);
	}
public:
	template <typename type>
	type getOg() {
		return type(m_og);
	}
public:
	char const* m_name;
	void* m_dtr;
	void* m_ptr;
	void* m_og;
	bool m_wasCreationShouldBeStoppedSet;
};
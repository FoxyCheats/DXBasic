#pragma once
#include <cstdint>
#include <sysinfoapi.h>

class simpleTimer {
public:
	void start(uint64_t ticks) {
		if (m_tick) {
			m_ready_at = GetTickCount64() + ticks;
			m_tick = false;
		}
	}
	bool isReady() {
		return GetTickCount64() > m_ready_at;
	}
	void reset() {
		m_tick = true;
	}
private:
	std::uint64_t m_ready_at;
	bool m_tick;
};
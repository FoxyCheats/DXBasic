#pragma once
#include "mem.h"
#include "signature.h"
#include "module.h"

struct ptrEntry { std::string name; signature pattern; std::function<void(mem)> callback; };
inline uint32_t g_foundSigCount{}, g_failedSigCount{}, g_totalSigCount{};
class patternBatch {
public:
	void add(strung nm, strung ptr, std::function<void(mem)> cb) {
		m_patterns.push_back(ptrEntry{ nm, ptr, cb });
	}
	void run(hmod mod = {}) {
		for (auto& entry : m_patterns) {
			g_totalSigCount++;
			if (auto res = entry.pattern.get(mod)) {
				entry.callback(res);
				g_foundSigCount++;
			}
			else {
				logNow(info, "Failed to find pattern {}", entry.name)
				g_failedSigCount++;
			}
		}
		m_patterns.clear();
	}
public:
	std::vector<ptrEntry> m_patterns{};
};
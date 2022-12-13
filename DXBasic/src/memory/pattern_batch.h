#pragma once
#include "mem.h"
#include "signature.h"
#include "module.h"

struct ptrEntry { std::string name; signature pattern; std::function<void(mem)> callback; };
inline uint32_t g_foundSigCount{}, g_failedSigCount{}, g_totalSigCount{};
class patternBatch {
public:
	void add(std::string nm, std::string_view ptr, std::function<void(mem)> cb) {
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
				std::cout << "Pattern Scanning | " << std::format("Found {}.", entry.name) << std::endl;
				g_failedSigCount++;
			}
		}
		m_patterns.clear();
	}
public:
	std::vector<ptrEntry> m_patterns{};
};
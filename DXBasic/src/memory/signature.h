#pragma once
#include "pch/pch.h"
#include "mem.h"
#include "module.h"

inline std::optional<uint8_t> charToHex(char const c) {
	switch (c) {
	case '0':
		return static_cast<uint8_t>(0x0);
	case '1':
		return static_cast<uint8_t>(0x1);
	case '2':
		return static_cast<uint8_t>(0x2);
	case '3':
		return static_cast<uint8_t>(0x3);
	case '4':
		return static_cast<uint8_t>(0x4);
	case '5':
		return static_cast<uint8_t>(0x5);
	case '6':
		return static_cast<uint8_t>(0x6);
	case '7':
		return static_cast<uint8_t>(0x7);
	case '8':
		return static_cast<uint8_t>(0x8);
	case '9':
		return static_cast<uint8_t>(0x9);
	case 'A':
		return static_cast<uint8_t>(0xA);
	case 'B':
		return static_cast<uint8_t>(0xB);
	case 'C':
		return static_cast<uint8_t>(0xC);
	case 'D':
		return static_cast<uint8_t>(0xD);
	case 'E':
		return static_cast<uint8_t>(0xE);
	case 'F':
		return static_cast<uint8_t>(0xF);
	}
	return std::nullopt;
}
inline bool doesMemoryMatch(uint8_t* target, std::optional<uint8_t> const* sig, size_t len) {
	for (size_t i{}; i != len; ++i)
		if (sig[i] && *sig[i] != target[i])
			return false;
	return true;
}
inline char* findPattern(std::optional<uint8_t>* elements, size_t bCount, hmod mod = {}) {
	for (uintptr_t i{}; i < mod.m_size - bCount; ++i)
		if (doesMemoryMatch(mod.m_base.add(i).as<uint8_t*>(), elements, bCount))
			return mod.m_base.as<char*>() + i;
	return nullptr;
}
class signature {
public:
	signature(strung ptr) {
		for (size_t i{}; i != ptr.size(); ++i) {
			if (ptr[i] == ' ')
				continue;
			if (ptr[i] != '?') {
				if (i != ptr.size() - 1) {
					auto c1 = charToHex(ptr[i]);
					auto c2 = charToHex(ptr[i + 1]);
					if (c1 && c2)
						m_bytes.emplace_back(static_cast<uint8_t>((*c1 * 0x10) + *c2));
				}
			}
			else {
				m_bytes.push_back(std::nullopt);
			}
		}
	}
public:
	mem get(hmod mod = {}) {
		size_t maxShift = m_bytes.size();
		size_t maxIdx = m_bytes.size() - 1;
		//Get wildcard index, and store max shifable byte count
		size_t wildCardIdx{ size_t(-1) };
		for (int i{ int(maxIdx - 1) }; i >= 0; --i) {
			if (!m_bytes[i]) {
				maxShift = maxIdx - i;
				wildCardIdx = i;
				break;
			}
		}
		//Store max shiftable bytes for non wildcards.
		size_t shiftTable[UINT8_MAX + 1]{};
		for (size_t i{}; i <= UINT8_MAX; ++i)
			shiftTable[i] = maxShift;
		for (size_t i{ wildCardIdx + 1 }; i != maxIdx; ++i)
			shiftTable[*m_bytes[i]] = maxIdx - i;
		//Loop data
		for (size_t curIdx{}; curIdx != mod.m_size - m_bytes.size();) {
			for (size_t sigIdx = maxIdx; sigIdx >= 0; --sigIdx) {
				if (m_bytes[sigIdx] && *mod.m_base.add(curIdx + sigIdx).as<uint8_t*>() != *m_bytes[sigIdx]) {
					curIdx += shiftTable[*mod.m_base.add(curIdx + maxIdx).as<uint8_t*>()];
					break;
				}
				else if (sigIdx == NULL) {
					return mod.m_base.add(curIdx);
				}
			}
		}
		return {};
	}
	mem getLegacy(hmod mod = {}) {
		return findPattern(m_bytes.data(), m_bytes.size(), mod);
	}
	std::vector<mem> getAll(hmod mod = "") {
		std::vector<mem> ptrs{};
		for (uintptr_t i{}; i != (mod.m_size - m_bytes.size()); ++i)
			if (doesMemoryMatch(mod.m_base.add(i).as<uint8_t*>(), m_bytes.data(), m_bytes.size()))
				ptrs.push_back(mod.m_base.add(i));
		return ptrs;
	}
public:
	std::vector<std::optional<uint8_t>> m_bytes{};
};
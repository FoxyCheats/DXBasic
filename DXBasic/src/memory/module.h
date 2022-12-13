#pragma once
#include "mem.h"
#include <libloaderapi.h>

class hmod {
public:
	hmod(HMODULE hmod) {
		m_base.setPtr(hmod);
		auto dosHdr = reinterpret_cast<IMAGE_DOS_HEADER*>(m_base.as<char*>());
		auto ntHdr = reinterpret_cast<IMAGE_NT_HEADERS64*>(m_base.as<char*>() + dosHdr->e_lfanew);
		m_size = ntHdr->OptionalHeader.SizeOfImage;
		m_end = m_base.as<char*>() + m_size;
	}
	hmod(const char* hmod) : hmod(GetModuleHandleA(hmod)) {}
	hmod(std::string_view hmod) : hmod(hmod.data()) {}
	hmod() : hmod(GetModuleHandleA(NULL)) {}
public:
	mem m_base{}, m_end{};
	size_t m_size{};
};
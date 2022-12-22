#pragma once
#ifndef PCH_H
#define PCH_H
#define WIN32_LEAN_AND_MEAN
#define _HAS_STD_BYTE 0

#include "framework.h"

#define BRANDING_NAME "Foxy"
#define UPPER_BRANDING_NAME "FOXY"
#define LOWER_BRANDING_NAME "foxy"

template <typename t>
using comPtr = Microsoft::WRL::ComPtr<t>;
template <typename t>
	requires std::is_function_v<t>
using fnptr = std::add_pointer_t<t>;

namespace defines {
	inline bool g_running{};
	inline HMODULE g_module{};
}
using namespace defines;

using strung = std::string;

namespace fs = std::filesystem;

inline constexpr char tolower(char c) {
	return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
inline uint32_t joaat(std::string_view str) {
	uint32_t hash = 0;
	for (auto c : str) {
		hash += tolower(c); hash += (hash << 10); hash ^= (hash >> 6);
	}
	hash += (hash << 3); hash ^= (hash >> 11); hash += (hash << 15);
	return hash;
}
template <typename t = std::string_view>
inline consteval uint32_t constexprJoaat(t str, bool const forceLowerCase = true) {
	uint32_t hash{};
	while (*str != '\0') {
		hash += forceLowerCase ? tolower(*str) : *str, ++str;
		hash += hash << 10, hash ^= hash >> 6;
	}
	hash += (hash << 3), hash ^= (hash >> 11), hash += (hash << 15);

	return hash;
}
inline consteval uint32_t operator ""_joaat(const char* str, size_t) { return constexprJoaat(str); }

//Helper classes
// StackWalker
class stackWalker : public StackWalker {
public:
	stackWalker() : StackWalker() {}
	stackWalker(ExceptType exType) : StackWalker(exType) {}
	virtual void OnOutput(LPCSTR szText);
	virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion);
	virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName);
	virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr);
	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);
};
// Random Number Generator
class rng {
	std::random_device m_rd{};
	std::mt19937 m_mtRes{};
public:
	template <typename t> requires std::is_integral_v<t>
		rng() : m_mtRes(m_rd()), m_min(std::numeric_limits<t>::min()), m_max(std::numeric_limits<t>::max()) {}
		rng(size_t min, size_t max) : m_mtRes(m_rd()), m_min(min), m_max(max) {}
public:
	template <typename t>
	t get() {
		std::uniform_int_distribution m_intDis(m_min, m_max);
		return static_cast<t>(m_intDis(m_mtRes));
	}
public:
	size_t m_min{};
	size_t m_max{};
};
// Stopwatch
class stopwatch {
public:
	stopwatch() : m_startTime(std::chrono::steady_clock::now()), m_endTime(std::chrono::steady_clock::now()) {}
public:
	template <typename t>
	t getAs() {
		m_endTime = std::chrono::steady_clock::now();
		std::chrono::duration<float> diff = m_endTime - m_startTime;
		return t(diff.count());
	}
public:
	std::chrono::steady_clock::time_point m_startTime;
	std::chrono::steady_clock::time_point m_endTime;
};

#endif //PCH_H
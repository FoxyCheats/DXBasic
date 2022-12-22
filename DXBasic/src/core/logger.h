#pragma once
#include "pch/pch.h"
#define DEBUG_MODE

enum class eLogColor : uint16_t {
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	Intensify = FOREGROUND_INTENSITY,
	White = Red | Green | Blue | Intensify,
	Grey = Intensify,
	LightRed = Red | Intensify,
	LightGreen = Green | Intensify,
	LightBlue = Blue | Intensify,
};
enum class eLogType : uint8_t {
	info,
	warn,
	fatal,
	exception,
	registers,
#if defined(DEBUG_MODE)
	debug,
#endif
	stackwalker,
	detours,
};
inline eLogColor operator|(eLogColor a, eLogColor b) {
	return static_cast<eLogColor>(static_cast<std::underlying_type_t<eLogColor>>(a) | static_cast<std::underlying_type_t<eLogColor>>(b));
}
class logger {
public:
	logger() {
		initConsoleHandles();
		initFileHandles();
	}
	~logger() {
		freeConsoleHandles();
		freeFileHandles();
	}
public:
	void initConsoleHandles() {
		if (!AttachConsole(GetCurrentProcessId()))
			AllocConsole();
		SetConsoleTitleA(BRANDING_NAME);
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}
	void initFileHandles() {
		m_console.open("CONOUT$");
		m_path.append(std::getenv("appdata")).append(BRANDING_NAME).append(BRANDING_NAME".log");
		m_file.open(m_path, std::ios_base::out | std::ios_base::app);
		m_file.clear();
	}
public:
	void freeConsoleHandles() {
		fclose(stdout);
		FreeConsole();
	}
	void freeFileHandles() {
		m_console.clear();
		m_console.close();
		m_path.clear();
		m_file.close();
	}
public:
	template <typename ...arguments>
	void log(eLogColor col, strung type, strung fmt, arguments... args) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<uint16_t>(col));
		auto getTime = std::time(nullptr);
		auto timeStruct = std::localtime(&getTime);
		auto msg = std::format("{:0>2}:{:0>2}:{:0>2}", timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec) + " | " + type + " | " + std::vformat(fmt, std::make_format_args(args...));
		m_console << msg << std::endl;
		m_file << msg << '\n';
	}
	template <typename ...arguments>
	void log(eLogType type, strung fmt, arguments... args) {
		switch (type) {
		case eLogType::info: log(eLogColor::White, "Info", fmt, args...); break;
		case eLogType::warn: log(eLogColor::LightBlue, "Warning", fmt, args...); break;
		case eLogType::fatal: log(eLogColor::Red, "Fatal", fmt, args...); g_running = false; break;
		case eLogType::exception: log(eLogColor::LightRed, "Exception", fmt, args...); break;
		case eLogType::registers: log(eLogColor::LightRed, "Registers", fmt, args...); break;
#if defined(DEBUG_MODE)
		case eLogType::debug: log(eLogColor::Grey, "Debug", fmt, args...); break;
#endif
		case eLogType::stackwalker: log(eLogColor::LightRed, "StackWalker", fmt, args...); break;
		case eLogType::detours: log(eLogColor::Red, "Hooking", fmt, args...); break;
		}
	}
public:
	std::filesystem::path m_path{};
	std::ofstream m_file{};
	std::ofstream m_console{};
};
inline std::unique_ptr<logger> g_logger{};

#define logNow(type, value, ...) g_logger.get()->log(eLogType::type, value, __VA_ARGS__);

#if defined(DEBUG_MODE)
#define logNow_Debug(value, ...) logNow(debug, value, __VA_ARGS__)
#else
#define logNow_Debug(value, ...) ;
#endif
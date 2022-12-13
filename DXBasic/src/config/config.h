#pragma once
#include "nlohmann/json.hpp"
#include "pch/pch.h"
namespace fs = std::filesystem;

inline nlohmann::json g_dummyJson =
R"({
	"self" : {
		"godMode" : true,
		"neverWanted" : true
	}
})"_json;
class config {
public:
	void load();
	void save();
public:
	nlohmann::json& get() { return m_json; }
private:
	void writeDummy();
private:
	nlohmann::json m_json{};
	fs::path m_path{ std::getenv("appdata") };
};
inline config g_config{};
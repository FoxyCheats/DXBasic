#pragma once
#include "nlohmann/json.hpp"
#include "pch/pch.h"
namespace fs = std::filesystem;

inline nlohmann::json g_dummyJson =
R"({
	"self" : {
		"movement" : {
			"superRun" : false,
			"superJump" : false,
			"run" : {
				"value" : 2.00,
				"toggle" : false,
			},
			"swim" : {
				"value" : 2.00,
				"toggle" : false,
			}
		}
		"godMode" : false,
		"neverWanted" : false
	}
})"_json;
class config {
public:
	void load();
	void save();
public:
	void writeDummy();
public:
	nlohmann::json& get() { return m_json; }
private:
	nlohmann::json m_json{};
	fs::path m_path{ std::getenv("appdata") };
};
inline config g_config{};
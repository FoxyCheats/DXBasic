#pragma once
#include "pch/pch.h"
#include "nlohmann/json.hpp"

class translate {
public:
	translate();
	translate(strung key, strung value, bool translate, bool addToArray = true);
	~translate();
public:
	void registerValue();
	void reset();
	void set(strung str);
	void setFile(strung str);
public:
	strung getOrig();
	strung get();
	bool containsModifiedValue();
private:
	strung m_key{};
	strung m_original{};
	strung m_value{};
	bool m_translate{};
};

inline std::vector<translate*> g_translations{};

class translation {
public:
	bool load(strung lang);
	bool save();
public:
	nlohmann::json m_json{};
	strung m_currentLanguage{};
	fs::path m_path{ std::getenv("appdata") };
};
inline translation g_translation{};
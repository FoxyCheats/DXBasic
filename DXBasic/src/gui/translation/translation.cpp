#include "gui/translation/translation.h"

translate::translate() : m_key{ strung() }, m_original{ strung() }, m_value{ strung() }, m_translate{ false } {}

translate::translate(strung key, strung value, bool translate, bool addToArray) : m_translate{ translate }, m_key{ key }, m_original{ value }, m_value{ m_original } {
	if (addToArray) {
		registerValue();
	}

	set(m_original);
	if (containsModifiedValue()) {
		setFile(g_translation.m_json[m_key]["value"].get<strung>());
	}
}

translate::~translate() {
	reset();
}

void translate::registerValue() {
	g_translations.push_back(this);
}

void translate::reset() {
	setFile(m_original);
}

void translate::set(strung str) {
	m_original = str;
}
void translate::setFile(strung str) {
	m_value = str;
}
strung translate::getOrig() {
	return m_original;
}
strung translate::get() {
	return m_translate ? m_value : m_original;
}
bool translate::containsModifiedValue() {
	return m_translate && !g_translation.m_json[m_key]["value"].is_null() && g_translation.m_json[m_key]["value"].get<strung>() != m_value;
}


inline nlohmann::json g_bruhMoment = {
	{ "translationAuthor", "Vali" },
	{ "translationRevision", "3" },
	{ "translationLanguage", "English" },
	{
		"Home", {
			"value", "Home"
		}
	}
};

bool translation::load(strung lang) {
	strung l = lang;
	if (l.empty()) {
		l = "English";
	}
	m_path /= BRANDING_NAME"\\TranslationsLol";
	if (!fs::exists(m_path))
		fs::create_directories(m_path);
	if (m_path.extension().string() != ".json")
		m_path /= l + ".json";
	if (m_currentLanguage != l)
		m_currentLanguage = l;
	std::ifstream m_stream{};
	m_stream.open(m_path);
	/*if (!m_stream.is_open()) {
		std::ofstream file;
		file.open(m_path, std::ios::out | std::ios::trunc);
		file << g_bruhMoment.dump(1, '	');
		file.close();
		m_json.clear();
		m_json = g_bruhMoment;
		m_stream.open(m_path);
	}*/
	if (m_stream.is_open()) {
		m_stream >> m_json;
		m_stream.close();
		return true;
	}
	return false;
}
bool translation::save() {
	std::ofstream file;
	file.open(m_path, std::ios::out | std::ios::trunc);
	file << m_json.dump(1, '	');
	file.close();
	return true;
}
#include "config.h"

void config::load() {
	m_path /= BRANDING_NAME;
	if (!fs::exists(m_path))
		fs::create_directories(m_path);
	if (!m_path.has_extension())
		m_path /= "Config.json";
	std::ifstream file(m_path, std::ios::in | std::ios::trunc);
	if (!file.is_open()) {
		writeDummy();
		file.open(m_path);
	}
	file >> m_path;
	bool shouldSave{};
	for (auto& e : g_dummyJson.items()) {
		if (!get().count(e.key())) {
			shouldSave = true;
			get()[e.key()] = e.value();
		}

	}
	if (shouldSave)
		save();
}
void config::save() {
	std::ofstream file(m_path, std::ios::out | std::ios::trunc);
	file << get().dump(4);
	file.close();
}
void config::writeDummy() {
	get() = g_dummyJson;
	save();
}
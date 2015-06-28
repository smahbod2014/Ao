#include "FontManager.h"
#include "../graphics/Font.h"

std::map<const std::string, Font*> FontManager::m_Cache;

void FontManager::load(const std::string& alias, const std::string& filepath, float size)
{
	auto it = m_Cache.find(alias);
	if (it != m_Cache.end())
		return;

	m_Cache[alias] = new Font(filepath, size);
}

void FontManager::add(const std::string& alias, Font* font)
{
	auto it = m_Cache.find(alias);
	if (it != m_Cache.end())
		return;

	m_Cache[alias] = font;
}

Font* FontManager::get(const std::string& alias)
{
	auto it = m_Cache.find(alias);
	if (it == m_Cache.end())
		return nullptr;

	return m_Cache[alias];
}
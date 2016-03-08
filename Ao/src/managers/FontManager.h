#pragma once

#include <map>
#include <string>

class Font;

class FontManager
{
private:
	FontManager() {}
public:
	static void load(const std::string& alias, const std::string& filepath, float size);
	static void add(const std::string& alias, Font* font);
	static void initDefaultFonts();
	static Font* get(const std::string& alias);
	static void clean();
private:
	static std::map<const std::string, Font*> m_Cache;
};
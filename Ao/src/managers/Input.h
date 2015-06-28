#pragma once

#include <map>

class Input
{
	friend class Window;
public:
	static bool isKeyJustPressed(int key);
	static bool isKeyDown(int key);
private:
	static void pressKey(int key);
	static void releaseKey(int key);
	static void update();

	static std::map<int, int> m_KeyMap;
};
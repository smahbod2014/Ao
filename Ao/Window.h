#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <iostream>

class Window
{
public:
	Window(const std::string& name, int width, int height);
	~Window();

	void input();
	void swapBuffer();
	void synchronize(int fps);
	
	bool shouldClose() const { return m_ShouldClose; }
	int getTicks() const { return m_Ticks; }
private:
	SDL_Window* m_Window;
	int m_Width, m_Height;
	bool m_ShouldClose = false;
	Uint32 m_LastFrameTime = 0;
	int m_Ticks = 0;
};
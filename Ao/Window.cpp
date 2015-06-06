#include "Window.h"

Window::Window(const std::string& name, int width, int height)
{
	m_Width = width;
	m_Height = height;

	Uint32 flags = SDL_WINDOW_OPENGL;
	m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);

	if (glewInit() != GLEW_OK)
		std::cout << "Couldn't initialize Glew!" << std::endl;

	std::cout << "Open GL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0, 0, 1, 1);

	SDL_GL_SetSwapInterval(0);
}

Window::~Window()
{
	if (m_Window)
		SDL_DestroyWindow(m_Window);
}

void Window::input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_ShouldClose = true;
			break;
		case SDL_KEYDOWN:
			std::cout << "Pressed " << event.key.keysym.sym << std::endl;
			break;
		}
	}
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(m_Window);
}

void Window::synchronize(int fps)
{
	Uint32 maxFrameTime = 1000 / fps; //16
	Uint32 currentTime = SDL_GetTicks(); //800
	Uint32 difference = currentTime - m_LastFrameTime; //800 - 0 = 800
	int timeToSleep = maxFrameTime - difference; //16 - 800 = -784
	m_Ticks++;
	if (timeToSleep > 0)
		SDL_Delay(timeToSleep);
	m_LastFrameTime = currentTime + timeToSleep;
}
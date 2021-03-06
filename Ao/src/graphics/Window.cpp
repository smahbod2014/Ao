#include "Window.h"
#include "../managers/Input.h"
#include "../managers/SoundManager.h"

int Window::m_Width = 0;
int Window::m_Height = 0;
vec4 Window::m_ClearColor;

Window::Window(const std::string& name, int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_Name = name;

	SDL_Init(SDL_INIT_EVERYTHING);

	Uint32 flags = SDL_WINDOW_OPENGL;
	m_Window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);

	if (glewInit() != GLEW_OK)
		std::cout << "Couldn't initialize Glew!" << std::endl;

	SoundManager::init();
	
	std::cout << "Open GL version: " << glGetString(GL_VERSION) << std::endl;

	m_ClearColor = vec4(1, 0, 0, 0);
	glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glViewport(0, 0, m_Width, m_Height);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_SetSwapInterval(0);
}

Window::~Window()
{
	if (m_Window)
		SDL_DestroyWindow(m_Window);

	SoundManager::destroy();
	SDL_Quit();
}

void Window::swapBuffer()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "Open GL error: " << error << std::endl;

	SDL_GL_SwapWindow(m_Window);
}

void Window::begin()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_StartFrameTime = SDL_GetTicks();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_ShouldClose = true;
			break;
		case SDL_KEYDOWN:
			Input::pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			Input::releaseKey(event.key.keysym.sym);
			break;
		}
	}
}

void Window::end()
{
	Input::update();

#if 1
	Uint32 difference = SDL_GetTicks() - m_StartFrameTime;
	float maxFrameTime = 1000.0f / m_MaxFps;
	if ((Uint32)maxFrameTime > difference)
	{
		SDL_Delay((Uint32)maxFrameTime - difference);
		m_Delta = 1.0f / m_MaxFps;
		m_InstantaneousFps = m_MaxFps;
	}
	else
	{
		m_Delta = difference / 1000.0f;
		m_InstantaneousFps = 1.0f / m_Delta;
	}
#else
	Uint32 difference = SDL_GetTicks() - m_StartFrameTime;
	if (difference > 0)
	{
		m_InstantaneousFps = 1000.0f / difference;
		m_Delta = 1.0f / m_InstantaneousFps;
	}
#endif

	m_Ticks++;

	if (m_Ticks % (int)m_MaxFps == 0)
	{
		std::string fpsName = m_Name + " - FPS: " + std::to_string(getFps());
		SDL_SetWindowTitle(m_Window, fpsName.c_str());
		//std::cout << SDL_GetTicks() << std::endl;
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "Open GL error: " << error << std::endl;
}

void Window::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static Uint32 frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static Uint32 prevTicks = SDL_GetTicks();

	Uint32 currentTicks = SDL_GetTicks();
	Uint32 frameTime = currentTicks - prevTicks; //in milliseconds
	prevTicks = currentTicks;

	frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

	currentFrame++;

	int count;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float average = 0;

	for (int i = 0; i < count; i++)
		average += frameTimes[i];

	average /= count;

	if (average > 0)
		m_Fps = 1000.0f / average;
	else
		m_Fps = 60.0f;
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
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
#ifdef AO_EMSCRIPTEN
			Input::pressKey(event.key.keysym.sym);
#else
			Input::pressKey(event.key.keysym.scancode);
#endif
			break;
		case SDL_KEYUP:
#ifdef AO_EMSCRIPTEN
			Input::releaseKey(event.key.keysym.sym);
#else
			Input::releaseKey(event.key.keysym.scancode);
#endif
			break;
		}
	}
}

void Window::updateInput()
{
	Input::update();
}
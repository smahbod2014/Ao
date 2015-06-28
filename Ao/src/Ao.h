#pragma once

#include <iostream>
#include <glm/gtx/transform.hpp>
#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Layer.h"
#include "graphics/BatchRenderer2D.h"
#include "graphics/Sprite.h"
#include "graphics/Group.h"
#include "graphics/Label.h"
#include "graphics/Font.h"
#include "managers/TextureManager.h"
#include "managers/FontManager.h"
#include "managers/Input.h"
#include "managers/Timer.h"
#include <ctime>

class Ao
{
public:
	void start()
	{
		srand((unsigned int)time(NULL));
		FontManager::load("default", "Resources/Fonts/arial.ttf", 35.0f);
		init();
		run();
	}
protected:
	Ao() {}
	virtual ~Ao()
	{
		if (m_Window) delete m_Window;
		if (m_Timer) delete m_Timer;
	}

	void createWindow(const std::string& name, int width, int height)
	{
		m_Window = new Window(name, width, height);
	}

	virtual void init() = 0;
	virtual void tick() {}
	virtual void update(float dt) {}
	virtual void render() = 0;
	virtual void finish() {}

	const unsigned int getFps() const { return m_Fps; }
	const unsigned int getUps() const { return m_Ups; }
	const float getDelta() const { return m_Delta; }
private:
	void run()
	{
		m_Timer = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		const float updateTick = 1.0f / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;

		while (!m_Window->shouldClose())
		{
			m_Window->clear();

			float dt = m_Timer->elapsed() - updateTimer;
			if (dt >= updateTick)
			{
				m_Delta = dt;
				update(dt);
				m_Window->updateInput();
				updates++;
				updateTimer += updateTick;
			}

			render();
			frames++;
			m_Window->update();

			float tickDelta = m_Timer->elapsed() - timer;
			if (tickDelta >= 1.0f)
			{
				timer += 1.0f;
				m_Fps = frames;
				m_Ups = updates;
				frames = 0;
				updates = 0;
				tick();
			}
		}

		finish();
	}
private:
	Window* m_Window = nullptr;
	Timer* m_Timer = nullptr;
	unsigned int m_Fps = 0, m_Ups = 0;
	float m_Delta;
};
#if 0
#include <iostream>
#include <glm/gtx/transform.hpp>
#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include "src/graphics/Layer.h"
#include "src/graphics/BatchRenderer2D.h"
#include "src/graphics/Sprite.h"
#include "src/graphics/Group.h"
#include "src/graphics/Label.h"
#include "src/graphics/Font.h"
#include "src/managers/TextureManager.h"
#include "src/managers/FontManager.h"
#include <ctime>

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));

	float MAX_FPS = 120.0f;
	Window window("Ao", 960, 540);
	window.setMaxFPS(MAX_FPS);

	//load default font!
	TextureManager::loadTexture("face", "Resources/Textures/wtf face.png");
	TextureManager::loadTexture("whocares", "Resources/Textures/whocares.png");
	TextureManager::loadTexture("bricks", "Resources/Textures/bricks.png");
	TextureManager::loadTexture("checker", "Resources/Textures/checkerboard.png");
	FontManager::load("arial", "Resources/Fonts/arial.ttf", 35.0f);

	FontManager::get("arial")->setScale(Window::getWidth() / 32.0f, Window::getHeight() / 18.0f);

	Shader* shader = new Shader();
	shader->load("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");

	BatchRenderer2D* renderer = new BatchRenderer2D();

	Layer layer(renderer, shader, glm::ortho<float>(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	
	int iterations = 0;
	float step = 2.0f;
	for (float y = -9.0f; y < 9.0f; y += step)
		for (float x = -16.0f; x < 16.0f; x += step)
		{
			const Texture* texture = nullptr;
			int tex = rand() % 4;
			if (tex == 0)
				texture = TextureManager::getTexture("face");
			else if (tex == 1)
				texture = TextureManager::getTexture("whocares");
			else if (tex == 2)
				texture = TextureManager::getTexture("bricks");
			else if (tex == 3)
				texture = TextureManager::getTexture("checker");
			layer.add(new Sprite(glm::vec3(x, y, 0), glm::vec2(step, step), 0xffffffff, texture));
			iterations++;
		}

	std::cout << "Made " << iterations << " sprites" << std::endl;

	
	//layer.add(label);

	//layer.add(new Sprite(glm::vec3(-15.75f, 7.25f, 0), glm::vec2(4.0f, 1.5f), glm::vec4(1, 1, 1, 0.75f)));

	Group* fpsGroup = new Group(glm::translate(glm::vec3(-15.0f, 7.0f, 0.0f)));
	Label* fpsLabel = new Label("", 0.4f, 0.4f, "arial", glm::vec4(1.0, 1.0, 1.0, 1.0f));
	fpsGroup->add(new Sprite(glm::vec3(0, 0, 0), glm::vec2(5.0f, 1.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.5f)));
	fpsGroup->add(fpsLabel);
	
	layer.add(fpsGroup);

	while (!window.shouldClose())
	{
		window.begin();
		float dt = window.getDelta();
		
		fpsLabel->m_Text = std::to_string((int)window.getFps()) + " fps";
		layer.render();

		window.swapBuffer();
		window.end();
	}

	return 0;
}
#endif

#include "src/Ao.h"
#include <iostream>

class Game : public Ao
{
public:
	Game() {}
	~Game() {}

	void init() override
	{
		createWindow("Ao!", 960, 540);
		FontManager::get("default")->setScale(Window::getWidth() / 32.0f, Window::getHeight() / 18.0f);
		TextureManager::load("face", "Resources/Textures/wtf face.png");
		TextureManager::load("smiley", "Resources/Textures/bricks.png");
		TextureManager::load("x", "Resources/Textures/X16.png");
		TextureManager::load("yaku", "Resources/Textures/whocares.png");
		TextureManager::load("kirito", "Resources/Textures/kirito.png");

		m_Shader = new Shader("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");
		m_Layer = new Layer(new BatchRenderer2D(), m_Shader, glm::ortho<float>(-16, 16, -9, 9, -1, 1));

		int iterations = 0;
		float step = 2.0f;
		for (float y = -9.0f; y < 9.0f; y += step)
			for (float x = -16.0f; x < 16.0f; x += step)
			{
				const Texture* texture = nullptr;
				int tex = rand() % 4;
				if (tex == 0)
					texture = TextureManager::get("face");
				else if (tex == 1)
					texture = TextureManager::get("smiley");
				else if (tex == 2)
					texture = TextureManager::get("x");
				else if (tex == 3)
					texture = TextureManager::get("yaku");
				m_Layer->add(new Sprite(glm::vec3(x, y, 0), glm::vec2(step, step), 0xffffffff, texture));
				iterations++;
			}

		std::cout << "Made " << iterations << " sprites" << std::endl;

		m_Player = new Sprite(glm::vec3(0, 0, 0), glm::vec2(10, 10), TextureManager::get("kirito"));
		m_Layer->add(m_Player);

		Group* fpsGroup = new Group(glm::translate(glm::vec3(-15.0f, 7.0f, 0.0f)));
		m_FpsLabel = new Label("", 0.4f, 0.4f, "default", glm::vec4(1.0, 1.0, 1.0, 1.0f));
		fpsGroup->add(new Sprite(glm::vec3(0, 0, 0), glm::vec2(5.0f, 1.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.5f)));
		fpsGroup->add(m_FpsLabel);

		m_Layer->add(fpsGroup);
	}

	void tick() override
	{
		m_FpsLabel->m_Text = std::to_string(getFps()) + " fps";
		std::cout << "FPS: " << getFps() << ", UPS: " << getUps() << ", Delta: " << getDelta() << std::endl;
	}

	void update(float dt) override
	{
		const float speed = 15.0f * dt;
		//m_Player->position.x -= speed;
		if (Input::isKeyJustPressed(SDLK_a))
			m_Player->position.x = 10;
		if (Input::isKeyDown(SDLK_LEFT))
			m_Player->position.x -= speed;
		if (Input::isKeyDown(SDLK_RIGHT))
			m_Player->position.x += speed;
		if (Input::isKeyDown(SDLK_DOWN))
			m_Player->position.y -= speed;
		if (Input::isKeyDown(SDLK_UP))
			m_Player->position.y += speed;
	}

	void render() override
	{
		m_Layer->render();
	}

	void finish() override
	{
		std::cout << "Finished" << std::endl;
	}

private:
	Shader* m_Shader;
	Layer* m_Layer;
	Label* m_FpsLabel;
	Sprite* m_Player;
};

int main(int argc, char* argv[])
{
	Game game;
	game.start();
	return 0;
}
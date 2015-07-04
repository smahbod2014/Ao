#include "src/Ao.h"
#include <iostream>

class Game : public Ao
{
public:
	Game(const std::string& name, unsigned int width, unsigned int height) : Ao(name, width, height) {}
	virtual ~Game()
	{
		delete m_Layer;
	}

	void init() override
	{
		FontManager::get("default")->setScale(Window::getWidth() / 32.0f, Window::getHeight() / 18.0f);
		TextureManager::load("face", "Resources/Textures/wtf_face.png");
		TextureManager::load("smiley", "Resources/Textures/bricks.png");
		TextureManager::load("x", "Resources/Textures/X16.png");
		TextureManager::load("yaku", "Resources/Textures/whocares.png");
		TextureManager::load("kirito", "Resources/Textures/kirito2.png");
		//SoundManager::loadSound("holyshit", "Resources/Sounds/holy_shit.ogg", 0.25f);
		SoundManager::loadMusic("forest", "Resources/Sounds/forest_temple.ogg", 0.1f);
		
#ifdef AO_EMSCRIPTEN
		m_Shader = new Shader("Resources/Shaders/Basic_gles.vert", "Resources/Shaders/Basic_gles.frag");
#else
		m_Shader = new Shader("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");
#endif
		m_Layer = new Layer(new BatchRenderer2D(), m_Shader, mat4::orthographic(-16, 16, -9, 9, -1, 1));

		int iterations = 0;
		float step = 0.5f;
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
				m_Layer->add(new Sprite(vec3(x, y, 0), vec2(step, step), 0xffffffff, texture));
				iterations++;
			}

		std::cout << "Made " << iterations << " sprites" << std::endl;

		m_Player = new Sprite(vec3(0, 0, 0), vec2(12.5f, 12.5f), TextureManager::get("kirito"));
		m_Layer->add(m_Player);

		m_FpsGroup = new Group();
		m_FpsGroup->setOrigin(2.5f, 0.75f);
		m_FpsGroup->translate(-15.0f, 7.0f, 0.0f);
		m_FpsLabel = new Label("", 0.4f, 0.4f, "default", vec4(1.0, 1.0, 1.0, 1.0f));
		m_FpsGroup->add(new Sprite(vec3(0, 0, 0), vec2(5.0f, 1.5f), vec4(0.2f, 0.2f, 0.2f, 0.5f)));
		m_FpsGroup->add(m_FpsLabel);

		m_Layer->add(m_FpsGroup);

		SoundManager::getMusic("forest")->play();
	}

	void tick() override
	{
		m_FpsLabel->m_Text = std::to_string(getFps()) + " fps";
		std::cout << "FPS: " << getFps() << ", Delta: " << getDelta() << std::endl;
	}

	void update(float dt) override
	{
		const float speed = 15.0f * dt;

		m_Player->position.x -= speed * 0.01f;
		
		if (Input::isKeyDown(SDLK_LEFT))
			m_Player->position.x -= speed;
		if (Input::isKeyDown(SDLK_RIGHT))
			m_Player->position.x += speed;
		if (Input::isKeyDown(SDLK_DOWN))
			m_Player->position.y -= speed;
		if (Input::isKeyDown(SDLK_UP))
			m_Player->position.y += speed;

		if (Input::isKeyJustPressed(SDLK_q))
			SoundManager::getSound("holyshit")->play();

		if (Input::isKeyJustPressed(SDLK_p))
			SoundManager::getMusic("forest")->play();

		if (Input::isKeyJustPressed(SDLK_a))
			SoundManager::getMusic("forest")->pause();

		if (Input::isKeyJustPressed(SDLK_r))
			SoundManager::getMusic("forest")->resume();

		if (Input::isKeyJustPressed(SDLK_s))
			SoundManager::getMusic("forest")->stop();

		if (Input::isKeyJustPressed(SDLK_t))
			std::cout << "T key just pressed" << std::endl;

		if (Input::isKeyDown(SDLK_y))
			std::cout << "Y key down" << std::endl;

		m_FpsGroup->rotate(vec3(0, 0, 1), speed);
	}

	void render() override
	{
		m_Layer->render();
	}

	void finish() override
	{
		std::cout << "AO HAS FINISHED EXECUTING!" << std::endl;
	}

private:
	Shader* m_Shader;
	Layer* m_Layer;
	Label* m_FpsLabel;
	Sprite* m_Player;
	Group* m_FpsGroup;
};

int main(int argc, char* argv[])
{
	Game game("Ao", 960, 540);
	game.start();
	return 0;
}
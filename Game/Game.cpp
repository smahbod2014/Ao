#include <Ao.h>
#include <iostream>
#include <selene.h>

#if 0

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
		//TODO: Maybe create a loadResources() function dedicated to making these load() calls?
		FontManager::get("default")->setScale(Window::getWidth() / 32.0f, Window::getHeight() / 18.0f);
		TextureManager::load("face", "Resources/Textures/wtf16.png");
		TextureManager::load("smiley", "Resources/Textures/bricks.png");
		TextureManager::load("x", "Resources/Textures/X16.png");
		TextureManager::load("yaku", "Resources/Textures/whocares.png");
		TextureManager::load("kirito", "Resources/Textures/kirito2.png");
		//SoundManager::loadSound("holyshit", "Resources/Sounds/holy_shit.ogg", 0.25f);
		SoundManager::loadMusic("forest", "Resources/Sounds/forest_temple.ogg", 0.1f);
		
		/*
		TODO: Having to load the default shader here, not to mention the use of
		the Emscripten macros in the game file, is unacceptable. See the TODOs in Shader.cpp
		*/
#ifdef AO_EMSCRIPTEN
		m_Shader = new Shader("Resources/Shaders/Basic_gles.vert", "Resources/Shaders/Basic_gles.frag");
#else
		m_Shader = new Shader("Resources/Shaders/Basic.vert", "Resources/Shaders/Basic.frag");
#endif
		//TODO: Maybe create a default layer in Ao.h?
		m_Layer = new Layer(new BatchRenderer2D(), m_Shader, mat4::orthographic(-16, 16, -9, 9, -1, 1));
		//m_Layer = new Layer(new BatchRenderer2D(), m_Shader, mat4::orthographic(0, 32, 0, 18, -1, 1));

		int iterations = 0;
		float step = 0.5f;
		for (float y = -9.0f; y < 9.0f; y += step)
		{
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
		}

		std::cout << "Made " << iterations << " sprites" << std::endl;

		m_Player = new Sprite(vec3(0, 0, 0), vec2(12.5f, 11.5f), TextureManager::get("kirito"));
		m_Layer->add(m_Player);

		m_FpsGroup = new Group();
		m_FpsGroup->setOrigin(2.5f, 0.75f);
		m_FpsGroup->translate(-15.0f, 7.0f, 0.0f);
		m_FpsLabel = new Label("", 0.4f, 0.4f, "default", vec4(1.0, 1.0, 1.0, 1.0f));
		m_FpsGroup->add(new Sprite(vec3(0, 0, 0), vec2(5.0f, 1.5f), vec4(0.2f, 0.2f, 0.2f, 0.5f)));
		m_FpsGroup->add(m_FpsLabel);

		m_Layer->add(m_FpsGroup);

		SoundManager::getMusic("forest")->play();

		sel::State state(true);
		state.Load("script.lua");

		double speed = (double)state["speed"];
		std::cout << "C++ says 'speed' is " << speed << std::endl;

		m_Speed = (float)speed;
	}

	void tick() override
	{
		m_FpsLabel->m_Text = std::to_string(getFps()) + " fps";
		std::cout << "FPS: " << getFps() << ", Delta: " << getDelta() << std::endl;
	}

	void update(float dt) override
	{
		const float speed = 15.0f * dt;

		//m_Player->position.x -= m_Speed * dt;
		
		if (Input::isKeyDown(AO_KEY_LEFT))
			m_Player->position.x -= speed;
		if (Input::isKeyDown(AO_KEY_RIGHT))
			m_Player->position.x += speed;
		if (Input::isKeyDown(AO_KEY_DOWN))
			m_Player->position.y -= speed;
		if (Input::isKeyDown(AO_KEY_UP))
			m_Player->position.y += speed;

		
		if (Input::isKeyJustPressed(AO_KEY_Q))
			SoundManager::getSound("holyshit")->play();

		if (Input::isKeyJustPressed(AO_KEY_P))
			SoundManager::getMusic("forest")->play();

		if (Input::isKeyJustPressed(AO_KEY_A))
			SoundManager::getMusic("forest")->pause();

		if (Input::isKeyJustPressed(AO_KEY_R))
			SoundManager::getMusic("forest")->resume();

		if (Input::isKeyJustPressed(AO_KEY_S))
			SoundManager::getMusic("forest")->stop();

		if (Input::isKeyJustPressed(AO_KEY_T))
			std::cout << "T key just pressed" << std::endl;

		if (Input::isKeyDown(AO_KEY_Y))
			std::cout << "Y key down" << std::endl;

		m_FpsGroup->rotate(vec3(0, 0, 1), speed);
	}

	void render() override
	{
		m_Layer->render();
	}

	void finish() override
	{
		
	}

private:
	float m_Speed;
	Shader* m_Shader;
	Layer* m_Layer;
	Label* m_FpsLabel;
	Sprite* m_Player;
	Group* m_FpsGroup;
};

#else

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
		//TODO: Camera class!

		//TODO: Maybe create a loadResources() function dedicated to making these load() calls?
		TextureManager::load("face", "Resources/Textures/wtf16.png");
		TextureManager::load("smiley", "Resources/Textures/bricks.png");
		TextureManager::load("x", "Resources/Textures/X16.png");
		TextureManager::load("yaku", "Resources/Textures/whocares.png");
		TextureManager::load("kirito", "Resources/Textures/kirito2.png");
		TextureManager::load("kiritoorig", "Resources/Textures/kirito.png");
		//SoundManager::loadSound("holyshit", "Resources/Sounds/holy_shit.ogg", 0.25f);
		SoundManager::loadMusic("forest", "Resources/Sounds/forest_temple.ogg", 0.1f);


		//TODO: Maybe create a default layer in Ao.h?
		float w = (float)Window::getWidth();
		float h = (float)Window::getHeight();
		m_Layer = new Layer(new BatchRenderer2D(), mat4::orthographic(0, w, 0, h, -1, 1));

		/*int iterations = 0;
		float step = 20.0f;
		for (float y = 0.0f; y < (float)h; y += step)
		{
			for (float x = 0.0f; x < (float)w; x += step)
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
		}

		std::cout << "Made " << iterations << " sprites" << std::endl;*/
		m_Layer->add(new Sprite(vec3(0, 0, 0), vec2(480.0f, 270.0f), 0xffffffff, TextureManager::get("face")));
		m_Layer->add(new Sprite(vec3(480.0f, 270.0f, 0), vec2(480.0f, 270.0f), 0xffffffff, TextureManager::get("yaku")));

		m_Player = new Sprite(vec3(0, 0, 0), vec2(480.0f, 540.0f), TextureManager::get("kiritoorig"));
		m_Layer->add(m_Player);

		float fpsWidth = 166.65f;
		float fpsHeight = 50.0f;
		m_FpsGroup = new Group();
		m_FpsGroup->setOrigin(fpsWidth / 2.0f, fpsHeight / 2.0f);
		m_FpsGroup->translate(480.0f, 270.0f, 0.0f);
		m_FpsLabel = new Label("", 10.0f, 10.0f, "arial", vec4(1.0, 1.0, 1.0, 1.0f));
		m_FpsGroup->add(new Sprite(vec3(0, 0, 0), vec2(fpsWidth, fpsHeight), vec4(0.2f, 0.2f, 0.2f, 0.5f)));
		m_FpsGroup->add(m_FpsLabel);

		m_Layer->add(m_FpsGroup);

		SoundManager::getMusic("forest")->play();

		sel::State state(true);
		state.Load("script.lua");

		double speed = (double)state["speed"];
		std::cout << "C++ says 'speed' is " << speed << std::endl;

		m_Speed = (float)speed;
	}

	void tick() override
	{
		m_FpsLabel->m_Text = std::to_string(getFps()) + " fps";
		std::cout << "FPS: " << getFps() << ", Delta: " << getDelta() << std::endl;
	}

	void update(float dt) override
	{
		const float speed = 480.0f * dt;

		//m_Player->position.x -= m_Speed * dt;

		if (Input::isKeyDown(AO_KEY_LEFT))
			m_Player->position.x -= speed;
		if (Input::isKeyDown(AO_KEY_RIGHT))
			m_Player->position.x += speed;
		if (Input::isKeyDown(AO_KEY_DOWN))
			m_Player->position.y -= speed;
		if (Input::isKeyDown(AO_KEY_UP))
			m_Player->position.y += speed;


		if (Input::isKeyJustPressed(AO_KEY_Q))
			SoundManager::getSound("holyshit")->play();

		if (Input::isKeyJustPressed(AO_KEY_P))
			SoundManager::getMusic("forest")->play();

		if (Input::isKeyJustPressed(AO_KEY_A))
			SoundManager::getMusic("forest")->pause();

		if (Input::isKeyJustPressed(AO_KEY_R))
			SoundManager::getMusic("forest")->resume();

		if (Input::isKeyJustPressed(AO_KEY_S))
			SoundManager::getMusic("forest")->stop();

		if (Input::isKeyJustPressed(AO_KEY_T))
			std::cout << "T key just pressed" << std::endl;

		if (Input::isKeyDown(AO_KEY_Y))
			std::cout << "Y key down" << std::endl;

		m_FpsGroup->rotate(vec3(0, 0, 1), speed / 4.0f);
	}

	void render() override
	{
		m_Layer->render();
	}

	void finish() override
	{

	}

private:
	float m_Speed;
	Layer* m_Layer;
	Label* m_FpsLabel;
	Sprite* m_Player;
	Group* m_FpsGroup;
};

#endif

int main(int argc, char* argv[])
{
	Game game("Ao", 960, 540);
	game.start();
	return 0;
}
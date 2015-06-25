#include <iostream>
#include <glm/gtx/transform.hpp>
#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include "src/graphics/Layer.h"
#include "src/graphics/BatchRenderer2D.h"
#include "src/graphics/Sprite.h"
#include "src/graphics/Group.h"
#include "src/graphics/Label.h"
#include "src/managers/TextureManager.h"
#include <ctime>

int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));

	float MAX_FPS = 120.0f;
	Window window("Ao", 960, 540);
	window.setMaxFPS(MAX_FPS);

	TextureManager::loadTexture("face", "Resources/Textures/wtf face.png");
	TextureManager::loadTexture("whocares", "Resources/Textures/whocares.png");
	TextureManager::loadTexture("bricks", "Resources/Textures/bricks.png");
	TextureManager::loadTexture("checker", "Resources/Textures/checkerboard.png");

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
			layer.add(new Sprite(glm::vec3(x, y, 0), glm::vec2(step, step), texture));
			iterations++;
		}

	std::cout << "Made " << iterations << " sprites" << std::endl;
	
	Label* label = new Label("Hello", 10, 3, 0xffffffff);
	layer.add(label);

	/*glm::mat4 matrix(1.0);
	matrix[3][0] = -5;
	matrix[3][1] = -7;
	Group* group = new Group(matrix);
	group->add(new Sprite(glm::vec3(0, 0, 0), glm::vec2(7, 7), TextureManager::getTexture("face")));
	group->add(new Sprite(glm::vec3(2, 2, 0), glm::vec2(7, 7), TextureManager::getTexture("whocares")));

	layer.add(group);*/

	while (!window.shouldClose())
	{
		window.begin();
		float dt = window.getDelta();
		
		layer.render();

		window.swapBuffer();
		window.end();
	}

	return 0;
}
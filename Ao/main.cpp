#include <iostream>
#include <GL/glew.h>
#include "Window.h"
#include "Shader.h"

int main(int argc, char* argv[])
{
	Window window("Ao", 800, 600);
	Shader shader("Shaders/Shine.vert", "Shaders/Shine.frag");

	int fps = 60;
	float t = 0;
	while (!window.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.setUniform1("t", t);
		glBegin(GL_QUADS);
		//glColor3f(1, 0, 0);
		glVertex3f(-.5, .5, 0);
		glVertex3f(-.5, -.5, 0);
		glVertex3f(.5, -.5, 0);
		glVertex3f(.5, .5, 0);
		glEnd();
		shader.unbind();

		window.input();
		window.swapBuffer();
		window.synchronize(fps);
		t += .01667f;

#if 0
		if (window.getTicks() % fps == 0)
			std::cout << "Frame" << std::endl;
#endif
	}

	return 0;
}
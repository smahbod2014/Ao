#include <iostream>
#include <GL/glew.h>
#include "Window.h"

int main(int argc, char* argv[])
{
	Window window("Ao", 800, 600);
	
	int fps = 60;
	while (!window.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(-.5, .5, 0);
		glVertex3f(-.5, -.5, 0);
		glVertex3f(.5, -.5, 0);
		glVertex3f(.5, .5, 0);
		glEnd();
		window.input();
		window.swapBuffer();
		window.synchronize(fps);

		if (window.getTicks() % fps == 0)
			std::cout << "Frame" << std::endl;
	}

	return 0;
}
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

constexpr int WINDOW_WIDTH = 640, WINDOW_HEIGHT = 520;

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "Failed to init SDL.";
		return -1;
	}

	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window* window = SDL_CreateWindow("Raytrace", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Failed to create window.";
		return -1;
	}

	glewExperimental = GL_TRUE;

	SDL_GLContext ctx = SDL_GL_CreateContext(window);
	if (ctx == nullptr)
	{
		std::cout << "Failed to create OpenGL Context.";
		return -1;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init glew.";
		return -1;
	}

	/* must be 8+8+8 = 24
	int rS, gS, bS;
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &rS);
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &gS);
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &bS);

	std::cout << rS << ' ' << gS << ' ' << bS;
	*/

	SDL_Event e;
	bool quit = false;
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			quit = (e.type == SDL_QUIT);
		}
		if (quit)
			break;

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

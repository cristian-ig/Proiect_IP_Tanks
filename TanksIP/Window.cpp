#include "Window.h"
#include <iostream>

namespace tanks {

Window::Window()
{
}

Window::~Window()
{
}

int Window::init(std::string windowName,
	int windowWidth,
	int windowHeight,
	unsigned int windowFlag)
{
	Uint32 flags = SDL_WINDOW_OPENGL;
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	if (windowFlag & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (windowFlag & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (windowFlag & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}
	if (windowFlag & RESIZABLE) {
		flags |= SDL_WINDOW_RESIZABLE;
	}

	//Create a window
	_window = SDL_CreateWindow(windowName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowHeight,
		windowWidth,
		flags);
	if (_window == nullptr)
	{
		//eroare fatala
		std::cout << "cancer\n";
	}
	//set up OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		//eroare fatala
	}
	//init glew
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << error;
	}

	//Set the background color to blue.. kind of
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//********OPTIONAL************//
	//Check the OpenGL version
	std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	//Set VSYNC
	SDL_GL_SetSwapInterval(1);

	return 0;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_window);
}

}
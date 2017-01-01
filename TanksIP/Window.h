#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <string>
#include "Defines.h"


namespace Engine{

	enum Flags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4,
		RESIZABLE = 0x8
	};

class Window
{
public:

	int init(std::string windowName,
		int windowWidth,
		int windowHeight,
		unsigned int windowFlag); //Creates a sdl basic window

	void swapBuffer(); //swaps buffers between clear and draw for no screen flikering

	//getters
	int getWindowWidth() { return _windowWidth; }
	int getWindowHeight() { return _windowHeight; }

	Window();
	~Window();
private:
	SDL_Window *_window = nullptr;
	int _windowWidth = 0;
	int _windowHeight = 0;
	
};

}
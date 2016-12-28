#pragma once
#include<iostream>
#include<SDL.h>
#include "Window.h"
#include "Input.h"

namespace tanks{

enum class GameState {
	PLAY,
	EXIT
};


class MainGame {

public:
	MainGame();
	~MainGame();

	void start();
private:
	void init();
	void mainLoop();
	void draw();
	void processInput();

	Window _window;
	Input _input;
	GameState _gameState;
	int _width = 1024;
	int _height = 768;


};
}
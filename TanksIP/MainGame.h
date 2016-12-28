#pragma once
#include<iostream>
#include<SDL.h>
#include "GLSL.h"
#include "Window.h"
#include "Input.h"
#include "Map.h"

namespace Engine{

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
	void update();
	void loadShaders();

	int _height = 768;
	int _width = 1024;
	float _fps = 0;
	int _currentMap = -1;

	Window _window;
	Input _input;
	GameState _gameState;
	GLSL _texProgram;

	std::vector<Mapz*> _map;
};
}
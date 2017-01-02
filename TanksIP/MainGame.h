#pragma once
#include<iostream>
#include<SDL.h>
#include "Window.h"
#include "Input.h"
#include"Camera.h"
#include"FPS.h"
#include"GLSL.h"
#include"Harta.h"
#include <vector>
#include "Entity.h"
#include "Players.h"

using namespace Engine;

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
	Camera _camera;
	FPS _frameTimer;
	GLSL _shaders;
	Players _player;
	std::vector<Harta*> _harta;
	
	
	


};

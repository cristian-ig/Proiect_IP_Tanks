#pragma once
#include<iostream>
#include<SDL.h>
#include "Window.h"
#include "Input.h"
#include"Camera.h"
#include"FPS.h"
#include"GLSL.h"



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
	Camera _camera;
	FPS _frameTimer;
	GLSL _shaders;
	


};
}
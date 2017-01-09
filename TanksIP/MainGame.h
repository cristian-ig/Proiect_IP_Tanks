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
#include "Enemys.h"
#include"Projectiles.h"
#include"Artillery.h"
#include "DrawClass.h"
#include "BonusBox.h"

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
	void initShaders();
	void init();
	//void initMap();
	void mainLoop();
	void draw();
	void processInput();
	void updateEntitys();
	void updateBullets();

	Window _window;
	Input _input;
	GameState _gameState;
	Camera _camera;
	FPS _frameTimer;
	GLSL _shaders;
	DrawSprites _drawEntityHandler;

	std::vector<Players*> _player;
	std::vector<Enemys*> _enemy;
	std::vector<Harta*> _harta;
	std::vector<Projectiles> _projectiles;
	std::vector<BonusBox*> _bonuses;
	//BonusBox* _bonuses;


	//Artillery _artilllery;

	int _curLevel = -1;

	char _numEnem = 3;
	char _numPlayers = 1;
	
	
	


};

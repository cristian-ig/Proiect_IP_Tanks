#pragma once
#include<iostream>
#include<SDL.h>
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "FPS.h"
#include "GLSL.h"
#include "Harta.h"
#include <vector>
#include "Entity.h"
#include "Players.h"
#include "Enemys.h"
#include "Projectiles.h"
#include "Artillery.h"
#include "DrawClass.h"
#include "BonusBox.h"
#include "AudioManager.h"
#include "FileLoad.h"


using namespace Engine;

class Butt {

public:
	glm::vec4 quad;
	GLuint texture;
	std::vector<GLuint> textureID;
	bool isSelected = false;
	void ButtonState() {

		if (isSelected)
			texture = textureID[1];
		else texture = textureID[0];

	}



};

class MainGame {

public:
	MainGame();
	~MainGame();

	GameState start(Window * window);
	void setGameState(GameState gamestate) { _gameState = gamestate; }
	void setTankType(TankType player1, TankType player2);
	void isKeyPressed();
	void setLevel(int level) { _curLevel = level; }
private:
	void initShaders();
	void init();
	//void initMap();
	GameState mainLoop();
	void draw();
	void drawMenu();
	
	void processInput();
	void updateEntitys();
	void updateBullets();
	void normalizeTanksStats(BonusType boxTime, Entity* entity);
	
	Window *_window;
	Music music;
	Input _input;
	GameState _gameState,state =GameState::SINGLEPLAYER;
	Camera _camera;
	FPS _frameTimer;
	GLSL _shaders;
	DrawSprites _drawEntityHandler;
	DrawSprites drawHandler;
	AudioManager _audioManager;
	SoundEffect _SEffect;

	TankType pl1;
	TankType pl2;
	Butt resume, quit, finish;
	int _fin ,_finTime=0;
	int currButton = 1;
	std::vector<Players*> _player;
	std::vector<Enemys*> _enemy;
	std::vector<Harta*> _harta;
	std::vector<Projectiles> _projectiles;
	std::vector<BonusBox*> _bonuses;
	//std::vector<int*> timer;
	int _timer = 0;
	//BonusBox* _bonuses;
	std::vector<std::pair<BonusType, int>> _bonusesTimers;

	//Artillery _artilllery;
	bool inited = false;
	int _curLevel = -1;

	char _numEnem = 3;
	char _numPlayers = 2;
	
	
	


};

#include"MainGame.h"
#include "glm/glm.hpp"
#include <iostream>
#include "FPS.h"

using namespace Engine;

MainGame::MainGame() : _gameState(GameState::PLAY)
{
}
MainGame::~MainGame()
{
}

void MainGame::start() 
{
	//inits
	init();

	//loop
	mainLoop();

}
void MainGame::init() 
{
	//0 normal, 2 fs, 4 borderlass, 8 resizalbe 
	_window.init("Tanks", SCREEN_WIDTH, SCREEN_HEIGHT, 0); 

	//Harta
	_harta.push_back(new Harta("Maps/Map1.txt", 1, 1));
	_curLevel = 0;
	
	// camera
	glm::vec2 cameraMij = glm::vec2((_harta[0]->getWidth() / 2) * 32 + 16, (_harta[0]->getHeight()) *16);
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	const float CAMERA_SCALE = 1.0f / 1.0f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(cameraMij);
	//_camera.setPosition(glm::vec2(380, 220));
	//std::cout << cameraMij.x << ", " << cameraMij.y << std::endl;
	
	//player
	_player.push_back(new Players);
	_player[0]->init(_harta[_curLevel]->getPlayerStartPos()[0], &_input, &_camera, &_projectiles);
	_player[0]->initGun(new Artillery(20, 1, 100, TANK_SPEED));
	//enemys
	for (int i = 0; i<_numEnem; i++)
	{
		_enemy.push_back(new Enemys);
		_enemy[i]->init(glm::vec2(i*25+250.0f, i*25+250.0f));
	}

	//timer
	_frameTimer.init(60);

	//shaders
	initShaders();
	
	

}
void MainGame::draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	_shaders.use();


	GLint textureUniform = _shaders.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
    GLint pUniform = _shaders.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	
	_harta[_curLevel]->draw();
	_player[0]->draw();

	for (size_t i = 0; i < _numEnem; i++) {
		if (_enemy[i] != nullptr)
			_enemy[i]->draw();
	}

	for (size_t i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].draw();
	}
	

	

	_shaders.unuse();
}
void MainGame::mainLoop() 
{

	// Some helpful constants.
	const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
	const int MAX_PHYSICS_STEPS = 5; // Max number of physics steps per frame
	const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
	const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

									   // Used to cap the FPS
	Engine::FPS fpsLimiter;
	fpsLimiter.init(70.0f);

	Uint32 previousTicks = SDL_GetTicks();


while (_gameState == GameState::PLAY) 
{
	fpsLimiter.start();
					// Calculate the frameTime in milliseconds
	Uint32 newTicks = SDL_GetTicks();
	Uint32 frameTime = newTicks - previousTicks;
	previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
							  // Get the total delta time
	float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
	_input.update();
	processInput(); //gets input

	int i = 0; // This counter makes sure we don't spiral to death!
			   // Loop while we still have steps to process.
	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
		// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
		float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		// Update all physics here and pass in deltaTime
		updateEntitys();
		updateBullets();
		// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		totalDeltaTime -= deltaTime;
		// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		i++;
	}

	_camera.update();
	_player[0]->update(_harta[_curLevel]->getMapData(), _player, _enemy);
	draw();  //draws the game

	fpsLimiter.end();

	_window.swapBuffer();
}
}
void MainGame::processInput() {

	SDL_Event newEvent;
	while (SDL_PollEvent(&newEvent)) {

		switch (newEvent.type)
		{
		case SDL_QUIT: 
			SDL_Quit();
			_gameState = GameState::EXIT;  //quit game
			break;
		case SDL_MOUSEMOTION:
			_input.setMouseCoords(newEvent.motion.x, newEvent.motion.y); //keep track of mouse
			break;
		case SDL_KEYDOWN:
			_input.pressKey(newEvent.key.keysym.sym); //keep track if the key is held down
			break;
		case SDL_KEYUP:
			_input.releaseKey(newEvent.key.keysym.sym); //keep track if the key is released
			break;
		case SDL_MOUSEBUTTONDOWN:
			_input.pressKey(newEvent.button.button);  //keep track if the mouse buttons are held down
			break;
		case SDL_MOUSEBUTTONUP:
			_input.releaseKey(newEvent.button.button); //release mouse buttons
			break;
		}

	}
}
void MainGame::initShaders()
{
	//shaders
	_shaders.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shaders.addAttribute("vertexPosition");
	_shaders.addAttribute("vertexColor");
	_shaders.addAttribute("vertexUV");
	_shaders.linkShaders();
}
void MainGame::updateEntitys()
{
	//check collision with world
	for (size_t i = 0; i < _player.size(); i++)
		_player[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy);

	for (size_t i = 0; i < _numEnem; i++)
		_enemy[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy);

}
void MainGame::updateBullets() {
	//Update and collide with world
	for (size_t i = 0; i < _projectiles.size(); ) {
		// If update returns true, the bullet collided with a wall
		if (_projectiles[i].update(_harta[_curLevel]->getMapData()))
		{
			//ricochet
			glm::ivec2 gridPosition =floor( _projectiles[i].getPosition()/(float)TILE_WIDTH);

			glm::vec2 dir = _projectiles[i].getDirection();

			if (gridPosition.x < 0 || gridPosition.x >= _harta[_curLevel]->getMapData()[0].size()) 
				_projectiles[i].setDirection(glm::vec2(-dir.x, dir.y));
			
			else _projectiles[i].setDirection(glm::vec2(dir.x, -dir.y));

			


		//	_projectiles[i] = _projectiles.back();
			//_projectiles.pop_back();
		}
		else {
			i++;
		}
	}
	bool wasBulletRemoved;

	// Collide with players and enemys
	for (size_t i = 0; i < _projectiles.size(); i++) {
		wasBulletRemoved = false;
		// Loop through enemys
		for (size_t j = 0; j < _enemy.size(); ) {
			// Check collision
			if (_projectiles[i].collideWithEntity(_enemy[j])) {

				// Damage enemy, and kill it if its out of health
				if (_enemy[j]->applyDamage(_projectiles[i].getDamage())) {
					// If the enemy died, remove him
					delete _enemy[j];
					if (!_enemy.empty()) 
						_enemy[j] = _enemy.back();

						_enemy.pop_back();
					_numEnem--;

				}
				else {
					j++;
				}

				// Remove the bullet
				_projectiles[i] = _projectiles.back();
				_projectiles.pop_back();
				wasBulletRemoved = true;
				i--; // Make sure we don't skip a bullet
					 // Since the bullet died, no need to loop through any more zombies
				break;
			}
			else {
				j++;
			}
		}
	}
}
#include"MainGame.h"
#include "glm/glm.hpp"
#include <iostream>
#include "FPS.h"
#include <math.h>
#include "FatError.h"
using namespace Engine;

MainGame::MainGame() : _gameState(GameState::MULTYPLAYER)
{
}

MainGame::~MainGame()
{
	for (size_t i = 0; i < _harta.size(); i++)
		delete _harta[i];

	for (size_t i = 0; i < _player.size(); i++)
		delete _player[i];

	for (size_t i = 0; i < _enemy.size(); i++)
		delete _enemy[i];
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

	//shaders
	initShaders();

	//render
	_drawEntityHandler.init();
	
	//map
	_harta.push_back(new Harta("Maps/Map1.txt", 1, 1));
	_curLevel = 0;
	//const std::vector<glm::vec2>& enemyPositions = _harta[_curLevel]->getEnemysStartPos();

	// camera
	glm::vec2 cameraMij = glm::vec2((_harta[0]->getWidth() / 2) * 32 + 16, (_harta[0]->getHeight()) * 16);
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	const float CAMERA_SCALE = 1.0f / 1.0f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(cameraMij);
	
	//player
	_player.push_back(new Players);
	_player[0]->init(_harta[_curLevel]->getPlayerStartPos()[0], &_input, &_camera, &_projectiles);
	_player[0]->setNumPlayer(1);
	_player[0]->initGun(new Artillery(20, 1, 100, BULLET_SPEED));

	_player.push_back(new Players);
	_player[1]->init(glm::vec2(400,400), &_input, &_camera, &_projectiles);
	_player[1]->setNumPlayer(2);
	_player[1]->initGun(new Artillery(20, 1, 100, BULLET_SPEED));
	
	//enemys
	for (int i = 0; i<_numEnem; i++)
	{
		_enemy.push_back(new Enemys);
		_enemy[i]->init(glm::vec2(i*25+250.0f, i*25+250.0f), &_projectiles, TANK_SPEED/1.5f);
		_enemy[i]->initGun(new Artillery(20, 1, 100, BULLET_SPEED));
	}

	//timer
	_frameTimer.init(70);

	//_bonuses = new BonusBox(22,22);
	//_bonuses->spawnBonus( _harta[0]->getMapData());
	for (int i = 0; i < 2; i++)
	{
	_bonuses.push_back(new BonusBox(cameraMij));
	_bonuses[0]->spawnBonus(_harta[0]->getMapData(), BonusType::RANDOM, _bonuses);
	}
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
	
	_drawEntityHandler.begin();

	_harta[_curLevel]->draw();

	_player[0]->drawP(_drawEntityHandler);
	_player[1]->drawP(_drawEntityHandler);

	for (size_t i = 0; i < _numEnem; i++) 
	{
		if (_enemy[i] != nullptr)
			_enemy[i]->draw(_drawEntityHandler);
	}

	for (size_t i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].draw(_drawEntityHandler);
	}
	
	for (size_t i = 0; i < _bonuses.size(); i++) 
	{
		_bonuses[i]->drawBox(BonusType::RANDOM, _drawEntityHandler);
		//std::cout << _bonuses[i]->getPosition().x << ", " << _bonuses[i]->getPosition().y << std::endl;
	}


	//_bonuses->drawBox(BonusType::DAMAGE, _drawEntityHandler);
	
	_drawEntityHandler.end();
	_drawEntityHandler.renderBatch();
	_shaders.unuse();
}
void MainGame::mainLoop() 
{
	//semi fixed timesteps
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

	
while (_gameState != GameState::EXIT) 
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
		//float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		float deltaTime = (totalDeltaTime < MAX_DELTA_TIME) ? totalDeltaTime : MAX_DELTA_TIME;
		// Update all physics here and pass in deltaTime
		updateEntitys();
		updateBullets();
		// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		totalDeltaTime -= deltaTime;
		// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		i++;
	}

	_camera.update();
	//_player[0]->update(_harta[_curLevel]->getMapData(), _player, _enemy);
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
#if 0
if(_timer){
		//std::cout << _timer << " " << std::endl;
		_timer--;
		if (_timer == 1)
		{
			std::cout <<"Danage " << _player[0]->getDamage() << std::endl;
			std::cout <<"Speed " << _player[0]->getSpeed() << std::endl;
			std::cout <<"Health " << _player[0]->getHealth() << std::endl;
		}
		if (_timer == 0)
		{
			_player[0]->initTankTypes(TankType::DEFAULT);
			std::cout << "time is 0 \n \n";
			std::cout << "Danage " << _player[0]->getDamage() << std::endl;
			std::cout << "Speed " << _player[0]->getSpeed() << std::endl;
			std::cout << "Health " << _player[0]->getHealth() << std::endl;
		}
	}
//apply time
for (size_t j = 0; j < _player.size(); j++)
for (size_t i = 0; i < _bonusesTimers.size(); i++)
{
	_bonusesTimers[i].second--;
	if (_bonusesTimers[i].second == 0)
	{
		normalizeTanksStats(_bonusesTimers[i].first, _player[j]);
	}
}
#endif


	//check collision with world
	for (size_t i = 0; i < _player.size(); i++)
		_player[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy, _bonuses, _gameState);

	for (size_t i = 0; i < _numEnem; i++) {
	//	_enemy[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy, _bonuses, _gameState);
	}

	// Update Enemy collisions
	for (size_t i = 0; i < _enemy.size(); i++) 
	{
		for (size_t j = i + 1; j < _enemy.size(); j++)  //so they dont collide with themself or do redudant collision
		{
			_enemy[i]->collideWithEntity(_enemy[j]);
		}
	}

	// Update Players collisions
	for (size_t i = 0; i < _player.size(); i++)
	{
		for (size_t j = i + 1; j < _player.size(); j++)
		{
			_player[i]->collideWithEntity(_player[j]);
		}
	}
	for (size_t i = 0; i < _player.size(); i++)
	{
		for (size_t j = 0; j < _enemy.size(); j++)
		{
			_player[i]->collideWithEntity(_enemy[j]);
		}
	}

	for (size_t i = 0; i < _player.size(); i++)
	{
		for (size_t j = 0; j < _bonuses.size(); j++)
			if (_player[i]->collideWithBonusBox(_player[i],_bonuses[j]))
			{
				//do collision and apply bonus
				_bonuses[j]->applyBonus(_bonuses[j]->getBonusType(), *_player[i]);
				//std::pair<BonusType, int> tmp(_bonuses[j]->getBonusType(), 600);
			//	_bonusesTimers.push_back(std::make_pair(_bonuses[j]->getBonusType(), 600));

				//hacky way to delete things
				delete _bonuses[j];
				_bonuses[j] = _bonuses.back();
				_bonuses.pop_back();

			}
	}


}

void MainGame::updateBullets()
{
	//Update and collide with world
	for (size_t i = 0; i < _projectiles.size(); ) {
		// If update returns true, the bullet collided with a wall
		if (_projectiles[i].update(_harta[_curLevel]->getMapData()))
		{
			//ricochet
			glm::ivec2 gridPosition =floor( _projectiles[i].getPosition()/(float)TILE_WIDTH);
			glm::vec2 dir = _projectiles[i].getDirection();

		   //if (gridPosition.x < 0 || gridPosition.x >= _harta[_curLevel]->getMapData()[0].size()) 
			  //_projectiles[i].setDirection(glm::vec2(-dir.x, dir.y));
		  //else _projectiles[i].setDirection(glm::vec2(dir.x, -dir.y));


			_projectiles[i] = _projectiles.back();
			_projectiles.pop_back();
		}
		else {
			i++;
		}
	}
//

	bool wasBulletRemoved;
	// Collide with players and enemys
	for (size_t i = 0; i < _projectiles.size(); i++) {
		wasBulletRemoved = false;
		// Loop through enemys
		for (size_t j = 0; j < _enemy.size(); ) {
			// Check collision
			if (_projectiles[i].collideWithEntity(_enemy[j])) {

				// Damage enemy, and kill it if its out of health
				if (_enemy[j]->applyDamage(_projectiles[i].getDamage())) 
				{
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
	

	for (size_t i = 0; i < _projectiles.size(); i++) {
		wasBulletRemoved = false;
		// Loop through enemys
		for (size_t j = 0; j < _player.size(); ) {
			// Check collision
			if (_projectiles[i].collideWithEntity(_player[j])) {

				// Damage enemy, and kill it if its out of health
				if (_player[j]->applyDamage(_projectiles[i].getDamage()))
				{
					// If the enemy died, remove him
					delete _player[j];
					FatalError("YOU DIEDEDED!"); //dont crash our game
					if (!_player.empty()) 
					{
						_player[j] = _player.back();
						_player.pop_back();
					}
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

void MainGame::normalizeTanksStats(BonusType boxTime, Entity* entity)
{
	return;
}

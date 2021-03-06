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

	music.pause();
}

GameState MainGame::start(Window * window) 
{
	_window = window;
	//inits
	
		init();

	//make it rain
    music = _audioManager.loadMusic("Assets/Audio/battle_music.mp3");
	//music.play(-1);

	resume.textureID.push_back(FileLoad::getTexture("Assets/resume1.png").id);
	resume.textureID.push_back(FileLoad::getTexture("Assets/resume2.png").id);

	quit.textureID.push_back(FileLoad::getTexture("Assets/quit1.png").id);
	quit.textureID.push_back(FileLoad::getTexture("Assets/quit2.png").id);

	resume.quad = glm::vec4(110, 230, 564, 100);
	resume.texture = resume.textureID[0];

	quit.quad = glm::vec4(110, 100, 564, 100);
	quit.texture = quit.textureID[0];

	finish.quad = glm::vec4(200, 200, 500, 200);

	//loop
	return mainLoop();

}
void MainGame::init() 
{
	//0 normal, 2 fs, 4 borderlass, 8 resizalbe 
	//_window.init("Tanks", SCREEN_WIDTH, SCREEN_HEIGHT, 0); 
	
	//shaders
	initShaders();

	//render
	_drawEntityHandler.init();
	drawHandler.init();
	std::cout << _curLevel << std::endl;
	switch (_curLevel)
	{
	case 0:_harta.push_back(new Harta("Maps/Map1.txt", 1, 1));
		break;
	case 1:_harta.push_back(new Harta("Maps/Map2.txt", 1, 1));
		break;
	case 2:_harta.push_back(new Harta("Maps/Map3.txt", 1, 1));
		break;
	case 3:_harta.push_back(new Harta("Maps/Map4.txt", 1, 1));
		break;
	case 4:_harta.push_back(new Harta("Maps/Map5.txt", 1, 1));
		break;
	case 5:_harta.push_back(new Harta("Maps/Map6.txt", 1, 1));
		break;
	case 6:_harta.push_back(new Harta("Maps/Map7.txt", 1, 1));
		break;
	case 7:_harta.push_back(new Harta("Maps/Map8.txt", 1, 1));
		break;
	case 8:_harta.push_back(new Harta("Maps/Map9.txt", 1, 1));
		break;
	case 9:_harta.push_back(new Harta("Maps/Map10.txt", 1, 1));
		break;
	case 10:_harta.push_back(new Harta("Maps/Map11.txt", 1, 1));
		break;
	case 11:_harta.push_back(new Harta("Maps/Map12.txt", 1, 1));
		break;

	default:
		break;
	}
	_curLevel = 0;
	
	//map
	
	
	//const std::vector<glm::vec2>& enemyPositions = _harta[_curLevel]->getEnemysStartPos();

	// camera
	glm::vec2 cameraMij = glm::vec2((_harta[0]->getWidth() / 2) * 32 + 16, (_harta[0]->getHeight()) * 16);
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	const float CAMERA_SCALE = 1.0f / 1.0f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(cameraMij);
	
	//Audio
	if(!inited)
	_audioManager.init();


	//player
	_player.push_back(new Players);
	_player[0]->init(_harta[_curLevel]->getPlayerStartPos()[0], &_input, &_camera, &_projectiles , pl1);
	_player[0]->setNumPlayer(1);
	_player[0]->initGun(new Artillery(_player[0]->getFireSpeed(), 1, 100, BULLET_SPEED, true));
	if (GameState::MULTYPLAYER == _gameState) {
		_player.push_back(new Players);
		_player[1]->init(_harta[_curLevel]->getPlayerStartPos()[1], &_input, &_camera, &_projectiles,pl2);
		_player[1]->setNumPlayer(2);
		_player[1]->initGun(new Artillery(_player[1]->getFireSpeed(), 1, 100, BULLET_SPEED, true));
	}
	//enemys
	_numEnem = _harta[_curLevel]->getNumEnemy();
	for (int i = 0; i< _numEnem ; i++)
	{
		_enemy.push_back(new Enemys);
		_enemy[i]->init(_harta[_curLevel]->getEnemysStartPos()[i], &_projectiles, TANK_SPEED/1.5f);
		_enemy[i]->initGun(new Artillery(20, 1, 100, BULLET_SPEED, false));
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

	inited = true;

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
	if(_fin ==1)
		_drawEntityHandler.draw(finish.quad, glm::vec4(0, 0, 1, 1), finish.texture, 0, Engine::Color(255, 255, 255, 255));
	_harta[_curLevel]->draw();

	_player[0]->drawP(_drawEntityHandler);
	if (GameState::MULTYPLAYER == _gameState) 
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
GameState MainGame::mainLoop() 
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

	
while (_gameState != GameState::EXIT && _gameState!=GameState::MAIN) 
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
	if (_fin == 1) {
		_finTime++;
	}
	if (_finTime > 100) _gameState = GameState::MAIN;
	if (state == GameState::MENU)
		drawMenu();
	else {
		if (rand() % 302 == 0)
			if (_bonuses.size() != 0)
				_bonuses[0]->spawnBonus(_harta[0]->getMapData(), (BonusType)(rand() % 9), _bonuses);
			else {
				_bonuses.push_back(new BonusBox(glm::vec2(-1000, -1000)));
				_bonuses[_bonuses.size() - 1]->spawnBonus(_harta[0]->getMapData(), BonusType::RANDOM, _bonuses);
			}

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
	}
	fpsLimiter.end();

	_window->swapBuffer();
}
music.stop();

return _gameState;
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
			isKeyPressed();
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

void MainGame::isKeyPressed() {
	
	if (_input.isKeyPressed(SDLK_ESCAPE)) {

		state = GameState::MENU;
		resume.isSelected = true;
		resume.ButtonState();

	}
	if (state == GameState::MENU) {
		if (_input.isKeyPressed(SDLK_RETURN)) {
			if (resume.isSelected) {
				state = GameState::SINGLEPLAYER;
			}
			if (quit.isSelected) {
				_gameState = GameState::MAIN;
			}
		}
		if (_input.isKeyPressed(SDLK_DOWN)) {
			if (currButton == 1) {
				resume.isSelected = false;
				resume.ButtonState();
				currButton++;
				quit.isSelected = true;
				quit.ButtonState();
			}
		}
		if (_input.isKeyPressed(SDLK_UP)) {
			if (currButton == 2) {
				resume.isSelected = true;
				resume.ButtonState();
				currButton--;
				quit.isSelected = false;
				quit.ButtonState();
			}
		}

	}
	

}
void MainGame::drawMenu() {

	_shaders.use();
	drawHandler.begin();
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaders.use();

	GLint textureUniform = _shaders.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _shaders.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	drawHandler.begin();

	glm::vec4 uvCoords(0.0f, 0.0f, 1.0f, 1.0f);
	
	drawHandler.draw(resume.quad, uvCoords, resume.texture, 0, Engine::Color(255, 255, 255, 255));
	drawHandler.draw(quit.quad, uvCoords, quit.texture, 0, Engine::Color(255, 255, 255, 255));


	drawHandler.end();
	drawHandler.renderBatch();
	_shaders.unuse();

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
		_player[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy, _bonuses, _projectiles, _gameState);
	
	for (size_t i = 0; i < _numEnem; i++) {
			_enemy[i]->update(_harta[_curLevel]->getMapData(), _player, _enemy, _bonuses, _projectiles, _gameState);
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

	for (size_t i = 0; i < _enemy.size(); i++)
	{
		for (size_t j = 0; j < _bonuses.size(); j++)
			if (_enemy[i]->collideWithBonusBox(_enemy[i], _bonuses[j]))
			{
				//do collision and apply bonus
				_bonuses[j]->applyBonus(_bonuses[j]->getBonusType(), *_enemy[i]);
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

				if (_projectiles[i].getSource() == true) {
					if (_enemy[j]->applyDamage(_projectiles[i].getDamage()))
					{
						// If the enemy died, remove him
						
						delete _enemy[j];		
						_enemy[j] = _enemy.back();
						_enemy.pop_back();
						_numEnem--; 
						if (_gameState == GameState::SINGLEPLAYER && _numEnem ==0) {
							finish.texture = FileLoad::getTexture("Assets/youwon.png").id;
							_fin = 1;

						}
					}
					else {
						j++;
					}
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
					if (_player[j]->getNumPlayer() == 1 && _gameState == GameState::SINGLEPLAYER) {
						finish.texture = FileLoad::getTexture("Assets/youlose.png").id;
						_fin = 1;
					}if (_player[j]->getNumPlayer() == 1 && _gameState == GameState::MULTYPLAYER) {
						finish.texture = FileLoad::getTexture("Assets/playertwowon.png").id;
						_fin = 1;
					}if (_player[j]->getNumPlayer() == 2 && _gameState == GameState::MULTYPLAYER) {
						finish.texture = FileLoad::getTexture("Assets/player1won.png").id;
						_fin = 1;
					}
					//delete _player[j];
					//FatalError("YOU DIEDEDED!"); //dont crash our game
					//if (!_player.empty()) 
					//{
					//	_player[j] = _player.back();
					//	_player.pop_back();
					//}
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
void MainGame::setTankType(TankType player1, TankType player2) {

	if (_gameState == GameState::SINGLEPLAYER)
		pl1 = player1;
	else if (_gameState == GameState::MULTYPLAYER)
	{
		pl1 = player1;
		pl2 = player2;
	}
}
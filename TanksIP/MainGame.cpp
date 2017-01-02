#include"MainGame.h"
#include "glm/glm.hpp"

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

	// camera
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	const float CAMERA_SCALE = 1.0f / 1.0f;
	_camera.offsetScale(CAMERA_SCALE);

	//Harta
	_harta.push_back(new Harta("Maps/Map1.txt", 1, 1));
	_curLevel = 0;
	
	//player
	_player.push_back(new Players);
	_player[0]->init(_harta[_curLevel]->getPlayerStartPos()[0], &_input, _camera);

	//enemys
	for (size_t i = 0; i<_numEnem; i++)
	{
		_enemy.push_back(new Enemys);
		_enemy[i]->init(glm::vec2(14.0f, 6.0f));
	}

	//timer
	_frameTimer.init(60);

	//gl
	glDisable(GL_DEPTH_TEST);

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

	_shaders.unuse();
}
void MainGame::mainLoop() 
{
while (_gameState == GameState::PLAY) 
{
	
	draw();  //draws the game
 
	processInput(); //gets input

	/* DEBUG
	std::cout << "(" << _input.getMouseCoords().x << ", " << _input.getMouseCoords().y << ")\n";
	//*/

	//_camera.offsetPosition(_player.getPosition());
	_camera.setPosition(_player[0]->getPosition());
	_camera.update();
	_player[0]->update(_harta[_curLevel]->getMapData(), _player, _enemy);

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
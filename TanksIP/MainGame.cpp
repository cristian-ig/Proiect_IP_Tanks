#include"MainGame.h"

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
	_camera.init(SCREEN_WIDTH,SCREEN_HEIGHT);

	//timer
	_frameTimer.init(60);

	//gl

	glDisable(GL_DEPTH_TEST);

	//shaders
	_shaders.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shaders.addAttribute("vertexPosition");
	_shaders.addAttribute("vertexColor");
	_shaders.addAttribute("vertexUV");
	_shaders.linkShaders();
}

void MainGame::draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void MainGame::mainLoop() {

	while (_gameState == GameState::PLAY) 
	{
		draw();
		processInput();
		/* DEBUG

		std::cout << "(" << _input.getMouseCoords().x << ", " << _input.getMouseCoords().y << ")\n";
		
		//*/
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


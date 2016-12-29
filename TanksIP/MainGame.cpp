#include"MainGame.h"

namespace Engine{

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
	//SDL_Init(SDL_INIT_EVERYTHING);
void MainGame::update()
{
	return;
}

void MainGame::init() 
{
	//0 normal, 2 fs, 4 borderlass, 8 resizalbe 
	_window.init("Tanks", _width, _height, 0);  //creates a window
	loadShaders(); //load and compile shaders
	_map.push_back(new Mapz("Maps/Map1.level"));
}

void MainGame::draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	_texProgram.bind();

	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = _texProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	//TODO: Add Camera
	//FIX THIS?!?!?
	try {
   		_map[0]->draw();
	}
	catch (int ex) { std::cout << "_map[0]->draw(); err"; }

	_texProgram.unbind();
	_window.swapBuffer();
}

void MainGame::mainLoop() {

	while (_gameState == GameState::PLAY) 
	{
		draw();
		processInput();
		update();

		/* DEBUG

		std::cout << "(" << _input.getMouseCoords().x << ", " << _input.getMouseCoords().y << ")\n";
		
		//*/

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
			std::cout << "(" << _input.getMouseCoords().x << ", " << _input.getMouseCoords().y << ")\n";
			break;
		case SDL_KEYDOWN:
			_input.pressKey(newEvent.key.keysym.sym); //keep track if the key is held down
			std::cout << "Key is pressed!\n";
			break;
		case SDL_KEYUP:
			_input.releaseKey(newEvent.key.keysym.sym); //keep track if the key is released
			std::cout << "Key is realeased!\n";
			break;
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "MouseButton is pressed!\n";
			_input.pressKey(newEvent.button.button);  //keep track if the mouse buttons are held down
			break;
		case SDL_MOUSEBUTTONUP:
			_input.releaseKey(newEvent.button.button); //release mouse buttons
			std::cout << "MouseButton is realeased!\n";
			break;
		}

	}
}
void MainGame::loadShaders()
{
	// Compile our color shader
	_texProgram.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_texProgram.addAttribute("vertexPosition");
	_texProgram.addAttribute("vertexColor");
	_texProgram.addAttribute("vertexUV");
	_texProgram.linkShaders();
}


}
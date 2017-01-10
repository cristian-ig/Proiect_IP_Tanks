#include "Menu.h"
#include<iostream>


Menu::Menu()
{
	//window
	_window = new Window;
	_window->init("Tanks", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	//shaders
	_shaders.compileShaders("Shaders/colorShader.vert", "Shaders/colorShader.frag");
	_shaders.addAttribute("vertexPosition");
	_shaders.addAttribute("vertexColor");
	_shaders.addAttribute("vertexUV");
	_shaders.linkShaders();

	//drawing
	_drawHandler.init();

	//camera
	_camera.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	const float CAMERA_SCALE = 1.0f / 1.0f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));

}


Menu::~Menu()
{
}

void Menu::menuLoop() {

	while (_menuState != MenuState::EXIT) {

		if (_gamestate == GameState::SINGLEPLAYER) {
			_mainGame.setGameState(_gamestate);
			_mainGame.start(_window);
		}
		if (_gamestate == GameState::MULTYPLAYER) {
			_mainGame.setGameState(_gamestate);
			_mainGame.start(_window);
		}
		_input.update();
		proccesInput();
		if (_menuState == MenuState::MAIN_MENU)
			drawMain();

		_window->swapBuffer();

	}


}
void Menu::start(TankType player1, TankType player2) {

	

}
void Menu::proccesInput() {

	SDL_Event newEvent;
	while (SDL_PollEvent(&newEvent)) {

		switch (newEvent.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			_menuState =MenuState::EXIT;  //quit game
			break;
		case SDL_MOUSEMOTION:
			_input.setMouseCoords(newEvent.motion.x, newEvent.motion.y); //keep track of mouse
			std::cout << _input.getMouseCoords().x << " " << _input.getMouseCoords().y << std::endl;
			break;
		case SDL_KEYDOWN:
			_input.pressKey(newEvent.key.keysym.sym); //keep track if the key is held down
			break;
		case SDL_KEYUP:
			_input.releaseKey(newEvent.key.keysym.sym); //keep track if the key is released
			break;
		case SDL_MOUSEBUTTONDOWN:
			_input.pressKey(newEvent.button.button);  //keep track if the mouse buttons are held down
			_gamestate = GameState::SINGLEPLAYER;
			break;
		case SDL_MOUSEBUTTONUP:
			_input.releaseKey(newEvent.button.button); //release mouse buttons
			break;
		}

	}

}

void Menu::drawMain() {

	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(213, 122, 13,255);


}
void Menu::drawSingleplayer() {


}
void Menu::drawMultiplayer() {


}
void Menu::drawSinglePlayerMapSelection() {



}
void Menu::drawSinglePlayerTankSelection() {



}
void Menu::drawMultiplayerMapSelection() {



}
void Menu::drawMultiplayerTankSelection() {




}
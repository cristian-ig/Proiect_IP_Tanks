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
	const float CAMERA_SCALE = 1.0f / 2.9f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(glm::vec2(SCREEN_WIDTH/2.2, SCREEN_HEIGHT/1.495));
	glMatrixMode(GL_MODELVIEW);

}


Menu::~Menu()
{
}
void Menu::init() {

	//main menu buttons

	MainMenuButtons.resize(3);
	float mainMenuOffset = 42.0f;
	float firstX = 500.0;
	float firstY = 334.0f;
	float mainMenuSize_w = 564.0f;
	float mainMenuSize_h = 132.0f;


	MainMenuButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu1.png").id);
	MainMenuButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu2.png").id);
	MainMenuButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu3.png").id);

	MainMenuButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu1.png").id);
	MainMenuButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu2.png").id);
	MainMenuButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu3.png").id);

	MainMenuButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu1.png").id);
	MainMenuButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu2.png").id);
	MainMenuButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/mainMenu3.png").id);

	for (size_t i = 0; i < 3; i++) {
		
		MainMenuButtons[i].quad = glm::vec4(firstX, firstY + (i*(mainMenuOffset + mainMenuSize_h)), mainMenuSize_w,mainMenuSize_h);
		MainMenuButtons[i].texture = MainMenuButtons[i].textureID[0];
	}
	



}
void Menu::updateButtons() {

	if(_menuState == MenuState::MAIN_MENU)
		for (size_t i = 0; i < 3; i++) {

			MainMenuButtons[i].ButtonState(_input.getMouseCoords(), isMouseDown);
		}

}

void Menu::menuLoop() {

	init();

	while (_menuState != MenuState::EXIT) {

		_input.update();
		proccesInput();
		updateButtons();

		if (_gamestate == GameState::SINGLEPLAYER) {

			_mainGame.setGameState(_gamestate);
			_mainGame.start(_window);
		}
		if (_gamestate == GameState::MULTYPLAYER) {
			_mainGame.setGameState(_gamestate);
			_mainGame.start(_window);
		}
		
		if (_menuState == MenuState::MAIN_MENU)
			drawMain();
		
		_camera.update();

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
			mousePressed();
			_input.pressKey(newEvent.button.button);  //keep track if the mouse buttons are held down
			_gamestate = GameState::SINGLEPLAYER;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseReleased();
			_input.releaseKey(newEvent.button.button); //release mouse buttons
			break;
		}

	}

}

void Menu::drawMain() {

	_shaders.use();
	_drawHandler.begin();
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaders.use();

	GLint textureUniform = _shaders.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _shaders.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_drawHandler.begin();

	glm::vec4 uvCoords(0.0f, 0.0f, 1.0f, 1.0f);
	for (size_t i = 0; i < 3; i++) {
		_drawHandler.draw(MainMenuButtons[i].quad, uvCoords, MainMenuButtons[i].texture, 0, Engine::Color(122, 122, 122, 255));
	}
	_drawHandler.end();
	_drawHandler.renderBatch();
	_shaders.unuse();

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
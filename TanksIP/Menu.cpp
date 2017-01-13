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
	//const float CAMERA_SCALE = 0.0000000001f;

	const float CAMERA_SCALE = 1.0f / 2.9f;
	_camera.offsetScale(CAMERA_SCALE);
	_camera.setPosition(glm::vec2(SCREEN_WIDTH/2.2, SCREEN_HEIGHT/1.495));
	//_camera.setPosition(glm::vec2(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT / 8));
	

	//glMatrixMode(GL_MODELVIEW);
	//glClearColor(188, 203, 255, 180);

}


Menu::~Menu()
{
}
void Menu::init() {

	//main menu buttons

	MainMenuButtons.resize(3);
	TankSelectionButtons.resize(6);
	MapSelectionButtons.resize(13);
	MainMenuButtons[2].isSelected = true;

	background.quad = glm::vec4(0, 0, 1920, 1080);
	background.texture = Engine::FileLoad::getTexture("Assets/background.png").id;

	//main menu
	float mainMenuOffset = 42.0f;
	float firstX1 = 500.0;
	float firstY1 = 334.0f;
	float mainMenuSize_w = 564.0f;
	float mainMenuSize_h = 132.0f;
	


	MainMenuButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/quit1.png").id);
	MainMenuButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/quit2.png").id);
	

	MainMenuButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/multiplayer1.png").id);
	MainMenuButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/multiplayer2.png").id);


	MainMenuButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/SinglePlayer1.png").id);
	MainMenuButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/SinglePlayer2.png").id);


	for (size_t i = 0; i < 3; i++) {
		
		MainMenuButtons[i].quad = glm::vec4(firstX1, firstY1 + (i*(mainMenuOffset + mainMenuSize_h)), mainMenuSize_w,mainMenuSize_h);
		MainMenuButtons[i].texture = MainMenuButtons[i].textureID[0];
	}

	//tank selection menu

	float firstX2 = 450;
	float firstY2 = 270;
	float tankSelection_w = 579;
	float tankSelection_h = 101;
	float offset2 = 10;


	
	TankSelectionButtons[5].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionDefault1.png").id);
	TankSelectionButtons[5].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionDefault2.png").id);

	TankSelectionButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionPanzer1.png").id);
	TankSelectionButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionPanzer2.png").id);

	TankSelectionButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionMotherRussia1.png").id);
	TankSelectionButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionMotherRussia2.png").id);

	TankSelectionButtons[3].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionSpeedRunner1.png").id);
	TankSelectionButtons[3].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionSpeedRunner2.png").id);

	TankSelectionButtons[4].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionRandom1.png").id);
	TankSelectionButtons[4].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionRandom2.png").id);

	TankSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack1.png").id);
	TankSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack2.png").id);

	for (size_t i = 0; i < 6; i++) {

		TankSelectionButtons[i].quad = glm::vec4(firstX2, firstY2 + (i*(offset2 + tankSelection_h)), tankSelection_w, tankSelection_h);
		TankSelectionButtons[i].texture = TankSelectionButtons[i].textureID[0];
	}

	// map selection

	float x1 = 225;
	float y1 = 600;
	float mapSelection_w = 120;
	float mapSelection_h = 120;
	float buttonOffset_x = 60;
	float buttonOffset_y = 45;



	//MapSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack1.png").id);
	//MapSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack2.png").id);

	MapSelectionButtons[6].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection1_1.png").id);
	MapSelectionButtons[6].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection1_2.png").id);


	MapSelectionButtons[7].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection2_1.png").id);
	MapSelectionButtons[7].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection2_2.png").id);


	MapSelectionButtons[8].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection3_1.png").id);
	MapSelectionButtons[8].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection3_2.png").id);


	MapSelectionButtons[9].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection4_1.png").id);
	MapSelectionButtons[9].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection4_2.png").id);


	MapSelectionButtons[10].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection5_1.png").id);
	MapSelectionButtons[10].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection5_2.png").id);


	MapSelectionButtons[11].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection6_1.png").id);
	MapSelectionButtons[11].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection6_2.png").id);


	MapSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection7_1.png").id);
	MapSelectionButtons[0].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection7_2.png").id);


	MapSelectionButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection8_1.png").id);
	MapSelectionButtons[1].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection8_2.png").id);


	MapSelectionButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection9_1.png").id);
	MapSelectionButtons[2].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection9_2.png").id);


	MapSelectionButtons[3].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection10_1.png").id);
	MapSelectionButtons[3].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection10_2.png").id);


	MapSelectionButtons[4].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection11_1.png").id);
	MapSelectionButtons[4].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection11_2.png").id);


	MapSelectionButtons[5].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection12_1.png").id);
	MapSelectionButtons[5].textureID.push_back(Engine::FileLoad::getTexture("Assets/MapSelection12_2.png").id);
	

	MapSelectionButtons[12].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack1.png").id);
	MapSelectionButtons[12].textureID.push_back(Engine::FileLoad::getTexture("Assets/TankSelectionBack2.png").id);

	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < 6; j++) {
			
			MapSelectionButtons[(i*6)+j].quad=glm::vec4(x1 +(j*(buttonOffset_x + mapSelection_w)), y1 + (i*(buttonOffset_y + mapSelection_h)), mapSelection_w, mapSelection_h);
			MapSelectionButtons[(i*6)+j].texture = MapSelectionButtons[(i*6) + j].textureID[0];
		}
	}

	MapSelectionButtons[12].quad = glm::vec4(450, 350, 579, 101);
	MapSelectionButtons[12].texture = MapSelectionButtons[12].textureID[0];

}
void Menu::updateButtons() {

	if(_menuState == MenuState::MAIN_MENU)
		for (size_t i = 0; i < 3; i++) {

			MainMenuButtons[i].ButtonState();

		}
	if (_menuState == MenuState::TANK_SELECTION_SINGLEPLAYER || _menuState == MenuState::TANK_SELECTION_MULTIPLAYER) {
		for (size_t i = 0; i < 6; i++) {

			TankSelectionButtons[i].ButtonState();

		}
	}
	if(_menuState == MenuState::MAP_SELECTION_SINGLEPLAYER || _menuState == MenuState::MAP_SELECTION_MULTIPLAYER)
		for (size_t i = 0; i < 13; i++) {
			MapSelectionButtons[i].ButtonState();
		}

}

void Menu::menuLoop() {

	init();

	while (_menuState != MenuState::EXIT) {

		_input.update();
		proccesInput();
		updateButtons();

		if (_gamestate == GameState::SINGLEPLAYER) {
			_mainGame->setLevel(map_x);
			_mainGame->setTankType(_player1, _player2);
			_mainGame->setGameState(GameState::SINGLEPLAYER);
			if (_mainGame->start(_window) == GameState::EXIT)
				_menuState = MenuState::EXIT;
			else {
				delete _mainGame;
				_mainGame = new MainGame;
				_gamestate = GameState::MENU;
				_menuState = MenuState::MAIN_MENU;
				buttonIndex = 2;
				for (size_t i = 0; i < 3; i++) {
					MainMenuButtons[i].isSelected = false;
				}
				MainMenuButtons[2].isSelected = true;
			}
		}

			if (_gamestate == GameState::MULTYPLAYER) {
				_mainGame->setLevel(map_x);
				_mainGame->setTankType(_player1, _player2);
				_mainGame->setGameState(GameState::MULTYPLAYER);
				if (_mainGame->start(_window) == GameState::EXIT)
				_menuState = MenuState::EXIT;

				else {
					delete _mainGame;
					_mainGame = new MainGame;
					_gamestate = GameState::MENU;
					_menuState = MenuState::MAIN_MENU;
					buttonIndex = 2;
					for (size_t i = 0; i < 3; i++) {
						MainMenuButtons[i].isSelected = false;
					}
					MainMenuButtons[2].isSelected = true;
				}
			}
		
		if (_menuState == MenuState::MAIN_MENU)
			drawMain();
		if (_menuState == MenuState::TANK_SELECTION_SINGLEPLAYER)
			drawTankSelection();
		if (_menuState == MenuState::TANK_SELECTION_MULTIPLAYER)
			drawTankSelection();
		if (_menuState == MenuState::MAP_SELECTION_SINGLEPLAYER)
			drawMapSelection();
		if (_menuState == MenuState::MAP_SELECTION_MULTIPLAYER)
			drawMapSelection();

		_camera.update();

		_window->swapBuffer();
		if (_gamestate != GameState::MENU)
			_menuState = MenuState::EXIT;

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
			arrowPressed();
			break;
		case SDL_KEYUP:
			_input.releaseKey(newEvent.key.keysym.sym); //keep track if the key is released
			break;
		case SDL_MOUSEBUTTONDOWN:
			_input.pressKey(newEvent.button.button);  //keep track if the mouse buttons are held down
			//_gamestate = GameState::SINGLEPLAYER;
			break;
		case SDL_MOUSEBUTTONUP:
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
		_drawHandler.draw(MainMenuButtons[i].quad, uvCoords, MainMenuButtons[i].texture, 0, Engine::Color(255, 255, 255, 255));
	}
	_drawHandler.draw(background.quad, uvCoords, background.texture, 0, Engine::Color(255, 255, 255, 255));
	_drawHandler.end();
	_drawHandler.renderBatch();
	_shaders.unuse();

}

void Menu::drawBG() {

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
	
	_drawHandler.draw(background.quad, uvCoords, background.texture, 0, Engine::Color(255, 255, 255, 255));
	_drawHandler.end();
	_drawHandler.renderBatch();
	_shaders.unuse();
}

void Menu::drawMapSelection() {
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
	for (size_t i = 0; i < 13; i++) {
		_drawHandler.draw(MapSelectionButtons[i].quad, uvCoords, MapSelectionButtons[i].texture, 0, Engine::Color(255, 255, 255, 255));
	}
	_drawHandler.draw(background.quad, uvCoords, background.texture, 0, Engine::Color(255, 255, 255, 255));

	_drawHandler.end();
	_drawHandler.renderBatch();
	_shaders.unuse();


}

void Menu::drawTankSelection() {

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
	for (size_t i = 0; i < 6; i++) {
		_drawHandler.draw(TankSelectionButtons[i].quad, uvCoords, TankSelectionButtons[i].texture, 0, Engine::Color(255, 255, 255, 255));
	}
	_drawHandler.draw(background.quad, uvCoords, background.texture, 0, Engine::Color(255, 255, 255, 255));

	_drawHandler.end();
	_drawHandler.renderBatch();
	_shaders.unuse();



}

void Menu::arrowPressed() {

	if (_menuState == MenuState::MAIN_MENU) {

		if (_input.isKeyPressed(SDLK_UP)) {

			if (buttonIndex < 2) {
				MainMenuButtons[buttonIndex].isSelected = false;
				buttonIndex++;
				MainMenuButtons[buttonIndex].isSelected = true;
				std::cout << buttonIndex << std::endl;

			}
		}
		else if (_input.isKeyPressed(SDLK_DOWN)) {

			if (buttonIndex > 0) {
				MainMenuButtons[buttonIndex].isSelected = false;
				buttonIndex--;
				MainMenuButtons[buttonIndex].isSelected = true;
				std::cout << buttonIndex << std::endl;

			}
		}

	}
	else if (_menuState == MenuState::TANK_SELECTION_SINGLEPLAYER) {

		std::cout << buttonIndex << std::endl;
		if (_input.isKeyPressed(SDLK_UP)) {

			if (buttonIndex < 5) {
				TankSelectionButtons[buttonIndex].isSelected = false;
				buttonIndex++;
				TankSelectionButtons[buttonIndex].isSelected = true;
				std::cout << buttonIndex << std::endl;
			}

		}else if (_input.isKeyPressed(SDLK_DOWN)) {
				if (buttonIndex > 0) {
					TankSelectionButtons[buttonIndex].isSelected = false;
					buttonIndex--;
					TankSelectionButtons[buttonIndex].isSelected = true;
					std::cout << buttonIndex << std::endl;
				}
			}
	}
	else if (_menuState == MenuState::TANK_SELECTION_MULTIPLAYER) {
		if (_input.isKeyPressed(SDLK_UP)) {

			if (buttonIndex < 5) {
				TankSelectionButtons[buttonIndex].isSelected = false;
				buttonIndex++;
				TankSelectionButtons[buttonIndex].isSelected = true;
				std::cout << buttonIndex << std::endl;
			}

		}
		else if (_input.isKeyPressed(SDLK_DOWN)) {
			if (buttonIndex > 0) {
				TankSelectionButtons[buttonIndex].isSelected = false;
				buttonIndex--;
				TankSelectionButtons[buttonIndex].isSelected = true;
				std::cout << buttonIndex << std::endl;
			}
		}
	}
	else if (_menuState == MenuState::MAP_SELECTION_SINGLEPLAYER || _menuState == MenuState::MAP_SELECTION_MULTIPLAYER) {
		if (_input.isKeyPressed(SDLK_UP)) {
			if (map_y == 2) {
				map_y--;
				MapSelectionButtons[map_x].isSelected = false;
				map_x += 6;
				MapSelectionButtons[map_x].isSelected = true;
			}else if (map_y == 3) {
				MapSelectionButtons[12].isSelected = false;
				MapSelectionButtons[map_x].isSelected = true;
				map_y--;
			}
		}
		else if (_input.isKeyPressed(SDLK_DOWN)) {
			if (map_y == 1) {
				map_y++;
				MapSelectionButtons[map_x].isSelected = false;
				map_x -= 6;
				MapSelectionButtons[map_x].isSelected = true;
			}
			else if (map_y == 2) {
				MapSelectionButtons[map_x].isSelected = false;
				map_y++;
				MapSelectionButtons[12].isSelected = true;
			}

		}
		else if (_input.isKeyPressed(SDLK_LEFT)) {
			if (map_y == 1) {
				if (map_x > 6) {
					MapSelectionButtons[map_x].isSelected = false;
					map_x--;
					MapSelectionButtons[map_x].isSelected = true;
				}
			}
			else if (map_y == 2) {
				if (map_x > 0) {
					MapSelectionButtons[map_x].isSelected = false;
					map_x--;
					MapSelectionButtons[map_x].isSelected = true;
				}
			}

		}
		else if (_input.isKeyPressed(SDLK_RIGHT)) {
			if (map_y == 1) {
				if (map_x < 11) {
					MapSelectionButtons[map_x].isSelected = false;
					map_x++;
					MapSelectionButtons[map_x].isSelected = true;
				}
			}
			else if (map_y == 2) {
				if (map_x < 5) {
					MapSelectionButtons[map_x].isSelected = false;
					map_x++;
					MapSelectionButtons[map_x].isSelected = true;
				}
			}
		}

	}


	//enter key
	if (_input.isKeyPressed(SDLK_RETURN)) {
		//main menu
		if (_menuState == MenuState::MAIN_MENU) {

			if (MainMenuButtons[0].isSelected) {
				_menuState = MenuState::EXIT;
			}
			 if (MainMenuButtons[1].isSelected) {
				_menuState = MenuState::TANK_SELECTION_MULTIPLAYER;
				MainMenuButtons[1].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			 if (MainMenuButtons[2].isSelected) {
				_menuState = MenuState::TANK_SELECTION_SINGLEPLAYER;
				MainMenuButtons[2].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
		}
		//main menu end

		//single player
		else	if (_menuState == MenuState::TANK_SELECTION_SINGLEPLAYER) {
			if (TankSelectionButtons[0].isSelected) {
				_menuState = MenuState::MAIN_MENU;
				TankSelectionButtons[0].isSelected = false;
				buttonIndex = 2;
				MainMenuButtons[buttonIndex].isSelected = true;

			}
			if (TankSelectionButtons[1].isSelected) {
				_player1 = TankType::PANZER;
				TankSelectionButtons[1].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_SINGLEPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;

			}
			if (TankSelectionButtons[2].isSelected) {

				_player1 = TankType::MOTHER_RUSSIA;
				TankSelectionButtons[2].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_SINGLEPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}
			if (TankSelectionButtons[3].isSelected) {

				_player1 = TankType::SPEEDRUNNER;
				TankSelectionButtons[3].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_SINGLEPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}
			if (TankSelectionButtons[4].isSelected) {

				_player1 = TankType::RANDOM;
				TankSelectionButtons[4].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_SINGLEPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}
			if (TankSelectionButtons[5].isSelected) {

				_player1 = TankType::DEFAULT;
				TankSelectionButtons[5].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_SINGLEPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}
		}
		//single player end

		//multyplayer
		else if (_menuState == MenuState::TANK_SELECTION_MULTIPLAYER) {
			//back
			if (TankSelectionButtons[0].isSelected && player == 1) {
				_menuState = MenuState::MAIN_MENU;
				TankSelectionButtons[0].isSelected = false;
				buttonIndex = 2;
				MainMenuButtons[buttonIndex].isSelected = true;

			}
			else if (TankSelectionButtons[0].isSelected && player == 2) {
				TankSelectionButtons[0].isSelected = false;
				player--;
				_player1 = TankType::DEFAULT;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}else
			//back end
			//panzer
			if (TankSelectionButtons[1].isSelected && player == 1) {

				_player1 = TankType::PANZER;
				player++;
				TankSelectionButtons[1].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (TankSelectionButtons[1].isSelected && player == 2) {
				_player2 = TankType::PANZER;
				TankSelectionButtons[1].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_MULTIPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;

				//index

			}else
			//panzer end
			//mo9ther russia
			if (TankSelectionButtons[2].isSelected && player == 1) {

				_player1 = TankType::MOTHER_RUSSIA;
				player++;
				TankSelectionButtons[2].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (TankSelectionButtons[2].isSelected && player == 2) {
				_player2 = TankType::MOTHER_RUSSIA;
				TankSelectionButtons[2].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_MULTIPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;

				//index

			}else
			//motherrussia end
			//speed runner
			if (TankSelectionButtons[3].isSelected && player == 1) {

				_player1 = TankType::SPEEDRUNNER;
				player++;
				TankSelectionButtons[3].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (TankSelectionButtons[3].isSelected && player == 2) {
				_player2 = TankType::SPEEDRUNNER;
				TankSelectionButtons[3].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_MULTIPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}else
			//speedrunner end
			//random
			if (TankSelectionButtons[4].isSelected && player == 1) {

				_player1 = TankType::RANDOM;
				player++;
				TankSelectionButtons[4].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (TankSelectionButtons[4].isSelected && player == 2) {
				_player2 = TankType::RANDOM;
				TankSelectionButtons[4].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_MULTIPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}else
			//random end
			//default
			if (TankSelectionButtons[5].isSelected && player == 1) {

				_player1 = TankType::DEFAULT;
				player++;
				TankSelectionButtons[5].isSelected = false;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (TankSelectionButtons[5].isSelected && player == 2) {
				_player2 = TankType::DEFAULT;
				TankSelectionButtons[5].isSelected = false;
				_menuState = MenuState::MAP_SELECTION_MULTIPLAYER;
				map_x = 6;
				map_y = 1;
				MapSelectionButtons[map_x].isSelected = true;
			}
			//default end
			//multyplayer end
		}
		//map selection
		else if (_menuState == MenuState::MAP_SELECTION_SINGLEPLAYER || _menuState == MenuState::MAP_SELECTION_MULTIPLAYER) {

			if (MapSelectionButtons[12].isSelected && _menuState == MenuState::MAP_SELECTION_SINGLEPLAYER) {
				MapSelectionButtons[12].isSelected = false;
				_menuState = MenuState::TANK_SELECTION_SINGLEPLAYER;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			else if (MapSelectionButtons[12].isSelected && _menuState == MenuState::MAP_SELECTION_MULTIPLAYER) {

				MapSelectionButtons[12].isSelected = false;
				_menuState = MenuState::TANK_SELECTION_MULTIPLAYER;
				buttonIndex = 5;
				TankSelectionButtons[buttonIndex].isSelected = true;
			}
			if (map_x < 12) {
				_map = map_x;
				if (_menuState == MenuState::MAP_SELECTION_SINGLEPLAYER)
					_gamestate = GameState::SINGLEPLAYER;
				else if (_menuState == MenuState::MAP_SELECTION_MULTIPLAYER)
					_gamestate = GameState::MULTYPLAYER;
			}



		//map end
		}

		



		
	}
}


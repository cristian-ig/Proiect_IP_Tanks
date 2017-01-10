#pragma once
#include"MainGame.h"
#include"Defines.h"
#include"Entity.h"
#include"DrawClass.h"
#include<SDL.h>
#include"Window.h"


enum class MenuState {
	MAIN_MENU,
	SINGLEPLAYER_MENU,
	MULTYPLAYER_MENU,
	EXIT
};
class Button {

	glm::vec4 quad;
	GLuint textureID;

};
class Menu
{
public:
	Menu();
	~Menu();
	void init();
	void menuLoop();
	void start(TankType player1, TankType player2);
	void proccesInput();
	void drawMain();
	void drawSingleplayer();
	void drawSinglePlayerMapSelection();
	void drawSinglePlayerTankSelection();
	void drawMultiplayerMapSelection();
	void drawMultiplayerTankSelection();
	void drawMultiplayer();
	Window *_window;

	

private:

	std::vector<Button> MainMenuButtons;
	std::vector<Button> SinglePlayerMenuButtons;
	std::vector<Button> MultiplayerMenuButtons;
	std::vector<Button> MapSelectionButtons;
	std::vector<Button> SinglePlayerTankSelectionButtons;
	std::vector<Button> MultiplayerTankSelectionButtons;
	MainGame _mainGame;
	Engine::DrawSprites _drawHandler;
	Engine::GLSL _shaders;
	Engine::Camera _camera;
	TankType _player1;
	TankType _player2;
	MenuState _menuState = MenuState::MAIN_MENU;
	GameState _gamestate = GameState::MENU;
	Input _input;

};


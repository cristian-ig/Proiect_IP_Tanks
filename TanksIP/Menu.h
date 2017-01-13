#pragma once
#include"MainGame.h"
#include"Defines.h"
#include"Entity.h"
#include"DrawClass.h"
#include<SDL.h>
#include"Window.h"
#include"FileLoad.h"


enum class MenuState {
	MAIN_MENU,
	SINGLEPLAYER_MENU,
	MULTYPLAYER_MENU,
	TANK_SELECTION_SINGLEPLAYER,
	TANK_SELECTION_MULTIPLAYER,
	MAP_SELECTION_SINGLEPLAYER,
	MAP_SELECTION_MULTIPLAYER,
	EXIT
};
class Button {

public:
	glm::vec4 quad;
	GLuint texture;
	std::vector<GLuint> textureID;
	bool isSelected = false;
	void ButtonState() {
		
		if (isSelected)
			texture = textureID[1];
		else texture = textureID[0];

	}



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
	void drawTankSelection();
	void drawMapSelection();
	void updateButtons();
	void arrowPressed();
	void drawBG();
	int getLevel() {
		return map_x;
	}
	Window *_window;

	

private:
	int buttonIndex = 2;
	int map_x =6, map_y = 1;
	int player = 1;
	int _map =1;
	Button background;
	std::vector<Button> MainMenuButtons;
	std::vector<Button> SinglePlayerMenuButtons;
	std::vector<Button> MultiplayerMenuButtons;
	std::vector<Button> MapSelectionButtons;
	std::vector<Button> TankSelectionButtons;
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


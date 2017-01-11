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
	EXIT
};
class Button {

public:
	glm::vec4 quad;
	GLuint texture;
	std::vector<GLuint> textureID;
	bool isHovered = false;
	bool isPressed = false;
	void ButtonState(glm::vec2 pos, bool isMousePressed) {
		if (pos.x > quad.x && pos.x<quad.x + quad.z && pos.y > quad.y &&pos.y < quad.y + quad.w && !isMousePressed) {
			texture = textureID[1];
		}
		else if (isMousePressed && pos.x > quad.x && pos.x  < quad.x + quad.z && pos.y > quad.y &&pos.y < quad.y + quad.w) {
			texture = textureID[2];
		}
		else {
			texture = textureID[0];
		}

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
	void drawSingleplayer();
	void drawSinglePlayerMapSelection();
	void drawSinglePlayerTankSelection();
	void drawMultiplayerMapSelection();
	void drawMultiplayerTankSelection();
	void drawMultiplayer();
	void updateButtons();
	void mousePressed() { isMouseDown = true; isMouseReleased = false; updateButtons(); }
	void mouseReleased() { isMouseDown = false; isMouseReleased = true; updateButtons(); isMouseReleased = false; }
	Window *_window;

	

private:
	bool isMouseDown;
	bool isMouseReleased;
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


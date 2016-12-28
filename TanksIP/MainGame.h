#pragma once
#include<iostream>
#include<SDL.h>
#include "Window.h"

namespace tanks{

enum class GameState {
	PLAY,
	EXIT
};


class MainGame {

	public:
		MainGame();
		~MainGame();
		bool isRunnig;

		void start();
	private:
		void init();
		void mainLoop();
		void draw();

		Window window;



};
}
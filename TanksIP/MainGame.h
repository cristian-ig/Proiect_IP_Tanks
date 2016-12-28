#pragma once
#include<iostream>
#include<SDL.h>


enum class GameState {
	PLAY,
	EXIT
};


class MainGame {

	public:
		MainGame();
		~MainGame();
		bool isRunnig;

	private:
		void init();
		void mainLoop();
		void start();
		void draw();




};
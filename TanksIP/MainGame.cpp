#include"MainGame.h"

namespace tanks{

MainGame::MainGame() :
	isRunnig(true)
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
void MainGame::init() {

	window.init("Tanks", 1024, 768, 0);
	
}

void MainGame::mainLoop() {

	while (isRunnig) {
		
		
		processInput();

	}
}
void MainGame::processInput() {


	SDL_Event newEvent;

	while (SDL_PollEvent(&newEvent)) {

		switch (newEvent.type)
		{
		case SDL_QUIT: 
			isRunnig = false;
			break;
		}

	}
}

}
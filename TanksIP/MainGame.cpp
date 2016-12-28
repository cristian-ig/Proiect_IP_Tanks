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
	//mainLoop();

}
void MainGame::init() {

	window.init("Tanks", 1024, 768, 0);
	
}
}
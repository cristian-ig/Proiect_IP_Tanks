#include "FatError.h"

namespace Engine{

void Engine::FatalError(std::string errorString)
{
	std::cout << "FATAL ERROR! Something went wrong!" << std::endl;
	std::cout << errorString << std::endl;
	std::cout << "The program terminated with an error" << std::endl;
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(6969);
}
}
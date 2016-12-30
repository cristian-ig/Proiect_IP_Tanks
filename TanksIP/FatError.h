#pragma once
#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <string>

namespace Engine {

void FatalError(std::string errorString)
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
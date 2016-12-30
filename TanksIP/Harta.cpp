#include "Harta.h"
#include <iostream>
#include <fstream>
//#include "FatError.h"
#include "Vertex.h"

Harta::Harta(const std::string& fileName, char numPlayers, char numEnemys)
{
	std::ifstream file;
	file.open(fileName);

	//failure check
	if (file.fail()) {}
		//Engine::FatalError("Failed to open " + fileName);


	std::string temp;
	while (std::getline(file, temp))
	{
		_mapData.emplace_back(temp);  //read the map line by line
	}

	Engine::Color(255, 255, 255, 255); //white

									  // Render all the tiles
	for (size_t y = 0; y < _mapData.size(); y++) 
	{
		for (size_t x = 0; x < _mapData[y].size(); x++) 
		{
			// Grab the tile
			char tile = _mapData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			// Process the tile
			switch (tile) {
			case '#':
				break;
			case '@':
				_mapData[y][x] = '.'; //so we dont collide with the tile later on
				if (numPlayers > 0)
				{
					_playerStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					_numEntitys++;
					numPlayers--;
				}
				break;
			case 'E':
				_mapData[y][x] = '.';//so we dont collide with the tile later on
				if (numEnemys > 0)
				{
					_enemyStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					_numEntitys++;
					numEnemys--;
				}
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	
}


Harta::~Harta()
{
}

void Harta::draw()
{
	return;
}

#include "Harta.h"
#include <iostream>
#include <fstream>
#include "FatError.h"
#include "FileLoad.h"

Harta::Harta(const std::string& fileName, char numPlayers, char numEnemys)
{
	std::ifstream file;
	file.open(fileName);

	//failure check
	if (file.fail()) 
		Engine::FatalError("Failed to open " + fileName);


	std::string temp;
	while (std::getline(file, temp))
	{
		_mapData.emplace_back(temp);  //read the map line by line
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	Engine::Color color(255, 255, 255, 255); //white
	glm::vec4 uvCoords(0.0f, 0.0f, 1.0f, 1.0f);


		 // Render all the tiles
	for (size_t y = 0; y < _mapData.size(); y++) 
	{
		for (size_t x = 0; x < _mapData[y].size(); x++) 
		{
			// Grab the tile
			char tile = _mapData[y][x];

			// Get dest rect
			
			glm::vec4 destRect((x * TILE_WIDTH), (y * TILE_WIDTH), TILE_WIDTH, TILE_WIDTH);
		

			// Process the tile
			switch (tile) {
			case 'W':
				_spriteBatch.draw(destRect, uvCoords, Engine::FileLoad::getTexture("Assets/light_wall.png").id,0.0f, color);
				break;
			case '@':
				_spriteBatch.draw(destRect, uvCoords, Engine::FileLoad::getTexture("Assets/wall.png").id, 0.0f, color);
				_mapData[y][x] = '.'; //so we dont collide with the tile later on
				if (numPlayers > 0)
				{
					_playerStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					_numEntitys++;
					numPlayers--;
				}
				break;
			case 'E':
				_spriteBatch.draw(destRect, uvCoords, Engine::FileLoad::getTexture("Assets/wall.png").id, 0.0f, color);
				_mapData[y][x] = '.';//so we dont collide with the tile later on
				if (numEnemys > 0)
				{
					_enemyStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					_numEntitys++;
					numEnemys--;
				}
				break;
			case 'c':
				_spriteBatch.draw(destRect, uvCoords, Engine::FileLoad::getTexture("Assets/wall.png").id, 0.0f, color);
				_cameraPos.x = x;
				_cameraPos.y = y;
				_mapData[y][x] = '.';//so we dont collide with the tile later on
				break;
			case '.':
				_spriteBatch.draw(destRect, uvCoords, Engine::FileLoad::getTexture("Assets/wall.png").id, 0.0f, color);
				break;
			default:
				std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_spriteBatch.end();
	
}


Harta::~Harta()
{
}

void Harta::draw()
{
	_spriteBatch.renderBatch();
}

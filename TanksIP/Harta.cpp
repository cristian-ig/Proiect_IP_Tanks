#include "Harta.h"
#include <iostream>
#include <fstream>
#include "FatError.h"
#include "Vertex.h"

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

	Engine::Color color(255, 255, 255, 255); //white
	glm::vec4 uvCoords(0.0f, 0.0f, 1.0f, 1.0f);

	_wallTexture = _textureHandler.loadTexture("Assets/light_wall.png");
	_waterTexture = _textureHandler.loadTexture("Assets/water.png");
	_drawHandler.init();
	_drawHandler.begin();

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
			case 'W':
				_drawHandler.addObj(destRect, uvCoords, _wallTexture.id, color);
				break;
			case '@':
				_drawHandler.addObj(destRect, uvCoords, _waterTexture.id, color);
				//_playerStartPos = glm::vec2(y, x);
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
				_drawHandler.addObj(destRect, uvCoords, _waterTexture.id, color);
				break;
			default:
				std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_drawHandler.end();
	
}


Harta::~Harta()
{
}

void Harta::draw()
{
	_drawHandler.renderBatch();
}

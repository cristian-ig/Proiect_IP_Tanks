#include "Map.h"
//#include "FatError.h"
#include "FileLoad.h"
#include "Vertex.h"
#include <fstream>
#include <iostream>

Mapz::Mapz(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	// Error checking
	if (file.fail()) {
	//	Engine::FatalError("Failed to open " + fileName);
	}

	std::string tmp;

	 // Read the level data
	while (std::getline(file, tmp)) 
	{
		_levelData.emplace_back(tmp);
	}

	//_spriteBatch.init();
	//_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Engine::Color whiteColor(255, 255, 255, 255);

	// Render all the tiles
	for (size_t y = 0; y < _levelData.size(); y++) {
		for (size_t x = 0; x < _levelData[y].size(); x++) {
			// Grab the tile
			char tile = _levelData[y][x];
			std::cout << _levelData[y][x];
			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			//std::cout << &destRect << std::endl;
			//TODO : FIX THIS
			//*/ Process the tile
			try {
				switch (tile) {
				case '#':
					_spriteBatch.draw(destRect,
						uvRect,
						Engine::FileLoad::getTexture("Assets/wall.png").id,
						0.0f,
						whiteColor);
					break;
				case 'W':
					_spriteBatch.draw(destRect,
						uvRect,
						Engine::FileLoad::getTexture("Assets/water.png").id,
						0.0f,
						whiteColor);
					break;
				case 'L':
					_spriteBatch.draw(destRect,
						uvRect,
						Engine::FileLoad::getTexture("Assets/light_wall.png").id,
						0.0f,
						whiteColor);
					break;
				case '@':
					Engine::FileLoad::getTexture("Assets/tank.png").id;
					//_levelData[y][x] = '.'; /// So we dont collide with a @
					//_startPlayerPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break;
				case 'Z':
					//	EasyEngine::ResourceManager::getTexture("Textures/zombie.png").id,
				//	_levelData[y][x] = '.'; /// So we dont collide with a Z
				//	_enemyStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break;
				case '.':
					break;
				default:
					std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
					break;
				}//*/
			}
			catch (int  ex) { std::cout << "err";  }
		}
		std::cout << std::endl;
	}

	_spriteBatch.end();
}


Mapz::~Mapz()
{
}


void Mapz::draw()
{
	try {
		_spriteBatch.renderBatch();
	}
	catch (...) { std::cout << "err";  }
}
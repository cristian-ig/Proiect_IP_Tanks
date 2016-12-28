#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "SpriteBatch.h"

class Mapz
{
#define TILE_WIDTH 32

public:
	Mapz(const std::string& fileName);
	~Mapz();

	void draw(); //draw the map

	//getters
	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }

	const std::vector<std::string>& getLevelData()            const { return _levelData; }
	const std::vector<glm::vec2>&   getStartPlayerPos()       const { return _startPlayerPos; }
	const std::vector<glm::vec2>&   getZombieStartPositions() const { return _enemyStartPos; }
	 
private:
	std::vector<std::string> _levelData; //store each line of text as a texture
	std::vector<glm::vec2> _startPlayerPos; //store player start positions
	std::vector<glm::vec2> _enemyStartPos; //store enemy start positions
	Engine::SpriteBatch _spriteBatch;
};


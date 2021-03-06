#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Defines.h"
#include "DrawClass.h"
#include "OpenGLTexture.h"


class Harta
{
public:
	Harta(const std::string& fileName, char numPlayers, char numEnemys );
	~Harta();

	void draw();
	const std::vector<std::string>& getMapData() { return _mapData; }
	const std::vector<glm::vec2>& getPlayerStartPos() const { return _playerStartPos; }
    const std::vector<glm::vec2>& getEnemysStartPos() const { return _enemyStartPos; }

	//getters
	int getWidth()		const { return _mapData[0].size(); }
	int getHeight()		const { return _mapData.size(); }
	int getEntitys()	const { return _numEntitys; }
	int getEnemysLeft() const { return _numEnemyLeft; }
	int getNumEnemy() const { return _numEnem; }
	char32_t getMapTile(glm::ivec2 position) { return (getMapData()[floor(position.y / float(TILE_WIDTH))][(position.x / float(TILE_WIDTH))]); }
	glm::vec2 getCameraCenter() { return _cameraPos; }


private:
	int _numEntitys = 0;
	int _numEnemyLeft = 0;
	int _numEnem=0;
	std::vector<std::string> _mapData;
	
	std::vector<glm::vec2> _playerStartPos;
	std::vector<glm::vec2> _enemyStartPos;

	glm::vec2 _cameraPos;
	
	Engine::DrawSprites _spriteBatch;

};


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

	//getters
	int getWidth()		const { return _mapData[0].size(); }
	int getHeight()		const { return _mapData.size(); }
	int getEntitys()	const { return _numEntitys; }
	int getEnemysLeft() const { return _numEnemyLeft; }

	glm::vec2 getCameraCenter() { return _cameraPos; }
	const std::vector<std::string>& getMapData() { return _mapData; }
	const std::vector<glm::vec2>& getPlayerStartPos() const { return _playerStartPos; }
	const std::vector<glm::vec2>& getEnemysStartPos() const { return _enemyStartPos; }


private:
	int _numEntitys = 0;
	int _numEnemyLeft = 0;

	std::vector<std::string> _mapData;
	std::vector<glm::vec2> _playerStartPos;
	std::vector<glm::vec2> _enemyStartPos;

	glm::vec2 _cameraPos;
	
	Engine::DrawSprites _spriteBatch;

};


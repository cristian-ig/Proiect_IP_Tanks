#include "Projectiles.h"
#include "Defines.h"
#include "Entity.h"
#include "Enemys.h"
#include "Players.h"
#include "Harta.h"
#include "FileLoad.h"
#include<random>


Projectiles::Projectiles(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	_position(position), _direction(direction), _damage(damage), _speed(speed), _isFirst(true),
	colided(false), acceleration(2.0f)
{
}

Projectiles::~Projectiles()
{
}

bool Projectiles::update(const std::vector<std::string>& harta)
{
	
	if (!colided) {
		if (collideWithWorld(harta)) {

			glm::ivec2 projPosition = _position;
			glm::ivec2 fgridPosition = glm::ivec2(floor(projPosition.x / (float)TILE_WIDTH), floor(projPosition.y / (float)TILE_WIDTH));
			glm::ivec2 cgridPosition = glm::ivec2(ceil(projPosition.x / (float)TILE_WIDTH), ceil(projPosition.y / (float)TILE_WIDTH));


		//	std::cout << "projPos " << projPosition.x << " " << projPosition.y << std::endl;
			//std::cout << "gridPosition " << gridPosition.x << " " << gridPosition.y << std::endl;
			//std::cout << "gridPositionX32 " << gridPosition.x*TILE_WIDTH << " " << gridPosition.y*TILE_WIDTH << std::endl << std::endl;
			if ((projPosition.x <= fgridPosition.x * TILE_WIDTH + TILE_WIDTH - BULLET_RADIUS  || projPosition.x >= fgridPosition.x * TILE_WIDTH + BULLET_RADIUS) && (projPosition.x <= cgridPosition.x * TILE_WIDTH + TILE_WIDTH - BULLET_RADIUS || projPosition.x >= cgridPosition.x * TILE_WIDTH + BULLET_RADIUS))
				_direction = glm::vec2(-_direction.x, _direction.y);
			if((projPosition.y <= fgridPosition.y * TILE_WIDTH + TILE_WIDTH - BULLET_RADIUS || projPosition.y >= fgridPosition.y * TILE_WIDTH + BULLET_RADIUS) && (projPosition.y <= cgridPosition.y * TILE_WIDTH + TILE_WIDTH - BULLET_RADIUS || projPosition.y >= cgridPosition.y * TILE_WIDTH + BULLET_RADIUS))
				_direction = glm::vec2(_direction.x, -_direction.y);
			_position += _direction * _speed*acceleration;
			if (acceleration > 0.5f)
				acceleration -= 0.0005f;
			colided = true;
			return true;

		}
		

	}
	else colided = false;
	_position += _direction * _speed*acceleration;
	if (acceleration > 1.0f)
		acceleration -= 0.02f;
	return false;
		
	

}

void Projectiles::draw(Engine::DrawSprites& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	//first draw substrac tank with and height from position for good colision
	if (_isFirst){
	//	_position.x -= TANK_WIDTH / 2;
		//_position.y -= TANK_HEIGHT / 2;
		_isFirst = false;
	}
	destRect.x = _position.x ;
	destRect.y = _position.y;
	destRect.z = BULLET_RADIUS;
	destRect.w = BULLET_RADIUS;

	Engine::Color color;
	color.R = 255;
	color.G = 255;
	color.B = 255;
	color.A = 255;

	spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/bullet.png").id, 0.0f, color,_direction);

	return;
}

bool Projectiles::collideWithEntity(Entity* entity)
{
#if 0
	const float MIN_DISTANCE_X = TANK_WIDTH / 4.0f + BULLET_RADIUS;
	const float MIN_DISTANCE_Y = TANK_HEIGHT / 2.0f + BULLET_RADIUS;


	//add with and height/2 for better colision
	glm::vec2 pos(_position.x + TANK_WIDTH / 2, _position.y + TANK_HEIGHT / 2);
	glm::vec2 centerPosA = pos;
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(TANK_WIDTH / 1.4f, TANK_HEIGHT / 1.4f);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	glm::vec2 collisionDepth = glm::vec2(MIN_DISTANCE_X - glm::length(distVec), MIN_DISTANCE_Y - glm::length(distVec));
	// If collision depth > 0 then we did collide
	if (xDepth > 0 && yDepth > 0)
		return true;

	return false;
#endif // 0
	const float MIN_DISTANCE_X = TANK_WIDTH / 8.0f + BULLET_RADIUS;
	const float MIN_DISTANCE_Y = TANK_HEIGHT / 2.0f + BULLET_RADIUS;


	//add with and height/2 for better colision
	glm::vec2 pos(_position.x , _position.y + TANK_HEIGHT / 2);
	glm::vec2 centerPosA = pos;
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 1.4f);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	glm::vec2 collisionDepth = glm::vec2(MIN_DISTANCE_X - glm::length(distVec), MIN_DISTANCE_Y - glm::length(distVec));
	// If collision depth > 0 then we did collide
	if (xDepth > 0 && yDepth > 0)
		return true;

	return false;
}

bool Projectiles::collideWithWorld(const std::vector<std::string>& harta)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor((_position.x + BULLET_RADIUS) / (float)TILE_WIDTH);
	gridPosition.y = floor((_position.y + BULLET_RADIUS) / (float)TILE_WIDTH);

	// If we are outside the world, just return
	if (gridPosition.x < 0 || gridPosition.x >= harta[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= harta.size()) {
		return true;
	}

	return (harta[gridPosition.y][gridPosition.x] != '.');

}

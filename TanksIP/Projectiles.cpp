#include "Projectiles.h"
#include "Defines.h"
#include "Entity.h"
#include "Enemys.h"
#include "Players.h"
#include "Harta.h"
#include "FileLoad.h"


Projectiles::Projectiles(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	_position(position), _direction(direction), _damage(damage), _speed(speed)
{
}

Projectiles::~Projectiles()
{
}

bool Projectiles::update(const std::vector<std::string>& harta)
{
	_position += _direction * _speed;
	return collideWithWorld(harta);
}

void Projectiles::draw(Engine::DrawSprites& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x - TANK_WIDTH /2 ;
	destRect.y = _position.y - TANK_HEIGHT/2;
	destRect.z = BULLET_RADIUS;
	destRect.w = BULLET_RADIUS;

	Engine::Color color;
	color.R = 255;
	color.G = 255;
	color.B = 255;
	color.A = 255;

	spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/bullet.png").id, 0.0f, color);

	return;
}

bool Projectiles::collideWithEntity(Entity* entity)
{
	const float MIN_DISTANCE_X = TANK_WIDTH / 4.0f + BULLET_RADIUS;
	const float MIN_DISTANCE_Y = TANK_HEIGHT / 2.0f+ BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
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
}

bool Projectiles::collideWithWorld(const std::vector<std::string>& harta)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	// If we are outside the world, just return
	if (gridPosition.x < 0 || gridPosition.x >= harta[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= harta.size()) {
		return true;
	}

	return (harta[gridPosition.y][gridPosition.x] != '.');

}

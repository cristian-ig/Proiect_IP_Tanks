#include "Projectiles.h"
#include "Defines.h"
#include "Entity.h"
#include "Enemys.h"
#include "Players.h"
#include "Harta.h"

Projectiles::Projectiles(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
	_position(position), _drection(direction), _damage(damage), _speed(speed)
{
}

Projectiles::~Projectiles()
{
}

bool Projectiles::update(const std::vector<std::string>& harta)
{
	_position += _drection * _speed;
	return collideWithWorld(harta);
}

void Projectiles::draw()
{
	return;
}

bool Projectiles::collideWithEntity(Entity* entity)
{
	const float MIN_DISTANCE_X = TANK_WIDTH + BULLET_RADIUS;
	const float MIN_DISTANCE_Y = TANK_HEIGHT + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);

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

void Projectiles::fireUpdate(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets)
{
	_counter++;
	if (_counter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets);
	}
}

void Projectiles::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets)
{
	for (size_t i = 0; i < _bulletsPerShot; i++) {
		// Add a new bullet
		bullets.emplace_back(position - glm::vec2(BULLET_RADIUS),direction, _damage, _speed);
	}
}

void Projectiles::weaponsInit(int fireRate, int BPS, float counter)
{
	_fireRate = fireRate;
	_bulletsPerShot = BPS;
	_counter = counter;
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

#include "Artillery.h"
#include "Defines.h"


Artillery::Artillery(int fireRate, int bulletsPerShot,
	 float bulletDamage, float bulletSpeed) :
	_fireRate(fireRate),
	_bulletsPerShot(bulletsPerShot),
	_bulletDamage(bulletDamage),
	_bulletSpeed(bulletSpeed),
	_frameCounter(0.0f)
{
}


Artillery::~Artillery()
{
}

void Artillery::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Projectiles>& bullets)
{
	for (int i = 0; i < _bulletsPerShot; i++) 
	{
		// Add a new bullet
		//TODO Add Sound
		//bullets.emplace_back(position + glm::vec2(BULLET_RADIUS ), direction, _bulletDamage, _bulletSpeed);
		bullets.emplace_back(position + glm::vec2(BULLET_RADIUS) + glm::vec2(TANK_WIDTH/2, 0)*direction, direction, _bulletDamage, _bulletSpeed);
	}
}

void Artillery::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets)
{
	_frameCounter++;
	// After a certain number of frames has passed we fire our gun
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets);
		_frameCounter = 0;
	}
}

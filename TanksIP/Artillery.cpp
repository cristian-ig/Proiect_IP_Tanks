#include "Artillery.h"
#include "Defines.h"
#include<iostream>


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

void Artillery::fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Projectiles>& bullets, const std::vector<std::string>& harta, GameState gamestate)
{
	for (int i = 0; i < _bulletsPerShot; i++) 
	{
		// Add a new bullet
		//TODO Add Sound
		//bullets.emplace_back(position + glm::vec2(BULLET_RADIUS ), direction, _bulletDamage, _bulletSpeed);

		glm::ivec2 gridPosition;
		gridPosition.x = floor((position.x + 2.5) / (float)TILE_WIDTH);
		gridPosition.y = floor((position.y + 3.5) / (float)TILE_WIDTH);

		if (gamestate == GameState::SINGLEPLAYER) {
		

			glm::vec2 oldpos = position + glm::vec2(BULLET_RADIUS) + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);
			glm::vec2 newpos = position + glm::vec2(BULLET_RADIUS) + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);
			newpos -= position;
			float nx = newpos.x;
			float ny = newpos.y;

			glm::vec2 up(1.0f, 0.0f);
			float angle = acos(glm::dot(up, direction));

			if (direction.y < 0)angle = -angle;

			std::cout << angle << std::endl;

			float s = sin(angle);
			float c = cos(angle);

			newpos.x = nx * c - ny* s;
			newpos.y = nx * s + ny* c;


			//newpos.x = cos(angle)*(px - position.x) - sin(angle)*(py - position.y) + position.x;
			//newpos.y = sin(angle)*(px - position.x) + cos(angle)*(py - position.y) + position.y;

			newpos += position;
		}else
			if (gamestate == GameState::MULTYPLAYER) {

				if (direction == glm::vec2(1.0f, 0.0f)) {
					if (harta[gridPosition.y][gridPosition.x] == '.')
						bullets.emplace_back(position+ glm::vec2(TANK_WIDTH/1.0f,TANK_HEIGHT/2.5f)+ glm::vec2(BULLET_RADIUS*2, 0.0f), direction, _bulletDamage, _bulletSpeed);
				}else if (direction == glm::vec2(-1.0f, 0.0f)) {
					if (harta[gridPosition.y][gridPosition.x] == '.')
						bullets.emplace_back(position + glm::vec2( -TANK_WIDTH / 6.0f, TANK_HEIGHT / 2.5f) - glm::vec2(BULLET_RADIUS /2.0f , 0.0f), direction, _bulletDamage, _bulletSpeed);
				}
				else if (direction == glm::vec2(0.0f, 1.0f)) {
					if (harta[gridPosition.y][gridPosition.x] == '.')
						bullets.emplace_back(position + glm::vec2(TANK_HEIGHT/ 2.0f, TANK_WIDTH ) + glm::vec2(BULLET_RADIUS / 2.0f, 0.0f), direction, _bulletDamage, _bulletSpeed);
				
				}else if (direction == glm::vec2(0.0f, -1.0f)) {
					if (harta[gridPosition.y][gridPosition.x] == '.')
						bullets.emplace_back(position + glm::vec2( TANK_WIDTH / 2.0f, - TANK_HEIGHT / 2.5f) - glm::vec2(BULLET_RADIUS /2.0f , 0.0f), direction, _bulletDamage, _bulletSpeed);
				}
			}

	
	}
}

void Artillery::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets, const std::vector<std::string>& harta, GameState gamestate)
{
	_frameCounter++;
	// After a certain number of frames has passed we fire our gun
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets, harta, gamestate );
		_frameCounter = 0;
	}
}

#include "Enemys.h"
#include "Players.h"
#include "FileLoad.h"
#include "Artillery.h"

Enemys::Enemys()
{
}


Enemys::~Enemys()
{
}
void Enemys::initGun(Artillery* gun)
{
	_guns.push_back(gun);
	//if no gun, just equip
	if (_currentIndex == -1)
		_currentIndex = 0;
}
void Enemys::update(const std::vector<std::string>& harta, std::vector<Players*>& players, std::vector<Enemys*>& enemys)
{
	//find closest player
	Players* closestTarget = getNearestPlayer(players);

	// If we found a player, move towards him
	//TODO: ADD SAFETY DISTANCE
	if (closestTarget != nullptr) 
	{
		// Get the direction vector twoards the player
		_direction = glm::normalize(closestTarget->getPosition() - _position);
	//	_position += _direction * _speed;
	}

	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);
//	glm::vec2 newDirection(1.0f, 0.0f);
	//_guns[0]->update(true, centerPosition, _direction, *_bullets);
	//ADD AI
}

void Enemys::init(glm::vec2 position, std::vector<Projectiles>* bullets, float speed, float damage, float health)
{
	_position = position;
	_speed = speed;
	_damage = damage;
	_health = health;
	_bullets = bullets;
	//_color = color;
	//TODO: LOAD TEXTURE;
	_textureID = Engine::FileLoad::getTexture("Assets/tank.png").id;
}

Players* Enemys::getNearestPlayer(std::vector<Players*> players)
{
	Players* closestPlayer = nullptr;
	float minDist = 999999999.0f;

	//AI
	for (size_t i = 0; i < players.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = players[i]->getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this person is closer than the closest person, this is the new closest
		if (distance < minDist) {
			minDist = distance;
			closestPlayer = players[i];
		}
	}

	return closestPlayer;
}

BonusBox* Enemys::getNearestBonus(std::vector<BonusBox*> bonusBoxes)
{
	BonusBox* closestBonus = nullptr;
	

	return closestBonus;
}

void Enemys::dogeBullet()
{
	return;
}

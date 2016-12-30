#include "Enemys.h"
#include "Players.h"

Enemys::Enemys()
{
}


Enemys::~Enemys()
{
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
		_position += _direction * _speed;
	}
	
	//ADD AI
}

void Enemys::init(glm::vec2 position, float speed, float damage, float health)
{
	_position = position;
	_speed = speed;
	_damage = damage;
	_health = health;

	//TODO: LOAD TEXTURE;
}

Players* Enemys::getNearestPlayer(std::vector<Players*> players)
{
	Players* closestPlayer = nullptr;
	float minDist = 999999999.0f;

	//AI
	for (int i = 0; i < players.size(); i++) {
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

#include "Enemys.h"
#include "Players.h"
#include "FileLoad.h"
#include "Artillery.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
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
void Enemys::update(const std::vector<std::string>& harta, const std::vector<Players*>& players, 
	const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes)
{
	//find closest player
	Players* closestTarget = getNearestPlayer(players);
	BonusBox* closestBonus = getNearestBonus(bonusBoxes);

	// If we found a player, move towards him
	 if (pitagoraDistance(closestTarget) < 200.0f)
	{
		// Get the direction vector twoards the player
		_direction = glm::normalize(closestTarget->getPosition() - _position);
		/*
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, _direction));
		if (_direction.y < 0.0f) angle = -angle;
		//std::cout << angle << std::endl;

		if ((angle > 0.1f) && (angle < 1.30f) || (angle > 1.7f) && (angle < 3.1f) || (angle < -0.1f) && (angle > -1.30f) || (angle < -1.7f) && (angle > -3.10f))
		{
		_position += _direction * _speed / 2.0f;
		} 
		else
		{
		_position += _direction * _speed;
		}
		
		if (angle == 0.0f || angle == (float)M_PI_2 || angle == (float)M_PI || angle == (float)-M_PI_2)
		{
		} 
		else
		{
			_position += _direction * _speed / 2.0f;
		}
		//std::cout << "direction: " << _direction.x << ", " << _direction.y << std::endl;
		//_position += _direction * _speed;*/
	}
	 else if (pitagoraDistance(closestBonus) < 400.0f)// && pitagoraDistance(closestTarget) <= 200.0f)
	{
		_direction = glm::normalize(closestBonus->getPosition() - _position);
	}


	_position += _direction * _speed;

	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH /2.0f, TANK_HEIGHT / 2.0f);
	//_guns[0]->update(true, centerPosition, _direction, *_bullets);
	//ADD AI
	collideWithBonusBox(this, closestBonus);
	collideWithMap(harta);
}

void Enemys::init(glm::vec2 position, std::vector<Projectiles>* bullets, float speed, float damage, float health)
{
	_position = position;
	_speed = speed;
	_damage = damage;
	_health = health;
	_bullets = bullets;
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
	float minDist = 999999999.0f;

	//AI
	for (size_t i = 0; i < bonusBoxes.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = bonusBoxes[i]->getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this Box is closer than the closest person, this is the new closest
		if (distance < minDist) {
			minDist = distance;
			closestBonus = bonusBoxes[i];
		}
	}

	return closestBonus;
}


void Enemys::dogeBullet()
{
	return;
}

float Enemys::pitagoraDistance(Players* player)
{
	float distX = this->getPosition().x - player->getPosition().x;
	float distY = this->getPosition().y - player->getPosition().y;

	return sqrt((distX * distX) + (distY * distY)); //pitagora ftw
}

float Enemys::pitagoraDistance(BonusBox* BB)
{
	float distX = this->getPosition().x - BB->getPosition().x;
	float distY = this->getPosition().y - BB->getPosition().y;

	return sqrt((distX * distX) + (distY * distY)); //pitagora ftw
}
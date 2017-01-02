#pragma once
#include <glm/glm.hpp>
#include <vector>

class Entity;
class Player;
class Enemy;

class Projectiles
{
public:
	Projectiles(glm::vec2 position, glm::vec2 direction, float damage, float speed);
	~Projectiles();

	bool update(const std::vector<std::string>& harta); //delete the bullet if returns true

	void draw();

	bool collideWithEntity(Entity* entity);

	void fireUpdate();

	void weaponsInit();

	glm::vec2 getPosition() const { return _position; }

private:

	bool collideWithWorld(const std::vector<std::string>& harta);

	void fire();

	glm::vec2 _position = glm::vec2(0.0f, 0.0f);
	glm::vec2 _drection = glm::vec2(1.0f, 0.0f);

	float _speed = 0.0f;
	float _damage = 0.0f;
	int _fireRate = 20;
	int _bulletsPerShot = 0.0f;
	float _counter = 0.0f;

};


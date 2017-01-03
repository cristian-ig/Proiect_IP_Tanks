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


	//getters
	glm::vec2 getPosition() const { return _position; }
	float getSpeed() { return _speed; }
	float getDamage() { return _damage; }

	//setters
	void setSpeed(float newSpeed) { _speed = newSpeed; }
	void setDamage(float newDamage) { _damage = newDamage; }

private:

	bool collideWithWorld(const std::vector<std::string>& harta);

	glm::vec2 _position = glm::vec2(0.0f, 0.0f);
	glm::vec2 _drection = glm::vec2(1.0f, 0.0f);

	float _speed = 0.0f; //pixels / frame
	float _damage = 0.0f; //bullet damage
	

};


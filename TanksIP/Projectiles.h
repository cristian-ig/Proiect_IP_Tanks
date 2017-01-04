#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "DrawClass.h"
#include "OpenGLTexture.h"

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
	glm::vec2 getDirection() const { return _direction; };
	float getSpeed() { return _speed; }
	float getDamage() { return _damage; }


	//setters
	void setSpeed(float newSpeed) { _speed = newSpeed; }
	void setDamage(float newDamage) { _damage = newDamage; }
	void setDirection(glm::vec2 dir) { _direction = dir; }

private:

	bool collideWithWorld(const std::vector<std::string>& harta);
	unsigned short _reflections;

	glm::vec2 _position = glm::vec2(0.0f, 0.0f);
	glm::vec2 _direction = glm::vec2(1.0f, 0.0f);

	float _speed = 0.0f; //pixels / frame
	float _damage = 0.0f; //bullet damage
	Engine::OpenGLTexture _textureHandler;
	Engine::DrawClass _drawHandler;
	GLuint _projectileTexture = _textureHandler.loadTexture("Assets/bullet.png").id;
	

};


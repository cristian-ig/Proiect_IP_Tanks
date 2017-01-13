#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "DrawClass.h"


class Entity;
class Player;
class Enemy;

class Projectiles
{
public:
	Projectiles(glm::vec2 position, glm::vec2 direction, float damage, float speed, bool isFromPlayer);
	~Projectiles();

	bool update(const std::vector<std::string>& harta); //delete the bullet if returns true

	void draw(Engine::DrawSprites& spriteBatch);

	bool collideWithEntity(Entity* entity);

	void setSource(bool isfromPlayer) { _isFromPlayer = isfromPlayer; }
	bool getSource() { return _isFromPlayer; }

	//getters
	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDirection() const { return _direction; };
	float getSpeed() { return _speed; }
	float getDamage() { return _damage; }
	


	//setters
	void setSpeed(float newSpeed) { _speed = newSpeed; }
	void setDamage(float newDamage) { _damage = newDamage; }
	void setDirection(glm::vec2 dir) { _direction = dir; }
	void addDirection() { _position += _direction; }

	 
private:
	float acceleration;
	glm::vec2 rotationPoint(const glm::vec2& pos, float angle);
	bool collideWithWorld(const std::vector<std::string>& harta);
	unsigned short _reflections;
	bool _colided;
	bool _isFromPlayer = true;
	glm::vec2 _position = glm::vec2(0.0f, 0.0f);
	glm::vec2 _direction = glm::vec2(1.0f, 0.0f);

	bool _isFirst;
	

	float _speed = 0.0f; //pixels / frame
	float _damage = 0.0f; //bullet damage

	//GLuint _projectileTexture = _textureHandler.loadTexture("Assets/bullet.png").id;
	

};


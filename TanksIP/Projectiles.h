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

	void fireUpdate(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets);

	void weaponsInit(int fireRate, int BPS, float counter);

	//getters
	glm::vec2 getPosition() const { return _position; }
	float getSpeed() { return _speed; }
	float getDamage() { return _damage; }
	int getFireRate() {return  _fireRate; }
	int getBPS() { return _bulletsPerShot; }

	//setters
	void setSpeed(float newSpeed) { _speed = newSpeed; }
	void setDamage(float newDamage) { _damage = newDamage; }
	void setFireRate(int newFireRate) { _fireRate = newFireRate; }
	void setBPS(int newBPS) { _bulletsPerShot = newBPS; }

private:

	bool collideWithWorld(const std::vector<std::string>& harta);

	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets);

	glm::vec2 _position = glm::vec2(0.0f, 0.0f);
	glm::vec2 _drection = glm::vec2(1.0f, 0.0f);

	float _speed = 0.0f; //pixels / frame
	float _damage = 0.0f; //bullet damage
	int _fireRate = 20; //fire every 20 frames
	int _bulletsPerShot = 0; //BPS
	float _counter = 0.0f; //increment every frame to use fire rate

};


#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Projectiles.h"

class Artillery
{
public:
	Artillery(int fireRate, int bulletsPerShot,
		float spread, float bulletDamage, float bulletSpeed);
	~Artillery();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets, float deltaTime);

	int getFireRate() { return  _fireRate; }
	int getBPS() { return _bulletsPerShot; }
	void setFireRate(int newFireRate) { _fireRate = newFireRate; }
	void setBPS(int newBPS) { _bulletsPerShot = newBPS; }


private:

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Projectiles>& bullets);

	std::string _name;

	int _fireRate; ///< Fire rate in terms of frames

	int _bulletsPerShot; ///< How many bullets are fired at at time

	float _spread; ///< Accuracy

	float _bulletSpeed;

	int _bulletDamage;

	float _frameCounter; ///< Counts frames so we know when to shoot bullets

};


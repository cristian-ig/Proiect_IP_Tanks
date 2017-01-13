#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Projectiles.h"
#include "Harta.h"
#include"AudioManager.h"

class Artillery
{
public:
	Artillery(int fireRate, int bulletsPerShot,
		float bulletDamage, float bulletSpeed, bool isFromPlayer, Engine::SoundEffect fireEffect);
	~Artillery();

	void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Projectiles>& bullets, const std::vector<std::string>& harta, GameState gamestate);

	int getFireRate() { return  _fireRate; }
	int getBPS() { return _bulletsPerShot; }
	void setFireRate(int newFireRate) { _fireRate = newFireRate; }
	void setBPS(int newBPS) { _bulletsPerShot = newBPS; }

	bool getSource() { return _isFromPlayer; }


private:

	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Projectiles>& bullets, const std::vector<std::string>& harta, GameState gamestate);
	Engine::AudioManager _audioManager;
	Engine::Music music = _audioManager.loadMusic("Assets/Audio/tank_fire.mp3");
	std::string _name;

	int _fireRate; // Fire rate in terms of frames

	int _bulletsPerShot; // How many bullets are fired at at time

	//float _spread; // Accuracy

	float _bulletSpeed;

	Engine::SoundEffect _fireEffect;

	bool _isFromPlayer;

	int _bulletDamage;

	float _frameCounter; // Counts frames so we know when to shoot bullets

};


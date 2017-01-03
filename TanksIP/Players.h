#pragma once
#include<math.h>
#include "Entity.h"
#include "Input.h"
#include "Camera.h"
#include "Artillery.h"
#include <vector>

class Players : public Entity
{
public:
	Players();
	~Players();

	void update(const std::vector<std::string>& harta, std::vector<Players*>& players, std::vector<Enemys*>& enemys) override;
	
	void init(glm::vec2 position,Engine::Input* input, Engine::Camera* camera, std::vector<Projectiles>* bullets, float speed = TANK_SPEED, float damage = TANK_DAMAGE, float health = TANK_HEALTH);
	void initGun(Artillery* gun);


private:
	Engine::Input* _input;
	Engine::Camera* _camera;
	int _currentIndex = -1;
	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;
};


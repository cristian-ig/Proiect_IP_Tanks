#pragma once
#include "Entity.h"
#include "Input.h"
#include "Camera.h"


class Players : public Entity
{
public:
	Players();
	~Players();

	virtual void update(const std::vector<std::string>& harta, std::vector<Players*>& players, std::vector<Enemys*>& enemys) override;
	
	void init(glm::vec2 position, Engine::Camera camera, float speed = TANK_SPEED, float damage = TANK_DAMAGE, float health = TANK_HEALTH);


private:
	Engine::Input* _input;
	Engine::Camera _camera;
};


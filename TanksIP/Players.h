#pragma once
#include "Entity.h"
#include "Input.h"
#include "Camera.h"
#include "Artillery.h"

class Players : public Entity
{
public:
	Players();
	~Players();

	void update(const std::vector<std::string>& harta, const std::vector<Players*>& players,
		const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes) override;
	
	void init(glm::vec2 position,Engine::Input* input, Engine::Camera* camera, std::vector<Projectiles>* bullets, 
		TankType tankType = TankType::DEFAULT, float speed = TANK_SPEED, float damage = TANK_DAMAGE, float health = TANK_HEALTH);
	void initGun(Artillery* gun);

	void drawP(Engine::DrawSprites& spriteBatch);

	void initTankTypes(TankType tankType);
private:
	Engine::Input* _input;
	Engine::Camera* _camera;

	int _currentIndex = -1;
	bool _shootPerClick;

	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;
};


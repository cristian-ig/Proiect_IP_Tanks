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
		const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes, 
		 std::vector<Projectiles>& bullets, GameState gamestate) override;

	void init(glm::vec2 position, Engine::Input* input, Engine::Camera* camera, std::vector<Projectiles>* bullets,
		TankType tankType);
	void initGun(Artillery* gun);

	void drawP(Engine::DrawSprites& spriteBatch);

	void initTankTypes(TankType tankType);
	//set num player
	void setNumPlayer(unsigned char numPlayer) { nPlayer = numPlayer; }

	unsigned char getNumPlayer() { return nPlayer; }
private:
	Engine::Input* _input;
	Engine::Camera* _camera;

	int _currentIndex = -1;
	bool _shootPerClick;
	unsigned char nPlayer;
	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;
};


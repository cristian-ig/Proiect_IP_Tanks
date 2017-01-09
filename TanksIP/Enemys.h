#pragma once
#include "Entity.h"
#include <glm/glm.hpp>


class Enemys : public Entity
{
public:
	Enemys();
	~Enemys();

	void update(const std::vector<std::string>& harta, const std::vector<Players*>& players,
		const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes, GameState gamestate) override;

	void init(glm::vec2 position, std::vector<Projectiles>* bullets, float speed = TANK_SPEED, float damage = TANK_DAMAGE, float health = TANK_HEALTH);
	void initGun(Artillery* gun);
private:
	Players* getNearestPlayer(std::vector<Players*> players);
	BonusBox* getNearestBonus(std::vector<BonusBox*> bonusBoxes);
	void dogeBullet(); // or we can make a bool and if returns true, score ++ :~)
	float pitagoraDistance(Players* players);
	float pitagoraDistance(BonusBox* BB);
	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;


};


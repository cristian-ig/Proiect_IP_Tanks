#pragma once
#include "Entity.h"
#include <glm/glm.hpp>


class Enemys : public Entity
{
public:
	Enemys();
	~Enemys();

	virtual void update(const std::vector<std::string>& harta, std::vector<Players*>& players, std::vector<Enemys*>& enemys) override;

	void init(glm::vec2 position, float speed = TANK_SPEED, float damage = TANK_DAMAGE, float health = TANK_HEALTH);

private:
	Players* getNearestPlayer(std::vector<Players*> players);
	BonusBox* getNearestBonus(std::vector<BonusBox*> bonusBoxes);
	void dogeBullet(); // or we can make a bool and if returns true, score ++ :~)

};


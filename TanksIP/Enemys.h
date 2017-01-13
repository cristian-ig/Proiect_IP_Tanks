#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <queue>
#include <math.h>

struct nod;

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

	//A*
	std::list<nod*> findPath(glm::ivec2 start, glm::ivec2 goal, const std::vector<std::string>& harta);
	int nodSorter(nod *n1, nod *n2); //sorting nodes by distance from goal
	bool isInList(const std::list<nod*>& list, const glm::ivec2& vector);
	std::list<nod*> _path;
	float vectorDistance(glm::vec2 vector1, glm::vec2 vector2);

	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;
	 
	int _timer = 0;
};

struct nod
{
	glm::ivec2 tile;
	nod *parent;
	float fCost;
	float gCost;
	float hCost;
	nod(glm::ivec2 tile, nod* parent, float gCost, float hCost)
	{
		this->tile = tile;
		this->parent = parent;
		this->gCost = gCost;
		this->hCost = hCost;
		this->fCost = this->gCost + this->hCost;
	}

};

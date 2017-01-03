#pragma once
#include "Entity.h"
#include "Harta.h"

enum class BonusType
{
	MAX_HEALTH, //10%
	HEAL,//15%
	HEAL_PLUS, //10%
	SPEED, //10%
	SPEED_PLUS, //10%
	DAMAGE, //15%
	DAMAGE_PLUS, //10%
	ONE_HIT_KILL, //5 %
	SHIELD, //10 % Take less damage for a period of time
	INVULNERABILITY, //5 % cant be touched ..what happens when ONHITKILL shots an INVULNERABLE tank? Divide by 0 to find out.
	NO_BONUS,
	RANDOM //10%
};

class BonusBox
{
public:
	BonusBox(float x, float y);
	~BonusBox();

	void spawnBonus(const Harta& harta);
	void spawnBonus(float x, float y, Harta harta);

	BonusType getBonusType() const { return _type; }
	
	void applyBonus(BonusType bonusType, Entity& entity);

	void drawBox(BonusType bonusType);

	void addDamage(float damage, Entity& entity);
	void addHealth(float health, Entity& entity);
	void addMaxHealth(float addmaxHealth, Entity& entity);
	void addInvulnerability(Entity& entity, float duration);
	void addShield(Entity& entity, float duration);
	void addSpeed(float speed, Entity& entity);

private:
	BonusType _type = BonusType::NO_BONUS;
	std::vector<BonusBox*> _bonusBoxes;
	Entity *_entity;

	float _posX = 0.0f;
	float _posY = 0.0f;

};


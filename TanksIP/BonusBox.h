#pragma once
#include "Entity.h"
#include "Harta.h"
#include "DrawClass.h"
#include "glm/glm.hpp"

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
	BonusBox(glm::vec2 position);
	BonusBox();
	~BonusBox();

	void spawnBonus(const std::vector<std::string>& harta, BonusType bonusType, std::vector<BonusBox*>& _bonuses);
	void spawnBonus(float x, float y, const std::vector<std::string>& harta);

	BonusType getBonusType() const { return _type; }
	glm::vec2 getPosition() const { return _position; }

	void applyBonus(BonusType bonusType, Entity& entity);

	void drawBox(BonusType bonusType, Engine::DrawSprites spriteBatch);

	void addDamage(float damage, Entity& entity);
	void addHealth(float health, Entity& entity);
	void addMaxHealth(float addmaxHealth, Entity& entity);
	void addInvulnerability(Entity& entity, float duration);
	void addShield(Entity& entity, float duration);
	void addSpeed(float speed, Entity& entity);

private:
	BonusType _type = BonusType::NO_BONUS;
	//std::vector<BonusBox*> _bonusBoxes;
	Entity *_entity;

	Engine::DrawSprites _spriteBatch;

	glm::vec2 _position;
	
	//float _posX = 0.0f;
	//float _posY = 0.0f;

};


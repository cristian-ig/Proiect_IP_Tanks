#include "BonusBox.h"
#include "Defines.h"
#include <random>
#include <ctime>

BonusBox::BonusBox(float x, float y)
{
	_posX = x * BONUS_BOX_WIDTH;
	_posY = y * BONUS_BOX_WIDTH;
}


BonusBox::~BonusBox()
{
	for (size_t i = 0; i < _bonusBoxes.size(); i++)
		delete _bonusBoxes[i];
}

void BonusBox::spawnBonus(const Harta& harta)
{

		static std::mt19937 randomEngine(time(nullptr));
		// For offsetting the coordonates
		std::uniform_real_distribution<float> randX(0, harta.getWidth());
		std::uniform_real_distribution<float> randY(0, harta.getHeight());

		_bonusBoxes.push_back(new BonusBox(randX(randomEngine), randY(randomEngine)));

}

void BonusBox::spawnBonus(float x, float y, Harta harta)
{
	_bonusBoxes.push_back(new BonusBox(x, y));
}

void BonusBox::applyBonus(BonusType bonusType, Entity& entity)
{
	if (bonusType == BonusType::RANDOM)
		bonusType = static_cast<BonusType>(rand() % MAX_BONUSES);

	switch (bonusType)
	{
	case BonusType::MAX_HEALTH:
		addMaxHealth(BONUS_MAX_HEALTH, entity);
		break;
	case BonusType::HEAL:
		addHealth(BONUS_HEAL, entity);
		break;
	case BonusType::HEAL_PLUS:
		addHealth(BONUS_HEAL_PLUS, entity);
		break;
	case BonusType::SPEED:
		addSpeed(BONUS_SPEED, entity);
		break;
	case BonusType::SPEED_PLUS:
		addSpeed(BONUS_SPEED_PLUS, entity);
		break;
	case BonusType::DAMAGE:
		addDamage(BONUS_DAMAGE, entity);
		break;
	case BonusType::DAMAGE_PLUS:
		addDamage(BONUS_DAMAGE_PLUS, entity);
		break;
	case BonusType::ONE_HIT_KILL:
		addDamage(BONUS_ONE_HIT_KILL, entity);
		break;
	case BonusType::SHIELD:
		addShield(entity, BONUS_DURATION);
		break;
	case BonusType::INVULNERABILITY:
		addInvulnerability(entity, BONUS_DURATION);
		break;
	default:
		break;
	}
}

void BonusBox::addDamage(float damage, Entity& entity)
{
	entity._damage += damage;
}

void BonusBox::addHealth(float health, Entity& entity)
{
	entity._health += health;
}

void BonusBox::addShield(Entity& entity, float duration)
{
	entity._isShielded = true;
}

void BonusBox::addSpeed(float speed, Entity& entity)
{
	entity._speed += speed;
}

void BonusBox::addInvulnerability(Entity& entity, float duration)
{
	entity._isInvulnerable = true;
}

void BonusBox::addMaxHealth(float addmaxHealth, Entity& entity)
{
	entity._maxHlealth += addmaxHealth;
}

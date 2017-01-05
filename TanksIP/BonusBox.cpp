#include "BonusBox.h"
#include "Defines.h"
#include <random>
#include <ctime>
#include "FileLoad.h"

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

void BonusBox::spawnBonus(const std::vector<std::string>& harta)
{

		static std::mt19937 randomEngine(time(nullptr));
		// For offsetting the coordonates
		std::uniform_int_distribution<int> randX(0, 11);
		std::uniform_int_distribution<int> randY(0, 11);

		_bonusBoxes.push_back(new BonusBox(randX(randomEngine), randY(randomEngine)));

}

void BonusBox::spawnBonus(float x, float y, const std::vector<std::string>& harta)
{
	_bonusBoxes.push_back(new BonusBox(x, y));
	
}

void BonusBox::drawBox(BonusType bonusType, Engine::DrawSprites spriteBatch)
{

	_spriteBatch.begin();

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _posX;
	destRect.y = _posY;
	destRect.z = BONUS_BOX_WIDTH;
	destRect.w = BONUS_BOX_WIDTH;

	Engine::Color color;
	color.R = 255;
	color.G = 255;
	color.B = 255;
	color.A = 255;

	switch (bonusType)
	{
	case BonusType::MAX_HEALTH:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Max_Health.png").id, 0.0f, color);
		break;
	case BonusType::HEAL:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Heal.png").id, 0.0f, color);
		break;
	case BonusType::HEAL_PLUS:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Heal_plus.png").id, 0.0f, color);
		break;
	case BonusType::SPEED:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Speed.png").id, 0.0f, color);
		break;
	case BonusType::SPEED_PLUS:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Speed_plus.png").id, 0.0f, color);
		break;
	case BonusType::DAMAGE:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Damage.png").id, 0.0f, color);
		break;
	case BonusType::DAMAGE_PLUS:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Damage_plus.png").id, 0.0f, color);
		break;
	case BonusType::ONE_HIT_KILL:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/OHT.png").id, 0.0f, color);
		break;
	case BonusType::SHIELD:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Shield.png").id, 0.0f, color);
		break;
	case BonusType::INVULNERABILITY:
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Invulnerability.png").id, 0.0f, color);
		break;
	default:
		//draw random box
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Random.png").id, 0.0f, color);
		break;
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

}

void BonusBox::applyBonus(BonusType bonusType, Entity& entity)
{
	//generate a random bonus
	if (bonusType == BonusType::RANDOM)
		bonusType = static_cast<BonusType>(rand() % MAX_BONUSES);

	//apply every bonus possible
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

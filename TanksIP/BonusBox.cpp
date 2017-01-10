#include "BonusBox.h"
#include "Defines.h"
#include <random>
#include <ctime>
#include "FileLoad.h"
#include<iostream>
BonusBox::BonusBox(glm::vec2 position)
{
	_position.x = position.x;// *BONUS_BOX_WIDTH;
	_position.y = position.y;// *BONUS_BOX_WIDTH;
}
BonusBox::BonusBox()
{
}

BonusBox::~BonusBox()
{
// 	for (size_t i = 0; i < _bonusBoxes.size(); i++)
// 		delete _bonusBoxes[i];
}

void BonusBox::spawnBonus(const std::vector<std::string>& harta, BonusType bonusType, std::vector<BonusBox*>& bonuses)
{
	bonusType = BonusType::RANDOM;
	glm::vec2 pos;
	static std::mt19937 randomEngine(time(nullptr));
	// For offsetting the coordonates
	while (true)
	{
	std::uniform_int_distribution<int> randX(1, harta[0].size()-2);
	std::uniform_int_distribution<int> randY(0, harta.size()-2);
	pos.x = randX(randomEngine) * TILE_WIDTH;
	pos.y = randY(randomEngine) * TILE_WIDTH;

	// Get the position of this corner in grid-space
	glm::vec2 bonusPos = glm::vec2(floor(pos.x / (float)TILE_WIDTH),
		floor(pos.y / (float)TILE_WIDTH));

	// If this is not an air tile, we should create a bonus on it
	if (harta[bonusPos.y][bonusPos.x] == '.')
		break;
	}

	bonuses.push_back(new BonusBox(pos));
	

}

void BonusBox::spawnBonus(float x, float y, const std::vector<std::string>& harta, std::vector<BonusBox*>& bonuses)
{
	bonuses.push_back(new BonusBox(glm::vec2(x, y)));
	return;
}

void BonusBox::drawBox(BonusType bonusType, Engine::DrawSprites&  spriteBatch)
{

	//_spriteBatch.begin();

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
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
		//std::cout << "bonus" << std::endl;
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Max_Health.png").id, 0.0f, color);
		break;
	case BonusType::HEAL:
		//draw
		//std::cout << "bonus" << std::endl;
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Heal.png").id, 0.0f, color);
		break;
	case BonusType::HEAL_PLUS:
		//draw
		//std::cout << "bonus" << std::endl;
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Heal_plus.png").id, 0.0f, color);
		break;
	case BonusType::SPEED:
		//draw
		//std::cout << "bonus" << std::endl;
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Speed.png").id, 0.0f, color);
		break;
	case BonusType::SPEED_PLUS:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Speed_plus.png").id, 0.0f, color);
		break;
	case BonusType::DAMAGE:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Damage.png").id, 0.0f, color);
		break;
	case BonusType::DAMAGE_PLUS:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Damage_plus.png").id, 0.0f, color);
		break;
	case BonusType::ONE_HIT_KILL:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/OHT.png").id, 0.0f, color);
		break;
	case BonusType::SHIELD:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Shield.png").id, 0.0f, color);
		break;
	case BonusType::INVULNERABILITY:
		//std::cout << "bonus" << std::endl;
		//draw
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Invulnerability.png").id, 0.0f, color);
		break;
	default:
		//draw random box
		//std::cout << "bonus" << std::endl;
		spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/Bonus/Random.png").id, 0.0f, color);
		break;
	}

	//_spriteBatch.end();
	//_spriteBatch.renderBatch();

}

void BonusBox::applyBonus(BonusType bonusType, Entity& entity)
{
	//generate a random bonus
	if (bonusType == BonusType::RANDOM)
		bonusType = static_cast<BonusType>(rand() % MAX_BONUSES);
	//std::cout << "BONUS ! " << (int)bonusType << std::endl;
	//apply every bonus possible
	switch (bonusType)
	{
	case BonusType::MAX_HEALTH:
		addMaxHealth(BONUS_MAX_HEALTH, entity);
		std::cout << "BONUS APPLYED HEAL! " << std::endl;
		break;
	case BonusType::HEAL:
		addHealth(BONUS_HEAL, entity);
		std::cout << "BONUS HEAL ! " << std::endl;
		break;
	case BonusType::HEAL_PLUS:
		addHealth(BONUS_HEAL_PLUS, entity);
		std::cout << "BONUS HEAL_PLUS ! " << std::endl;
		break;
	case BonusType::SPEED:
		addSpeed(BONUS_SPEED, entity);
		std::cout << "BONUS APPLYED SPEED! " << std::endl;
		break;
	case BonusType::SPEED_PLUS:
		addSpeed(BONUS_SPEED_PLUS, entity);
		std::cout << "BONUS APPLYED SPEED_PLUS! " << std::endl;
		break;
	case BonusType::DAMAGE:
		addDamage(BONUS_DAMAGE, entity);
		std::cout << "BONUS APPLYED DAMAGE! " << std::endl;
		break;
	case BonusType::DAMAGE_PLUS:
		addDamage(BONUS_DAMAGE_PLUS, entity);
		std::cout << "BONUS APPLYED DAMAGE_PLUS! " << std::endl;
		break;
	case BonusType::ONE_HIT_KILL:
		addDamage(BONUS_ONE_HIT_KILL, entity);
		std::cout << "BONUS APPLYED ONE_HIT_KILL! " << std::endl;
		break;
	case BonusType::SHIELD:
		addShield(entity, BONUS_DURATION);
		std::cout << "BONUS APPLYED SHIELD! " << std::endl;
		break;
	case BonusType::INVULNERABILITY:
		addInvulnerability(entity, BONUS_DURATION);
		std::cout << "BONUS APPLYED INVULNERABILITY! " << std::endl;
		break;
	default:
		break;
	}
	_timers.push_back(BONUS_DURATION);
	//std::cout << "BONUS APPLYED ! " << (int)bonusType << std::endl;
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
	if (entity._speed >= TANK_MAX_SPEED)
		entity.setSpeed(TANK_MAX_SPEED);
}

void BonusBox::addInvulnerability(Entity& entity, float duration)
{
	entity._isInvulnerable = true;
}

void BonusBox::addMaxHealth(float addmaxHealth, Entity& entity)
{
	entity._maxHlealth += addmaxHealth;
}

bool BonusBox::update(float timeElapsed) {
	_timeElapsed += timeElapsed;

	return (_timeElapsed > BONUS_LIFE_TIME);
}
#pragma once
#include <glm/glm.hpp>
#include "OpenGLTexture.h"
#include <vector>
#include "Defines.h"
#include "DrawClass.h"
#include "Artillery.h"
#include "BonusBox.h"

class Players;
class Enemys;
class BonusBox;

enum class TankType
{
	DEFAULT, //default balanced
	PANZER, //more damage, less hp or speed
	SPEEDRUNNER, //more speed, less damage or hp
	MOTHER_RUSSIA,  //More health, less speed
	RANDOM
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const std::vector<std::string>& harta, const std::vector<Players*>& players,
		const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes,
		 std::vector<Projectiles>& bullets, GameState gamestate) = 0;

	void draw(Engine::DrawSprites& _spriteBatch);

	bool applyDamage(float damage); //return true if kill confirmed

	bool collideWithMap(const std::vector<std::string>& harta); //returns true if collision

	bool collideWithEntity(Entity* entity); //returns true if collisions

	bool collideWithBonusBox(Entity* entity, BonusBox* bonusBox);

	//void initGun(Artillery* gun);

	//getters
	glm::vec2 getPosition() const { return _position; }
	float getSpeed() { return _speed; }
	float getDamage() { return _damage; }
	float getHealth() { return _health; }
	TankType getTankType() { return _tankType; }
	//std::vector<std::pair<BonusType, int>> getAppliedBonuses() { return _bonusesTimers; }
	//setters
	void setSpeed(float newSpeed) { _speed = newSpeed; }
	void setDamage(float newDamage) { _damage = newDamage; }
	void setTankType(TankType newTankType) { _tankType = newTankType; }
	void setHealth(float newHealth) { _health = newHealth; }
	//bonus related
	friend class BonusBox;
	
protected:

	//float getEntityDistance(Entity* entity);
	void checkTilePosition(const std::vector<std::string>& harta,
		std::vector<glm::vec2>& collideTilePositions,
		float x,
		float y);

	void collideWithTile(glm::vec2 tilePos);

	float _maxHlealth = 500.0f;
	//float _maxSpeed = 20.0f;
	float _health = 0.0f;
	float _damage = 0.0f;
	float _speed  = 0.0f;
	bool _isInvulnerable = false;
	bool _isShielded = false;
	float _drawAngle = 0.0f;

	glm::vec2 _position;// = glm::vec2(1.0f, 1.0f);
	glm::vec2 _direction;// = glm::vec2(1.0f, 0.0f); //directia dreapta
	Engine::Color _color = Engine::Color(255,22,255,255);
	GLuint _textureID;

	TankType _tankType;

	//std::vector<std::pair<BonusType, int>> _bonusesTimers;
	std::vector<Artillery*> _guns;
	std::vector<Projectiles>* _bullets;
	int _currentIndex = -1;
};


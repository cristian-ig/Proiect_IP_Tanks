#pragma once
#include <glm/glm.hpp>
#include "OpenGLTexture.h"
#include <vector>
#include "Defines.h"

namespace tanks{


class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update() = 0;

	void draw();

	bool applyDamage(float damage);

	bool collideWithMap(const std::vector<std::string>& harta);

	bool collideWithEntity(Entity* entity);

	//getters
	glm::vec2 getPosition() const { return _position; }

protected:

	void checkTilePosition(const std::vector<std::string>& harta,
		std::vector<glm::vec2>& collideTilePositions,
		float x,
		float y);

	void collideWithTile(glm::vec2 tilePos);

	float _health = 0.0f;
	float _damage = 0.0f;
	float _speed  = 0.0f;
	glm::vec2 _position = glm::vec2(1.0f, 1.0f);
	glm::vec2 _direction = glm::vec2(1.0f, 0.0f); //directia dreapta
	GLuint _textureID;
};

}
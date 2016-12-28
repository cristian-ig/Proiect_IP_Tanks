#pragma once
#include <glm/glm.hpp>

namespace tanks{
class Entity
{
public:
	Entity();
	~Entity();
private:

	float _health = 0.0f;
	float _speed = 1.0f;
	glm::vec2 _position = glm::vec2(12.0f, 110.0f);
	glm::vec2 _direction = glm::vec2(1.0f, 0.0f); //directia dreapta
};

}
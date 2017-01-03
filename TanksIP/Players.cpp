#include "Players.h"
#include <SDL.h>

Players::Players()
{
}


Players::~Players()
{
}


void Players::update(const std::vector<std::string>& harta, std::vector<Players*>& players, std::vector<Enemys*>& enemys)
{
	if (_input->isKeyDown(SDLK_w))
		_position.y += _speed;

	else if (_input->isKeyDown(SDLK_s))
		_position.y -= _speed;

	if (_input->isKeyDown(SDLK_a))
		_position.x -= _speed;

	else if (_input->isKeyDown(SDLK_d))
		_position.x += _speed;

	glm::vec2 mouseCoords = _input->getMouseCoords();
	mouseCoords = _camera.convertToWorldCoordonates(mouseCoords);

	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);

	_direction = glm::normalize(mouseCoords - centerPosition);
}

void Players::init(glm::vec2 position, Engine::Input* input, Engine::Camera camera, float speed /*= TANK_SPEED*/, float damage /*= TANK_DAMAGE*/, float health /*= TANK_HEALTH*/)
{
	_speed = speed;
	_position = position;
	_input = input;
	_camera = camera;
	_damage = damage;
	_health = health;


}


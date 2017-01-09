#include "Players.h"
#include <SDL.h>
#include<iostream>
#include "FileLoad.h"
Players::Players()
{
}


Players::~Players()
{
}


void Players::update(const std::vector<std::string>& harta, const std::vector<Players*>& players,
	const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxess)
{
	//if (this->getDamage() > 5.0f)
		//this->setSpeed(5.0f);

	if (_input->isKeyDown(SDLK_w) && _input->isKeyDown(SDLK_d))
	{
		_position.y += _speed / 2.0f;
		_position.x += _speed / 2.0f;
		//std::cout << " W S \n" << _speed << std::endl;
	} 
	else if(_input->isKeyDown(SDLK_w) && _input->isKeyDown(SDLK_a))
	{
		_position.y += _speed / 2.0f;
		_position.x -= _speed / 2.0f;
	}

	else if (_input->isKeyDown(SDLK_s) && _input->isKeyDown(SDLK_d))
	{
		_position.y -= _speed / 2.0f;
		_position.x += _speed / 2.0f;
	}
	else if (_input->isKeyDown(SDLK_s) && _input->isKeyDown(SDLK_a))
	{
		_position.y -= _speed / 2.0f;
		_position.x -= _speed / 2.0f;
	} 
	else 
	{
		if (_input->isKeyDown(SDLK_w))
			_position.y += _speed;

		else if (_input->isKeyDown(SDLK_s))
			_position.y -= _speed;

		if (_input->isKeyDown(SDLK_a))
			_position.x -= _speed;

		else if (_input->isKeyDown(SDLK_d))
			_position.x += _speed;
	}
	

	glm::vec2 mouseCoords = _input->getMouseCoords();
	mouseCoords = _camera->convertToWorldCoordonates(mouseCoords);


	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);

	_direction = glm::normalize(mouseCoords - centerPosition);

	_guns[0]->update(_input->isKeyDown(SDL_BUTTON_LEFT),
		centerPosition,
		_direction,
		*_bullets, harta);

	collideWithMap(harta);
	
}
void Players::initGun(Artillery* gun)
{
	_guns.push_back(gun);
	//if no gun, just equip
	if (_currentIndex == -1)
		_currentIndex = 0;
}

void Players::drawP(Engine::DrawSprites& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = TANK_WIDTH;
	destRect.w = TANK_HEIGHT;

	Engine::Color color;
	color.R = 255;
	color.G = 255;
	color.B = 255;
	color.A = 255;

	spriteBatch.draw(destRect, uvRect, Engine::FileLoad::getTexture("Assets/tank.png").id, 0.0f, color, _direction);
}

void Players::initTankTypes(TankType tankType)
{
	switch (tankType)
	{
	case TankType::DEFAULT:
		_health = TANK_HEALTH;
		_speed = TANK_SPEED;
		_damage = TANK_DAMAGE;
		_isInvulnerable = false;
		_isShielded = false;
		break;
	case TankType::PANZER:
		_isInvulnerable = false;
		_isShielded = false;
		break;
	case TankType::SPEEDRUNNER:
		_isInvulnerable = false;
		_isShielded = false;
		break;
	case TankType::MOTHER_RUSSIA:
		_isInvulnerable = false;
		_isShielded = false;
		break;
	case TankType::RANDOM:
		break;
	default:
		break;
	}
}

void Players::init(glm::vec2 position, Engine::Input* input, Engine::Camera* camera, std::vector<Projectiles>* bullets,
	TankType tankType /* = DEFAULT */, float speed /*= TANK_SPEED*/, float damage /*= TANK_DAMAGE*/, float health /*= TANK_HEALTH*/)
{
	_speed = speed;
	_position = position;
	_input = input;
	_camera = camera;
	_damage = damage;
	_health = health;
	_bullets = bullets;
	_textureID = Engine::FileLoad::getTexture("Assets/tank.png").id;


}


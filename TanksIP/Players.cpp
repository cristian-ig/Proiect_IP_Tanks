#include "Players.h"
#include <SDL.h>
#include<iostream>
#include "FileLoad.h"
Players::Players(){

}


Players::~Players()
{
}


void Players::update(const std::vector<std::string>& harta, const std::vector<Players*>& players,
	const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxess, 
	 std::vector<Projectiles>& bullets, GameState gamestate)
{
	//if (this->getDamage() > 5.0f)
		//this->setSpeed(5.0f);

	glm::vec2 mouseCoords = _input->getMouseCoords();

	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);


	if (nPlayer == 1) {
		if (_input->isKeyDown(SDLK_q)) {
			//cadran 1
			if (_direction.x >= 0 && _direction.y >= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 2
			else if (_direction.x <= 0 && _direction.y >= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 3
			else if (_direction.x <= 0 && _direction.y <= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 4
			else if (_direction.x >= 0 && _direction.y <= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
		}
		else if (_input->isKeyDown(SDLK_e)) {
			//cadran 1
			if (_direction.x >= 0 && _direction.y >= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 2
			else if (_direction.x <= 0 && _direction.y >= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 3
			else if (_direction.x <= 0 && _direction.y <= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 4
			else if (_direction.x >= 0 && _direction.y <= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
		}else
		if (_input->isKeyDown(SDLK_w) && _input->isKeyDown(SDLK_d))
		{
			_position.y += _speed / 2.0f;
			_position.x += _speed / 2.0f;
			_direction = glm::vec2(1.0f, 1.0f);
			//std::cout << " W S \n" << _speed << std::endl;
		}
		else if (_input->isKeyDown(SDLK_w) && _input->isKeyDown(SDLK_a))
		{
			_position.y += _speed / 2.0f;
			_position.x -= _speed / 2.0f;
			_direction = glm::vec2(-1.0f, 1.0f);
		}

		else if (_input->isKeyDown(SDLK_s) && _input->isKeyDown(SDLK_d))
		{
			_position.y -= _speed / 2.0f;
			_position.x += _speed / 2.0f;
			_direction = glm::vec2(1.0f, -1.0f);
		}
		else if (_input->isKeyDown(SDLK_s) && _input->isKeyDown(SDLK_a))
		{
			_position.y -= _speed / 2.0f;
			_position.x -= _speed / 2.0f;
			_direction = glm::vec2(-1.0f, -1.0f);
		}
		if (_input->isKeyDown(SDLK_w))
		{
			if (gamestate == GameState::SINGLEPLAYER)
			{
				_position += _direction*_speed;
			}
			else 
			{
				_position.y += _speed;
				_direction = glm::vec2(0.0f, 1.0f);
			}
		}
		else if (_input->isKeyDown(SDLK_s))
		{

			if (gamestate == GameState::SINGLEPLAYER)
			{
				_position.y -= _speed / 2.0f;

			}
			else
			{
				_position.y -= _speed;
				_direction = glm::vec2(0.0f, -1.0f);
			}
		}
		else if (_input->isKeyDown(SDLK_a))
		{
			_position.x -= _speed;
			if (gamestate == GameState::MULTYPLAYER)
				_direction = glm::vec2(-1.0f, 0.0f);
		}
		else if (_input->isKeyDown(SDLK_d))
		{
			_position.x += _speed;
			if (gamestate == GameState::MULTYPLAYER)
				_direction = glm::vec2(1.0f, 0.0f);
		}
	

	if (gamestate == GameState::SINGLEPLAYER) {

		mouseCoords = _camera->convertToWorldCoordonates(mouseCoords);
		_direction = glm::normalize(mouseCoords - centerPosition);

	}

	_guns[0]->update(_input->isKeyDown(SDLK_SPACE),
		centerPosition,
		_direction,
		*_bullets, harta, gamestate);
	_direction = glm::normalize(_direction);

}
	else
	{
		if (_input->isKeyDown(SDLK_KP_1)) {
			//cadran 1
			if (_direction.x >= 0 && _direction.y >= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 2
			else if (_direction.x <= 0 && _direction.y >= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 3
			else if (_direction.x <= 0 && _direction.y <= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 4
			else if (_direction.x >= 0 && _direction.y <= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
		}else if(_input->isKeyDown(SDLK_KP_3)) {
			//cadran 1
			if (_direction.x >= 0 && _direction.y >= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 2
			else if (_direction.x <= 0 && _direction.y >= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x += players[0]->getSpeed() / 100.0f;
			}
			//cadran 3
			else if (_direction.x <= 0 && _direction.y <= 0) {
				_direction.y += players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
			//cadran 4
			else if (_direction.x >= 0 && _direction.y <= 0) {
				_direction.y -= players[0]->getSpeed() / 100.0f;
				_direction.x -= players[0]->getSpeed() / 100.0f;
			}
		}
		else

		if (_input->isKeyDown(SDLK_UP) && _input->isKeyDown(SDLK_RIGHT))
		{
			_position.y += _speed / 2.0f;
			_position.x += _speed / 2.0f;
			_direction = glm::vec2(1.0f, 1.0f);
			//std::cout << " W S \n" << _speed << std::endl;
		}
		else if (_input->isKeyDown(SDLK_UP) && _input->isKeyDown(SDLK_LEFT))
		{
			_position.y += _speed / 2.0f;
			_position.x -= _speed / 2.0f;
			_direction = glm::vec2(-1.0f, 1.0f);
		}

		else if (_input->isKeyDown(SDLK_DOWN) && _input->isKeyDown(SDLK_RIGHT))
		{
			_position.y -= _speed / 2.0f;
			_position.x += _speed / 2.0f;
			_direction = glm::vec2(1.0f, -1.0f);
		}
		else if (_input->isKeyDown(SDLK_DOWN) && _input->isKeyDown(SDLK_LEFT))
		{
			_position.y -= _speed / 2.0f;
			_position.x -= _speed / 2.0f;
			_direction = glm::vec2(-1.0f, -1.0f);
		}
		else
		{
			if (_input->isKeyDown(SDLK_UP)) {
				_position.y += _speed;
				_direction = glm::vec2(0.0f, 1.0f);
			}


			else if (_input->isKeyDown(SDLK_DOWN)) {
				_position.y -= _speed;
				_direction = glm::vec2(0.0f, -1.0f);
			}

			if (_input->isKeyDown(SDLK_LEFT)) {
				_position.x -= _speed;
				_direction = glm::vec2(-1.0f,0.0f);
			}

			else if (_input->isKeyDown(SDLK_RIGHT)) {
				_position.x += _speed;
				_direction = glm::vec2(1.0f, 0.0f);
			}
		}

	
		_guns[0]->update(_input->isKeyDown(SDLK_KP_2),
			centerPosition,
			_direction,
			*_bullets, harta, gamestate);
		_direction = glm::normalize(_direction);
	}
	
	//_direction = glm::normalize(_direction);

	

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

	spriteBatch.draw(destRect, uvRect, _textureID, 0.0f, color, _direction);
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
		_textureID = Engine::FileLoad::getTexture("Assets/default.png").id;
		break;
	case TankType::PANZER:
		_health = TANK_HEALTH + 100;
		_speed = TANK_SPEED/1.2f;
		_damage = TANK_DAMAGE+20;
		_isInvulnerable = false;
		_isShielded = false;
		_textureID = Engine::FileLoad::getTexture("Assets/panzer.png").id;
		break;
	case TankType::SPEEDRUNNER:
		_health = TANK_HEALTH/3.0f;
		_speed = TANK_SPEED*2.0f;
		_damage = TANK_DAMAGE*1.5f;
		_isInvulnerable = false;
		_isShielded = false;
		_textureID = Engine::FileLoad::getTexture("Assets/speedrunner.png").id;
		break;
	case TankType::MOTHER_RUSSIA:
		_health = TANK_HEALTH*2.0f;
		_speed = TANK_SPEED/3.0f;
		_damage = TANK_DAMAGE - 20;
		_isInvulnerable = false;
		_isShielded = false;
		_textureID = Engine::FileLoad::getTexture("Assets/motherrussia.png").id;
		break;
	case TankType::RANDOM:
		break;
	default:
		break;
	}
}

void Players::init(glm::vec2 position, Engine::Input* input, Engine::Camera* camera, std::vector<Projectiles>* bullets,
	TankType tankType /* = DEFAULT */)
{
	initTankTypes(tankType);
//	_speed = speed;
	_position = position;
	_direction = glm::vec2(1.0f, 0.0f);
	_input = input;
	_camera = camera;
	//_damage = damage;
	//_health = health;
	_bullets = bullets;
	
	//_textureID = Engine::FileLoad::getTexture("Assets/panzer.png").id;


}


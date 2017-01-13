#include "Enemys.h"
#include "Players.h"
#include "FileLoad.h"
#include "Artillery.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <ctime>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

Enemys::Enemys()
{
}


Enemys::~Enemys()
{
}
void Enemys::initGun(Artillery* gun, bool isFromPlayer)
{
	_guns.push_back(gun);
	//if no gun, just equip
	if (_currentIndex == -1)
		_currentIndex = 0;
}
void Enemys::update(const std::vector<std::string>& harta, const std::vector<Players*>& players, 
	const std::vector<Enemys*>& enemys, const std::vector<BonusBox*>& bonusBoxes, 
	const std::vector<Projectiles>& bullets, GameState gamestate)
{

#if 0
//find closest player
	Players* closestTarget = getNearestPlayer(players);
	
	 glm::ivec2 closestPlayerPos = closestTarget->getPosition() / TANK_WIDTH;
	 glm::ivec2 start = this->getPosition() / TANK_WIDTH;
	 _path = findPath(start, closestPlayerPos, harta);

	 if (_path.size())
	 {
		 glm::ivec2 vectorPath = _path.back()->tile;
		 if (_position.x < vectorPath.x) _direction.x = 1.0f;
		 if (_position.x > vectorPath.x) _direction.x = -1.0f;
		 if (_position.y < vectorPath.y) _direction.y = 1.0f;
		 if (_position.y < vectorPath.y) _direction.y = -1.0f;
	 }

	 else
	 {
		 //add second AI
	 }

#endif
	Players* closestTarget = getNearestPlayer(players);
	BonusBox* closestBonus = getNearestBonus(bonusBoxes);
	Projectiles* closestBullet = getNearestProjectile(bullets);

	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, _direction));
	glm::vec2 centerPosition = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-60.0f, 60.0f);

	// If we found a player, move towards him
	if (closestTarget != nullptr && pitagoraDistance(closestTarget) < 200.0f)
	{
		// Get the direction vector twoards the player
	//	_direction = glm::normalize(closestTarget->getPosition() - _position);
		_guns[0]->update(true, centerPosition, _direction, *_bullets, harta, gamestate);
	}
	else if (closestBonus != nullptr && pitagoraDistance(closestBonus) < 400.0f)// && pitagoraDistance(closestTarget) <= 200.0f)
	{
		// Get the direction vector twoards the bonusBox
		_direction = glm::normalize(closestBonus->getPosition() - _position);

	}
	bool OK = false;
	for (size_t i = 0; i < players.size(); i++)
	{
		if (this->collideWithEntity(players[i]))
			 OK = true;
	}

	for (size_t i = 0; i < enemys.size(); i++)
	{
		if (this != enemys[i] && this->collideWithEntity(enemys[i]))
			OK = true;
	}
	if (OK && _timer >= 200)
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_timer = 0;
	}

	if (collideWithMap(harta) )
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
	else if (_timer >= 300)
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_timer = 0;
	}
		_timer++;
		

	//std::cout << _timer << std::endl;

	if (_direction.y < 0.0f) angle = -angle;
	//std::cout << angle << std::endl;
	//smooth moviment
	if ((angle > 0.1f) && (angle < 1.30f) || (angle > 1.7f) && (angle < 3.1f) || (angle < -0.1f) && (angle > -1.30f) || (angle < -1.7f) && (angle > -3.10f))
	{
		_position += _direction * _speed / 2.0f;
	}
	else
	{
		_position += _direction * _speed;
	}

	//_guns[0]->update(true, centerPosition, _direction, *_bullets);
	//ADD AI
	
}

void Enemys::init(glm::vec2 position, std::vector<Projectiles>* bullets, float speed, float damage, float health)
{
	_position = position;
	_speed = speed;
	_damage = damage;
	_health = health;
	_bullets = bullets;
	_textureID = Engine::FileLoad::getTexture("Assets/tank.png").id;
}

Players* Enemys::getNearestPlayer(const std::vector<Players*>& players)
{
	Players* closestPlayer = nullptr;
	float minDist = 999999999.0f;

	//AI
	for (size_t i = 0; i < players.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = players[i]->getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this person is closer than the closest person, this is the new closest
		if (distance < minDist) {
			minDist = distance;
			closestPlayer = players[i];
		}
	}

	return closestPlayer;
}

BonusBox* Enemys::getNearestBonus(const std::vector<BonusBox*>& bonusBoxes)
{
	BonusBox* closestBonus = nullptr;
	float minDist = 999999999.0f;

	//AI
	for (size_t i = 0; i < bonusBoxes.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = bonusBoxes[i]->getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this Box is closer than the closest person, this is the new closest
		if (distance < minDist) {
			minDist = distance;
			closestBonus = bonusBoxes[i];
		}
	}

	return closestBonus;
}


Projectiles* Enemys::getNearestProjectile(const std::vector<Projectiles>& bullets)
{
	Projectiles* closestProjectile = nullptr;
	float minDist = 999999999.0f;

	//AI
	for (size_t i = 0; i < bullets.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = bullets[i].getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this person is closer than the closest person, this is the new closest
		if (distance < minDist) {
			minDist = distance;
			closestProjectile = (Projectiles*)&bullets[i];
		}
	}

	return closestProjectile;
}

void Enemys::dogeBullet()
{
	return;
}

float Enemys::pitagoraDistance(Players* player)
{
	float distX = this->getPosition().x - player->getPosition().x;
	float distY = this->getPosition().y - player->getPosition().y;

	return sqrt((distX * distX) + (distY * distY)); //pitagora ftw
}

float Enemys::pitagoraDistance(BonusBox* BB)
{
	float distX = this->getPosition().x - BB->getPosition().x;
	float distY = this->getPosition().y - BB->getPosition().y;

	return sqrt((distX * distX) + (distY * distY)); //pitagora ftw
}



float Enemys::pitagoraDistance(Projectiles* bullet)
{
	float distX = this->getPosition().x - bullet->getPosition().x;
	float distY = this->getPosition().y - bullet->getPosition().y;

	return sqrt((distX * distX) + (distY * distY)); //pitagora ftw
}

float Enemys::vectorDistance(glm::vec2 vector1, glm::vec2 vector2)
{
	float Xdist = vector1.x - vector2.x;
	float Ydist = vector1.y - vector2.y;
	return sqrt(Xdist * Xdist + Ydist * Ydist);

}
#if 0
int Enemys::nodSorter(nod *n0, nod *n1)
{
	if (n1->fCost < n0->fCost) return 1;
	if (n1->fCost > n0->fCost) return -1;
	return 0;
}

void listSorter(std::list<nod*>& alist)
{
	std::list<nod*>::iterator it;
	for each (auto it in alist)
	{
		if (it + 1 != nullptr) {
			float first = it->fCost;
			float second = (it + 1)->fCost;
			if (first > second) {
				float aux = first;
				first = second;
				second = aux;
			}
		}
	}
}

bool Enemys::isInList(const std::list<nod*>& list, const glm::ivec2& vector)
{
	for (nod* n : list)
		if (n->tile == vector)
			return true;

	return false;
}

 std::list<nod*> Enemys::findPath(glm::ivec2 start, glm::ivec2 goal, const std::vector<std::string>& harta)
 {
	 std::list<nod*> closedList; //tileuri 
	 std::list<nod*> openList; //tileuri pe care ne am deplasat spre goal
	
	float HC = vectorDistance(start, goal);
	//static_cast<float>(HC = glm::distance(start, goal));

	nod* current = new nod(start, nullptr, 0.0f, HC);
	openList.push_back(current);

	while (openList.size() > 0)
	{
		current = openList.back();
	    listSorter(openList);
		if (current->tile == goal)
		{
			std::cout << "happened";
			std::list<nod*> path;

			while (current->parent != nullptr)
			{
				path.push_back(current);
				current = current->parent;
			}

			openList.clear();
			closedList.clear();
			return path;
		}
		openList.remove(current);
		closedList.push_back(current);

		for (int i = 0; i < 9; i++)
		{
			if (i == 4) continue;

			int x = current->tile.x;
			int y = current->tile.y;

			int xi = (i % 3) - 1; //values on the x axes -1 0 1
			int yi = (i / 3) - 1; //values on the y axes -1 0 1

								  /*auto charTile = Harta::getMapTile(glm::ivec2((x + xi) * TILE_WIDTH, (y + yi) * TILE_WIDTH));*/
			//std::cout << harta[2][1];
			//std::cout <<  harta[(x + xi )/ TILE_WIDTH][(y + yi ) / TILE_WIDTH];
			char verifTile = harta[(x + xi) / TILE_WIDTH][(y + yi) / TILE_WIDTH];
			//glm::ivec2 verifyingTile = glm::ivec2(verifTile, 0); //x is for tile, use this later ofr player pos
			if (verifTile == NULL) continue;
			if (verifTile == 'W' || verifTile == 'E') continue;
			//TODO: ADD IF VERIFYIUNG TILE IS A PLAYER
			//for( entity : Entity) //for each entity in Entity
			//tankPos == entity.getposition();
			//if(verifyingtile == tankPos[i]


			glm::ivec2 a = glm::vec2(((x + xi) * TILE_WIDTH) , ((y + yi) * TILE_WIDTH) );
			float gCost = current->gCost + vectorDistance(current->tile, a); //distance between tiles (1 or sqrt 2 ..~1.4) 
			float hCost = vectorDistance(a, goal);
			
			nod* n = new nod(a, current, gCost, hCost);
			if (isInList(closedList, a) && gCost >= n->gCost) continue;
			if (!isInList(closedList, a) || gCost < n->gCost)
				openList.push_back(n);
		}

	}
	return _path;
 }


#endif
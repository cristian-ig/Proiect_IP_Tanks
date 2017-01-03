#include "Entity.h"
#include <algorithm>
#include "DrawClass.h"

	// The minimum distance before a collision occurs
const float MIN_DISTANCE_X = TANK_WIDTH / 2.0f + TILE_RADIUS;
const float MIN_DISTANCE_Y = TANK_HEIGHT / 2.0f + TILE_RADIUS;

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::draw()
{
	
	
	Engine::DrawClass _drawHandler;

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
	_drawHandler.init();
	_drawHandler.begin();
	_drawHandler.addObj(destRect, uvRect, _textureID, color,_direction);
	_drawHandler.end();
	_drawHandler.renderBatch();
}

bool Entity::applyDamage(float damage)
{
	if (!_isInvulnerable)
	{

		if (_isShielded)
			_health -= damage / 2.5f; //ia 1/4 din dmg
		else
			_health -= damage;
	
	// If we died, return True
		if (_health <= 0)
			return true;
	}

	if (damage == BONUS_ONE_HIT_KILL) //invinc se anuleaza cu OHK
		_health -= TANK_DAMAGE;

	return false;
}
//AABB, returns true if there was a collision
bool Entity::collideWithMap(const std::vector<std::string>& harta)
{
	std::vector<glm::vec2> collideTilePositions;

	// Check the four corners
	// First corner
	checkTilePosition(harta,
		collideTilePositions,
		_position.x+getSpeed(),
		_position.y+getSpeed());
	// Second Corner
	checkTilePosition(harta,
		collideTilePositions,
		_position.x + TANK_WIDTH,
		_position.y);

	// Third Corner
	checkTilePosition(harta,
		collideTilePositions,
		_position.x,
		_position.y + TANK_HEIGHT);

	// Third Corner
	checkTilePosition(harta,
		collideTilePositions,
		_position.x + TANK_WIDTH,
		_position.y + TANK_HEIGHT);

	// Check if there was no collision
	if (collideTilePositions.size() == 0) 
		return false;

	// Do the collision
	for (size_t i = 0; i < collideTilePositions.size(); i++) 
		collideWithTile(collideTilePositions[i]);

	return true;
}

bool Entity::collideWithEntity(Entity* entity)
{
	// Center position of this agent
	glm::vec2 centerPosA = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);
	// Center position of the parameter agent
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);

	// Distance vector between the two agents
	glm::vec2 distVec = centerPosA - centerPosB;

	// Length of the distance vector
	//float distance = glm::length(distVec);

	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	glm::vec2 collisionDepth = glm::vec2(MIN_DISTANCE_X - glm::length(distVec), MIN_DISTANCE_Y - glm::length(distVec));
	// If collision depth > 0 then we did collide
	if (xDepth > 0 && yDepth > 0) {

		// Get the direction times the collision depth so we can push them away from each other
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		// Push them in opposite directions
		_position += collisionDepthVec / 2.0f;
		entity->_position -= collisionDepthVec / 2.0f;

		return true;
	}
	return false;
}

void Entity::checkTilePosition(const std::vector<std::string>& harta, std::vector<glm::vec2>& collideTilePositions, float x, float y)
{
	// Get the position of this corner in grid-space
	glm::vec2 gridPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	// If we are outside the world, just return
	if (gridPos.x < 0 || gridPos.x >= harta[0].size() ||
		gridPos.y < 0 || gridPos.y >= harta.size()) {
		return;
	}

	// If this is not an air tile, we should collide with it
	if (harta[gridPos.y][gridPos.x] != '.') {
		collideTilePositions.push_back(gridPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Entity::collideWithTile(glm::vec2 tilePos)
{

	// Center position of the agent
	glm::vec2 centerAgentPos = _position + glm::vec2(TANK_WIDTH / 2.0f, TANK_HEIGHT / 2.0f);
	// Vector from the agent to the tile
	glm::vec2 distVec = centerAgentPos - tilePos;

	// Get the depth of the collision
	float xDepth = MIN_DISTANCE_X - abs(distVec.x);
	float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

	// If both the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) {

		// Check which collision depth is less
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			// X collsion depth is smaller so we push in X direction
			if (distVec.x < 0) {
				_position.x -= xDepth;
			}
			else {
				_position.x += xDepth;
			}
		}
		else {
			// Y collsion depth is smaller so we push in X direction
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
		}
	}
}

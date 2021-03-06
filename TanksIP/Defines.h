#pragma once
//Window
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//Map
#define TILE_WIDTH 32.0f
#define TILE_RADIUS  (float)TILE_WIDTH / 2.0f
//Tanks
#define TANK_WIDTH 24.0f
#define TANK_HEIGHT 18.0f
#define TANK_SPEED 1.5f
#define TANK_DAMAGE 100.0f
#define TANK_HEALTH 500.0f
#define TANK_MAX_SPEED 7.0f
//Bonus Boxes
#define MAX_BONUSES 10 //number of bonuses
#define BONUS_BOX_WIDTH 16.0f //box dimensions
#define BONUS_DAMAGE 100.0f
#define	BONUS_DAMAGE_PLUS 250.0f
#define BONUS_HEAL 100.0f
#define BONUS_HEAL_PLUS 300.0f
#define BONUS_MAX_HEALTH 100.0f
#define BONUS_SPEED 1.0f
#define BONUS_SPEED_PLUS 3.0f
#define BONUS_ONE_HIT_KILL 9999.0f
#define BONUS_DURATION 600.0F // secunde * 60
//Bullet
#define BULLET_RADIUS 5.0f
#define REFLECTIONS 4
#define BULLET_SPEED 1.5*TANK_SPEED
//GameState

enum class GameState {
	MENU,
	MAIN,
	SINGLEPLAYER,
	MULTYPLAYER,
	EXIT
};
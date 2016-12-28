#pragma once
#include "Entity.h"
namespace tanks{

class Enemys : public Entity
{
public:
	Enemys();
	~Enemys();
	void update();
};

}
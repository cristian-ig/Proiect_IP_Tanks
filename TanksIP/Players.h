#pragma once
#include "Entity.h"

namespace tanks {

class Players : public Entity
{
public:
	Players();
	~Players();

	void update();
};

}
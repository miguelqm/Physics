#pragma once

#include "Entity.h"

namespace Physics
{
	class Box : public Entity
	{
	public:
		void Setup(b2Vec2 dimensions[], int count);
	};
}

#pragma once

#include "Entity.h"

namespace Physics
{
	class Circle : public Entity
	{
	public:
		void Setup(b2Vec2 dimensions[], int count);
	};
}


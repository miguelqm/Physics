#pragma once
#include "Entity.h"

namespace Physics
{
	class PhysPolygon : public Entity
	{
		void Setup(b2Vec2 dimensions[], int count);
	};
}

#include "Chain.h"

namespace Physics
{
	void Chain::Setup(b2Vec2 dimensions[], int count)
	{
		dragCoeficient = 0.05f;

		shape = new b2ChainShape();
		((b2ChainShape*)shape)->CreateChain(dimensions, count);
	}
}
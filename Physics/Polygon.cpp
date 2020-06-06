#include "Polygon.h"

namespace Physics
{
	void PhysPolygon::Setup(b2Vec2 dimensions[], int count)
	{
		dragCoeficient = 1.05f;

		shape = new b2PolygonShape();
		((b2PolygonShape*)shape)->Set(dimensions, count);
	}
}
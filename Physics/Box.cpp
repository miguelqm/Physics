#include "Box.h"

namespace Physics
{
	void Box::Setup(b2Vec2 dimensions[], int count)
	{
		dragCoeficient = 1.05f;
			
		shape = new b2PolygonShape();
		((b2PolygonShape*)shape)->SetAsBox(dimensions[0].x, dimensions[0].y);
	}
}
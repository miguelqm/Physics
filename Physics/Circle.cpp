#include "Circle.h"

namespace Physics
{
	void Circle::Setup(b2Vec2 dimensions[], int count)
	{
		dragCoeficient = 0.47;

		shape = new b2CircleShape();
		((b2CircleShape*)shape)->m_radius = dimensions[0].Length();
	}
}
#pragma once

#include "box2d/box2d.h"

namespace Physics
{
	class World : public b2World
	{
	private:
		b2Vec2 b2dGravity;
		float b2dTimeStep;
		int32 b2dVelocityIterations;
		int32 b2dPositionIterations;
	public:
		World();
		void SetBorders(b2Vec2 vector);
		void SetBorders(float width, float height);
		void Step();
		void ClearBodies(b2BodyType type = b2BodyType::b2_all);
		void ApplyForceToAll(b2Vec2 force);
		void genApplyForceToAll(void (b2Body::*f)(b2Vec2, bool), b2Vec2 force);
	};
}

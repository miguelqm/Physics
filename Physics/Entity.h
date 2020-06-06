#pragma once

#include "Settings.h"
#include "World.h"

namespace Physics
{
	class Entity
	{
	public:
		b2World* ownerWorld;
		b2Body* body;
		b2Shape* shape;

		b2Vec2 netForce;
		float dragCoeficient;

		virtual void Setup(b2Vec2 dimensions[], int count = 1) = 0;

		void Init(b2World* world, float x, float y, b2Vec2 dimensions[], int count = 1, float angle = 0.0f, float density = DEF_DENSITY, float friction = DEF_FRICTION, float restitution = DEF_RESTITUTION);
		void Destroy();
		void ApplyDrag();
	};
}


#include "Entity.h"

namespace Physics
{
	void Entity::Init(b2World* world, float x, float y, b2Vec2 dimensions[], int count, float angle, float density, float friction, float restitution)
	{
		ownerWorld = world;
		dragCoeficient = DRAG_COEFICIENT;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x, y);
		bodyDef.angle = angle * b2_pi/180.0F;
		bodyDef.userData.pointer = (uintptr_t)this;

		body = world->CreateBody(&bodyDef);
		//body->SetBullet(true);
		//body->SetLinearDamping(0.001);

		Setup(dimensions, count);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		

		body->CreateFixture(&fixtureDef);
	}

	void Entity::Destroy()
	{
		ownerWorld->DestroyBody(body);
	}

	void Entity::ApplyDrag()
	{
		float dragForce;
		b2Vec2 appliedDrag;
		b2Vec2 vDragAngle;
		float p, A, Cd, v;

		p = FLUID_DENSITY_OF_AIR;// * getAtmosphericDensity(ent.getAltitude()); // density of the fluid
		A = 1.0f;
		Cd = dragCoeficient;
		v = body->GetLinearVelocity().LengthSquared();
		dragForce = 0.5f * p * v * Cd * A;
		if (dragForce != 0)
		{
			appliedDrag = body->GetLinearVelocity();
			appliedDrag.Normalize();
			appliedDrag *= -dragForce;
			body->ApplyForceToCenter(appliedDrag, true);
		}
	}
}
#include "World.h"
#include "Box2d.h"
#include "Settings.h"

namespace Physics
{
	World::World() : b2World(b2Vec2(GRAVITY_X, GRAVITY_Y))
	{
		bool x = GetContinuousPhysics();
		b2dTimeStep = TIME_STEP;
		b2dVelocityIterations = VEL_ITERATIONS;
		b2dPositionIterations = POS_ITERATIONS;
	}

	void World::SetBorders(b2Vec2 vector)
	{
		SetBorders(vector.x, vector.y);
	}

	void World::SetBorders(float width, float height)
	{
		//width /= PTM_RATIO;
		//height /= PTM_RATIO;
		b2Body* body;
		b2Body* edge = nullptr;
		b2Vec2 pos;
		b2Fixture* fixture;
		b2Shape::Type type;
		for (body = GetBodyList(); body != NULL; body = body->GetNext())
		{
			fixture = body->GetFixtureList();
			type = fixture->GetType();
			if (type == b2Shape::Type::e_edge)
			{
				edge = body;
			}
			else
			{
				pos = body->GetPosition();
				if (pos.x > width || pos.y > height)
					body->SetTransform(b2Vec2(width / 2, height / 2), body->GetAngle());
			}
		}
		if(edge != nullptr)
			DestroyBody(edge);

		b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
		b2Vec2 lowerRightCorner = b2Vec2(width, 0);
		b2Vec2 upperLeftCorner = b2Vec2(0, height);
		b2Vec2 upperRightCorner = b2Vec2(width, height);

		b2BodyDef b2dScreenBorderDef;
		b2dScreenBorderDef.position.Set(0, 0);

		b2Body* b2dScreenBorderBody;
		b2dScreenBorderBody = CreateBody(&b2dScreenBorderDef);
		b2dScreenBorderBody->DestroyFixture(b2dScreenBorderBody->GetFixtureList());

		b2EdgeShape screenBorderShape;
		screenBorderShape.Set(lowerLeftCorner, lowerRightCorner);
		b2dScreenBorderBody->CreateFixture(&screenBorderShape, 0);
		screenBorderShape.Set(lowerRightCorner, upperRightCorner);
		b2dScreenBorderBody->CreateFixture(&screenBorderShape, 0);
		screenBorderShape.Set(upperRightCorner, upperLeftCorner);
		b2dScreenBorderBody->CreateFixture(&screenBorderShape, 0);
		screenBorderShape.Set(upperLeftCorner, lowerLeftCorner);
		b2dScreenBorderBody->CreateFixture(&screenBorderShape, 0);
	}

	void World::Step()
	{
		b2World::Step(b2dTimeStep, b2dVelocityIterations, b2dPositionIterations);
	}

	void World::ClearBodies(b2BodyType type)
	{
		b2Body* body = GetBodyList();
		b2Body* next;
		while (body != nullptr)
		{
			next = body->GetNext();
			if(body->GetType() == type || body->GetType() == b2BodyType::b2_all)
				DestroyBody(body);
			body = next;
		}
	}

	void World::ApplyForceToAll(b2Vec2 force)
	{
		b2Body* body;
		for (body = GetBodyList(); body != NULL; body = body->GetNext())
		{
			body->ApplyForceToCenter(force, true);
		}
	}

	void World::genApplyForceToAll(void (b2Body::*m)(b2Vec2, bool), b2Vec2 force)
	{
		b2Body* body;
		for (body = GetBodyList(); body != NULL; body = body->GetNext())
		{
			(body->*m)(force, true);
		}
	}
}
#include "Engine.h"
#include "box2d/box2d.h"
#include "Utils.h"
#include "Box.h"
#include "Circle.h"
#include "Polygon.h"
#include "Chain.h"
#include "Windowsx.h"

#define LMBUTTON 1;
#define RMBUTTON 2;

using namespace Rendering;
using namespace Physics;


template<class ShapeClass>
ShapeClass* CreateObject(b2World* world, float x, float y, b2Vec2 dimensions[], int count = 1, float angle = 0.0f, float density = DEF_DENSITY, float friction = DEF_FRICTION, float restitution = DEF_RESTITUTION)
{
	ShapeClass* newObj = new ShapeClass();
	newObj->Init(world, x, y, dimensions, count, angle, density, friction, restitution);
	
	return newObj;
}

void Engine::CreateWorld(HWND hWnd)
{
	isDrawing = true;
	isBoundaries = STARTING_FORCES;
	isGravity = STARTING_FORCES;
	isDrag = !STARTING_FORCES;
	isAttraction = !STARTING_FORCES;
	isRepulsion = !STARTING_FORCES;
	isBlackhole = !STARTING_FORCES; 

	lastSpringBody = nullptr;

	myWorld = new Physics::World();
	myWindow = new Rendering::MyWindow(hWnd);

	myWorld->SetGravity(isGravity ? b2Vec2(GRAVITY_X, GRAVITY_Y) : b2Vec2(0, 0));

	Resize();

	sf::Vector2f winSize = (sf::Vector2f)myWindow->getSize();
	Box* b;
	b2Vec2 wSize = VectorSFToB2f(winSize);
	//b = CreateObject<Box>(myWorld, wSize.x / 2 , 0, &b2Vec2((wSize.x/2)-0.04, 0.01), 1, 0, 888);
	//b->body->SetLinearDamping(999999999);
	//b->body->SetType(b2BodyType::b2_kinematicBody);
	//b->body->SetAngularDamping(999999999);
	//b = CreateObject<Box>(myWorld, 0, wSize.y / 2, &b2Vec2(0.01, (wSize.y / 2) - 0.02), 1, 0, 888);
	//b->body->SetLinearDamping(999999999);
	//b->body->SetAngularDamping(999999999);
	//b->body->SetType(b2BodyType::b2_kinematicBody);
	//b = CreateObject<Box>(myWorld, wSize.x, wSize.y / 2, &b2Vec2(0.01, (wSize.y / 2) - 0.02), 1, 0, 888);
	//b->body->SetLinearDamping(999999999);
	//b->body->SetAngularDamping(999999999);
	//b->body->SetType(b2BodyType::b2_kinematicBody);
	//b = CreateObject<Box>(myWorld, wSize.x / 2, wSize.y, &b2Vec2((wSize.x / 2) - 0.04, 0.01), 1, 0, 888);
	//b->body->SetLinearDamping(999999999);
	//b->body->SetAngularDamping(999999999);
	//b->body->SetType(b2BodyType::b2_kinematicBody);

	//b = CreateObject<Box>(myWorld, wSize.x / 2, 5, &b2Vec2(10, 0.02), 1, 0, 8);
	////b->body->SetLinearDamping(999999999);
	//b->body->SetBullet(true);
	
	//b = CreateObject<Box>(myWorld, wSize.x / 2, 4, &b2Vec2(8, 0.02), 1, 0, 888);
	////b->body->SetLinearDamping(999999999);
	//b->body->SetBullet(true); 
	//b = CreateObject<Box>(myWorld, wSize.x / 2, 6, &b2Vec2(6, 0.02), 1, 0, 888);
	////b->body->SetLinearDamping(999999999);
	//b->body->SetBullet(true); 
	//b = CreateObject<Box>(myWorld, wSize.x / 2, 7, &b2Vec2(4, 0.02), 1, 0, 888);
	//b->body->SetLinearDamping(999999999);
	//b->body->SetBullet(true);

	b2Vec2 dim[1]{ b2Vec2(1, 1.4) };
	float x = 2;

	CreateObject<Box>(myWorld, 5, 2, &b2Vec2(0.5, 0.5), 1, 1.15f * b2_pi, 0.05)->body->SetBullet(true);
	//new Box(myWorld, 5, 13, dim, 1.15f * b2_pi);
	
	//CreateObject<Circle>(myWorld, (vec.x / 2) / PTM_RATIO, (vec.y+3 / 2) / PTM_RATIO, &b2Vec2(1, 1));
	//for (int i = 1; i < 19; ++i)
	//{
	//	new Box(myWorld, i*3, 3, 0.9, 0.9, 11*i);
	//	new Circle(myWorld, i*5, 4, 1, 11 * i);
	//}

	b2Vec2 vertices[1000];
	vertices[0].Set(1.0f, 0.0f);
	vertices[1].Set(2.0f, 0.0f);
	vertices[2].Set(2 + sqrt(0.5f), sqrt(0.5f));
	vertices[3].Set(2 + sqrt(0.5f), sqrt(0.5) + 1);
	vertices[4].Set(2.0f, 2* sqrt(0.5f) + 1);
	vertices[5].Set(1.0f, 2 * sqrt(0.5f) + 1);
	vertices[6].Set(1-sqrt(0.5), sqrt(0.5) + 1);
	vertices[7].Set(1 - sqrt(0.5), sqrt(0.5f));

	CreateObject<PhysPolygon>(myWorld, 3, 3, vertices, 8, 0.12f, 0.002);

	x = 0.0f;
	float y = 0.0f;
	for (int i = 0; i < 1000; ++i)
	{
		y = 5+sin(x) - x/9;
		vertices[i].Set(x, y);
		x += 0.1f;
	}
	//vertices[0].Set(0.0f, 0.0f);
	//vertices[1].Set(1.0f, 1.0f);
	//vertices[2].Set(2.0f, 2.5f);
	//vertices[3].Set(3.0f, 4.0f);
	//vertices[4].Set(4.0f, 3.8f);
	//vertices[5].Set(5.0f, 3.5f);
	//vertices[6].Set(6.0f, 2.7f);
	//vertices[7].Set(7.0f, 2.0f);

	 CreateObject<Chain>(myWorld, 0, 0, vertices, 1000);
}

void Engine::Step()
{
	if (isAttraction) Attraction();
	if (isRepulsion) Repulsion();
	if (isDrag) Drag();

	myWorld->Step();
	if (isDrawing)
	{
		//myWindow->SetView(true);
		myWindow->Clear();
		myWindow->DrawShapes(myWorld);
		myWindow->display();
	}
	myWorld->ClearForces();
}

void Engine::Resize(bool bounds)
{
	if (myWindow != nullptr)
	{
		if (bounds)
		{
			//sf::View v = myWindow->getView();
			sf::Vector2f vec = (sf::Vector2f)myWindow->getSize();
			myWorld->SetBorders(VectorSFToB2f(vec));
		}
		else
			ClearStaticBodies();

		myWindow->SetView(true);
	}
}

void Engine::ClearStaticBodies()
{
	myWorld->ClearBodies(b2BodyType::b2_staticBody);
}

void Engine::ClearDynamicBodies()
{
	myWorld->ClearBodies(b2BodyType::b2_dynamicBody);
	lastSpringBody = nullptr;
}

bool AABBCallback::ReportFixture(b2Fixture* fixture)
{
	b2Body* body;
	body = fixture->GetBody();
	b2Vec2 v = b2Vec2(55,55);
	//body->ApplyForce(v, body->GetPosition() + b2Vec2(0.3, -0.3), true);
	return true;
}


void Engine::MouseEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	b2Body* body;
	b2Vec2 point;

	int width = myWindow->getSize().x;
	int height = myWindow->getSize().y;
	
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	point = VectorSFToB2f(sf::Vector2f(xPos, (height - yPos)));
	AABBCallback cb;
	b2AABB box;
	float msClickElapsed;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		tmrMouseButtonClick.Reset();
		ptMouseClickStart = point;
		box.lowerBound = b2Vec2(point.x - 0.01, point.y - 0.01);
		box.upperBound = b2Vec2(point.x + 0.01, point.y + 0.01);
		myWorld->QueryAABB(&cb, box);
		break;
	case WM_LBUTTONUP:
		msClickElapsed = tmrMouseButtonClick.GetMilliseconds()/500;
		ptMouseClickEnd = point;
		point = (ptMouseClickEnd - ptMouseClickStart);
		point *= 1/msClickElapsed;
		myWorld->ApplyForceToAll(point);
		break;
	default:
		break;
	}
	if (wParam == MK_LBUTTON)
	{
		b2Vec2 v = b2Vec2(xPos - width/2, -1 * (yPos - height/2));
	
		//myWorld->ApplyForceToAll(v);
	}
	if (wParam == MK_RBUTTON)
	{
		sf::Vector2f v = myWindow->mapPixelToCoords(sf::Mouse::getPosition(*myWindow));
		//if(isBlackhole)	
			CreateNewBall(v.x, (height - v.y));
		//CreateNewSpringBall(v.x, (height - v.y));
	}
}

LRESULT Engine::ProcessMsgs(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	sf::View v;
	Circle* c;
    switch (message)
    {
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			isAttraction = !isAttraction;
			break;
		case 'R':
			isRepulsion = !isRepulsion;
			break;
		case 'C':
			ClearDynamicBodies();
			break;
		case 'D':
			isDrag = !isDrag;
			break;
		case 'G':
			isGravity = !isGravity;
			myWorld->SetGravity(isGravity ? b2Vec2(GRAVITY_X, GRAVITY_Y) : b2Vec2(0, 0));
			break;
		case 'V':
			isDrawing = !isDrawing;
			break;
		case 'B':
			isBlackhole = !isBlackhole;
			break;
		case VK_ADD:
			v = myWindow->getView();
			v.zoom(0.9);
			myWindow->setView(v);
			break;
		case VK_SUBTRACT:
			v = myWindow->getView();
			v.zoom(1.1);
			myWindow->setView(v);
			break;
		case VK_RIGHT:
			v = myWindow->getView();
			v.move(10, 0);
			myWindow->setView(v);
			break;
		case VK_UP:
			v = myWindow->getView();
			v.move(0, 10);
			myWindow->setView(v);
			break;
		case VK_DOWN:
			v = myWindow->getView();
			v.move(0, -10);
			myWindow->setView(v);
			break;
		case VK_LEFT:
			v = myWindow->getView();
			v.move(-10, 0);
			myWindow->setView(v);
		break; 
		case 'Q':
			isBoundaries = !isBoundaries;
			Resize(isBoundaries);
			break;
		case 'T':
			myWindow->CenterView(myWorld);
			break;
		}
		break;
    case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		MouseEvent(message, wParam, lParam);
        break;
	case WM_SIZE:
        if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED)
            Resize();
        break;
    case WM_EXITSIZEMOVE:
        Resize();
        break;
    }
    return 0;
}

void Engine::Drag()
{
	b2Body* body;
	for (body = myWorld->GetBodyList(); body != NULL; body = body->GetNext())
	{
		if (body->GetType() == b2BodyType::b2_dynamicBody)
		{
			bool a = body->IsAwake();
			Entity* obj = (Entity*)body->GetUserData();
			obj->ApplyDrag();
		}
	}
}

void Engine::Attraction(int sign)
{
	float fGrav;
	float distance;
	b2Body* body;
	b2Body* otherBody;
	b2Vec2 vGravity;
	int numBodies;
	std::vector<b2Body*> bodies;

	bodies = GetDynamicBodies(myWorld);
	numBodies = bodies.size();

	for (int i = 0; i < numBodies; ++i)
	{
		body = bodies[i];
		
		for (int j = 0; j < numBodies; j++)
		{
			otherBody = bodies[j];
			
			if (body != otherBody)
			{				
				vGravity = body->GetPosition() - otherBody->GetPosition();
				distance = vGravity.Length();
				vGravity.Normalize();

				fGrav = (GRAVITY_CONSTANT * body->GetMass() * otherBody->GetMass()) / (distance * distance);
				vGravity *= sign * fGrav;

				body->ApplyForceToCenter(vGravity, true);
			}
		}
	}
}

void Engine::Repulsion()
{
	Attraction(1);
}

void Engine::CreateNewBall(int xPos, int yPos)
{
	b2Body* body;
	int x = myWindow->getSize().x / 2;
	int y = myWindow->getSize().y / 2;

	if (isBlackhole)
	{
		Circle* c = CreateObject<Circle>(myWorld, xPos / PTM_RATIO, ((y * 2) - yPos) / PTM_RATIO, &b2Vec2(0.1, 0), 1, 0, 771);
		body = c->body;
		//body->SetLinearDamping(9999);
	}
	else
	{
		//CreateObject<Circle>(myWorld, xPos / PTM_RATIO, ((y * 2) - yPos + 0.1) / PTM_RATIO, &b2Vec2(0.08, 0.08));
		body = CreateObject<Circle>(myWorld, xPos / PTM_RATIO, ((y * 2) - yPos) / PTM_RATIO, &b2Vec2(0.05, 0.05), 1, 0, 0.8)->body;
		//body->SetBullet(true);
		//body->GetFixtureList()->SetRestitution(0);
		//body->SetLinearDamping(9);
		//body->ApplyForceToCenter(b2Vec2(0, 16.9), true);
		//CreateObject<Box>(myWorld, xPos/PTM_RATIO, ((y * 2)-yPos) / PTM_RATIO, &b2Vec2(0.9, 0.9));
	}
	body->SetBullet(DEF_BULLET);
}

void Engine::CreateNewSpringBall(int xPos, int yPos)
{
	b2Body* body;
	int x = myWindow->getSize().x / 2;
	int y = myWindow->getSize().y / 2;
	

	body = CreateObject<Circle>(myWorld, xPos / PTM_RATIO, ((y * 2) - yPos) / PTM_RATIO, &b2Vec2(0.05, 0.05), 1, 0, 0.8)->body;
	body->SetBullet(DEF_BULLET);
	body->SetUserData(lastSpringBody);

	if (lastSpringBody != nullptr)
	{
		b2DistanceJointDef jointDef;
		jointDef.Initialize(body, lastSpringBody, body->GetWorldCenter(), lastSpringBody->GetWorldCenter());
		jointDef.collideConnected = true;
		//jointDef.frequencyHz = 24.0f;
		jointDef.dampingRatio = 1.0f;
		myWorld->CreateJoint(&jointDef);
	}
	lastSpringBody = body;
}
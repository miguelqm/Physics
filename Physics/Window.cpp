#include "Window.h"
#include "Utils.h"
#include "Settings.h"
#include "Entity.h"

namespace Rendering
{
	MyWindow::MyWindow(HWND hMainWnd)
	{
		sfBackgroundColor = sf::Color(0, 0, 0);

		sf::ContextSettings settings;
		settings.antialiasingLevel = ANTIALIASING_LEVEL;

		create(hMainWnd, settings);
		setVerticalSyncEnabled(true);
		SetView(true);
	}

	void MyWindow::DrawShapes(b2World* world)
	{
		int i = 0;
		for (b2Body* body = world->GetBodyList(); body != NULL; body = body->GetNext())
		{
			b2Fixture* fixture = body->GetFixtureList();
			b2Shape::Type type = fixture->GetType();
			switch (type)
			{
			case b2Shape::Type::e_circle:
				DrawCircle(body);
				break;
			case b2Shape::Type::e_polygon:
				DrawPolygon(body);
				break;
			case b2Shape::Type::e_edge:
				DrawEdge(body);
				break;
			case b2Shape::Type::e_chain:
				DrawChain(body);
				break;
			}
			if(isDrawVelocity)
				DrawVelocity(body);
			if (isDrawAcceleration)
				DrawAcceleration(body);
		}
	}

	void MyWindow::DrawCircle(b2Body* body)
	{
		sf::Vector2f position = VectorB2ToSFf(body->GetPosition());
		b2Fixture* fixture = body->GetFixtureList();
		b2CircleShape* shape = (b2CircleShape*)fixture->GetShape();

		float angle = body->GetAngle() * 180.0f / b2_pi;
		float sfRadius = FloatB2ToSF(shape->m_radius);

		sf::CircleShape s;
		s.setOrigin(sfRadius, sfRadius);
		s.setPosition(position);
		s.setRadius(sfRadius);
		s.setOutlineThickness(0);
		s.setOutlineColor(sf::Color(200, 50, 50));
		s.setFillColor(sf::Color(200, 50, 50));
		//s.setPointCount(10);
		s.setRotation(angle);
		draw(s);

		
		s.setOrigin(0, -sfRadius * 0.35);
		s.setPosition(position);
		s.setRadius(sfRadius / 6);
		s.setOutlineThickness(0);
		s.setOutlineColor(sf::Color(220, 220, 220));
		s.setFillColor(sf::Color(0, 0, 0));
		//s.setPointCount(10);
		s.setRotation(angle);
		draw(s);

		sf::RectangleShape r;
		r.setPosition(position);
		r.setSize(sf::Vector2f(sfRadius, 1));
		r.setOutlineColor(sf::Color(200, 50, 50));
		r.setRotation(angle);
		draw(r);
	}

	void MyWindow::DrawPolygon(b2Body* body)
	{
		sf::Vector2f position = VectorB2ToSFf(body->GetPosition());
		b2Fixture* fixture = body->GetFixtureList();
		b2PolygonShape* shape = (b2PolygonShape*)fixture->GetShape();
		
		float angle = body->GetAngle() * 180.0f / b2_pi;

		sf::ConvexShape s;
		s.setPosition(position);
		s.setPointCount(shape->m_count);
		for (int i = 0; i < shape->m_count; ++i)
		{			
			sf::Vector2f v = VectorB2ToSFf(shape->m_vertices[i]);
			s.setPoint(i, v);
		}
		s.setOutlineThickness(0);
		s.setOutlineColor(sf::Color(100, 0, 200));
		s.setFillColor(sf::Color(100, 0, 200));
		s.setRotation(angle);
		draw(s);
	}

	void MyWindow::DrawEdge(b2Body* body)
	{

	}

	void MyWindow::DrawChain(b2Body* body)
	{
		sf::Vector2f position = VectorB2ToSFf(body->GetPosition());
		b2Fixture* fixture = body->GetFixtureList();
		b2ChainShape* shape = (b2ChainShape*)fixture->GetShape();

		float angle = body->GetAngle() * 180.0f / b2_pi;

		sf::VertexArray line(sf::PrimitiveType::LinesStrip, shape->m_count);
		for (int i = 0; i < shape->m_count; ++i)
		{
			line[i].position = VectorB2ToSFf(shape->m_vertices[i]);
			line[i].color = sf::Color(100, 0, 200);
		}
		draw(line);
	}

	void MyWindow::SetView(bool resize)
	{
		RECT rect;
		int width = 0;
		int height = 0;

		if (GetClientRect(this->getSystemHandle(), &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
		sf::View view = getDefaultView();
		//view.setCenter(width/2, -height/2);
		
		view.reset(sf::FloatRect(rect.left, rect.top, width, height));
		view.setSize(width, -height);
		//view.zoom(0.01);
		setView(view);
		/*if (GetWindowRect(this->getSystemHandle(), &rect))
		{
			width = (rect.right - rect.left);
			height = (rect.bottom - rect.top);
		}*/
		setSize(sf::Vector2u(width, height));		

		//if (resize)
		//	b2dSetBorders(width, height);
	}

	void MyWindow::CenterView(b2World* world)
	{
		float sumX = 0;
		float sumY = 0;

		for (b2Body* body = world->GetBodyList(); body != NULL; body = body->GetNext())
		{
			if (body->GetType() == b2BodyType::b2_dynamicBody)
			{
				sumX += body->GetPosition().x;
				sumY += body->GetPosition().y;
			}
		}
		sumX = sumX / world->GetBodyCount();
		sumY = sumY / world->GetBodyCount();

		sf::View view = getView();
		view.setCenter(VectorB2ToSFf(b2Vec2(sumX, sumY)));
		setView(view);
	}

	void MyWindow::Clear()
	{
		clear(sfBackgroundColor);
	}

	void MyWindow::DrawVelocity(b2Body* body)
	{
		b2Vec2 p = body->GetPosition();
		b2Vec2 v = body->GetLinearVelocity();
		v *= 0.15f;
		v += p;

		//v *= l / 2;
		// v *= 0.5f;

		sf::Vector2f position = VectorB2ToSFf(p);
		sf::Vector2f velocity = VectorB2ToSFf(v);

		sf::Vertex line[] =
		{
			sf::Vertex(position),
			sf::Vertex(velocity)
		};

		draw(line, 2, sf::Lines);
	}

	void MyWindow::DrawAcceleration(b2Body* body)
	{
		//if (body->GetType() == b2BodyType::b2_dynamicBody)
		//{
		//	Physics::Entity* e = (Physics::Entity*)body->GetUserData();
		//	b2Vec2 p = body->GetPosition();
		//	b2Vec2 v = body->GetLinearVelocity();
		//	b2Vec2* lv = e->GetLastVelocity();
		//	b2Vec2 a = p + (v - *lv);

		//	e->SetLastVelocity(&v);

		//	sf::Vector2f position = VectorB2ToSFf(p);
		//	sf::Vector2f acceleration = VectorB2ToSFf(a);

		//	sf::Vertex line[] =
		//	{
		//		sf::Vertex(position),
		//		sf::Vertex(acceleration)
		//	};
		//	line->color = sf::Color(222, 0, 0);

		//	draw(line, 2, sf::Lines);
		//}
	}
}
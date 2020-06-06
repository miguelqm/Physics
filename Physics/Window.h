#pragma once

#include "Rendering.h"
#include "framework.h"

namespace Rendering
{
	class MyWindow : public sf::RenderWindow
	{
	public:
		bool isDrawVelocity = DRAW_VELOCITY;
		bool isDrawAcceleration = DRAW_ACCELERATION;

		sf::RectangleShape r;
		sf::Color sfBackgroundColor;
	
		MyWindow(HWND hMainWnd);
		void DrawShapes(b2World* world);
		void DrawCircle(b2Body* body);
		void DrawPolygon(b2Body* body);
		void DrawEdge(b2Body* body);
		void DrawChain(b2Body* body);
		void SetView(bool resize);
		void CenterView(b2World* world);
		void Clear();
		void DrawVelocity(b2Body* body);
		void DrawAcceleration(b2Body* body);
	};
}


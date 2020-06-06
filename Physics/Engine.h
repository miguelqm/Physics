#pragma once

#include "Physics.h"
#include "Rendering.h"

static Physics::World* myWorld;
static Rendering::MyWindow* myWindow;
static bool isDrawing, isGravity, isDrag, isAttraction, isRepulsion, isBlackhole, isBoundaries;
static b2Timer tmrMouseButtonClick;
static b2Vec2 ptMouseClickStart, ptMouseClickEnd;
static b2Body* lastSpringBody;

static class Engine
{
private:
	
public:
	static void CreateWorld(HWND hWnd);
	static void CreateNewBall(int xPos, int yPos);
	static void CreateNewSpringBall(int xPos, int yPos);

	static void Step();
	static void MouseEvent(UINT message, WPARAM wParam, LPARAM lParam);
	static void Resize(bool bounds = true);
	static void ClearStaticBodies();
	static void ClearDynamicBodies();
	
	static void Drag();
	static void Attraction(int sign = -1);
	static void Repulsion();

	static LRESULT ProcessMsgs(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

class AABBCallback : public b2QueryCallback
{
	bool ReportFixture(b2Fixture* fixture);
};
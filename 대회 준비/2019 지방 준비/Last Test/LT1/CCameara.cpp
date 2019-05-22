#include "DXUT.h"
#include "Header.h"

CCameara::CCameara()
	: position(0, 0), center(200, 384), limitPos_Max(9999, 9999), limitPos_Min(0, -9999), target(NULL), speed(0.05f)
{
}

CCameara::~CCameara()
{
	if (target)
		delete target;
}

void CCameara::Update(float deltaTime)
{
	if (target)
		D3DXVec2Lerp(&position, &position, &(target->position - center), speed);

	if (position.x <= limitPos_Min.x)
		position.x = limitPos_Min.x;
	if (position.x >= limitPos_Max.x)
		position.x = limitPos_Max.x;

	if (position.y <= limitPos_Min.y)
		position.y = limitPos_Min.y;
	if (position.y >= limitPos_Max.y)
		position.y = limitPos_Max.y;
}

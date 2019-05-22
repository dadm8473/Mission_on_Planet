#include "DXUT.h"
#include "Header.h"

CCamera::CCamera() : position(0,0), center(256, 384), limitPosition_Min(0, -9999), limitPosition_Max(9999, 9999), target(NULL), trackingSpeed(0.05f)
{
}

CCamera::~CCamera()
{
	target = NULL;
}

void CCamera::SetTarget(CMatrix * inputTarget)
{
	target = inputTarget;
}

void CCamera::Update(float deltaTime)
{
	if (target != NULL)
	{
		D3DXVec2Lerp(&position, &position, &(target->position - center), trackingSpeed);
	}

	// 움직임 최소 최대값 검사
	if (position.x <= limitPosition_Min.x)
		position.x = limitPosition_Min.x;
	if (position.x >= limitPosition_Max.x)
		position.x = limitPosition_Max.x;

	if (position.y <= limitPosition_Min.y)
		position.y = limitPosition_Min.y;
	if (position.y >= limitPosition_Max.y)
		position.y = limitPosition_Max.y;
}

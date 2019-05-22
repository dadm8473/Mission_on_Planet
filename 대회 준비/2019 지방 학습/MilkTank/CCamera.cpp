#include "DXUT.h"
#include "Header.h"


CCamera::CCamera()
	:position(0,0), center(256, 384), 
	limitPos_Max(9999, 9999), limitPos_Min(0, - 9999),
	target(NULL), speed(0.05f)
{
}

CCamera::~CCamera()
{
	delete target;
}

void CCamera::Update(float deltaTime)
{
	if (target != NULL)
		// 아래처럼 적용하면 매 프레임 마다 카메라의 포지션값이 타겟의 포지션에 스피드만큼 다가가게 된다.
		D3DXVec2Lerp(&position, &position, &(target->position - center), speed);


	// 카메라 움직임 제한 검사
	if (position.x <= limitPos_Min.x)
		position.x = limitPos_Min.x;
	if (position.x >= limitPos_Max.x)
		position.x = limitPos_Max.x;

	if (position.y <= limitPos_Min.y)
		position.y = limitPos_Min.y;
	if (position.y >= limitPos_Max.y)
		position.y = limitPos_Max.y;
		
}

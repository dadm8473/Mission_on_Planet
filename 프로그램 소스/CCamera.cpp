#include "DXUT.h"
#include "Header.h"

CCamera::CCamera()
	: position(0, 0), center(200, 384), limitPos_Min(0, -9999), limitPos_Max(9999, 9999), target(NULL), speed(0.05f), isCameraShake(false), shakeTime(0.01f), 
	shakeTimer(0), dir(1), timer(0), time(0.2f), strong(2048)
{
}

CCamera::~CCamera()
{
	delete target;
}

void CCamera::Update(float deltaTime)
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

	if (isCameraShake)
	{
		D3DXVECTOR2 randPos = D3DXVECTOR2(rand() % 2048, rand() % 2048);

		position.x += randPos.x * dir * deltaTime;
		position.y += randPos.y * dir * deltaTime;

		shakeTimer += deltaTime;
		if (shakeTimer > shakeTime)
		{
			shakeTimer = 0;
			dir = -dir;
		}

		timer += deltaTime;
		if (timer > time)
		{
			timer = 0;
			isCameraShake = false;
		}
	}
}

void CCamera::ShakeCamera(float timer, int strong)
{
	this->time = timer;
	this->strong = strong;

	isCameraShake = true;
}

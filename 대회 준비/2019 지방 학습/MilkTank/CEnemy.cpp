#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(CCamera * camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false), parentScene(NULL), hp(0), isDie(false),
	attackTime(0.3f), attackTimer(0), exitTime(2), exitTimer(0), exit(false), speed(0)
{
	position = pos;

	switch (type)
	{
	case 0:
		hp = 60;
		center = D3DXVECTOR2(128, 75);
		break;
	case 1:
		hp = 35;
		center = D3DXVECTOR2(100, 50);
		speed = 400;

		attackTime = 1;
		break;
	case 2:
		hp = 50;
		center = D3DXVECTOR2(100, 50);
		speed = 256;

		attackTime = 0.66f;
		break;
	}
}

void CEnemy::Update(float deltaTime)
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
}

#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int type, CCamera * camera)
	:camera(camera), type(type), hp(10), speed(300), isDie(false), isDestroy(false)
{
	position = pos;

	// 나중에 타입 별로 분류

	hp = 10;
	speed = 300;
	center = D3DXVECTOR2(100, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= speed * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroy = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	// 나중에 타입 별로 분류
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

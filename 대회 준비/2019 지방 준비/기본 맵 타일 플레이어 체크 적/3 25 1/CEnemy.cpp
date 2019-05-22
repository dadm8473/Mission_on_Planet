#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int type, CCamera * camera)
	:camera(camera), type(type), hp(10), speed(300), isDie(false), isDestroy(false)
{
	position = pos;

	// ���߿� Ÿ�� ���� �з�

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
	// ���߿� Ÿ�� ���� �з�
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

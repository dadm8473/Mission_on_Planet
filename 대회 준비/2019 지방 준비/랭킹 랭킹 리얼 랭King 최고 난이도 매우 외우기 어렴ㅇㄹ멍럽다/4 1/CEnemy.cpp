#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), speed(300), isDie(false), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
	scale = D3DXVECTOR2(-1, 1);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= speed * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

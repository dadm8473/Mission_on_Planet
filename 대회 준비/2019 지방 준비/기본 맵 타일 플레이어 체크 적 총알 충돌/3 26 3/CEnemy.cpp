#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * camera)
	: camera(camera), type(inputType), speed(300), isDie(false), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= speed * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 50, position.y - 50, position.x + 50, position.y + 50);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

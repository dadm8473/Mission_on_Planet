#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false), isDie(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 300 * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 50, position.x + 32, position.y + 50);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

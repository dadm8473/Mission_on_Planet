#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDie(false), isDestroy(false)
{
	position = pos;
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 300 * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1025 + 256)
		isDestroy = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

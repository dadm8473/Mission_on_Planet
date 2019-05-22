#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	:camera(inputCamera), type(inputType), hp(100), isDie(false), isDestroyed(false)
{
	position = pos;
	
	center = D3DXVECTOR2(100, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 300 * deltaTime;

	if (camera->position.x + 1024 + 256 < position.x || camera->position.x - 256 > position.x)
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprtie)
{
	Draw(sprtie, gAssetManager->GetTexture("Player"));
}

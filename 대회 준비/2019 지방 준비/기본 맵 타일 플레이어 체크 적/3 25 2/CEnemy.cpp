#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int type, CCamera * camera)
	: hp(10), type(type), camera(camera), isDie(false), isDestroy(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 100 * deltaTime;

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroy = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

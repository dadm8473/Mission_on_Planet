#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, CCamera * inputCamera, int inputType, float inputSpeed, float inputMoveAngle, float inputTimer)
	: camera(inputCamera), type(inputType), speed(inputSpeed), timer(inputTimer), moveAnlge(inputMoveAngle), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
	scale = D3DXVECTOR2(1, 0.1f);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAnlge*(D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAnlge*(D3DX_PI / 180)) * speed * deltaTime;

	timer -= deltaTime;

	if (timer < 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

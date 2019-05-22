#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera * camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float timer)
	: camera(camera), type(type), speed(speed), moveAngle(moveAngle), damage(damage), timer(timer), isDestroyed(false)
{
	position = pos;

	center = D3DXVECTOR2(128, 128);
	scale = D3DXVECTOR2(0.5f, 0.2f);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;

	timer -= deltaTime;
	if (timer <= 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

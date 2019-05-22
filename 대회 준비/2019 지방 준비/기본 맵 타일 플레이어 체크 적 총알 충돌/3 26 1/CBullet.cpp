#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera * camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float timer)
	: camera(camera), type(type), damage(damage), timer(timer), moveAngle(moveAngle), speed(speed), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 50);
	scale = D3DXVECTOR2(0.1f, 1);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;

	rotate = moveAngle;

	timer -= deltaTime;
	if (timer <= 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 16, position.y - 4, position.x + 16, position.y + 4);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

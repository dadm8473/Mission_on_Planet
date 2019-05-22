#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, CCameara * camera, int type, float moveAngle, float speed, float timer)
	: camera(camera), type(type), moveAngle(moveAngle), speed(speed), timer(timer), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(32, 32);
	scale = D3DXVECTOR2(0.2f, 1);

	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	}
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	rotate = moveAngle;

	// ÃÑ¾Ë ¼Ò¸ê
	timer -= deltaTime;
	if (timer < 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));

	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	}
}

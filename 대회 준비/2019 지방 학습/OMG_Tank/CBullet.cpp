#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float timer)
	:CMatrix(), type(type), speed(speed), moveAngle(moveAngle), damage(damage), isDestroyed(false), camera(camera), timer(timer)
{
	position = pos;

	center = D3DXVECTOR2(32, 32);
}

void CBullet::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);

	position.x += sin(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;

	rotate = moveAngle;

	timer -= deltaTime;
	if (timer <= 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 8, position.y - 2, position.x + 8, position.y + 2);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Bullet"));
}

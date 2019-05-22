#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(CCamera * camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), attackTime(1), attackTimer(0), isDestroyed(false), speed(256), hp(10), type(type)
{
	position = pos;
	center = D3DXVECTOR2(100, 75);
	scale = D3DXVECTOR2(-1, 1);

	speed = 256 + rand() % 100;
	
	switch (type)
	{
	case 1:
		SetAnimation(0.03f, 30, true);
		break;
	case 2:
		SetAnimation(0.03f, 20, true);
		break;
	}
}

void CEnemy::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
	
	position.x -= speed * deltaTime;

	attackTimer += deltaTime;
	if (attackTime < attackTimer)
	{
		attackTimer = 0;

		float angle = 180;
		/*if (parentScene->player)
		{
			angle = GetAngle(
				parentScene->player->position.x - position.x,
				parentScene->player->position.y - position.y
			);
		}*/

		parentScene->enemyBulletList.push_back(new CBullet(camera, position, 0, 256 + rand() % 512, angle, 10));
	}

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1280)
		isDestroyed = true;

	SetRect(&rect, position.x - 100, position.y - 75, position.x + 100, position.y + 75);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Enemy1"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Enemy2"));
		break;
	}
}

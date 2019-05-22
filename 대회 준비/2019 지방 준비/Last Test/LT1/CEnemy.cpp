#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCameara * camera)
	: type(type), camera(camera), isDie(false), isDestroyed(false),
	attackTime(1.5f), attackTimer(0)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

void CEnemy::Update(float deltaTime)
{
	position.x -= 200 * deltaTime;

	attackTimer += deltaTime;
	if (attackTime < attackTimer)
	{
		parentScene->enemyBulletList.push_back(new CBullet(position, camera, 2, 180, 400));
		attackTimer = 0;
	}

	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	// È­¸é¿¡¼­ 256ÇÈ¼¿ ¹þ¾î³´À» °æ¿ì »èÁ¦
	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false), isDie(false),
	attackTimer(1), attackTime(1.5f), hp(3),
	beHit(false), redTime(0.05f), redTimer(0)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
	
	switch (type)
	{
	case 1:
		SetAnimation(0.04f, 20, true);
		break;
	case 2:
		SetAnimation(0.04f, 20, true);
		break;
	default:
		break;
	}
}

void CEnemy::Update(float deltaTime)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	// 체력 0이하 죽음
	if (hp <= 0)
		isDie = true;

	// 이동
	position.x -= (200 + rand() % 200) * deltaTime;

	// 공격
	attackTimer += deltaTime;
	if (attackTimer > attackTime)
	{
		switch (type)
		{
		case 1:
			parentScene->enemyBulletList.push_back(new CBullet(position, camera, 3, 180, 300 + rand() % 100, 1));
			break;
		case 2:
			parentScene->enemyBulletList.push_back(new CBullet(position, camera, 4, 240, 300 + rand() % 100, 2));
			break;
		}
		attackTimer = 0;
	}
	
	// 맞으면 빨간색되게
	if (beHit)
	{
		g = 0;
		b = 0;

		redTimer += deltaTime;
		if (redTimer > redTime)
		{
			g = 255;
			b = 255;
			beHit = false;
			redTimer = 0;
		}
	}
	
	// 카메라 256 만큼 벗어날 경우 삭제
	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 64, position.y - 32, position.x + 64, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	switch (ext_Stage)
	{
	case 1:
		switch (type)
		{
		case 1:
			Draw(sprite, gAssetManager->GetTexture("Enemy1"));
			break;
		case 2:
			Draw(sprite, gAssetManager->GetTexture("Enemy2"));
			break;
		}
		break;
	case 2:
		switch (type)
		{
		case 1:
			Draw(sprite, gAssetManager->GetTexture("Enemy3"));
			break;
		case 2:
			Draw(sprite, gAssetManager->GetTexture("Enemy4"));
			break;
		}
		break;
	}

}

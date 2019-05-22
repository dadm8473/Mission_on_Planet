#include "DXUT.h"
#include "Header.h"

CClearAttack::CClearAttack(D3DXVECTOR2 pos, CCamera * inputCamera)
	: isDestroyed(false), camera(inputCamera)
{
	position = pos;
	SetAnimation(0.3f, 3, false);
}

void CClearAttack::Update(float deltaTime)
{
	if (isAniEnd)
	{
		parentScene->isClearAttack = false;
		isDestroyed = true;
	}

	if (parentScene)
	{
		// enemy clear
		for (auto it = parentScene->enemyList.begin(); it != parentScene->enemyList.end(); ++it)
			if (*it)
				(*it)->isDie = true;

		// Enemy Bullet List Clear
		for (auto it = parentScene->enemyBulletList.begin(); it != parentScene->enemyBulletList.end(); ++it)
			if (*it)
				(*it)->isDestroyed = true;
	}

	CMatrix::Update(deltaTime, camera->position);
}

void CClearAttack::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Effect"));
}

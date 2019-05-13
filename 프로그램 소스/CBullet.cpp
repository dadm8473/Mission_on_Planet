#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, CCamera * inputCamera, int inputType, float inputMoveAngle, float inputSpeed, float inputTimer, 
	CBullet* target1, CEnemy* target2, CObject* target3)
	: camera(inputCamera), type(inputType), moveAngle(inputMoveAngle), speed(inputSpeed), timer(inputTimer), isDestroyed(false), 
	target1(target1), target2(target2), target3(target3), targetTimer(0.25f)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	switch (type)
	{
	case 1: // 플레이어 주포
		center = D3DXVECTOR2(16, 64);
		break;
	case 2: // 플레이어 대공포
		scale = D3DXVECTOR2(1, 1.3f);
		center = D3DXVECTOR2(16, 32);
		break;
	case 3: // 적 수직
		scale = D3DXVECTOR2(1.2f, 0.8f);
		center = D3DXVECTOR2(32, 64);
		break;
	case 4: // 적 대각
		scale = D3DXVECTOR2(0.7f, 0.8f);
		center = D3DXVECTOR2(64, 64);
		break;
	case 100: // 이쁜 호밍 미사일
		scale = D3DXVECTOR2(1, 1.3f); 
		center = D3DXVECTOR2(16, 32);
		break;
	default:
		break;
	}
}

void CBullet::Update(float deltaTime)
{
	if (target1) //enemyBullet
	{
		targetTimer -= deltaTime;
		if (targetTimer < 0)
		{
			float angle = GetAngle(target1->position.x - position.x, target1->position.y - position.y);

			if (angle < moveAngle) moveAngle -= speed * deltaTime;
			if (angle > moveAngle) moveAngle += speed * deltaTime;

			//moveAngle = GetAngle(target1->position.x - position.x, target1->position.y - position.y);
			if (target1->isDestroyed)
			{
				target1 = NULL;
				isDestroyed = true;
			}
		}
	}
	else if (target2) // Enemy
	{
		targetTimer -= deltaTime;
		if (targetTimer < 0)
		{
			float angle = GetAngle(target2->position.x - position.x, target2->position.y - position.y);

			if (angle < moveAngle) moveAngle -= speed * deltaTime;
			if (angle > moveAngle) moveAngle += speed * deltaTime;

			//moveAngle = GetAngle(target2->position.x - position.x, target2->position.y - position.y);
			if (target2->isDestroyed || target2->isDie)
			{
				target2 = NULL;
				isDestroyed = true;
			}
		}
	}
	else if (target3) // obejct
	{
		targetTimer -= deltaTime;
		if (targetTimer < 0)
		{
			float angle = GetAngle(target3->position.x - position.x, target3->position.y - position.y);

			if (angle < moveAngle) moveAngle -= speed * deltaTime;
			if (angle > moveAngle) moveAngle += speed * deltaTime;

			//moveAngle = GetAngle(target3->position.x - position.x, target3->position.y - position.y);
			if (target3->isDestroyed)
			{
				target3 = NULL;
				isDestroyed = true;
			}
		}
	}

	position.x += sin(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;

	rotate = moveAngle;

	timer -= deltaTime;
	if (timer < 0)
		isDestroyed = true;

	SetRect(&rect, position.x - 16, position.y - 32, position.x + 16, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1: // 플레이어 주포
		Draw(sprite, gAssetManager->GetTexture("PlayerBullet_1"));
		break;
	case 2: // 플레이어 대공포
		Draw(sprite, gAssetManager->GetTexture("PlayerBullet_2"));
		break;
	case 3: // 적 수직
		Draw(sprite, gAssetManager->GetTexture("EnemyBullet_1"));
		break;
	case 4: // 적 대각
		Draw(sprite, gAssetManager->GetTexture("EnemyBullet_2"));
		break;
	case 100: // 이쁜 호밍 미사일
		Draw(sprite, gAssetManager->GetTexture("PlayerBullet_2"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("PlayerBullet_1"));
		break;
	}
}
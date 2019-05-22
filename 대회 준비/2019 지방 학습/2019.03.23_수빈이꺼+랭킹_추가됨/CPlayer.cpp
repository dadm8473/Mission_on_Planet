#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	:CMatrix(), attackTime(0.05f), attackTimer(0), isAttacking(false), velocity_Y(0), jumpCount(1), upgrade(0), isDie(false), target(NULL),
	homingAttack(false), attackRich(false), speedUp(false), multiAttack(false), speed(400), rich(0.3f), doubleJump(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 75);
	this->camera = camera;

	ground_Y_Pos = pos.y;

	SetAnimation(0.03f, 20, true);
}

void CPlayer::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);

	// 중력 가속도
	velocity_Y += 32 * deltaTime;

	position.y += velocity_Y;

	if (parentScene)
	{
		// 현재 플레이어가 위치한 타일의 번호 받기
		int tileIndex = position.x / gAssetManager->GetTexture("Tile")->width;

		// 플레이어가 타일을 벗어나지 않았을 경우
		if (parentScene->tileList.size() > tileIndex && tileIndex >= 0)
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0)
				ground_Y_Pos = outY;
		}
	}

	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0.0f;

		jumpCount = 1;

		if (doubleJump && upgrade != 2)
			jumpCount = 2;
	}

	if (isAttacking)
	{
		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			attackTimer = 0;

			if(!attackRich)
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2024, 90, 10, rich));

			if (homingAttack)
			{
				int angle = 90;

				if (target)
					parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2024,
						angle = (target) ? GetAngle(target->position.x - position.x, target->position.y - position.y) : 90, 10));
			}

			if (attackRich)
			{
				rich = 0.6f;

				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2024, 90, 10, rich));
			}

			if (multiAttack)
			{
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2024, 70, 10, rich));
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2024, 80, 10, rich));
			}

			target = NULL;

			isAttacking = false;
		}
	}

	if (speedUp)
	{
		speed += 75;
		speedUp = false;
	}

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	switch (upgrade)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Player1"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Player2"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Player3"));
		break;
	}
}

void CPlayer::Attack()
{
	isAttacking = true;
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (jumpCount > 0)
	{
 		jumpCount--;
		velocity_Y = -15.0f;
	}
}

void CPlayer::AllFalse()
{
	homingAttack = false;
	attackRich = false;
	speedUp = false;
	multiAttack = false;
	doubleJump = false;

	rich = 0.3f;
}

void CPlayer::Upgrade()
{
	upgrade++;
}
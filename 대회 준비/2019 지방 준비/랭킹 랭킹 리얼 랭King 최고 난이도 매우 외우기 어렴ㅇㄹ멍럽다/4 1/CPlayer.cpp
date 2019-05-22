#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: camera(inputCamera), ground_Y_Pos(0), velocity_Y(0), jumpCount(0), isDie(false),
	speed(350), rich(0.3f), isMultiAttack(false), isHomingAttack(false),
	isAttack(false), attackTime(0.3f), attackTimer(0), target(NULL),
	isAttack_H(false), attackTimer_H(0), attackTime_H(0.3f)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);

	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	velocity_Y += 32 * deltaTime;
	position.y += velocity_Y;

	if (parentScene)
	{
		int tileIndex = position.x / tileWidth;
		if (tileIndex >= 0 && tileIndex < parentScene->tileList.size())
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0)
				ground_Y_Pos = outY;
		}
	}

	if (isAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(position, camera, 0, 1000, 90, rich));

			if (target && isHomingAttack)
			{
				float angle = GetAngle(target->position.x - position.x, target->position.y - position.y);

				if(angle > 0)
					parentScene->playerBulletList.push_back(new CBullet(position, camera, 0, 1000, angle));

				target = NULL;
			}

			attackTimer = 0;
			isAttack = false;
		}
	}

	if (isAttack_H)
	{
		attackTimer_H += deltaTime;
		if (attackTimer_H > attackTime_H)
		{
			parentScene->playerBulletList.push_back(new CBullet(position, camera, 0, 1000, 70, rich));

			if (isMultiAttack)
			{
				parentScene->playerBulletList.push_back(new CBullet(position, camera, 0, 1000, 65, rich));
				parentScene->playerBulletList.push_back(new CBullet(position, camera, 0, 1000, 75, rich));
			}

			attackTimer_H = 0;
			isAttack_H = false;
		}
	}
	
	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0;
		
		if(jumpCount < 1)
			jumpCount = 1;
	}

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * 700 * deltaTime;
}

void CPlayer::Jump()
{
	if (--jumpCount >= 0)
		velocity_Y = -10;
}

void CPlayer::Attack()
{
	isAttack = true;
}

void CPlayer::Attack_H()
{
	isAttack_H = true;
}

void CPlayer::DoubleJump()
{
	jumpCount++;
}

void CPlayer::SpeedUP()
{
	speed += 75;
	if (speed > 600)
		speed = 600;
}

void CPlayer::LongAttack()
{
	rich = 1;
}

void CPlayer::MultiAttack()
{
	isMultiAttack = true;
}

void CPlayer::HomingAttack()
{
	isHomingAttack = true;
}

void CPlayer::Reset()
{
	rich = 0.3f;
	jumpCount = 1;
	isMultiAttack = false;
	isHomingAttack = false;
}

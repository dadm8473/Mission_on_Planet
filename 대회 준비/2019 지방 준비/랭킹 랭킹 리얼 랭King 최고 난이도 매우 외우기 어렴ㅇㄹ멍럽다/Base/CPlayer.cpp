#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: camera(inputCamera), velocitry_Y(0), isDie(false), isAttack(false), attackTime(0.3f), attackTimer(0), isMultiAttack(false), 
	isHomingAttack(false), speed(350), rich(0.4f), target(NULL)
{
	position = pos;

	center = D3DXVECTOR2(128, 128);

	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	velocitry_Y += 32 * deltaTime;
	position.y += velocitry_Y;

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
			parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, 90, 1, rich));

			if(isMultiAttack)
				for(int i = 1; i < 3; ++i)
					parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, 90 - i*10, 1, rich));

			if (isHomingAttack && target)
			{
				float angle = GetAngle(target->position.x - position.x, target->position.y - position.y);

				if(angle > 0)
					parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, angle, 1));

				target = NULL;
			}

			attackTimer = 0;
			isAttack = false;
		}
	}

	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocitry_Y = 0;

		if(jumpCount <= 0)
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
	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (--jumpCount >= 0)
		velocitry_Y = -10;
}

void CPlayer::Attack()
{
	isAttack = true;
}

void CPlayer::DoubleJump()
{
	jumpCount++;
}

void CPlayer::SpeedUP()
{
	speed += 75;
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
	rich = 0.4f;
	jumpCount = 1;
	isMultiAttack = false;
	isHomingAttack = false;
}

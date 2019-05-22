#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	: camera(camera), ground_Y_Pos(0), velocity_Y(0), jumpCount(1), isDie(false), isAttack(false), attackTime(0.3f), attackTimer(0), speed(350), richTimer(0.3f),
	isMultiAttack(false), isHomingAttack(false), target(NULL)
{
	position = pos;
	center = D3DXVECTOR2(100, 50);

	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	velocity_Y += 32 * deltaTime;
	position.y += velocity_Y;

	if (parentScene)
	{
		int tileIndex = position.x / gAssetManager->GetTexture("Tile")->width;
		if (tileIndex >= 0 && tileIndex < parentScene->tileList.size())
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0)
				ground_Y_Pos = outY;
		}
	}

	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0;

		if(jumpCount <= 0)
			jumpCount = 1;
	}

	if (isAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, 90, 1, richTimer));

			if (isMultiAttack)
			{
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, 80, 1, richTimer));
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 1000, 70, 1, richTimer));
			}

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
		velocity_Y = -10;
}

void CPlayer::Attack()
{
	isAttack = true;
}

void CPlayer::DoubleJump()
{
	jumpCount++;
}

void CPlayer::SpeedUp()
{
	speed += 75;
}

void CPlayer::LongAttack()
{
	richTimer = 1;
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
	jumpCount = 1;
	richTimer = 0.3f;
	isMultiAttack = false;
	isHomingAttack = false;
}

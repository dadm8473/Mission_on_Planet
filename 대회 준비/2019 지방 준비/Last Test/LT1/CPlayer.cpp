#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCameara * inputCamera)
	: camera(inputCamera), velocitry_Y(0), ground_Y_pos(0), jumpCount(1), isDie(false), 
	isAttack(false), attackTime(0.3f), attackTimer(0), rich(0.4f)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	ground_Y_pos = pos.y;
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
				ground_Y_pos = outY;
		}
	}

	if (position.y > ground_Y_pos)
	{
		position.y = ground_Y_pos;
		velocitry_Y = 0;

		jumpCount = 1;
	}

	if (isAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(position, camera, 1, 90, 1000, rich));

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
	position.x += dir * 700 * deltaTime;
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

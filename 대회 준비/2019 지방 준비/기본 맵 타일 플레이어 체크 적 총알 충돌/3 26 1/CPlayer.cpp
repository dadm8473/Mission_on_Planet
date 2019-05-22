#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	: camera(camera), ground_Y_Pos(0), velocity_Y(0), jumpCount(1), isDie(false)
{
	position = pos;
	ground_Y_Pos = pos.y;
	center = D3DXVECTOR2(100, 50);
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

		jumpCount = 1;
	}

	SetRect(&rect, position.x - 50, position.y - 25, position.x + 50, position.y + 25);
	CMatrix::Update(deltaTime, camera->position);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * 700 * deltaTime;
	parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 2000, 90, 10, 3));
}

void CPlayer::Jump()
{
	if (--jumpCount >= 0)
		velocity_Y = -10;
}

#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: velocity_Y(0), ground_Y_Pos(0), jumpcount(1), isDie(false), camera(inputCamera)
{
	position = pos;

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

		jumpcount = 1;
	}

	CMatrix::Update(deltaTime, camera->position);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * 600 * deltaTime;
}

void CPlayer::Jump()
{
	if (--jumpcount >= 0)
		velocity_Y = -10;
}

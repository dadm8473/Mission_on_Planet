#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: velocity_Y(0), jumpCount(0), isDie(false), camera(inputCamera)
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

	if (ground_Y_Pos < position.y)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0;

		jumpCount = 1;
	}

	CMatrix::Update(deltaTime, camera->position);
	SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

void CPlayer::Move(int dir, float deltatime)
{
	position.x += dir * 600 * deltatime;
}

void CPlayer::Jump()
{
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = -10;
	}
}

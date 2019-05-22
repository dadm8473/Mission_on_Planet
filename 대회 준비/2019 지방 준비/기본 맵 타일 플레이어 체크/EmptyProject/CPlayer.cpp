#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	:camera(camera), ground_Y_Pos(0), velocity_Y(0), jumpCount(1), isDie(false)
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
		int tileindex = position.x / gAssetManager->GetTexture("Tile")->width;
		if (tileindex >= 0 && tileindex < parentScene->tileList.size())
		{
			float outY = parentScene->tileList[tileindex]->GetGround_Y_Pos(position.x);
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
	if (jumpCount > 0)
	{
		jumpCount--;

		velocity_Y = -10;
	}
}

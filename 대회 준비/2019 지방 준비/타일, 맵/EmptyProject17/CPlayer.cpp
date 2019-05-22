#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)
	: camera(camera), velocity_Y(0), jumpCount(1), upgrade(0), isDie(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 75);

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
	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	switch (upgrade)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
{
	float speed = 600;

	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = -10;
	}
}

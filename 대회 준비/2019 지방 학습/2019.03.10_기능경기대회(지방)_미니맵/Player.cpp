#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)	: CMatrix(), camera(camera), 
velocity_Y(0), jumpCount(1), upgrade(0), isDie(false)
{
	position = pos;
	center = D3DXVECTOR2(100, 50);

	// ó�� ���� ��ġ�� ������ �� ������ pos.y�� ������
	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	velocity_Y += 32 * deltaTime; 
	position.y += velocity_Y;

	if (parentScene)
	{
		int tileIndex = position.x / gAssetManager->tile_Texture->width;

		if (parentScene->tileList.size() > tileIndex
			&& tileIndex >= 0) 
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
	}

	CMatrix::Update(deltaTime, camera->position);
	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
}


void CPlayer::Render(LPD3DXSPRITE sprite)
{
	CMatrix::Render(sprite);

	switch (upgrade)
	{
	case 0: // 1�ܰ�
		Draw(sprite, gAssetManager->player_1_Texture);
		break;
	case 1: // 2�ܰ�
		Draw(sprite, gAssetManager->player_2_Texture);
		break;
	case 2: // 3�ܰ�
		Draw(sprite, gAssetManager->player_3_Texture);
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
// �̵� ���� int dir (�� : -1, �� : +1)
{
	float speed = 600.0f;

	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = -10.0f;
	}
}
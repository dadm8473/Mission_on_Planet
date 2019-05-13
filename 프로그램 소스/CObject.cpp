#include "DXUT.h"
#include "Header.h"

CObject::CObject(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: type(inputType), camera(inputCamera), isDestroyed(false), isActive(true), hp(4)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	switch (type)
	{
	case 1:
		center = D3DXVECTOR2(128, 128);
		break;
	case 2:
		center = D3DXVECTOR2(128, 64);
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		SetAnimation(0.05f, 10, true);
		break;
	case 100:
		center = D3DXVECTOR2(128, 128);
		scale = D3DXVECTOR2(1.5f, 1.2f);
		break;
	case 777:
		if (ext_Stage == 2)
			position.y -= 128;
		center = D3DXVECTOR2(126, 80);
		break;
	default:
		break;
	}
}

void CObject::Update(float deltaTime)
{
	if (isActive)
	{
		switch (type)
		{
		case 1:
			currentScene = ext_Stage - 1;
			SetRect(&rect, position.x - 28, position.y - 18, position.x + 10, position.y + 28);
			break;
		case 2:
			SetRect(&rect, position.x - 100, position.y, position.x + 100, position.y + 9999);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
			break;
		case 100:
			SetRect(&rect, position.x, position.y - 128, position.x + 128, position.y + 128);
			break;
		case 777:
			SetRect(&rect, position.x - 64, position.y -1024, position.x + 64, position.y + 1024);
			break;
		default:
			SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
			break;
		}
	}
	else
		SetRect(&rect, position.x, position.y, position.x, position.y);

	if (hp <= 0)
	{
		isDestroyed = true;
		ext_Score += 70 + rand() % 80;
	}

	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Rock"));
		break;
	case 2:
		//Draw(sprite, gAssetManager->GetTexture("Hole"));
		break;
	case 11:
		Draw(sprite, gAssetManager->GetTexture("Item1"));
		break;
	case 12:
		Draw(sprite, gAssetManager->GetTexture("Item2"));
		break;
	case 13:
		Draw(sprite, gAssetManager->GetTexture("Item3"));
		break;
	case 14:
		Draw(sprite, gAssetManager->GetTexture("Item4"));
		break;
	case 15:
		Draw(sprite, gAssetManager->GetTexture("Item5"));
		break;
	case 16:
		Draw(sprite, gAssetManager->GetTexture("Item6"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("Upgrade"));
		break;
	case 777:
		switch (ext_Stage)
		{
		case 1:
			currentScene = 0;
			break;
		case 2:
			currentScene = 1;
			break;
		default:
			currentScene = 1;
			break;
		}
		Draw(sprite, gAssetManager->GetTexture("EndTile"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	}
}

#include "DXUT.h"
#include "Header.h"

CObject::CObject(CCamera * camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false), isActive(true)
{
	position = pos;

	switch (type)
	{
	case 0:
		center = D3DXVECTOR2(64, 32);
		scale.x = 1.3f;
		SetRect(&rect, position.x - 80, position.y - 50, position.x + 80, position.y + 50);
		break;
	case 1:
		center = D3DXVECTOR2(128, 75);
		SetRect(&rect, position.x - 108, position.y - 37, position.x + 108, position.y + 37);
		break;
	case 10: // 핵
	case 11: // 유도
	case 12: // 점프
	case 13: // 사거리
	case 14: // 이속
	case 15: // 3방향
		currentScene = type - 10;
		center = D3DXVECTOR2(32, 32);
		SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
		break;
	case 100:
		center = D3DXVECTOR2(126, 72.5f);
		scale = D3DXVECTOR2(1.3f, 1.5f);
		SetRect(&rect, position.x - 126, position.y - 72.5f, position.x + 126, position.y + 72.5f);
	case 777:
		SetRect(&rect, position.x - 128, position.y - 128, position.x + 128, position.y + 128);
		break;
	}
}

void CObject::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);

	if (!isActive)
		SetRect(&rect, position.x, position.y, position.x, position.y);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Trap"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Rock"));
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		Draw(sprite, gAssetManager->GetTexture("Item"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("Container"));
		break;
	}
}

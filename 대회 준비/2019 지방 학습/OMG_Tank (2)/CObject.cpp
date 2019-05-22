#include "DXUT.h"
#include "Header.h"

CObject::CObject(CCamera * camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false), isActive(true)
{
	position = pos;

	switch (type)
	{
	case 0:
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
		break;
	case 1:
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
		break;
	case 10: // 핵
	case 11: // 유도
	case 12: // 점프
	case 13: // 사거리
	case 14: // 이속
	case 15: // 3방향
		currentScene = type - 10;
		SetRect(&rect, position.x - 100, position.y, position.x + 156, position.y + 100);
		break;
	case 100:
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
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

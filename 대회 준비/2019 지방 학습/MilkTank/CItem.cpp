#include "DXUT.h"
#include "Header.h"

CItem::CItem(CCamera * camera, D3DXVECTOR2 pos, bool isContainer)
	:CMatrix(), camera(camera), isUse(false)
{
	position = pos;

	if (!isContainer)
	{
		center.x = 32;
		center.y = 32;

		SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);

		currentScene = index = rand() % gAssetManager->GetTexture("Item")->maxScene;
	}
	else
	{
		center.x = 126;
		center.y = 120;

		SetRect(&rect, position.x - 5, position.y - 50, position.x + 5, position.y + 35);
		SetRect(&bulletRect, position.x - 126, position.y - 120, position.x + 126, position.y + 35);

		index = -1;
	}
}

void CItem::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
} 

void CItem::Render(LPD3DXSPRITE sprite)
{
	if (index >= 0)
		Draw(sprite, gAssetManager->GetTexture("Item"));
	else // 컨테이너
		Draw(sprite, gAssetManager->GetTexture("Container"));
}

#include "DXUT.h"
#include "Header.h"

CTrap::CTrap(CCamera* camera, D3DXVECTOR2 pos)
	:CMatrix(), camera(camera)
{
	position = pos;

	SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
}

void CTrap::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
}

void CTrap::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->object_TrapTexture);
}
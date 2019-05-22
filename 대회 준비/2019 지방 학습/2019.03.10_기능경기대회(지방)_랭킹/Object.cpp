#include "DXUT.h"
#include "Header.h"

CObject::CObject(CCamera* camera, D3DXVECTOR2 pos, int type)
	:CMatrix(), camera(camera), type(type), isDestroyed(false)
{
	position = pos;

	if (type == 0) // ������
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
	else if (type == 1) // ����
		SetRect(&rect, position.x + 100, position.y, position.x + 156, position.y + 100);
}

void CObject::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	if (type == 0) // ������
		Draw(sprite, gAssetManager->object_TrapTexture);
	else if (type == 1) // ����
		Draw(sprite, gAssetManager->object_RockTexture);
}
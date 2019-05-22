#include "DXUT.h"
#include "Header.h"

CObject::CObject(D3DXVECTOR2 pos, int inputType, CCamera * camera)
	: camera(camera), type(inputType), hp(10), isDestroyed(false)
{
	position = pos;
	
	center = D3DXVECTOR2(100, 50);
	
	switch (type)
	{
	case 1: // µ¹
		break;
	case 2: // ±¸¸Û
		break;
	}
}

void CObject::Update(float deltaTime)
{
	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);

	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
}

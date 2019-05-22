#include "DXUT.h"
#include "Header.h"

CObject::CObject(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);
}

void CObject::Update(float deltaTime)
{
	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Object"));
}

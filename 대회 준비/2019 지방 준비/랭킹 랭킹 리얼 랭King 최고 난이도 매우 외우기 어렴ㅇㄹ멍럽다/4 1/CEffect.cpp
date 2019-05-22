#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: type(inputType), camera(inputCamera), isDestoryed(false)
{
	position = pos;
	center = D3DXVECTOR2(128, 128);

	SetAnimation(0.3f, 3, false);
}

void CEffect::Update(float deltaTime)
{
	if (isAniEnd)
		isDestoryed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Effect"));
}

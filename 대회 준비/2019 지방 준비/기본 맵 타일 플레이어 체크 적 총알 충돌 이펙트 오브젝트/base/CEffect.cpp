#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, CCamera * camera, D3DXVECTOR2 inputScale)
	: isDestroyed(false), camera(camera)
{
	position = pos;
	scale = inputScale;
	center = D3DXVECTOR2(320, 240);

	SetAnimation(0.03f, 20, false);
}

void CEffect::Update(float deltaTime)
{
	if (isAniEnd)
		isDestroyed = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Effect"));
}

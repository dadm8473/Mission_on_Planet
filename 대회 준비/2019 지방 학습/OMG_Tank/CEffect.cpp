#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, int type, CCamera * camera, D3DXVECTOR2 scale_)
	: type(type), camera(camera), mustDestroy(false)
{
	position = pos;

	texture = gAssetManager->GetTexture("effect");
	SetAnimation(0.03f, 20, false);

	center.x = texture->imageInfo.Width / 2.f;
	center.y = texture->imageInfo.Height / 2.f;
	scale = scale_;
}

void CEffect::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);

	if (isAniEnd)
		mustDestroy = true;
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, texture);
}
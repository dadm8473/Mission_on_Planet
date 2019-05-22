#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, CTexture*tex, int maxScene, float animationTime)
	:CMatrix(), effectTexture(tex)
{
	position = pos;

	center.x = tex->width / 2.f;
	center.y = tex->height / 2.f;

	SetAnimation(maxScene, animationTime, false);
}

void CEffect::Update(float deltaTime)
{
	CMatrix::Update(deltaTime);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, effectTexture);
}
#pragma once

class CEffect : public CMatrix
{
public:
	CTexture * effectTexture;
	CEffect(D3DXVECTOR2 pos, CTexture*tex, int maxScene, float animationTime);

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
#pragma once

class CEffect : public CMatrix
{
public:
	CCamera* camera;

	bool mustDestroy;
	int type;
	CTexture* texture;

	CEffect(D3DXVECTOR2 pos, int type, CCamera* camera, D3DXVECTOR2 scale_ = D3DXVECTOR2(1, 1));

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
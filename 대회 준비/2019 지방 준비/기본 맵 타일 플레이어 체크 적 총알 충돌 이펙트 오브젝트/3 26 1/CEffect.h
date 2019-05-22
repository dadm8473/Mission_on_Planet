#pragma once
class CEffect : public CMatrix
{
public:
	CCamera* camera;
	bool isDestroyed;

public:
	CEffect(D3DXVECTOR2 pos, CCamera* camera, D3DXVECTOR2 inputScale = D3DXVECTOR2 (1,1));
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


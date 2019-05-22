#pragma once
class CEffect : public CMatrix
{
public:
	CCamera* camera;

	int type;
	bool isDestroyed;

public:
	CEffect(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


#pragma once
class CEffect : public CMatrix
{
public:
	CCamera* camera;

	int type;
	bool isDestoryed;

public:
	CEffect(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


#pragma once
class CTrap : public CMatrix
{
public:
	CCamera * camera;
	RECT rect;

public:
	CTrap(CCamera* camera, D3DXVECTOR2 pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


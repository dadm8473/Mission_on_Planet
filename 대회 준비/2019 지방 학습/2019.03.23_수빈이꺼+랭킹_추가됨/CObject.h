#pragma once

class CObject : public CMatrix
{
public:
	CCamera * camera;
	int type;
	RECT rect;

	int hp;
	bool isDestroyed;
	bool isActive;

public:
	CObject(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


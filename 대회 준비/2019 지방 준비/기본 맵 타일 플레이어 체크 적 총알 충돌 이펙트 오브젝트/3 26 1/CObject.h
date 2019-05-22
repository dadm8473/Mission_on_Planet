#pragma once
class CObject : public CMatrix
{
public:
	CCamera* camera;

	int type;

	int hp;
	bool isDestroyed;

	RECT rect;

public:
	CObject(D3DXVECTOR2 pos, int inputType, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


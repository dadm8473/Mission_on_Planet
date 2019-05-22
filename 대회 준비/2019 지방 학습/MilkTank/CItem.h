#pragma once
class CItem : public CMatrix
{
public:
	CCamera* camera;

	bool isUse;

	int index;

	RECT rect;
	RECT bulletRect;

public:
	CItem(CCamera* camera, D3DXVECTOR2 pos, bool isContainer = false);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


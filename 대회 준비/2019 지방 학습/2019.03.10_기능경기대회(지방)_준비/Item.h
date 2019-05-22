#pragma once

class CItem : public CMatrix
{
public:
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	bool isUse;

	int index;

	//�浹
	RECT rect;
	RECT bulletRect;

	CItem(CCamera* camera, D3DXVECTOR2 pos, bool isContainer = false);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
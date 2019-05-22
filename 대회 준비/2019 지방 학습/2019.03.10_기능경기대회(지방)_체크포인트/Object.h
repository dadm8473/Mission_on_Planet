#pragma once

class CObject : public CMatrix
{
public:
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	int type;

	//�浹
	RECT rect;

	//ü��
	int hp;
	bool isDestroyed;

	CObject(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
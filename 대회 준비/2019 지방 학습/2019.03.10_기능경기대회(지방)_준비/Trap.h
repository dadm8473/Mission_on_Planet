#pragma once

class CTrap : public CMatrix
{
public:
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	//�浹
	RECT rect;

	CTrap(CCamera* camera, D3DXVECTOR2 pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
#pragma once

class CTile : public CMatrix
{
public:
	CCamera * camera;

	int type;
	// Type 0 : ����
	// Type 1 : ������
	// Type 2 : ������
	CTile(D3DXVECTOR2 pos, int type, CCamera * intputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	float GetGround_Y_Pos(float posX);
};
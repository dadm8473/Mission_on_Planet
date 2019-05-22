#pragma once

class CTile : public CMatrix
{
public:
	CCamera * camera;

	int type;
	// Type 0 : 평지
	// Type 1 : 오르막
	// Type 2 : 내리막
	CTile(D3DXVECTOR2 pos, int type, CCamera * intputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	float GetGround_Y_Pos(float posX);
};
#pragma once

class CTile : public CMatrix
{
public:
	CCamera * camera;

	int type;
	// Type 0 - 평지
	// Type 1 - 오르막
	// Type 2 - 내리막

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	// X 좌표를 넣으면 바닥 좌표를 넘겨줌
	float GetGround_Y_Pos(float posX);
};


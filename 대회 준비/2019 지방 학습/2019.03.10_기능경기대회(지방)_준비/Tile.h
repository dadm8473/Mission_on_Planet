#pragma once

class CTile : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	int type;
	// Type 0 : 평지
	// Type 1 : 오르막
	// Type 2 : 내리막
	CTile(D3DXVECTOR2 pos, int type, CCamera * intputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	float GetGround_Y_Pos(float posX);
	// X 좌표를 넣으면 바닥 좌표를 넘겨주는 함수
};
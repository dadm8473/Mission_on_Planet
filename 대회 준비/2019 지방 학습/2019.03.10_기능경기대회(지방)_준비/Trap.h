#pragma once

class CTrap : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	//충돌
	RECT rect;

	CTrap(CCamera* camera, D3DXVECTOR2 pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
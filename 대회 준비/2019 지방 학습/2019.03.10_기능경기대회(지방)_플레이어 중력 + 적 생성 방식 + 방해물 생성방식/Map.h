#pragma once

class CMap
{
public :
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	CMatrix skyLayer[2];
	CMatrix midLayer[2];

	CMap(int stage, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
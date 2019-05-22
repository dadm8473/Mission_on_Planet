#pragma once

class CItem : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	bool isUse;

	int index;

	//충돌
	RECT rect;
	RECT bulletRect;

	CItem(CCamera* camera, D3DXVECTOR2 pos, bool isContainer = false);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
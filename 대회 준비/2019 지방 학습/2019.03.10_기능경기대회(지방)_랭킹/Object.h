#pragma once

class CObject : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	int type;

	//충돌
	RECT rect;

	//체력
	int hp;
	bool isDestroyed;

	CObject(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
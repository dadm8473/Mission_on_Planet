#pragma once
class CBullet : public CMatrix
{
public:
	CCamera* camera;

	int type;

	float speed;
	float timer;
	float moveAnlge;

	bool isDestroyed;
	RECT rect;

public:
	CBullet(D3DXVECTOR2 pos, CCamera* inputCamera, int inputType, float inputSpeed, float inputMoveAngle, float inputTimer = 3);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


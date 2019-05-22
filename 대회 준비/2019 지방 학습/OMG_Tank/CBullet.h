#pragma once
class CBullet : public CMatrix
{
public:
	CCamera * camera;

	int type;

	float speed;
	float moveAngle;

	int damage;
	float timer;

	RECT rect;
	int isDestroyed;

public:
	CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float timer = 5);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


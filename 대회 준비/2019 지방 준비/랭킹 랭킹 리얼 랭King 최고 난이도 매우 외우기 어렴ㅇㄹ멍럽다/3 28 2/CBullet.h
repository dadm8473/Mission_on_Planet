#pragma once
class CBullet : public CMatrix
{
public:
	CCamera* camera;

	int type;
	int damage;

	float moveAngle;
	float timer;
	float speed;

	bool isDestroyed;
	RECT rect;

public:
	CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float timer = 3);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


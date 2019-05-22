#pragma once
class CBullet : public CMatrix
{
public:
	CCameara* camera;

	int type;
	
	float moveAngle;
	float speed;
	float timer;

	bool isDestroyed;
	RECT rect;

public:
	CBullet(D3DXVECTOR2 pos, CCameara* camera, int type, float moveAngle, float speed, float timer = 1);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


#pragma once

class CBullet;
class CObject;
class CEnemy;

class CBullet : public CMatrix
{
public:
	CCamera* camera;

	CBullet* target1;
	CEnemy* target2;
	CObject* target3;

	float targetTimer;

	int type;

	float moveAngle;
	float timer;
	float speed;

	bool isDestroyed;

	RECT rect;

public:
	CBullet(D3DXVECTOR2 pos, CCamera* inputCamera, int inputType, float inputMoveAngle, float inputSpeed, float inputTimer = 1, 
		CBullet* target1 = NULL, CEnemy* target2 = NULL, CObject* target3 = NULL);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


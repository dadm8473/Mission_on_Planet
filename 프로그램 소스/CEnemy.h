#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	int type;
	int hp;

	float attackTimer;
	float attackTime;

	bool beHit;
	float redTimer;
	float redTime;

	bool isDestroyed;
	bool isDie;
	
	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


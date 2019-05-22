#pragma once
class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCameara* camera;
	CGameScene* parentScene;

	int type;

	float attackTimer;
	float attackTime;

	bool isDie;
	bool isDestroyed;

	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCameara* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


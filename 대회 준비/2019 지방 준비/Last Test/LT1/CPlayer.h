#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCameara* camera;
	CGameScene* parentScene;

	float velocitry_Y;
	float ground_Y_pos;

	int jumpCount;

	// Attack
	bool isAttack;
	float attackTimer;
	float attackTime;
	float rich;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCameara* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
};


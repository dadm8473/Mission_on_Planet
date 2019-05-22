#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CGameScene* parentScene;
	CMatrix* target;
	CCamera* camera;

	float ground_Y_Pos;
	float velocity_Y;

	int jumpCount;

public:
	bool isAttack;
	float attackTimer;
	float attackTime;

public:
	bool isAttack_H;
	float attackTimer_H;
	float attackTime_H;

public:
	float speed;
	float rich;

	bool isMultiAttack;
	bool isHomingAttack;


public:
	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void GetTarget(CMatrix* inputTarget) { target = inputTarget; }

public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
	void Attack_H();

public:
	void DoubleJump();
	void SpeedUP();
	void LongAttack();
	void MultiAttack();
	void HomingAttack();

	void Reset();
};


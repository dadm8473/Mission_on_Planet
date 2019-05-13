#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	CBullet* target1;
	CEnemy* target2;
	CObject* target3;
	

	float velocity_Y;
	float velocity_X;
	float ground_Y_Pos;

	int jumpCount;
	float speed;
	int upgrade;


	// Attack
	bool isAttack;
	float attackTimer;
	float attackTime;
	float rich;

	// Attack Sky
	bool isAttack_Sky;
	float attackTimer_Sky;
	float attackTime_Sky;

	// item effect
	bool isMulti;
	bool isHoming;
	bool isDoubleJump;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void SetTarget1(CBullet* inputTarget) { target1 = inputTarget; }
	void SetTarget2(CEnemy* inputTarget) { target2 = inputTarget; }
	void SetTarget3(CObject* inputTarget) { target3 = inputTarget; }


public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
	void Attack_Sky();

public:
	void DoubleJump();
	void SpeedUp();
	void LongAttack();
	void MultiAttack();
	void HomingAttack();

	void Reset();
};


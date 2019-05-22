#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;
	CEnemy* target;

	float velocitry_Y;
	float ground_Y_Pos;

	int jumpCount;
	float speed;
	float rich;

	bool isAttack;
	float attackTimer;
	float attackTime;

	bool isMultiAttack;
	bool isHomingAttack;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
	void SetTarget(CEnemy* enemy) { target = enemy; }

public:
	void DoubleJump();
	void SpeedUP();
	void LongAttack();
	void MultiAttack();
	void HomingAttack();
	void Reset();
};


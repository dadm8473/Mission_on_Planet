#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;
	CEnemy* target;

	float ground_Y_Pos;
	float velocity_Y;

	int jumpCount;

	float speed;
	float richTimer;
	bool isMultiAttack;
	bool isHomingAttack;

	bool isAttack;
	float attackTimer;
	float attackTime;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
	void SetTarget(CEnemy* enemy = NULL) { target = enemy; }

public:
	void DoubleJump();
	void SpeedUp();
	void LongAttack();
	void MultiAttack();
	void HomingAttack();

	void Reset();
};


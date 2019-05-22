#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera * camera;
	CGameScene* parentScene;
	CEnemy* target;

	float velocity_Y;
	float ground_Y_Pos;

	int jumpCount;
	float speed;
	float rich;

	int upgrade;

	bool isDie;

	RECT rect;

	float attackTimer;
	float attackTime;

	bool isAttacking;

	bool homingAttack;
	bool doubleJump;
	bool attackRich;
	bool speedUp;
	bool multiAttack;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	void Attack();
	void Move(int dir, float deltaTime);
	void Jump();
	void SetEnemyPos(CEnemy* enemy = NULL) { target = enemy; }
	void AllFalse();
	void Upgrade();
};


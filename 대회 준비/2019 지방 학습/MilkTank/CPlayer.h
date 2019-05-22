#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	struct ItemEffect
	{
	public:
		bool on;
		float time;
		float timer;

		ItemEffect(float time) : on(false), time(time)
		{}
		void Active()
		{
			on = true;
			timer = 0.0f;
		}
		void Update(float deltaTime)
		{
			if (!on) return;
			timer += deltaTime;
			if (timer >= time)
				on = false;
		}
	};

public:
	CGameScene * parentScene;
	CCamera * camera;

	// 중력
	float velocity_Y;
	// 플레이어는 velocity_Y의 값이 - 면 떨어지고 + 면 뛰어오른다.

	// 땅 위치
	float ground_Y_Pos;
	// 점프 카운트
	int jumpCount;
	// 업그레이드 관련 변수
	int upgrade;

	// 아이템 관련 변수
	ItemEffect homingMissile;
	ItemEffect longShot;
	ItemEffect powerUp;
	ItemEffect doubleJump;
	bool speedUp;

	// 공격 관련 변수 & 함수들
	float attackTimer;
	float attackTime;
	float attackIntervalTimer;
	float attackIntervalTime;

	int mainAttackCounter;
	int mainAttackCount;

	int skyAttackCounter;
	int skyAttackCount;

	int homingAttackCounter;
	int homingAttackCount;

	bool isDie;
	RECT rect;

	//무적
	bool isInvincible; 
	float invincibleTimaer;
	float invincibleTimae;

	bool isAttacking;
	bool isAttackInterval;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camrea);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void Move(int dir, float deltaTime);
	void Attack();
	void Jump();
};
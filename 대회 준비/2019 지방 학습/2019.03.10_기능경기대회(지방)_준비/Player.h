#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public :
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

	CGameScene * parentScene;

	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	// �߷�, ������ Y�� ��ȭ�� ���� �����̴�.
	float velocity_Y;
	// �÷��̾�� velocity_Y�� ���� - �� �������� + �� �پ������.

	// �� ��ġ
	float ground_Y_Pos;

	// ���� ī��Ʈ
	int jumpCount;

	// ���׷��̵� ���� ����
	int upgrade;

	// ������ ���� ����
	ItemEffect homingMissile;
	ItemEffect longShot;
	ItemEffect powerUp;
	ItemEffect doubleJump;
	bool speedUp;

	// ���� ���� ���� & �Լ���
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

	bool isInvincible; //�����ΰ�?
	float invincibleTimaer;
	float invincibleTimae;

	bool isAttacking;
	bool isAttackInterval;

	void Move(int dir, float deltaTime);
	void Attack();
	void Jump();

	CPlayer(D3DXVECTOR2 pos, CCamera* camrea);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
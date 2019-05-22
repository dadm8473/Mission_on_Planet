#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene* parentScene;
	CCamera* camera;

	// �߷�
	float velocity_Y;

	// �� ��ġ
	float gorund_Y_Pos;

	int type;
	// type 0 - ��ֹ�

	// �������� 1, 2
	// type 1- �Ʒ��� ��ź�� ���� �ϸ鼭 ������
	// type 2 - �÷��̾ ���� �Ѿ��� ��� ������

	bool isDestroyed;

	float attackTimer;
	float attackTime;

	float exitTimer;
	float exitTime;
	bool exit;
	float speed;

	RECT rect;

	int hp;
	bool isDie;

public:
	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


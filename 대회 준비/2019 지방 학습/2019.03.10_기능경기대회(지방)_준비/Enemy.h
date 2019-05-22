#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene * parentScene;
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	// �߷�, ������ Y�� ��ȭ�� ���� �����̴�.
	float velocity_Y;

	// �� ��ġ
	float ground_Y_Pos;

	int type;
	// Ÿ��0: �� or ��ֹ�
	
	// �������� 1
	// Ÿ��1: ���ͼ� �Ʒ��� ��ź ������ �ڷ� �����
	// Ÿ��2: ���ͼ� �÷��̾ ���� �Ѿ� �߻�

	// �������� 2
	// Ÿ��1: ���ͼ� �Ʒ��� ��ź ������ �ڷ� �����
	// Ÿ��2: ���ͼ� �÷��̾ ���� �Ѿ� �߻�

	bool isDestroyed;

	float attackTimer;
	float attackTime;

	float exitTimer;
	float exitTime;
	bool exit;
	float speed;

	//�浹
	RECT rect;

	//ü��
	int hp;
	bool isDie;

	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
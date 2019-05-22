#pragma once
class CGameScene;
class CBullet : public CMatrix
{
public:
	CGameScene * parentScene;

	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	int type; //�Ѿ�Ÿ��

	float speed;		//�����̴� �ӵ�
	float moveAngle;	//�����̴� ����(������ ǥ�õ�)

	int damage;			//�� �Ѿ��� �ӱݰ� �ִ� ������

	float destroyTime;	// �Ѿ� ���ӽð�
	float destroyTimer;
	bool isDestroyed;	//�Ѿ��� �ı��Ǿ��°� �˻��ϴ� ����

	RECT rect;

	// ȣ�� �̻��� ����
	D3DXVECTOR2* targetPos;
	float homingTimer;
	float homingTime;
	float homingSpeed;

	// ��� źȯ + �ٴ� �浹�� ���� ����
	float velocity_Y;

	// �� ��ġ
	float ground_Y_Pos;

	void SetHoming(D3DXVECTOR2* target, float time, float speed);

	CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float destoryTime);
	virtual void Update(float deltaTIme);
	virtual void Render(LPD3DXSPRITE sprite);
};
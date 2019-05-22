#pragma once

// ���� �⺻���� �÷��̾� �ڵ忡 �̹� ������ �߰��� �ڵ带 ���ϱ⸸ ����
// �̰ɺ��� ���� �ڵ忡 �����غ���

// Header.h ������ CPlayer�� ������� CGameScene�� �ҷ��� �� ��� �̷��� ������ �̸��Ѵ�.
class CGameScene;
class CPlayer : public CMatrix
{
public:
	// �÷��̾ GameScene�� �����ϱ� ���� �����̴�.
	// �̰����� �÷��̾�� GameScene�� ������ Ÿ�� ����Ʈ�� �ҷ��� �� �ִ�.
	CGameScene * parentScene;

	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	// �߷�, ������ Y�� ��ȭ�� ���� �����̴�.
	// �� velocity_Y ������ �̿��� �÷��̾��� Y�� ��ǥ�� ������ ��
	// velocity_Y�� ���� -�� �ϴ÷� �ö󰡰� +�� ������ ��
	float velocity_Y;
	float ground_Y_Pos; // �� ��ġ

	// ���� ī��Ʈ
	// ���� ������ �� �� �ִ� ī��Ʈ
	int jumpCount;

	// ���׷��̵� ���� ����
	// ��ȹ���� ���� �÷��̾��� ��ũ�� �� 3�ܰ�� ��ȭ�ȴٰ� ������ �װ� ���� ��
	int upgrade;
	
	// ���� ó�� �ϴ� �� ���� ����
	bool isDie;
	// �浹 ó�� ���� ���� ����
	RECT rect;

	// ������ ����� ���ð��ӵ��� GameScene���� Player->position�� ���� �������� ��
	// �̹� ���ӿ����� �Լ��� �̿��ϵ��� ��
	// ������ ������ �����۶� �����ϵ��� �ϰ���
	void Move(int dir, float deltaTime);

	// �� �Լ��� ȣ���� �� ������ �� ����
	void Jump();

	CPlayer(D3DXVECTOR2 pos, CCamera* camrea);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
#pragma once

// Enemy�� ���� ���� + ī�޶� ���� ������ ����� �� ����� �ƹ� ����� �������� �ʾ���
// ��¥ �׳� ���� ����ó�� �ڵ� �����ϸ� ��
class CGameScene;
class CEnemy : public CMatrix
{
public:
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	int type;

	//�浹
	RECT rect;

	//ü��
	int hp;
	bool isDie;
	bool isDestroyed;

	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
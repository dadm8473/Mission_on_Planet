#pragma once

// ���� ��� �ϼ����� ���� ������Ʈ�� �ı������� �� ������ Enemy�� Type���� ���µ�
// �����غ��� �׳� �����̶� ������ Object�� ��ġ�°� �´� �� ����
// CObject�� ����� �׳� �浹 üũ�� ������ ü�¸� �������
class CObject : public CMatrix
{
public:
	// ī�޶� ������ ������ �߰����ش�.
	CCamera * camera;

	int type;

	//�浹
	RECT rect;

	//ü��
	int hp;
	bool isDestroyed;

	CObject(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
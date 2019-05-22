#pragma once

// ī�޶�
class CCamera
{
public:
	// ī�޶� ��ġ
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	// ī�޶� ������ ���Ѱ�
	D3DXVECTOR2 limitPos_Min;
	D3DXVECTOR2 limitPos_Max;

	// ���� ���
	CMatrix* target;
	// ���� �ӵ�
	float speed;

public:
	CCamera();
	~CCamera();

	void Update(float deltaTime);
	// ���� ��� ���� �Լ�
	void SetTarget(CMatrix* inputTarget) { target = inputTarget; }
};
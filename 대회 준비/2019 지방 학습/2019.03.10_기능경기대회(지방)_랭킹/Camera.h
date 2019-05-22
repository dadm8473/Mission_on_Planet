#pragma once

// ���ӿ��� ���� ���� ī�޶�
class CCamera
{
public :
	// ī�޶��� ��ġ
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	// ī�޶� �������� �ּ� �ִ밪
	D3DXVECTOR2 limitPosition_Min;
	D3DXVECTOR2 limitPosition_Max;

	// ������ ���
	CMatrix* target;
	// ������ ������ ���� ����
	float trackingSpeed;

	CCamera();
	~CCamera();

	// ���� ��� ���� �Լ�
	void SetTarget(CMatrix* inputTarget);
	void Update(float deltaTime);
};
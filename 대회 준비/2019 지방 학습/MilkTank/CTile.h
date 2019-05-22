#pragma once

class CTile : public CMatrix
{
public:
	CCamera * camera;

	int type;
	// Type 0 - ����
	// Type 1 - ������
	// Type 2 - ������

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	// X ��ǥ�� ������ �ٴ� ��ǥ�� �Ѱ���
	float GetGround_Y_Pos(float posX);
};


#pragma once
class CTile : public CMatrix
{
public:
	CCamera* camera;

	int type;
	// type 0 : ����
	// type 1 : ������ 
	// type 2 : ������

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


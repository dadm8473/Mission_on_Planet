#pragma once
class CTile : public CMatrix
{
public:
	CCamera* camera;

	int type;
	// type 0 : 평지
	// type 1 : 오르막 
	// type 2 : 내리막

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


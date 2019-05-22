#pragma once
class CTile : public CMatrix
{
public:
	CCameara* camera;

	int type;

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCameara* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	float GetGround_Y_Pos(float xPos);
};


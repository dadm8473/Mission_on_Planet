#pragma once
class CCameara
{
public:
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	D3DXVECTOR2 limitPos_Max;
	D3DXVECTOR2 limitPos_Min;

	CMatrix* target;
	float speed;

public:
	CCameara();
	~CCameara();
	virtual void Update(float deltaTime);
	void SetTarget(CMatrix* inputTarget) { target = inputTarget; }
};


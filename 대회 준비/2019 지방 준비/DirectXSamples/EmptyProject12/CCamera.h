#pragma once
class CCamera
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	D3DXVECTOR2 limitPos_Min;
	D3DXVECTOR2 limitPos_Max;

	CMatrix* target;
	float speed;

public:
	CCamera();
	~CCamera();

	void SetTarget(CMatrix* inputTarget);
	virtual void Update(float deltaTime);
};


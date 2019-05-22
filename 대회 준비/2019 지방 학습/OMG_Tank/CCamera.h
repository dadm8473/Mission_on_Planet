#pragma once

class CCamera
{
public:
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	D3DXVECTOR2 limitPosition_Min;
	D3DXVECTOR2 limitPosition_Max;

	CMatrix* target;
	float trackingSpeed;

	CCamera();
	~CCamera();

	void SetTarget(CMatrix* inputTarget);
	void Update(float deltaTime);
};
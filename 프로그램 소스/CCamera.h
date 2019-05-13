#pragma once
class CCamera
{
public:
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	D3DXVECTOR2 limitPos_Min;
	D3DXVECTOR2 limitPos_Max;

	CMatrix* target;
	float speed;

	bool isCameraShake;
	int dir;
	float shakeTimer;
	float shakeTime;

	float timer;
	float time;
	int strong;

public:
	CCamera();
	~CCamera();
	virtual void Update(float deltaTime);
	void SetTarget(CMatrix* inputTarget) { target = inputTarget; }
	void ShakeCamera(float timer, int strong);
};


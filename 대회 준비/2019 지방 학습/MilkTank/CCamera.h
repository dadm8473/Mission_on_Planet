#pragma once

// 카메라
class CCamera
{
public:
	// 카메라 위치
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	// 카메라 움직임 제한값
	D3DXVECTOR2 limitPos_Min;
	D3DXVECTOR2 limitPos_Max;

	// 추적 대상
	CMatrix* target;
	// 추적 속도
	float speed;

public:
	CCamera();
	~CCamera();

	void Update(float deltaTime);
	// 추적 대상 지정 함수
	void SetTarget(CMatrix* inputTarget) { target = inputTarget; }
};
#pragma once

// 게임에서 사용될 가상 카메라
class CCamera
{
public :
	// 카메라의 위치
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;

	// 카메라 움직임의 최소 최대값
	D3DXVECTOR2 limitPosition_Min;
	D3DXVECTOR2 limitPosition_Max;

	// 추적할 대상
	CMatrix* target;
	// 대상까지 도달을 위한 변수
	float trackingSpeed;

	CCamera();
	~CCamera();

	// 추적 대상 지정 함수
	void SetTarget(CMatrix* inputTarget);
	void Update(float deltaTime);
};
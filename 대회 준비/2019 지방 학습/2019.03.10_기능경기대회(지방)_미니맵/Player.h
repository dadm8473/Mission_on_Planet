#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CGameScene * parentScene;

	CCamera * camera;

	float velocity_Y;
	float ground_Y_Pos; // 땅 위치

	// 점프 카운트
	int jumpCount;

	// 업그레이드 관련 변수
	int upgrade;
	
	bool isDie;
	RECT rect;

	void Move(int dir, float deltaTime);

	void Jump();

	CPlayer(D3DXVECTOR2 pos, CCamera* camrea);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
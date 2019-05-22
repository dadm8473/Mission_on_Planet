#pragma once

class CGameScene;
class CPlayer : public  CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	float ground_Y_Pos;
	float velocity_Y;

	int jumpCount;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

public:
	void Move(int dir, float deltaTime);
	void Jump();
};


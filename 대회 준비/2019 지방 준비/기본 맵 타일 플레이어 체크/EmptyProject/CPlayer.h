#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CGameScene* parentScene;

	CCamera* camera;

	float ground_Y_Pos;
	float velocity_Y;

	int jumpCount;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

	void Move(int dir, float deltaTime);
	void Jump();
};


#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	float velocity_Y;
	float ground_Y_Pos;

	int jumpCount;
	int upgrade;

	bool isDie;
	RECT rect;

public:
	CPlayer();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

public:
	void Jump();
	void Move(int dir, float deltaTime);
};

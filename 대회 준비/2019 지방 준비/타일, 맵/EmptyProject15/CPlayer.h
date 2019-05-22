#pragma once
class CGameScene;
class CPlayer : public CMatrix
{
public:
	CGameScene* parentScene;

	CCamera* camera;

	float velocity_Y;
	float ground_Y_Pos;

	int jumpCount;

	int upgrade;

	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void Move(int dir, float deltaTime);
	void Jump();
};


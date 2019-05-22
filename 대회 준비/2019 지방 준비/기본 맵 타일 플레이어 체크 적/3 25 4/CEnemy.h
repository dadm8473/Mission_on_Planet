#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	int type;
	int hp;

	bool isDie;
	bool isDestroyed;

	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprtie);
};


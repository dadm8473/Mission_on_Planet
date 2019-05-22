#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	int type;

	int hp;

	int speed;

	bool isDie;
	bool isDestroy;

	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int type, CCamera* camera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	float attackTimer;
	float attackTime;
	bool isDestroyed;

	int hp;
	float speed;
	int type;

	RECT rect;

public:
	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


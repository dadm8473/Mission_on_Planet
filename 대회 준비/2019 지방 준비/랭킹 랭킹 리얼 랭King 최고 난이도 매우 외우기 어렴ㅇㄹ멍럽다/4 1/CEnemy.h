#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene* parentScene;
	CCamera* camera;

	int type;
	float speed;

	bool isDie;
	bool isDestroyed;

	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

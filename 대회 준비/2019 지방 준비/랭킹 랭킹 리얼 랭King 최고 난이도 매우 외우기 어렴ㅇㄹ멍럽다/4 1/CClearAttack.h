#pragma once
class CGameScene;
class CClearAttack : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	bool isDestroyed;

public:
	CClearAttack(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


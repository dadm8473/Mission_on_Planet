#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene* parentScene;
	CCamera* camera;

	// 중력
	float velocity_Y;

	// 땅 위치
	float gorund_Y_Pos;

	int type;
	// type 0 - 장애물

	// 스테이지 1, 2
	// type 1- 아래로 폭탄을 투하 하면서 지나감
	// type 2 - 플레이어를 향해 총알을 쏘며 지나감

	bool isDestroyed;

	float attackTimer;
	float attackTime;

	float exitTimer;
	float exitTime;
	bool exit;
	float speed;

	RECT rect;

	int hp;
	bool isDie;

public:
	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};


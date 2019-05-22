#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene * parentScene;
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	// 중력, 점프의 Y축 변화를 위한 변수이다.
	float velocity_Y;

	// 땅 위치
	float ground_Y_Pos;

	int type;
	// 타입0: 돌 or 장애물
	
	// 스테이지 1
	// 타입1: 나와서 아래로 폭탄 떨구고 뒤로 사라짐
	// 타입2: 나와서 플레이어를 향해 총알 발사

	// 스테이지 2
	// 타입1: 나와서 아래로 폭탄 떨구고 뒤로 사라짐
	// 타입2: 나와서 플레이어를 향해 총알 발사

	bool isDestroyed;

	float attackTimer;
	float attackTime;

	float exitTimer;
	float exitTime;
	bool exit;
	float speed;

	//충돌
	RECT rect;

	//체력
	int hp;
	bool isDie;

	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
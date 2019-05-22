#pragma once
class CGameScene;
class CBullet : public CMatrix
{
public:
	CGameScene * parentScene;

	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	int type; //총알타입

	float speed;		//움직이는 속도
	float moveAngle;	//움직이는 방향(각도로 표시됨)

	int damage;			//이 총알이 머금고 있는 데미지

	float destroyTime;	// 총알 지속시간
	float destroyTimer;
	bool isDestroyed;	//총알이 파괴되었는가 검사하는 변수

	RECT rect;

	// 호밍 미사일 전용
	D3DXVECTOR2* targetPos;
	float homingTimer;
	float homingTime;
	float homingSpeed;

	// 곡사 탄환 + 바닥 충돌을 위한 변수
	float velocity_Y;

	// 땅 위치
	float ground_Y_Pos;

	void SetHoming(D3DXVECTOR2* target, float time, float speed);

	CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float destoryTime);
	virtual void Update(float deltaTIme);
	virtual void Render(LPD3DXSPRITE sprite);
};
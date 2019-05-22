#pragma once

// Enemy는 생성 설명 + 카메라 영역 나가면 지우는 것 빼고는 아무 기능을 구현하지 않았음
// 진짜 그냥 슈팅 게임처럼 코드 구현하면 됨
class CGameScene;
class CEnemy : public CMatrix
{
public:
	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	int type;

	//충돌
	RECT rect;

	//체력
	int hp;
	bool isDie;
	bool isDestroyed;

	CEnemy(CCamera* camera, D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
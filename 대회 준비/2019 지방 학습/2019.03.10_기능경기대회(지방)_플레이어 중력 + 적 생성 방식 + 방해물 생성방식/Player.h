#pragma once

// 아주 기본적인 플레이어 코드에 이번 과제에 추가된 코드를 더하기만 했음
// 이걸보고 너희 코드에 적용해보길

// Header.h 순서상 CPlayer는 원래라면 CGameScene을 불러올 수 없어서 이렇게 선언을 미리한다.
class CGameScene;
class CPlayer : public CMatrix
{
public:
	// 플레이어가 GameScene에 접근하기 위한 변수이다.
	// 이것으로 플레이어는 GameScene에 생성된 타일 리스트를 불러올 수 있다.
	CGameScene * parentScene;

	// 카메라에 영향을 받으면 추가해준다.
	CCamera * camera;

	// 중력, 점프의 Y축 변화를 위한 변수이다.
	// 이 velocity_Y 변수를 이용해 플레이어의 Y축 좌표를 움직일 것
	// velocity_Y의 값이 -면 하늘로 올라가고 +면 떨어질 것
	float velocity_Y;
	float ground_Y_Pos; // 땅 위치

	// 점프 카운트
	// 현재 점프를 할 수 있는 카운트
	int jumpCount;

	// 업그레이드 관련 변수
	// 기획서를 보면 플레이어의 탱크는 총 3단계로 강화된다고 써있음 그걸 위한 것
	int upgrade;
	
	// 죽음 처리 하는 것 땜에 넣음
	bool isDie;
	// 충돌 처리 예시 땜에 넣음
	RECT rect;

	// 기존에 만들던 슈팅게임들은 GameScene에서 Player->position을 직접 움직였을 것
	// 이번 게임에서는 함수를 이용하도록 함
	// 이유는 다음번 아이템때 설명하도록 하겠음
	void Move(int dir, float deltaTime);

	// 이 함수를 호출할 때 점프를 할 것임
	void Jump();

	CPlayer(D3DXVECTOR2 pos, CCamera* camrea);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * camera)	: CMatrix(), camera(camera), 
velocity_Y(0), jumpCount(1), upgrade(0), isDie(false)
// 생성자에서 변수 초기화는 꼭 해줘야함
{
	position = pos;
	center = D3DXVECTOR2(100, 50);

	// 처음 땅의 위치는 생성될 때 정해준 pos.y로 지정함
	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	// 중력 기능 =========================================================================
	// 원리 : 중력은 그냥 중력을 받는 오브젝트들의 Y좌표를 항상 아래로 더해주는 것이고
	//		  바닥충돌은 그냥 더 아래로 못내려가게 하는 것 뿐
	
	// 중력 적용
	// velocity_Y 변수 설명 : 중력을 받는 모든 오브젝트들이 가지고 있는 변수이고
	//						  하는 역할은 position.y += velocity_Y 이런식으로 항상 Y축에 더해지는 변수이다.
	//						  그래서 velocity_Y의 값이 -면 올라가고 +면 내려간다.

	velocity_Y += 32 * deltaTime; 
	// 중력 값 (예 : 32 * deltaTime) 을 더해준다.
	// = 대입이 아닌 += 덧셈을 하는 이유는 중력의 영향을 받아 점점 가속도를 받아 빨리 떨어지는 움직임을 위해서이다.
	
	position.y += velocity_Y;	  // 이런식으로 velocity_Y에 저장된 값을 더해주기 때문에 Y축 위치는 항상 바뀐다.

	// 바닥 좌표 업데이트 하기 ===========================================================
	// 이전에 CTile에서 만들었던 함수(GetGround_Y_Pos)를 이용해 바닥의 위치를 알아내는 것

	// 씬에 생성되있는 타일을 검사하여 현재 서있는 땅의 위치를 알아낸다.
	if (parentScene)
	{
		// 타일의 가로 길이를 이용하여 현재 서있는 위치를 알 수 있다.

		// 현재 위치 나누기 타일의 가로 길이를 하면 현재 밟고있는 타일의 번호(tileIndex)를 알 수 있다.
		int tileIndex = position.x / gAssetManager->tile_Texture->width;

		// 배열 인덱스 오류를 막기위해 GameScene에 생성된 TileList.size()의 크기와 비교한다.
		// 타일 리스트 사이즈를 넘을 경우 방지
		if (parentScene->tileList.size() > tileIndex
			&& tileIndex >= 0) 
			// 그리고 플레이어가 -좌표에 있으면 tileIndex도 - 값이 나올 수 있다.
			// 이것도 예외처리 해야함
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0) // 저 함수에서 0이 나왔다면 에러라서 0이 아닐때 처리해준다. 
				ground_Y_Pos = outY;
			// GetGround_Y_Pos 함수에 플레이어의 현재 Position.X를 넣어 바닥 위치를 업데이트한다.
		}
	}

	// position.y가 바닥좌표를 넘어 내려갔을 경우를 땅을 밟았다고 판단한다.
	if (position.y > ground_Y_Pos)
	{
		// 땅을 밟았을 때 초기화 해줘야 하는 부분을 여기서 초기화한다.
		position.y = ground_Y_Pos;

		// 땅에 닿으면 중력 가속도를 0으로 바꿔준다.
		velocity_Y = 0.0f;
		// 중력기능 끝 ===================================================================

		// 바닥에 닿았기 때문에 점프 횟수를 초기화 해준다.

		// 기획서에 아이템을 먹으면 2단 점프가 가능하다고 써있는데 여기서 처리해 줄 수 있다.

		// 점프 아이템 효과 예시 + 업그레이드 3단계는 2단 점프를 못한다고함
		/*
		if(doubleJump && upgrade != 2) 
			jumpCount = 2;
		else
			jumpCount = 1;
		*/

		jumpCount = 1;
	}

	CMatrix::Update(deltaTime, camera->position);
	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
}


void CPlayer::Render(LPD3DXSPRITE sprite)
{
	CMatrix::Render(sprite);

	// upgrade 변수를 증가하는 것으로 이미지 변경하면 탱크 업그레이드 부분 완성
	switch (upgrade)
	{
	case 0: // 1단계
		Draw(sprite, gAssetManager->player_1_Texture);
		break;
	case 1: // 2단계
		Draw(sprite, gAssetManager->player_2_Texture);
		break;
	case 2: // 3단계
		Draw(sprite, gAssetManager->player_3_Texture);
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
// 이동 방향 int dir (좌 : -1, 우 : +1)
{
	float speed = 600.0f;

	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	// 점프는 jumpCount 만큼만 가능하도록 해야 함
	if (jumpCount > 0)
	{
		jumpCount--;
		velocity_Y = -10.0f;
		// 여기에 점프의 힘(예 : -10)을 넣음
		// 음수인 이유는 위로 올라가야 하기 때문

		// 여기는 덧셈이 아니라 대입으로 해줘야 공중을 박차고 오르는 움직임이 나옴
	}
}

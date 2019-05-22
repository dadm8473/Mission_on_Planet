#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera) :CMatrix(), camera(inputCamera)
{
	position = pos;
	currentScene = type = inputType;
}

void CTile::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
}

void CTile::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->tile_Texture);
}

// 이 함수는 posX로 들어온 좌표가 지금 이 타일을 밟고 있는지 검사 후 바닥의 높이를 전달해주는 함수임
float CTile::GetGround_Y_Pos(float posX)
{
	float yPos = 0.0f;

	// 플레이어가 해당 타일을 밟을 때만

	// 위에 플레이어가 라고 써놓았지만 총알도 쓰고 적도 쓸 수 있음

	// posX가 이 타일의 position.x 보다 크거나 같고 거기에 텍스처의 가로길이를 더한 것 보다 작으면 밟고있다고 판단
	// 이것에 설명은 그림을 첨부함
	if (posX >= position.x  &&
		posX < position.x + gAssetManager->tile_Texture->width)
	{
		// 플레이어의 위치와 타일의 거리를 통해 타일을 지나간 정도를 계산을 위해 사용 될 변수
		float length = posX - position.x;

		// 경사로 인한 변화값을 지정해준다
		float value = 0.0f; // 기본값은 평지다 (이 값은 기울기이다)
		float delta_Y = 0.0f; // 오르막의 Y 포지션은 기울기 값만큼 높기에 보정을 해준다. 
		// 높이 보정값은 그림에 설명해두었다
		switch (type)
		{
		case 1: // 오르막
			delta_Y = 100.0f;
			value = -100.0f;
			break;
		case 2: // 내리막 
			value = 100.0f;
			break;
		}
		// 플레이어의 땅 기준점을 수정
		yPos = position.y + delta_Y + value * (length / gAssetManager->tile_Texture->width);
		// 최종 계산식은 현재 타일의 Position.Y를 기준으로 보정값 + 비율 계산값을 더한 최종값을 반환한다.
		// 비율 계산값에 대해서는 그림에 설명함
	}

	return yPos;
}

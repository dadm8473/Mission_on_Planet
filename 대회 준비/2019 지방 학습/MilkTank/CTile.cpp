#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: CMatrix(), camera(inputCamera)
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
	Draw(sprite, gAssetManager->GetTexture("Tile"));
}

float CTile::GetGround_Y_Pos(float posX)
{
	float posY = 0.0f;

	// 플레이어가 해당 타일을 밟을 때만
	if (posX >= position.x &&
		posX < position.x + gAssetManager->GetTexture("Tile")->width)
	{
		// 플레이어의 위치와 타일의 거리를 통해 타일을 지나간 정도를 계산
		float length = posX - position.x;

		// 경사로 인한 변화값을 지정해준다
		float value = 0.0f;		// 기본값은 평지
		float delta_Y = 0.0f;	// 오르막의 Y 포지션은 기울기 값 만큼 높기 때문에 보정을 해준다.

		switch (type)
		{
		case 1:
			delta_Y = 100.0f;
			value = -100.0f;
			break;
		case 2:
			value = 100.0f;
			break;
		}

		// 플레이어의 땅 기준점을 수정
		posY = position.y + delta_Y + value * (length / gAssetManager->GetTexture("Tile")->width);
	}

	return posY;
}

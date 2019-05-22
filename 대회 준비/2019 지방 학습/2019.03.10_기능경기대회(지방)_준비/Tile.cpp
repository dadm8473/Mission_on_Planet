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

float CTile::GetGround_Y_Pos(float posX)
{
	float yPos = 0.0f;

	// 플레이어가 해당 타일을 밟을 때만
	if (posX >= position.x  &&
		posX < position.x + gAssetManager->tile_Texture->width)
	{
		// 플레이어의 위치와 타일의 거리를 통해 타일을 지나간 정도를 계산
		float length = posX - position.x;

		// 경사로 인한 변화값을 지정해준다
		float value = 0.0f; // 기본값은 평지다
		float delta_Y = 0.0f; // 오르막의 Y 포지션은 기울기 값만큼 높기에 보정을 해준다.
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
	}

	return yPos;
}

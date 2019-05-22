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
	Draw(sprite, gAssetManager->GetTexture("Tile"));
}

float CTile::GetGround_Y_Pos(float posX)
{
	float yPos = 0.0f;
	if (posX >= position.x  &&
		posX < position.x + gAssetManager->GetTexture("Tile")->width)
	{
		float length = posX - position.x;

		float value = 0.0f;
		float delta_Y = 0.0f;
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
		yPos = position.y + 100 + delta_Y + value * (length / gAssetManager->GetTexture("Tile")->width);
	}

	return yPos;
}

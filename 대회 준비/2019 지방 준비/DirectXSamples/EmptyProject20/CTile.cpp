#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	:type(inputType), camera(inputCamera)
{
	position = pos;

	currentScene = type;
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
	float posY = 0;

	if (position.x <= posX &&
		posX < position.x + gAssetManager->GetTexture("Tile")->width)
	{
		float lenght = posX - position.x;

		float value = 0;
		float deltaY = 0;

		switch (type)
		{
		case 1:
			value = -100;
			deltaY = 100;
			break;
		case 2:
			value = 100;
			break;
		}

		posY = position.y + deltaY + value * (lenght / gAssetManager->GetTexture("Tile")->width);
	}

	return posY;
}

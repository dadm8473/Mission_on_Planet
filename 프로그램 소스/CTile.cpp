#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * intputCamera)
	: type(inputType), camera(intputCamera)
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
	switch (ext_Stage)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Tile"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Tile2"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("Tile"));
		break;
	}
}

float CTile::GetGround_Y_Pos(float xPos)
{
	float yPos = 0;

	if (position.x <= xPos && xPos < position.x + tileWidth)
	{
		float length = xPos - position.x;

		float value = 0;
		float deltaY = 0;

		switch (type)
		{
		case 1:
			value = -87;
			deltaY = 87;
			break;
		case 2:
			value = 87;
			break;
		}

		yPos = position.y + deltaY + value * (length / tileWidth);
	}

	return yPos;
}
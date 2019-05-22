#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: type(inputType), camera(inputCamera)
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

float CTile::GetGround_Y_Pos(int xPos)
{
	float yPos = 0;

	if (xPos >= position.x && xPos < position.x + tileWidth)
	{
		float legnth = xPos - position.x;

		float value = 0;
		float delta_Y = 0;

		switch (type)
		{
		case 1:
			value = -128;
			delta_Y = 128;
			break;
		case 2:
			value = 128;
			break;
		}

		yPos = position.y + delta_Y + value * (legnth / tileWidth);
	}

	return yPos;
}

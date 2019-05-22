#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCameara * inputCamera)
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

float CTile::GetGround_Y_Pos(float xPos)
{
	float yPos = 0;

	if (position.x <= xPos && xPos < position.x + tileWidth)
	{
		float legnth = xPos - position.x;

		float deltaY = 0;
		float value = 0;

		switch (type)
		{
		case 1:
			deltaY = 105;
			value = -105;
			break;
		case 2:
			value = 105;
			break;
		}

		yPos = position.y + deltaY + value * (legnth / tileWidth);
	}

	return yPos;
}

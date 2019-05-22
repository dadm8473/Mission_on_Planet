#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	:camera(inputCamera), type(inputType)
{
	position = pos;
	currentScene = type;
}

void CTile::Update(float delatTime)
{
	CMatrix::Update(delatTime, camera->position);
}

void CTile::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Tile"));
}

float CTile::GetGround_Y_Pos(float posX)
{
	float posY = 0;

	if (posX >= position.x &&
		posX < position.x + gAssetManager->GetTexture("Tile")->width)
	{
		float length = posX - position.x;

		float value = 0;
		float delta_Y = 0;
		 
		switch (type)
		{
		case 1: //오르막
			delta_Y = 100;
			value = -100;
			break;
		case 2: //내리막
			value = 100;
			break;
		}
		posY = position.y + delta_Y + value * (length / gAssetManager->GetTexture("Tile")->width);
	}

	return posY;
}

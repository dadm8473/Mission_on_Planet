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
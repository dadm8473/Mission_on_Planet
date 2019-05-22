#include "DXUT.h"
#include "Header.h"

CMap::CMap(int stage, CCamera * inputCamera)
	:camera(inputCamera)
{
	for (int i = 0; i < 2; ++i)
	{
		skyLayer[i] = CMatrix();
		skyLayer[i].position.x = 1024 * i;

		midLayer[i] = CMatrix();
		midLayer[i].position.x = 1024 * i;
		midLayer[i].position.y = 128;

		skyLayer[i].currentScene = stage;
		midLayer[i].currentScene = stage;
	}
}

void CMap::Update(float deltaTime)
{
	if (!camera)
		return;

	for (int i = 0; i < 2; ++i)
	{
		if (skyLayer->position.x <= camera->position.x / 3 - 1024)
			skyLayer->position.x += 1024 * 2;
		if (skyLayer->position.x >= camera->position.x / 3 + 1024)
			skyLayer->position.x -= 1024 * 2;

		if (midLayer->position.x <= camera->position.x / 1.5f - 1024)
			midLayer->position.x += 1024 * 2;
		if (midLayer->position.x >= camera->position.x / 1.5f + 1024)
			midLayer->position.x -= 1024 * 2;

		skyLayer[i].Update(deltaTime);
		midLayer[i].Update(deltaTime, camera->position / 1.5f);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; ++i)
		skyLayer[i].Draw(sprite, gAssetManager->GetTexture("Sky"));
	for (int i = 0; i < 2; ++i)
		midLayer[i].Draw(sprite, gAssetManager->GetTexture("Mid"));
}

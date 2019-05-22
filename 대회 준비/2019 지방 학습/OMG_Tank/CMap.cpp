#include "DXUT.h"
#include "Header.h"

CMap::CMap(int stage, CCamera* inputCamera) : camera(inputCamera)
{
	for (int i = 0; i < 2; i++)
	{
		skyLayer[i] = CMatrix();
		skyLayer[i].position.x = 1024 * i;

		midLayer[i] = CMatrix();
		midLayer[i].position.x = 1024 * i;
		//midLayer[i].position.y = -128;
		//midLayer[i].scale.x = 1.0023f;

		midLayer[i].currentScene = i;
	}
}

void CMap::Update(float deltaTime)
{
	if (camera == NULL) return;

	for (int i = 0; i < 2; i++)
	{
		if (skyLayer[i].position.x <= camera->position.x - 1024)
			skyLayer[i].position.x += 1024 * 2;

		if (skyLayer[i].position.x >= camera->position.x + 1024)
			skyLayer[i].position.x -= 1024 * 2;

		skyLayer[i].position.y = camera->position.y;

		if (midLayer[i].position.x <= camera->position.x / 1.5f - 1024)
			midLayer[i].position.x += 1024 * 2;

		if (midLayer[i].position.x >= camera->position.x / 1.5f + 1024)
			midLayer[i].position.x -= 1024 * 2;

		skyLayer[i].Update(deltaTime, camera->position);
		midLayer[i].Update(deltaTime, camera->position / 1.5f);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; i++)
		skyLayer[i].Draw(sprite, gAssetManager->GetTexture("Sky"));
	for (int i = 0; i < 2; i++)
		midLayer[i].Draw(sprite, gAssetManager->GetTexture("Mid"));
}

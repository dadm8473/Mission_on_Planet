#include "DXUT.h"
#include "Header.h"

CMap::CMap(int stage, CCamera * camera)
	: camera(camera)
{
	for (int i = 0; i < 2; ++i)
	{
		skyLayer[i] = CMatrix();
		skyLayer[i].position.x = 1024 * i;

		midLayer[i] = CMatrix();
		midLayer[i].position.x = 1024 * i;
		midLayer[i].position.y = -528;

		midLayer2[i] = CMatrix();
		midLayer2[i].position.x = 1024 * i;
		midLayer2[i].position.y = -352;
	}
}

void CMap::Update(float deltaTime)
{
	if (!camera)
		return;

	for (int i = 0; i < 2; ++i)
	{
		if (skyLayer[i].position.x <= camera->position.x / 5 - 1024)
			skyLayer[i].position.x += 1024 * 2;
		if (skyLayer[i].position.x >= camera->position.x / 5 + 1024)
			skyLayer[i].position.x -= 1024 * 2;

		skyLayer[i].position.y = camera->position.y / 5;

		if (midLayer[i].position.x <= camera->position.x / 3 - 1024)
			midLayer[i].position.x += 1024 * 2;
		if (midLayer[i].position.x >= camera->position.x / 3 + 1024)
			midLayer[i].position.x -= 1024 * 2;

		if (midLayer2[i].position.x <= camera->position.x / 1.5f - 1024)
			midLayer2[i].position.x += 1024 * 2;
		if (midLayer2[i].position.x >= camera->position.x / 1.5f + 1024)
			midLayer2[i].position.x -= 1024 * 2;

		skyLayer[i].Update(deltaTime, camera->position / 5);

		midLayer[i].Update(deltaTime, camera->position / 3);
		midLayer[i].currentScene = i;

		midLayer2[i].Update(deltaTime, camera->position / 1.5f);
		midLayer2[i].currentScene = i;
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; ++i)
		skyLayer[i].Draw(sprite, gAssetManager->GetTexture("Sky"));
	for (int i = 0; i < 2; ++i)
		midLayer[i].Draw(sprite, gAssetManager->GetTexture("Mid2"));
	for (int i = 0; i < 2; ++i)
		if(ext_Stage == 1)
			midLayer2[i].Draw(sprite, gAssetManager->GetTexture("Mid"));
		else
			midLayer2[i].Draw(sprite, gAssetManager->GetTexture("Mid3"));
}

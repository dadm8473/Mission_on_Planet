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
		midLayer[i].position.y = 128;
		
		skyLayer[i].currentScene = stage;
		midLayer[i].currentScene = stage;
	}
}

void CMap::Update(float deltaTime)
{
	if (camera == NULL) return;

	// 맵은 슈팅 게임에서 화면을 넘어가면 처음 위치로 돌리는 것과 같은 원리로
	// 카메라 오른쪽으로 넘어가면 왼쪽으로
	// 카메라 왼쪽으로 넘어가면 오른족으로
	// 이동시켜주는 코드임

	for (int i = 0; i < 2; i++)
	{
		// -->
		if (skyLayer[i].position.x <= camera->position.x / 3.0f - 1024)
			skyLayer[i].position.x += 1024 * 2;
		// <--
		if (skyLayer[i].position.x >= camera->position.x / 3.0f + 1024)
			skyLayer[i].position.x -= 1024 * 2;

		if (midLayer[i].position.x <= camera->position.x / 1.5f - 1024)
			midLayer[i].position.x += 1024 * 2;

		if (midLayer[i].position.x >= camera->position.x / 1.5f + 1024)
			midLayer[i].position.x -= 1024 * 2;


		// 이 부분에서 camera->Posistion에 일정 값을 나누는 것은
		// 예를 들어 Sky 레이어는 카메라의 1/3 거리 만 이동 한 것 처럼해서 멀리 있는 물체처럼 보이도록 하는 작업임
		skyLayer[i].Update(deltaTime, camera->position / 3.0f);
		midLayer[i].Update(deltaTime, camera->position / 1.5f);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; i++)
		skyLayer[i].Draw(sprite, gAssetManager->map_Sky_Texture);
	for (int i = 0; i < 2; i++)
		midLayer[i].Draw(sprite, gAssetManager->map_Mid_Texture);
}

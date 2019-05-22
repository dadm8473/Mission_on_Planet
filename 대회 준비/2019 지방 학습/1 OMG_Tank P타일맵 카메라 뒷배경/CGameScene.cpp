#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	:CScene(), tileEntryInfo(), currentTileEntryIndex(0), tileList()
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));

	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width - 1024.0f;

	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (mainCamera)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
			mainCamera->position.x -= 700 * deltaTime;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			mainCamera->position.x += 700 * deltaTime;
		if (GetKeyState(VK_UP) & 0x8000)
			mainCamera->position.y -= 700 * deltaTime;
		if (GetKeyState(VK_DOWN) & 0x8000)
			mainCamera->position.y += 700 * deltaTime;

		mainCamera->Update(deltaTime);
	}

	if (map)
		map->Update(deltaTime);

	TileUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);
}

void CGameScene::TileUpdate(float deltaTime)
{
	// 지금까지 보였던 타일의 길이
	float currentTileLength = tileList.size() * gAssetManager->GetTexture("Tile")->width;

	// 메인카메라 보다 1280 먼저 타일을 생성하기 위해
	// 메인카메라 위치 + 1280 가 타일의 길이 보다 길 경우 타일을 생성하기 위함
	while (mainCamera->position.x + 1280.0f > currentTileLength)
	{
		// i == tileEntryInfo의 마지막 과 비슷함
		// 사이즈가 보다 많이 만들 수 없으니 브레이크
		if (currentTileEntryIndex == tileEntryInfo.size())
			break;
		// 타일 높아지고 낮아지게 생성을 도와줄 친구
		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);
		// 타일 리스트 0 - 1은 -1 이므로 리스트 체크할 때 오류남 예외쳐리
		if (currentTileEntryIndex == 0)
		{
			entryPos.x = 0.0f;
			entryPos.y = 384.0f;
		}
		else
		{
			// 이전 타일 검사를 도와줄 친구
			CTile* t = tileList[currentTileEntryIndex - 1];
			// 다음 타일로 넘어가기 위해서 왼쪽 끝에서 오른쪽 끝으로 x를 이동 & 한칸 넘어가는 길이를 더해줌
			entryPos.x = t->position.x + gAssetManager->GetTexture("Tile")->width;
			// 이전에 높이를 올리고 내리고 했음으로 이전 타일 높이에 맞춰서 생성을 도와줄 친구
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // 오르막
				// 만약에 이전 타일이 2번이아니면 포스를 100 올려줌 마이너스가 올려주는거임 이해안되면 그림 배치놀이 해보셈
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
					entryPos.y -= 100.0f;
				break;
			default: // 평지 & 내리막
				// 만약 이전 타일이 2번이면 100을 내려서 생성
				if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
					entryPos.y += 100.0f;
				break;
			}
		}
		// 타일 생성 리스트에 넣기
		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile);
		// for문 i같은 친구 ++ 해주기
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

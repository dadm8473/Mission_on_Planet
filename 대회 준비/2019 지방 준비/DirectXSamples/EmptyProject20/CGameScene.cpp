#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileList(), tileEntryInfo()
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth;

	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete(*it);
	tileList.clear();

	if (mainCamera)
		delete mainCamera;

	if (map)
		delete map;
}

void CGameScene::Update(float deltaTime)
{
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
	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	float currentTileLength = tileList.size() * tileWidth;

	while(currentTileLength < mainCamera->position.x + 1280)
	{
		if (currentTileIndex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileIndex == 0)
			entryPos.y = 284;
		else
		{
			CTile* t = tileList()
		}
	}
}

#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	:tileEntryInfo(), currentTileEntryIndex(0), tileList()
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
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	mainCamera->SetTarget(NULL);
}


CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	delete mainCamera;
	delete map;
}

void CGameScene::Update(float deltaTime)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		mainCamera->position.x -= 700 * deltaTime;
	if (GetKeyState(VK_RIGHT) & 0x8000)
		mainCamera->position.x += 700 * deltaTime;
	if (GetKeyState(VK_UP) & 0x8000)
		mainCamera->position.y -= 700 * deltaTime;
	if (GetKeyState(VK_DOWN) & 0x8000)
		mainCamera->position.y += 700 * deltaTime;

	map->Update(deltaTime);
	mainCamera->Update(deltaTime);

	TileUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}

void CGameScene::TileUpdate(float deltaTime)
{
	float currentTileLength = tileList.size() * tileWidth;

	while (mainCamera->position.x + 1280 > currentTileLength)
	{
		if (currentTileEntryIndex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileEntryIndex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileEntryIndex - 1];
			
			entryPos.x += t->position.x + tileWidth;
			entryPos.y += t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1:
				if (tileEntryInfo[currentTileEntryIndex].type != 2)
					entryPos.y -= 100;
				break;
			default:
				if (tileEntryInfo[currentTileEntryIndex].type == 2)
					entryPos.y += 100;
				break;
			}
		}

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile);
		currentTileEntryIndex++;
	}
	
	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}


#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileList(), titleEntryInfo(), currentTileIndex(0), tileWidth(0)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	titleEntryInfo.push_back(TileEntryInfo(0));
	titleEntryInfo.push_back(TileEntryInfo(0));
	titleEntryInfo.push_back(TileEntryInfo(1));
	titleEntryInfo.push_back(TileEntryInfo(1));
	titleEntryInfo.push_back(TileEntryInfo(2));
	titleEntryInfo.push_back(TileEntryInfo(2));
	titleEntryInfo.push_back(TileEntryInfo(0));
	titleEntryInfo.push_back(TileEntryInfo(1));
	titleEntryInfo.push_back(TileEntryInfo(2));
	titleEntryInfo.push_back(TileEntryInfo(0));
	titleEntryInfo.push_back(TileEntryInfo(2));
	titleEntryInfo.push_back(TileEntryInfo(2));
	titleEntryInfo.push_back(TileEntryInfo(1));
	titleEntryInfo.push_back(TileEntryInfo(1));
	titleEntryInfo.push_back(TileEntryInfo(0));
	titleEntryInfo.push_back(TileEntryInfo(0));

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	mainCamera->limitPos_Max.x = titleEntryInfo.size() * tileWidth - 1024;

	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	if (mainCamera)
		delete mainCamera;
	if (map)
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

	if (mainCamera)
		mainCamera->Update(deltaTime);

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
}

void CGameScene::TileUpdate(float deltaTime)
{
	float currentTileLenght = tileList.size() * tileWidth;

	while (mainCamera->position.x + 1280 > currentTileLenght)
	{
		if (currentTileIndex == titleEntryInfo.size())
			return;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileIndex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileIndex - 1];
			
			entryPos.x = t->position.x + tileWidth;
			entryPos.y = t->position.y;

			switch (titleEntryInfo[currentTileIndex].type)
			{
			case 1:
				if (t->type != 2)
					entryPos.y -= 100;
				break;
			default:
				if (t->type == 2)
					entryPos.y += 100;
				break;
			}
		}

		CTile* tile = new CTile(entryPos, titleEntryInfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);
		currentTileIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

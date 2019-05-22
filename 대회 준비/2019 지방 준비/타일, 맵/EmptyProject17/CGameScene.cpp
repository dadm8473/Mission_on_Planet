#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), tileList(), currentTileEntryIndex(0)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

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

	player = new CPlayer(D3DXVECTOR2(100, 384), mainCamera);
	player->parentScene = this;

	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	if (player)
		delete player;

	delete mainCamera;
	delete map;
}

void CGameScene::Update(float deltaTime)
{
	if (player)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x8000)
			player->Move(1, deltaTime);

		player->Update(deltaTime);
	}

	mainCamera->Update(deltaTime);

	map->Update(deltaTime);

	TileUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	if (player)
		player->Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (player)
				player->Jump();
			break;
		}
		break;
	}
}

void CGameScene::TileUpdate(float deltaTime)
{
	float currentTileLegnth = tileList.size() * tileWidth;

	while (currentTileLegnth < mainCamera->position.x + 1280)
	{
		if (currentTileEntryIndex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entry = D3DXVECTOR2(0, 0);

		if (currentTileEntryIndex == 0)
			entry.y = 384;
		else
		{
			CTile* t = tileList[currentTileEntryIndex - 1];
			
			entry.x = t->position.x + tileWidth;
			entry.y = t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1:
				if (t->type != 2)
					entry.y -= 100;
				break;
			default:
				if (t->type == 2)
					entry.y += 100;
				break;
			}
		}

		CTile* tile = new CTile(entry, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile);
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

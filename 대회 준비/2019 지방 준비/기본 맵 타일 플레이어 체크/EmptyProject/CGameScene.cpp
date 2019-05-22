#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileIndex(0), tileList(0), playerLife(3), rebirthTime(3), rebirthTimer(0), checkPointIndex(0)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0, true));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;

	mainCamera->SetTarget(player);
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

	if (player)
		delete player;
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

		int tileIndex = player->position.x / tileWidth;
		if (tileIndex >= 0 && tileIndex < tileList.size())
		{
			if (tileEntryInfo[tileIndex].checkPoint && checkPointIndex < tileIndex)
				checkPointIndex = tileIndex;
		}

		if (player->isDie)
		{
			mainCamera->SetTarget(NULL);

			player = NULL;
			delete player;
		}
	}
	else
	{
		rebirthTimer += deltaTime;
		if (rebirthTimer > rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				D3DXVECTOR2 rebirthPos = tileList[checkPointIndex]->position - D3DXVECTOR2(128, 0);

				player = new CPlayer(rebirthPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				// 게임 오버
			}
		}
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
		case 'A':
			if (player)
				player->isDie = true;
			break;
		}
		break;
	}
}

void CGameScene::TileUpdate(float deltaTime)
{
	float currentTileLength = tileList.size() * tileWidth;

	while (currentTileLength <= mainCamera->position.x + 1280)
	{
		if (currentTileIndex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileIndex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileIndex - 1];

			entryPos.x = t->position.x + tileWidth;
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileIndex].type)
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

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);
		currentTileIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

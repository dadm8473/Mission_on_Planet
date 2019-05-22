#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileindex(0), tileList(), tileWidth(0), playerLife(3), rebirthTime(3), rebirthTimer(0), checkRebirthIndex(0),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0), enemyBulletList(), playerBulletList()
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0, true));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));

	enemyEntryInfo.push_back(EnemyEntryInfo(0, 2));
	
	tileWidth = gAssetManager->GetTexture("Tile")->width;

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;

	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	// Tile delete
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	// enemyList delete
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	// enemyBulletList delete
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete (*it);
	enemyBulletList.clear();

	// playerBulletList delete
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

	// mainCamera delete
	if (mainCamera)
		delete mainCamera;

	// map delete
	if (map)
		delete map;

	// player delete
	if (player)
		delete player;
}

void CGameScene::Update(float deltaTime)
{
	if (mainCamera)
		mainCamera->Update(deltaTime);

	if (map)
		map->Update(deltaTime);

	TileUpdate(deltaTime);

	PlayerUpdate(deltaTime);

	EnemyUpdate(deltaTime);

	BulletUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	// map  Render
	if (map)
		map->Render(sprite);

	// Tile List Render
	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	// enemy bullet Render
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	// player bullet Render
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	// player Render
	if (player)
		player->Render(sprite);

	// enemy Render
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			(*it)->Render(sprite);
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
		if (currentTileindex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileindex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileindex - 1];

			entryPos.x = t->position.x + tileWidth;
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileindex].type)
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

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileindex].type, mainCamera);
		tileList.push_back(tile);
		currentTileindex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

void CGameScene::PlayerUpdate(float deltaTime)
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
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex > checkRebirthIndex)
				checkRebirthIndex = tileIndex;

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
				D3DXVECTOR2 rebirthPos = tileList[checkRebirthIndex]->position;

				player = new CPlayer(rebirthPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				//게임오버
			}
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	if (player && enemyEntryInfo.size() > 0)
	{
		enemyEntryTimer += deltaTime;
		while (enemyEntryTimer > enemyEntryInfo[currentEnemyIndex].time)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 200);

			CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
			enemyList.push_back(enemy);
			currentEnemyIndex++;

			if (currentEnemyIndex >= enemyEntryInfo.size())
			{
				currentEnemyIndex = 0;
				enemyEntryTimer = 0;
				break;
			}
		}
	}

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDie)
		{
			// Score Effect
		}

		if ((*it)->isDestroy || (*it)->isDie)
		{
			delete (*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::BulletUpdate(float deltaTime)
{
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}
}

#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileIndex(0), tileList(), playerLife(3), rebirthTimer(0), rebirthTime(3), checkPointIndex(0),
	enemyEntryIinfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0), enemyBulletList(), playerBulletList()
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

	enemyEntryIinfo.push_back(EnemyEntryInfo(0, 1));

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;
	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete(*it);
	enemyBulletList.clear();

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete(*it);
	playerBulletList.clear();

	if (mainCamera)
		delete mainCamera;

	if (map)
		delete map;

	if (player)
		delete player;
}

void CGameScene::Update(float deltaTime)
{
	if (mainCamera)
		mainCamera->Update(deltaTime);

	if (map)
		map->Update(deltaTime);

	// Tile Update
	TileUpdate(deltaTime);
	// Player Update
	PlayerUpdate(deltaTime);
	// Enemy Update
	EnemyUpdate(deltaTime);
	// Bullet Update
	BulletUpdate(deltaTime);
	// Rect Update
	RectUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	if (player)
		player->Render(sprite);

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
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

	while (currentTileLength < mainCamera->position.x + 1280)
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

void CGameScene::PlayerUpdate(float deltaTime)
{
	if (player)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x8000)
			player->Move(1, deltaTime);

		int tileIndex = player->position.x / tileWidth;

		if (tileList.size() > tileIndex && tileIndex >= 0)
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex > checkPointIndex)
				checkPointIndex = tileIndex;

		player->Update(deltaTime);

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
				D3DXVECTOR2 entryPos = tileList[checkPointIndex]->position;

				player = new CPlayer(entryPos, mainCamera);
				mainCamera->SetTarget(player);
				player->parentScene = this;
			}
			else
			{
				// Game Over
			}
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	if (player && enemyEntryIinfo.size() > 0)
	{
		enemyEntryTimer += deltaTime;
		while (enemyEntryTimer > enemyEntryIinfo[currentEnemyIndex].timer)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 200);

			CEnemy* enemy = new CEnemy(entryPos, enemyEntryIinfo[currentEnemyIndex].type, mainCamera);
			enemyList.push_back(enemy);
			enemy->parentScene = this;
			currentEnemyIndex++;

			if (enemyEntryIinfo.size() <= currentEnemyIndex)
			{
				enemyEntryTimer = 0;
				currentEnemyIndex = 0;
				break;
			}
		}
	}

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDie)
		{
			// scroe, effect
		}

		if ((*it)->isDestroyed || (*it)->isDie)
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
			it++;
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
			it++;
	}
}

void CGameScene::RectUpdate(float deltaTime)
{
	// Enemy <-> player
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if(IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDie = true;
				player->isDie = true;
			}
		}
	}

	// EnemnyBullet -> Player
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDestroyed = true;
				player->isDie = true;
			}
		}
	}

	// PlayerBullet -> EnemyList
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;
				(*it2)->isDie = true;
			}
		}
	}
}

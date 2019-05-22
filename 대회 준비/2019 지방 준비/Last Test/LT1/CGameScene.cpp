#include "DXUT.h"
#include "Header.h"


CGameScene::CGameScene()
	: tileEntryInfo(), currentTileIndex(0), tileList(),
	checkPointIndex(0), rebirthTime(3), rebirthTimer(0), playerLife(3),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0),
	playerBulletList(), enemyBulletList()
{
	mainCamera = new CCameara(); // 카메라 생성
	map = new CMap(0, mainCamera); // 맵 생성 0은 스테이지 임시값

	// 타일 배열 넣기
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
	tileEntryInfo.push_back(TileEntryInfo(0));
	
	// 적 배열 넣기
	enemyEntryInfo.push_back(EnemyEntryInfo(1, 2));
	enemyEntryInfo.push_back(EnemyEntryInfo(2, 4));
	enemyEntryInfo.push_back(EnemyEntryInfo(3, 6));
	enemyEntryInfo.push_back(EnemyEntryInfo(4, 8));

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024; // 카메라의 한계점 설정

	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera); // 플레이어 생성
	player->parentScene = this; // 플레이어 parentScene 설정
	mainCamera->SetTarget(player); // 카메라 타겟 설정
}

CGameScene::~CGameScene()
{
	// Tile List delete
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete(*it);
	tileList.clear();

	// Enemy List delete
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete(*it);
	enemyList.clear();

	// Enemy Bullet List delete
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete(*it);
	enemyBulletList.clear();

	// Player Bullet List delete
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete(*it);
	playerBulletList.clear();

	// main Camera delete
	if (mainCamera)
		delete mainCamera;

	// Map delete
	if (map)
		delete map;

	// player delete;
	if (player)
		delete player;
}

void CGameScene::Update(float deltaTime)
{
	// main Camera Update
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// Map Update
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
	// Map Render
	if (map)
		map->Render(sprite);

	// Tile Render
	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	// Enemy Bullet Render
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	// Player Bullet Render
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	// Player Render
	if (player)
		player->Render(sprite);

	// Enemy Render
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
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
			if (player) // Player Jump
				player->Jump();
			break;
		case 'Q':
			if (player) // Player Die Test
				player->isDie = true;
			break;
		case 'W':
			score += 50;
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
		if (currentTileIndex >= tileEntryInfo.size())
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
					entryPos.y -= 105;
				break;
			default:
				if (t->type == 2)
					entryPos.y += 105;
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
	// Player Update
	if (player)
	{
		// Player Move
		if (GetKeyState(VK_LEFT) & 0x8000)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x8000)
			player->Move(1, deltaTime);
		// Player Attack
		if (GetKeyState('X') & 0x8000)
			player->Attack();

		// 현재 플레이어의 타일 번호를 받아옴
		int tileIndex = player->position.x / tileWidth;
		// 체크포인트 등록
		if (tileIndex >= 0 && tileIndex < tileEntryInfo.size())
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex)
				checkPointIndex = tileIndex;

		player->Update(deltaTime);

		// 플레이어 사망
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
				// 플레이어 스폰 위치 지정
				D3DXVECTOR2 entrypos = tileList[checkPointIndex]->position + D3DXVECTOR2(128, 0);
				// 플레이어 스폰
				player = new CPlayer(entrypos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				// 게임 오버
			}
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	enemyEntryTimer += deltaTime;

	while (player && enemyEntryInfo[currentEnemyIndex].timer < enemyEntryTimer)
	{
		D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_pos - 200 - rand() % 100);

		CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
		enemy->parentScene = this;
		enemyList.push_back(enemy);
		currentEnemyIndex++;

		if (currentEnemyIndex >= enemyEntryInfo.size())
		{
			enemyEntryTimer = 0;
			currentEnemyIndex = 0;
			break;
		}
	}

	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDie)
		{
			// score & effect
		}

		if ((*it)->isDie || (*it)->isDestroyed)
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
	// Enemy Bullet Update
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end();)
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

	// Player Bullet Update
	for (auto it = playerBulletList.begin(); it != playerBulletList.end();)
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

void CGameScene::RectUpdate(float deltaTime)
{
	// player < enemybullet object
	if (player)
	{
		// enemyBullet
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
	}

	// playerbullet > enemy object
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// enemy
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect))
			{
				(*it2)->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
	}
}

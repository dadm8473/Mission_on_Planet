#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileIndex(0), tileList(), 
	playerLife(3), rebirthTime(3), rebirthTimer(0), checkPointIndex(0),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0),
	enemyBulletList(), playerBulletList(),
	effectList(), objectList(), 
	clearAttack(NULL), isClearAttack(false)
{
	// camera spawn
	mainCamera = new CCamera();
	// map spawn
	map = new CMap(0, mainCamera);

	// tiel spawn
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
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 2));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));

	// enemy spawn
	enemyEntryInfo.push_back(EnemyEntryInfo(0, 2));

	// camera limit
	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	// player setting
	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;
	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	// tile clear
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	// enemy clear
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete(*it);
	enemyList.clear();
	
	// Enemy Bullet List Clear
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete(*it);
	enemyBulletList.clear();

	// Player Bullet List Clear
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete(*it);
	playerBulletList.clear();

	// Effect List Clear
	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete(*it);
	effectList.clear();

	// Object List Clear
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (*it)
			delete (*it);
	objectList.clear();

	// Clear Attack Clear
	if (clearAttack)
		delete clearAttack;

	// camera delete
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
	// Camera Update
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// Map Update
	if (map)
		map->Update(deltaTime);

	// Tile Update
	TileUpdate(deltaTime);

	// Player Upate
	PlayerUpdate(deltaTime);

	// Enemy Update
	EnemyUpdate(deltaTime);

	// Bullet Update
	BulletUpdate(deltaTime);

	// Rect Update
	RectUpdate(deltaTime);

	// Effect Update
	EffectUpdate(deltaTime);

	// Object Update
	ObjectUpdate(deltaTime);

	// ClearAttack Update
	if (isClearAttack)
		clearAttack->Update(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	// Map Render
	if (map)
		map->Render(sprite);

	// Tile Render
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		(*it)->Render(sprite);

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

	// Object Render
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		(*it)->Render(sprite);

	// Effect Render
	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	// ClearAttack Update
	if (isClearAttack)
		clearAttack->Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			// Player Jump
			if (player)
				player->Jump();
			break;
		case 'A':
			// Player Die Test
			if (player)
				player->isDie = true;
			break;
		case 'C':
			// Player ClearAttack
			if (!isClearAttack)
			{
				isClearAttack = true;
				clearAttack = new CClearAttack(D3DXVECTOR2(player->position.x + 256, player->position.y), mainCamera);
				clearAttack->parentScene = this;
			}
			break;
		case 'S':
			// Score Test
			score += 100;
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
					entryPos.y -= 128;
				break;
			default:
				if (t->type == 2)
					entryPos.y += 128;
				break;
			}
		}

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);

		if (tileEntryInfo[currentTileIndex].objectType > 0)
		{
			if (tileEntryInfo[currentTileIndex].type == 0)
			{
				// 랜덤 생성 할꺼면 이상한 곳에 생성 안되게 잘 처리해주기
				D3DXVECTOR2 entryPos = D3DXVECTOR2(tile->position.x + 128, tile->position.y);
				CObject* object = new CObject(entryPos, tileEntryInfo[currentTileIndex].objectType, mainCamera);
				objectList.push_back(object);
			}
		}

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

		if (GetKeyState('X') & 0x8000)
			player->Attack();
		if (GetKeyState('Z') & 0x8000)
			player->Attack_H();

		int tileIndex = player->position.x / tileWidth;

		if (tileIndex >= 0 && tileIndex < tileList.size())
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
				D3DXVECTOR2 entryPos = D3DXVECTOR2(tileList[checkPointIndex]->position.x + 128,
					tileList[checkPointIndex]->position.y);

				player = new CPlayer(entryPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				// countinue
				// Game Over
			}
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	enemyEntryTimer += deltaTime;

	while (player && enemyEntryInfo[currentEnemyIndex].timer < enemyEntryTimer)
	{
		D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 200);

		CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
		enemyList.push_back(enemy);
		enemy->parentScene = this;
		currentEnemyIndex++;

		if (currentEnemyIndex >= enemyEntryInfo.size())
		{
			currentEnemyIndex = 0;
			enemyEntryTimer = 0;
			break;
		}
	}

	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if (player && !(*it)->isDestroyed)
			player->GetTarget(*it);

		if ((*it)->isDie)
		{
			// score effect
			effectList.push_back(new CEffect((*it)->position, 0, mainCamera));
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
	// player <-> enemyBullet, object
	if (player)
	{
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}

		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->Reset();
				switch ((*it)->type)
				{
				case 1: // Rock
					break;
				case 2: // Hole
					break;
				case 11: // Double Jump
					player->DoubleJump();
					break;
				case 12: // Speed Up
					player->SpeedUP();
					break;
				case 13: // Long Attack
					player->LongAttack();
					break;
				case 14: // Multi Attack
					player->MultiAttack();
					break;
				case 15: // Homing Attack
					player->HomingAttack();
					break;
				case 16: // Clear Attack
					break;
				}

				if((*it)->type == 1 || (*it)->type == 2)
					player->isDie = true;

				if((*it)->type != 2)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet <-> enemy, obejct
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;;
				(*it2)->isDie = true;
			}
		}

		for (auto it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect) && (*it2)->type == 1)
			{
				(*it)->isDestroyed = true;
				(*it2)->isDestroyed = true;
			}
		}
	}
}

void CGameScene::EffectUpdate(float deltaTime)
{
	for (auto it = effectList.begin(); it != effectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestoryed)
		{
			delete (*it);
			it = effectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::ObjectUpdate(float deltaTime)
{
	for (auto it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}
}

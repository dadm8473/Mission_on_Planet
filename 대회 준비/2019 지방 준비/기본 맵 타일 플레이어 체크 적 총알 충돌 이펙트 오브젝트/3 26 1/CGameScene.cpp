#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileIndex(0), tileList(), tileWidth(0), playerLife(3), rebirthTime(3), rebirthTimer(0), checkPointIndex(0),
	enemyEnterTimer(0), currentEnemyindex(0), enemyEntryInfo(), enemyList(), enemyBulletList(), playerBulletList(), effectList(), objectList(),
	clearAttack(NULL), isClearAttack(false)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(0, 2));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(0, 2));
	tileEntryInfo.push_back(TileEntryInfo(0));
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
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete(*it);
	tileList.clear();

	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete(*it);
	enemyBulletList.clear();

	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete(*it);
	playerBulletList.clear();

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete(*it);
	effectList.clear();

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (*it)
			delete(*it);
	objectList.clear();

	if (mainCamera)
		delete mainCamera;

	if (map)
		delete map;

	if (player)
		delete player;

	if (clearAttack)
		delete clearAttack;
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

	RectUpdate(deltaTime);

	EffectUpdate(deltaTime);

	ObjectUpdate(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);

	if (player)
		player->Render(sprite);

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	if (clearAttack)
		clearAttack->Draw(sprite, gAssetManager->GetTexture("ClearAttack"));
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
		case 'C':
			if (player && !isClearAttack)
				ClearAttack();
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

		if (tileEntryInfo[currentTileIndex].type == 0)
		{
			if (tileEntryInfo[currentTileIndex].objectType > 0)
			{
				D3DXVECTOR2 objectEntryPos = tile->position;

				CObject* object = new CObject(objectEntryPos, tileEntryInfo[currentTileIndex].objectType, mainCamera);
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
				D3DXVECTOR2 entryPos = tileList[checkPointIndex]->position;

				player = new CPlayer(entryPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				// Game Over
			}
		}
	}

	// ClearAttack
	if (isClearAttack)
	{
		clearAttack->Update(deltaTime, mainCamera->position);

		// 리스트 초기화
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
			if (*it)
				delete (*it);
		enemyList.clear();

		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
			if (*it)
				delete(*it);
		enemyBulletList.clear();

		for (auto it = objectList.begin(); it != objectList.end(); ++it)
			if (*it)
				if((*it)->type == 1 && (*it)->type == 2)
					delete(*it);
		objectList.clear();

		if (clearAttack->isAniEnd)
		{
			isClearAttack = false;
			delete clearAttack;
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	if (player && enemyEntryInfo.size() >= 0)
	{
		enemyEnterTimer += deltaTime;

		while (enemyEnterTimer > enemyEntryInfo[currentEnemyindex].timer)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 200);

			CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyindex].type, mainCamera);
			enemy->parentScene = this;
			enemyList.push_back(enemy);
			currentEnemyindex++;

			if (currentEnemyindex >= enemyEntryInfo.size())
			{
				enemyEnterTimer = 0;
				currentEnemyindex = 0;
				break;
			}
		}
	}

	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if (player && !(*it)->isDestroyed && !(*it)->isDie)
			player->SetTarget(*it);

		if ((*it)->isDie)
		{
			// score & effect
			effectList.push_back(new CEffect((*it)->position, mainCamera));
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
	// player <- enemy && enemyBullet && object
	if (player)
	{
		// Enemy
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDie = true;

				player->isDie = true;
			}
		}
		
		// Enemy Bullet
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDestroyed = true;

				player->isDie = true;
			}
		} 

		// Object
		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				player->isDie = true;

				// type 0이 아닐 경우 obejct삭제
				if((*it)->type != 2)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet -> enemy & object
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// enemy
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;

				(*it2)->isDie = true;
			}
		}
		// object
		for (auto it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;
			// 충돌하고 타입이 1일경우
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

		if ((*it)->isDestroyed)
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

void CGameScene::ClearAttack()
{
	clearAttack = new CMatrix();
	clearAttack->position = D3DXVECTOR2(player->position.x + 300, player->position.y);
	clearAttack->center = D3DXVECTOR2(320, 240);
	clearAttack->scale = D3DXVECTOR2(2, 2);
	clearAttack->SetAnimation(0.02f, 40, false);
	isClearAttack = true;
}

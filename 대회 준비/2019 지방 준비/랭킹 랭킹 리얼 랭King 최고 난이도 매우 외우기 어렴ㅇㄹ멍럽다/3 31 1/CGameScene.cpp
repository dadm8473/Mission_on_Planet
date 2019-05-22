#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryinfo(), currentTileIndex(0), tileList(), playerLife(3), rebirthTime(3), rebirthTimer(0), currentCheckIndex(0),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0), enemyBulletList(), playerBulletList(), effectList(),
	objectList(), clearAttack(NULL), isClearAttack(false), clearAttackCount(2)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryinfo.push_back(TileEntryInfo(0));
	tileEntryinfo.push_back(TileEntryInfo(0));
	tileEntryinfo.push_back(TileEntryInfo(1));
	tileEntryinfo.push_back(TileEntryInfo(1));
	tileEntryinfo.push_back(TileEntryInfo(2));
	tileEntryinfo.push_back(TileEntryInfo(2));
	tileEntryinfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryinfo.push_back(TileEntryInfo(1));
	tileEntryinfo.push_back(TileEntryInfo(2));
	tileEntryinfo.push_back(TileEntryInfo(1));
	tileEntryinfo.push_back(TileEntryInfo(0));
	tileEntryinfo.push_back(TileEntryInfo(0, 11));
	tileEntryinfo.push_back(TileEntryInfo(0, 12));
	tileEntryinfo.push_back(TileEntryInfo(0, 13));
	tileEntryinfo.push_back(TileEntryInfo(0, 14));
	tileEntryinfo.push_back(TileEntryInfo(0, 15));
	tileEntryinfo.push_back(TileEntryInfo(0, 16));

	enemyEntryInfo.push_back(EnemyEntryInfo(0, 2));

	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i] = CMatrix();
		scoreUI[i].position.x = 768 - 256 + (i * 32);
		scoreUI[i].position.y = 100;
	}

	for (int i = 0; i < 3; ++i)
	{
		playerLifeUI[i] = CMatrix();
		playerLifeUI[i].position.x = 100 + (i * 32);
		playerLifeUI[i].position.y = 100;
	}

	for (int i = 0; i < 2; ++i)
	{
		clearAttackUI[i] = CMatrix();
		clearAttackUI[i].position.x = 100 + (i * 32);
		clearAttackUI[i].position.y = 150;
	}

	mainCamera->limitPos_Max.x = tileEntryinfo.size() * tileWidth - 1024;

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
			delete(*it);
	enemyList.clear();

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete(*it);
	enemyBulletList.clear();

	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete(*it);
	playerBulletList.clear();

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (*it)
			delete(*it);
	objectList.clear();

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete(*it);
	effectList.clear();

	if (clearAttack)
		delete clearAttack;

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

	TileUpdate(deltaTime);
	
	PlayerUpdate(deltaTime);

	EnemyUpdate(deltaTime);

	BulletUpdaet(deltaTime);

	ObjectUpdate(deltaTime);

	RectUpdate(deltaTime);

	UIUpdate(deltaTime);
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

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);
	
	if (player)
		player->Render(sprite);

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	if (isClearAttack)
		clearAttack->Draw(sprite, gAssetManager->GetTexture("Effect"));

	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i].Draw(sprite, gAssetManager->GetTexture("Num"));
		if (playerLife > i)
			playerLifeUI[i].Draw(sprite, gAssetManager->GetTexture("Num"));
		if (clearAttackCount > i)
			clearAttackUI[i].Draw(sprite, gAssetManager->GetTexture("Num"));
	}
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
		if (currentTileIndex == tileEntryinfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileIndex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileIndex - 1];

			entryPos.x = t->position.x + tileWidth;
			entryPos.y = t->position.y;

			switch (tileEntryinfo[currentTileIndex].type)
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

		CTile* tile = new CTile(entryPos, tileEntryinfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);

		if (tileEntryinfo[currentTileIndex].type == 0)
		{
			if (tileEntryinfo[currentTileIndex].objectType > 0)
			{
				CObject* object = new CObject(tileList[currentTileIndex]->position, tileEntryinfo[currentTileIndex].objectType, mainCamera);
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

		if (tileIndex >= 0 && tileIndex < tileEntryinfo.size())
			if (tileEntryinfo[tileIndex].checkPoint && currentCheckIndex < tileIndex)
				currentCheckIndex = tileIndex;

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

		if (rebirthTime < rebirthTimer)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				D3DXVECTOR2 entryPos = tileList[currentCheckIndex]->position;

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

	if (isClearAttack)
	{
		clearAttack->Update(deltaTime, mainCamera->position);

		if (clearAttack->isAniEnd)
		{
			delete clearAttack;
			isClearAttack = false;
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	if (player && enemyEntryInfo.size() > 0)
	{
		enemyEntryTimer += deltaTime;
		while (enemyEntryTimer > enemyEntryInfo[currentEnemyIndex].timer)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 200);

			CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
			enemy->parentScene = this;
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

	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if (player && !(*it)->isDestroyed && !(*it)->isDie)
			player->SetTarget(*it);

		if ((*it)->isDie)
		{
			// score & effect;
			score += 150;
			effectList.push_back(new CEffect(mainCamera, (*it)->position, 0));
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

void CGameScene::BulletUpdaet(float deltaTime)
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

	// effect update
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
			// 돌이면 점수를 주기

			delete (*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::RectUpdate(float deltaTime)
{
	// player <- enemy enemyBullet object

	if (player)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDie = true;
			}
		}

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
				switch ((*it)->type)
				{
				case 11:
					player->DoubleJump();
					break;
				case 12:
					player->SpeedUP();
					break;
				case 13:
					player->LongAttack();
					break;
				case 14:
					player->MultiAttack();
					break;
				case 15:
					player->HomingAttack();
					break;
				case 16:
					if(clearAttackCount < 2)
						clearAttackCount++;
					break;
				default:
					player->isDie = true;
					break;
				}

				if ((*it)->type != 2)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet <- enemy
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect))
			{
				(*it)->isDestroyed = true;
				(*it2)->isDie = true;
			}
		}

		for (auto it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect) && (*it2)->type == 1) // 돌 일 때만
			{
				(*it)->isDestroyed = true;
				
				(*it2)->isDestroyed = true;
			}
		}
	}
}

void CGameScene::ClearAttack()
{
	if (!isClearAttack && player && clearAttackCount > 0)
	{
		clearAttack = new CMatrix();
		clearAttack->position = D3DXVECTOR2(player->position.x + 300, player->position.y);
		clearAttack->center = D3DXVECTOR2(128, 128);
		clearAttack->scale = D3DXVECTOR2(1, 1);
		clearAttack->SetAnimation(0.4f, 3, false);
		clearAttackCount--;

		isClearAttack = true;

		// list delete
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
			if (*it)
				delete(*it);
		enemyList.clear();

		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
			if (*it)
				delete(*it);
		enemyBulletList.clear();
	}
}

void CGameScene::UIUpdate(float deltaTime)
{
	int tempScore = score;
	for (int i = 5; i >= 0; --i)
	{
		scoreUI[i].currentScene = tempScore % 10;
		tempScore /= 10;
	}

	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i].Update(deltaTime);
		if (playerLife > i)
			playerLifeUI[i].Update(deltaTime);
		if (clearAttackCount > i)
			clearAttackUI[i].Update(deltaTime);
	}
}

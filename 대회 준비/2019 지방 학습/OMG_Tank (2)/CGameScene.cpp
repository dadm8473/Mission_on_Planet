#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	:CScene(), tileEntryInfo(), currentTileEntryIndex(0), playerBulletList(), enemyEntryInfo(), enemyBulletList(), enemyList(), enemyEntryTimer(0),
	currentEnemyEntryIndex(0), playerLife(3), rebirthTimer(0), rebirthTime(3), objectList(), checkPointTileInex(0), isItem(new CMatrix), isItemTimer(0),
	invincible(false)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 100));
	tileEntryInfo.push_back(TileEntryInfo(0, 12));
	tileEntryInfo.push_back(TileEntryInfo(0, 100));
	tileEntryInfo.push_back(TileEntryInfo(0, 14));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(0, 15));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0, 0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	for (int i = 0; i < 6; ++i)
	{
		scoreNumUI[i] = CMatrix();
		scoreNumUI[i].position.x = 1024 - 300 + (40 * i);
		scoreNumUI[i].position.y = 60;
		scoreNumUI[i].scale.x = 0.7f;
		scoreNumUI[i].scale.y = 0.7f;

		playerLifeUI[i] = CMatrix();
		playerLifeUI[i].position.x = 32 + (100 * i);
		playerLifeUI[i].position.y = 768 - 100;
		playerLifeUI[i].scale.x = 0.5f;
		playerLifeUI[i].scale.y = 0.5f;
	}

	for (int i = 0; i < 10; ++i)
		enemyEntryInfo.push_back(EnemyEntryInfo((i * 2), i%2));

	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width - 1024.0f;

	isItem->position = D3DXVECTOR2(100, 100);
	isItem->center = D3DXVECTOR2(32, 32);

	player = new CPlayer(D3DXVECTOR2(100.0f, 384.0f), mainCamera);
	player->parentScene = this;
	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		if (*it)
			delete(*it);
	}
	playerBulletList.clear();

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		if (*it)
			delete(*it);
	}
	enemyBulletList.clear();

	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;

	if (isItem)
		delete isItem;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				if ((*it)->type == 0 || (*it)->type == 1)
					player->isDie = true;
				else
				{
					// 모든 아이템 효과 종료
					player->AllFalse();
					// 아이템 scale 줄어드는 시간 초기화
					isItemTimer = 0;
					// 아이템 스케일 다시 1,1
					isItem->scale = D3DXVECTOR2(1, 1);

					switch ((*it)->type)
					{
					case 10: // 핵
						break;
					case 11: // 유도
						player->homingAttack = true;
						break;
					case 12: // 점프
						if(player->jumpCount <= 1)
							player->jumpCount++;
						break;
					case 13: // 사거리
						player->attackRich = true;
						break;
					case 14: // 이속
						player->speedUp = true;
						break;
					case 15: // 3방향
						player->multiAttack = true;
						break;
					case 100:
						if(player->upgrade < 2)
							player->upgrade++;
						(*it)->isActive = false;
						break;
					}

					isItem->currentScene = (*it)->type - 10;

					(*it)->isDestroyed = true;
				}
			}
		}
	}

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		for (list<CObject*>::iterator it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;

			if ((*it2)->type == 1 && IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;

				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 150;
					(*it2)->isDestroyed = true;
				}
			}
		}

		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;

				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 150;
					(*it2)->isDestroyed = true;
				}
			}
		}
	}

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		RECT ref;

		if (player)
		{
			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDestroyed = true;
				player->isDie = true;
			}
		}
	}

	enemyEntryTimer += deltaTime;

	if (player && enemyEntryInfo.size() > 0)
	{
		enemyEntryTimer += deltaTime;

		while (enemyEntryTimer >= enemyEntryInfo[currentEnemyEntryIndex].time)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 200 - rand() % 100);

			CEnemy*enemy = new CEnemy(mainCamera, entryPos, enemyEntryInfo[currentEnemyEntryIndex].type);
			enemyList.push_back(enemy);

			currentEnemyEntryIndex++;

			if (currentEnemyEntryIndex >= enemyEntryInfo.size())
			{
				currentEnemyEntryIndex = 0;
				enemyEntryTimer = 0.0f;
				break;
			}
		}
	}

	if (mainCamera)
		mainCamera->Update(deltaTime);

	if (player)
	{
		if (GetKeyState(VK_LEFT) & 0x8000)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x8000)
			player->Move(1, deltaTime);

		if (GetKeyState('X') & 0x8000)
			player->Attack();

		player->Update(deltaTime);

		int tileIndex = player->position.x / gAssetManager->GetTexture("Tile")->width;

		if (tileList.size() > tileIndex && tileIndex >= 0)
		{
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileInex < tileIndex)
			{
				checkPointTileInex = tileIndex;
			}
		}

		if (invincible)
		{
			player->isDie = false;
			player->a = 150;
		}
		else
			player->a = 255;

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
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				D3DXVECTOR2 rebirhtPos = tileList[checkPointTileInex]->position + D3DXVECTOR2(128.0f, 0.0f);

				player = new CPlayer(rebirhtPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				ChangeScene("Ending_GameOver");
				return;
			}
		}
	}

	if (map)
		map->Update(deltaTime);

	float currentTileLength = tileList.size() * gAssetManager->GetTexture("Tile")->width;

	while (mainCamera->position.x + 1280.0f > currentTileLength)
	{
		if (currentTileEntryIndex == tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileEntryIndex == 0)
		{
			entryPos.x = 0.0f;
			entryPos.y = 384.0f;
		}
		else
		{
			CTile* t = tileList[currentTileEntryIndex - 1];

			entryPos.x = t->position.x + gAssetManager->GetTexture("Tile")->width;
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // 오르막
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
					entryPos.y -= 100.0f;
				break;
			default: // 평지 & 내리막
				if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
					entryPos.y += 100.0f;
				break;
			}
		}

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile);

		if (tileEntryInfo[currentTileEntryIndex].type == 0)
		{
			D3DXVECTOR2 objectEntryPos = tile->position;
			objectList.push_back(new CObject(mainCamera, objectEntryPos, tileEntryInfo[currentTileEntryIndex].objectType));
		}

		currentTileLength = tileList.size() * gAssetManager->GetTexture("Tile")->width;
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);

	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed && (*it)->type != 100)
		{
			delete(*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);
		(*it)->parentScene = this;

		(*it)->b = 0;

		if (player && !(*it)->isDestroyed)
			player->SetEnemyPos((*it));

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = enemyList.erase(it);
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
			it = playerBulletList.erase(it++);
		}
		else
			++it;
	}

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); )
	{
		(*it)->Update(deltaTime);

		(*it)->b = 0;

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	int tempScore = score;
	for (int i = 5; i >= 0; i--)
	{
		scoreNumUI[i].currentScene = tempScore % 10;
		tempScore /= 10;
	}

	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Update(deltaTime);
		playerLifeUI[i].Update(deltaTime);
	}

	if (isItem)
	{
		if ((isItem->currentScene != 0) && (isItem->currentScene != 2) && (isItem->currentScene != 4))
		{
			// 시간이 갈 수록 아이템 스케일 줄임
			isItemTimer += deltaTime;

			if (isItemTimer > 3.0f)
				isItemTimer = 3.0f;

			float scale = 1 - (isItemTimer / 3.0f);

			isItem->scale = D3DXVECTOR2(scale, scale);

			if (isItemTimer >= 3.0f)
				player->AllFalse();
		}
		isItem->Update(deltaTime);
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}

	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	if(player)
		player->Render(sprite);

	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Draw(sprite, gAssetManager->GetTexture("Num"));
		if(playerLife > i)
			playerLifeUI[i].Draw(sprite, gAssetManager->GetTexture("Player1"));
	}

	if (isItem)
	{
		isItem->Draw(sprite, gAssetManager->GetTexture("Item"));
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			if (player)
				player->Jump();
			break;
		case VK_F1:
			invincible = !invincible;
			break;
		case VK_F2:
			if(player->upgrade < 2)
				player->upgrade++;
			break;
		case VK_F3:
			if (player->upgrade > 0)
				player->upgrade--;
			break;
		}
		break;
	}
}

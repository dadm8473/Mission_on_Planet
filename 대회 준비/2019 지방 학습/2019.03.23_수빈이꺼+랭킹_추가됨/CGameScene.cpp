#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	:CScene(), tileEntryInfo(), currentTileEntryIndex(0), playerBulletList(), enemyEntryInfo(), enemyBulletList(), enemyList(), enemyEntryTimer(0),
	currentEnemyEntryIndex(0), playerLife(3), rebirthTimer(0), rebirthTime(3), objectList(), checkPointTileIndex(0), isItem(new CMatrix), isItemTimer(0),
	invincible(false), clearAttackCount(2), isClearAttack(false), bonusLifeCounter(1), ui(new CMatrix), isWin(false), isLose(false), itemMessage(new CMatrix),
	isPlayerDie(false), effectList()
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// 타일 배치
	SetTile();

	// score, playerLife UI 초기화
	for (int i = 0; i < 6; ++i)
	{
		scoreNumUI[i] = CMatrix();
		scoreNumUI[i].position.x = 1024 - 240 + (32 * i);
		scoreNumUI[i].position.y = 30;
		/*scoreNumUI[i].scale.x = 0.7f;
		scoreNumUI[i].scale.y = 0.7f;*/

		playerLifeUI[i] = CMatrix();
		playerLifeUI[i].position.x = 210 + (70 * i);
		playerLifeUI[i].position.y = 11;
		/*playerLifeUI[i].scale.x = 0.5f;
		playerLifeUI[i].scale.y = 0.5f;*/
	}

	for (int i = 0; i < 2; ++i)
	{
		clearAttackUI[i] = CMatrix();
		clearAttackUI[i].position.x = 150 + (50 * i);
		clearAttackUI[i].position.y = 90;
		clearAttackUI[i].rotate = 30;

		clearAttackUI[i].scale.x = 0.7f;
		clearAttackUI[i].scale.y = 0.7f;
	}

	// 적 소환
	for (int i = 0; i < 10; ++i)
		enemyEntryInfo.push_back(EnemyEntryInfo((i * 3.5f), i%2 + 1));

	// 메인 카메라 초기화
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width - 1024.0f;

	// 아이템 초기화
	isItem->position = D3DXVECTOR2(71, 157);
	isItem->center = D3DXVECTOR2(32, 32);
	itemMessage->a = 0;

	// 플레이어 초기화, 카메라 설정
	player = new CPlayer(D3DXVECTOR2(100.0f, 384.0f), mainCamera);
	player->parentScene = this;
	mainCamera->SetTarget(player);

	// 미니맵 UI
	miniMapBar.position = D3DXVECTOR2(20.0f, 768.0f - 64.0f);
	miniMapBar.center = D3DXVECTOR2(20.0f, 27.0f);

	playerIcon.position = miniMapBar.position;
	playerIcon.center = D3DXVECTOR2(30.0f, 64.0f);

	checkPointIcon.position = miniMapBar.position;
	checkPointIcon.center = D3DXVECTOR2(30.0f, 64.0f);
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

	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete(*it);
	effectList.clear();

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

	// Rect Update
	RectUpdate(deltaTime);

	// Enemy EntryInfo && Enemy List 에너미 리스트 밑에 있었는데 올려도 되는가? 되는듯
	EnemyUpdate(deltaTime);

	// Camera Update;
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// Player Update
	PlayerUpdate(deltaTime);

	// Clear Attack Update
	if (isClearAttack)
		clearAttack->Update(deltaTime);

	// Tile EntryInfo && Tile Index
	TileUpdate(deltaTime);

	// Object List
	ObjectUpdate(deltaTime);

	// Enemy List ???
	//EnemyUpdate(deltaTime);

	// Bullet List Update (Player, Enemy)
	BulletUpdate(deltaTime);

	// Map Update
	if (map)
		map->Update(deltaTime);

	// UI Update
	UIUpdate(deltaTime);

	// Ending update
	if (isWin && !isLose)
		ChangeScene("Ending_Victory");

	if (isLose && !isWin)
		ChangeScene("Ending_GameOver");
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	// Map Render
	if (map)
		map->Render(sprite);

	// Tile List Render
	for (int i = 0; i < tileList.size(); i++)
		tileList[i]->Render(sprite);

	// Enemy Bullet List Render
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	// Enemy List Render
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);

	// Player Bullet List Render
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		(*it)->Render(sprite);
	}
	
	// Object List Render
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
		(*it)->Render(sprite);

	// Player Render
	if (player)
		player->Render(sprite);

	// Player Die Render
	if (isPlayerDie)
		switch (playerDie->temp)
		{
		case 0:
			playerDie->Draw(sprite, gAssetManager->GetTexture("Player1_Die"));
			break;
		case 1:
			playerDie->Draw(sprite, gAssetManager->GetTexture("Player2_Die"));
			break;
		case 2:
			playerDie->Draw(sprite, gAssetManager->GetTexture("Player3_Die"));
			break;
		}

	// Clear Attack Render
	if (isClearAttack)
		clearAttack->Draw(sprite, gAssetManager->GetTexture("ClearAttack"));

	// Score && PlayerLife Render
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Draw(sprite, gAssetManager->GetTexture("Num"));
		if(playerLife > i)
			playerLifeUI[i].Draw(sprite, gAssetManager->GetTexture("PlayerLife"));
	}

	// Item Render
	if (isItem)
		isItem->Draw(sprite, gAssetManager->GetTexture("Item"));

	// Item Message Render
	if (itemMessage)
		itemMessage->Draw(sprite, gAssetManager->GetTexture("ItemMessage"));

	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	// MiniMap Render
	miniMapBar.Draw(sprite, gAssetManager->GetTexture("MiniMap"));

	// Player Icon Render
	if (player)
		playerIcon.Draw(sprite, gAssetManager->GetTexture("PlayerIcon"));

	// Clear Attack UI Render
	for (int i = 0; i < 2; ++i)
		if (clearAttackCount > i)
			clearAttackUI[i].Draw(sprite, gAssetManager->GetTexture("ClearAttackUI"));

	// Check Point MiniMap Render
	if (checkPointTileIndex != 0)
		checkPointIcon.Draw(sprite, gAssetManager->GetTexture("PlayerIcon"));

	// UI Render
	ui->Draw(sprite, gAssetManager->GetTexture("UI"));
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
			// Jump
			if (player)
				player->Jump();
			break;
		case 'C':
			ClearAttack();
			break;
		case 'Z':
			player->speedUp = true;
			break;
		case VK_F1:
			// Invincible
			invincible = !invincible;
			break;
		case VK_F2:
			// Upgrade
			if(player->upgrade < 2)
				player->upgrade++;
			break;
		case VK_F3:
			// Degrade
			if (player->upgrade > 0)
				player->upgrade--;
			break;
		case 'A':
			if (player)
				player->isDie = true;
			break;
		}
		break;
	}
}

void CGameScene::ClearAttack()
{
	if (player && clearAttackCount > 0)
	{
		// clear attack spawn
		clearAttack = new CMatrix();
		clearAttack->position = D3DXVECTOR2(512, 368);
		clearAttack->center = D3DXVECTOR2(320, 240);
		clearAttack->scale = D3DXVECTOR2(2, 2);
		clearAttack->SetAnimation(0.03f, 40, false);

		isClearAttack = true;
		clearAttackCount--;

		// 애니메이션이 끝났다면 종료
		if (clearAttack->isAniEnd)
		{
			isClearAttack = false;
			delete clearAttack;
		}

		// 적 관련 리스트 초기화
		for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
			if ((*it))
				(*it)->isDestroyed = true;

		// 장애물만
		for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
			if ((*it)->type == 0 || (*it)->type == 1)
				(*it)->isDestroyed = true;

		for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
			if ((*it))
				(*it)->isDestroyed = true;
	}
}

void CGameScene::TileUpdate(float deltaTime)
{
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

		// 평평한 타일일 때 만 오브젝트를 생성함
		if (tileEntryInfo[currentTileEntryIndex].type == 0)
		{
			D3DXVECTOR2 objectEntryPos = tile->position;
			// 함정 오브젝트 두개가 이어져서 생성되지 않게함
			if (currentEnemyEntryIndex > 1)
				if (tileEntryInfo[currentTileEntryIndex - 1].objectType != 0 && tileEntryInfo[currentTileEntryIndex - 1].objectType != 1)
					objectList.push_back(new CObject(mainCamera, D3DXVECTOR2(objectEntryPos.x, objectEntryPos.y + 128), tileEntryInfo[currentTileEntryIndex].objectType));
		}

		currentTileLength = tileList.size() * gAssetManager->GetTexture("Tile")->width;
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	enemyEntryTimer += deltaTime;

	if (player && enemyEntryInfo.size() > 0)
	{
		enemyEntryTimer += deltaTime;

		// 다음에 생성되어야 하는 적의 등장 시간을 현재 시간 정보와 비교
		while (enemyEntryTimer >= enemyEntryInfo[currentEnemyEntryIndex].time)
		{
			// 적 생성 x축은 카메라 기준 오른쪽 y축은 플레이어가 밟고잇는 땅의 y축 기준으로 -200 -(0~100) 사이로 랜덤 생성
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

	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);
		(*it)->parentScene = this;

		if (player && !(*it)->isDestroyed)
			player->SetEnemyPos((*it));

		if ((*it)->isDestroyed)
		{
			effectList.push_back(new CEffect((*it)->position - mainCamera->position - mainCamera->center, 1, 0.03f));
			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::ObjectUpdate(float deltaTime)
{
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
}

void CGameScene::BulletUpdate(float deltaTime)
{
	// Player Bullet List
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

	// Enemy Bullet List
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

		player->Update(deltaTime);

		// score 2.5천 증가 마다 player life 증가
		if (score >= 2500 * bonusLifeCounter)
		{
			if(playerLife <3)
				playerLife++;

			bonusLifeCounter++;
		}

		// Player Check Point
		int tileIndex = player->position.x / gAssetManager->GetTexture("Tile")->width;

		if (tileList.size() > tileIndex && tileIndex >= 0)
		{
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileIndex < tileIndex)
			{
				// Check Message
				itemMessage = new CMatrix();
				itemMessage->currentScene = 7;

				checkPointTileIndex = tileIndex;
			}
		}

		// Player Invincible
		if (invincible)
		{
			player->isDie = false;
			player->a = 150;
		}
		else
			player->a = 255;

		// Player isDie
		if (player->isDie)
		{
			playerDie = new CMatrix();
			playerDie->center = D3DXVECTOR2(100, 75);
			playerDie->position = player->position - mainCamera->position;
			playerDie->SetAnimation(0.05f, 30, false);
			playerDie->temp = player->upgrade;
			isPlayerDie = true;

			mainCamera->SetTarget(NULL);

			player = NULL;
			delete player;
		}
	}
	else
	{
		// Player Rebirth
		rebirthTimer += deltaTime;
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				D3DXVECTOR2 rebirhtPos = tileList[checkPointTileIndex]->position + D3DXVECTOR2(128.0f, 0.0f);

				player = new CPlayer(rebirhtPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				// Game Over
				isLose = true;
				return;
			}
		}
	}

	if (isPlayerDie)
	{
		playerDie->Update(deltaTime);

		if (playerDie->isAniEnd)
			isPlayerDie = false;
	}
}

void CGameScene::UIUpdate(float deltaTime)
{
	// UI Update
	ui->Update(deltaTime);

	// Score Count
	int tempScore = score;
	for (int i = 5; i >= 0; i--)
	{
		scoreNumUI[i].currentScene = tempScore % 10;
		tempScore /= 10;
	}

	// Player Life && Score Update
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Update(deltaTime);
		playerLifeUI[i].Update(deltaTime);
	}

	// Clear Attck Update
	for (int i = 0; i < 2; ++i)
		clearAttackUI[i].Update(deltaTime);

	// Item Update ( Scale-- )
	if (isItem)
	{
		if ((isItem->currentScene != 0) && (isItem->currentScene != 4))
		{
			// 시간이 갈 수록 아이템 스케일 줄임
			isItemTimer += deltaTime;

			if (isItemTimer > 3.0f)
				isItemTimer = 3.0f;

			float scale = 1 - (isItemTimer / 3.0f);

			isItem->scale = D3DXVECTOR2(scale, scale);

			if (isItemTimer >= 3.0f && player)
				player->AllFalse();
		}
		isItem->Update(deltaTime);
	}

	// item Message
	if (itemMessage)
	{
		itemMessage->Update(deltaTime);
		// 알파값을 점점 줄임
		if (itemMessage->a <= 0)
			itemMessage->a = 0;
		else
			itemMessage->a -= 100 * deltaTime;
	}

	// MiniMap Update
	miniMapBar.Update(deltaTime);

	// PlayerIcon PositionUpdate
	if (player)
	{
		float temp = player->position.x / (tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width);

		if (temp < 0.0f) temp = 0.0f;
		if (temp > 1.0f) temp = 1.0;

		playerIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		playerIcon.Update(deltaTime);
	}

	// CheckPoint Index Update
	if (checkPointTileIndex != 0)
	{
		float temp = (tileList[checkPointTileIndex]->position.x + 128.0f) / (tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width);

		checkPointIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		checkPointIcon.Update(deltaTime);
	}

}

void CGameScene::RectUpdate(float deltaTime)
{
	// Player Item Rect
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
						if(clearAttackCount < 2)
							clearAttackCount++;
						break;
					case 11: // 유도
						player->homingAttack = true;
						break;
					case 12: // 점프
						player->doubleJump = true;
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
						if (player->upgrade < 2)
							player->upgrade++;
						(*it)->isActive = false;
						break;
					case 777:
						isWin = true;
						break;
					}
					// item Message
					itemMessage = new CMatrix();
					itemMessage->currentScene = (*it)->type - 10;
					// Upgrate Message
					if ((*it)->type == 100)
						itemMessage->currentScene = 6;

					// type에서 10을 빼서 currentScene을 맞춰줌
					isItem->currentScene = (*it)->type - 10;
					(*it)->isDestroyed = true;
				}
			}
		}
	}

	// Player Bullet Rect
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// Object Rect (Trap)
		for (list<CObject*>::iterator it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;

			if ((*it2)->type == 1 && IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;

				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 150 + rand() % 100;
					(*it2)->isDestroyed = true;
				}
			}
		}

		// Enemy Rect, Score ++
		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestroyed = true;

				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 150 + rand() % 100;
					(*it2)->isDestroyed = true;
				}
			}
		}
	}

	// Enemy Bullet Rect
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		RECT ref;

		// Player Rect;
		if (player)
		{
			if (IntersectRect(&ref, &(*it)->rect, &player->rect))
			{
				(*it)->isDestroyed = true;
				player->isDie = true;
			}
		}
	}

	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isAniEnd)
		{
			delete(*it);
			it = effectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::SetTile()
{
	for (int i = 0; i < 100; ++i)
	{
		int sum = rand() % 8;

		// 맵 랜덤 생성
		if (sum <= 5)
		{
			int sum2 = rand() % 6;
			if (sum2 <= 3)
			{
				tileEntryInfo.push_back(TileEntryInfo(0));
			}
			else if (sum2 == 4)
			{
				if (i > 3 && i < 97)
					tileEntryInfo.push_back(TileEntryInfo(0, (rand() % 2)));
			}
			else
			{
				if (i > 3 && i < 97)
					tileEntryInfo.push_back(TileEntryInfo(0, (rand() % 6 + 10)));
			}
		}
		else if(sum == 6)
			tileEntryInfo.push_back(TileEntryInfo(1));
		else if(sum == 7)
			tileEntryInfo.push_back(TileEntryInfo(2));

		// 체크포인트 , 컨테이너
		if (i % 33 == 0 && i > 32 && i < 98)
		{
			tileEntryInfo.push_back(TileEntryInfo(0, 100, true));
		}

		// is Win
		if (i >= 97)
		{
			tileEntryInfo.push_back(TileEntryInfo(0, 777));
		}
	}
}
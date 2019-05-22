#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage, CPlayer* inputPlayer, int score, int life) :
	CScene(), currentStage(stage), enemyEntryInfo(), tileEntryInfo(), enemyEntrytimer(0), currentTileEntryIndex(0),
	playerBulletList(), enemyBulletList(), playerLife(life), rebirthTimer(0), rebirthTime(2), checkPointTileInex(0), score(score), bonusLifeChecker(0),
	onContinerSpawn(false), continerChecker(0), entry(true), entryTime(2), entryTimer(0), victory(false), victoryTime(5), victoryTimer(0), superPower(false)
{
	onStageClearMessage = onUpgradeMessage = onCheckPointMessage = false;
	stageClearMessageTimer = upgradeMessageTimer = checkPointMessageTimer = 0.0f;

	mainCamera = new CCamera();
	map = new CMap(currentStage, mainCamera);

	// Ÿ�� ���� ����
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, false, true));

	// �� ���� ����
	enemyEntryInfo.push_back(EnemyEntryInfo(4, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(6, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(12, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(18, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(19.5, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(23, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(23, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(30, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(35, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(39, 0));

	// ī�޶��� X��ǥ�� �ִ�ġ�� Tile ������ �°� ����
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->tile_Texture->width - 1024.0f;

	if(inputPlayer == NULL)
		player = new CPlayer(D3DXVECTOR2(-200.0f, 384.0f), mainCamera);
	else
	{
		player = inputPlayer;
		player->camera = mainCamera;
		player->position = D3DXVECTOR2(-200.0f, 384.0f);
	}
	player->parentScene = this;

	// ī�޶��� Ÿ������ �÷��̾ ����
	mainCamera->SetTarget(player);

	// UI

	// �� ������������ �� ���ھ� ó��
	while (score >= 500 * (bonusLifeChecker + 1))
	{
		bonusLifeChecker++;
	}
	while (score >= 1000 * (continerChecker + 1))
	{
		continerChecker++;
	}

	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i] = CMatrix();
		scoreNumUI[i].position.x = 32 + (40 * i);
		scoreNumUI[i].position.y = 32;

		scoreNumUI[i].scale.x = 0.35f;
		scoreNumUI[i].scale.y = 0.35f;
	}

	for (int i = 0; i < 5; i++)
	{
		playerLifeUI[i] = CMatrix();
		playerLifeUI[i].position.x = 32 + (60 * i);
		playerLifeUI[i].position.y = 700;

		playerLifeUI[i].scale.x = 0.25f;
		playerLifeUI[i].scale.y = 0.25f;
	}

	stageClearMessage = CMatrix();
	upgradeMessage = CMatrix();
	checkPointMessage = CMatrix();

	stageClearMessage.position = D3DXVECTOR2(512, 200);
	upgradeMessage.position = D3DXVECTOR2(512, 200);
	checkPointMessage.position = D3DXVECTOR2(512, 200);
	stageClearMessage.center = upgradeMessage.center = checkPointMessage.center = D3DXVECTOR2(307.5f, 71);
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

	if (player && (currentStage != 0 || !victory)) // �������� 1���� 2�� �̵��Ҷ� ���� �÷��̾ ������ϱ� ������ ������ �ɾ��ش�.
		delete player;

	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end();++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	// ---�浹 üũ---
	//�浹 üũ
	//  �� - �÷��̾� �Ѿ�
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		//��
		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				score += 15;

				(*it)->isDestroyed = true;

				//�� ������ ����
				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					(*it2)->isDie = true;

					if ((*it2)->type == 0) // ���� �Ѽ���
					{
						score += 100;

						if(rand()%100 < 50)
							itemList.push_back(new CItem(mainCamera, (*it2)->position));
					}
					else if ((*it2)->type == 1)
					{
						score += 150;
					}
					else if ((*it2)->type == 2)
					{
						score += 300;
					}
				}
			}
		}
	}

	//  ���Ѿ� - �����̳�
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		for (list<CItem*>::iterator it2 = itemList.begin(); it2 != itemList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->bulletRect))
			{
				(*it)->isDestroyed = true;
			}
		}
	}

	//  ���Ѿ� - �÷��̾�
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		if (player && !player->isInvincible && !(*it)->isDestroyed && !victory && !superPower)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
	}
	//  ��(��ֹ�) - �÷��̾�
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		if (player && !victory && !superPower)
		{
			RECT ref;
	
			if ((*it)->type == 0 && IntersectRect(&ref, &player->rect, &(*it)->rect))
				player->isDie = true;
		}
	}

	// ����..
	for (list<CTrap*>::iterator it = trapList.begin(); it != trapList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
				player->isDie = true;
		}
	}

	// ������ - �÷��̾�
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
	{
		if (player && !(*it)->isUse)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				(*it)->isUse = true;

				switch ((*it)->index)
				{
				case -1: // ���׷��̵�
					if (player->upgrade < 2)
					{
						onUpgradeMessage = true;
						player->upgrade++;
					}
					break;
				case 0: // ����ź
					break;
				case 1:
					player->homingMissile.Active();
					break;
				case 2:
					player->doubleJump.Active();
					break;
				case 3:
					player->longShot.Active();
					break;
				case 4:
					player->speedUp = true;
					break;
				case 5:
					player->powerUp.Active();
					break;
				}
			}
		}
	}


	// ī�޶� ������Ʈ
	if(mainCamera)
	{
		mainCamera->Update(deltaTime);
	}

	// ---��---
	if (map)
		map->Update(deltaTime);


	// ---Ÿ��---
	float currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;

	// �׸��� ���� ī�޶��� ������ ��(ȭ���� ���� ������)���� Ÿ�ϵ��� ���̰� ª�ٸ� ���� �������ش�.
	if (mainCamera->position.x + 1280.0f > currentTileLength)
	{
		while (mainCamera->position.x + 1280.0f > currentTileLength)
		{
			if (currentTileEntryIndex == tileEntryInfo.size()) break;

			D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

			if (currentTileEntryIndex == 0)
			{
				entryPos.x = 0.0f;
				entryPos.y = 384.0f;
			}
			else
			{
				auto it = tileList.begin();
				std::advance(it, currentTileEntryIndex - 1);

				entryPos.x = (*it)->position.x + gAssetManager->tile_Texture->width;
				entryPos.y = (*it)->position.y;

				switch (tileEntryInfo[currentTileEntryIndex].type)
				{
				case 1: // ������
					if(tileEntryInfo[currentTileEntryIndex-1].type != 2)
						entryPos.y -= 100.0f;
					break;
				default: // ���� & ������
					if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
						entryPos.y += 100.0f;
					break;
				}
			}

			CTile*tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
			tileList.push_back(tile);

			// �������� �������� �ʵ��� �ϴ� ����
			bool itemSpawn = true;

			if (entry || tileEntryInfo[currentTileEntryIndex].stageEnd)
				itemSpawn = false;

			// ������ Ÿ���� �� ��ֹ� �Ǵ� �����̳� ��ġ
			if (tileEntryInfo[currentTileEntryIndex].type == 0)
			{
				if (!onContinerSpawn) // �����̳� ������ �ƴ� ��
				{
					switch (tileEntryInfo[currentTileEntryIndex].objectType)
					{
					case 0: // ������
						trapList.push_back(new CTrap(mainCamera, tile->position));
						break;
					case 1: // ��
						CEnemy * enemy = new CEnemy(mainCamera, tile->position + D3DXVECTOR2(128.0f, 0.0f), 0);
						enemy->parentScene = this;

						enemyList.push_back(enemy);
						break;
					}
				}
				else if(itemSpawn)
				{
					// �����̳� ��ġ
					itemList.push_back(new CItem(mainCamera, tile->position + D3DXVECTOR2(128, 25), true));

					onContinerSpawn = false;
					itemSpawn = false;
					// �����̳ʰ� ������ ������ ������ ������ ���ش�.
				}
			}

			
			// Ÿ���� ���� �� �������� ������ ��ġ
			if (itemSpawn && tileEntryInfo[currentTileEntryIndex].objectType == -1 && rand() % 100 < 50)
				itemList.push_back(new CItem(mainCamera, tile->position + D3DXVECTOR2(128, 25)));

			currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;
			currentTileEntryIndex++;
		}
	}
	
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Update(deltaTime);
	}

	//�� ���� ������ ���� �ð��� ���� �� ��ȯ
	enemyEntrytimer += deltaTime;

	bool resetEnemyEntryInfo = true;
	for (int i = 0; i < enemyEntryInfo.size(); i++)
	{
		if (!enemyEntryInfo[i].summoned)
		{
			if (enemyEntrytimer >= enemyEntryInfo[i].time)
			{
				int tileIndex = (mainCamera->position.x + 1280.0f) / gAssetManager->tile_Texture->width;
				if (tileList.size() > tileIndex && tileIndex >= 0) // Ÿ�ϸ���Ʈ ����� ���� ��츦 ����ó��
				{
					tileList[tileIndex]->position.x;

					float posY = tileList[tileIndex]->position.y;
					if (player)
						posY = player->position.y;

					CEnemy*enemy = new CEnemy(mainCamera, D3DXVECTOR2(tileList[tileIndex]->position.x, posY - 200.0f - rand()%100), enemyEntryInfo[i].type+1);
					enemy->parentScene = this;

					enemyList.push_back(enemy);
				}
				enemyEntryInfo[i].summoned = true;
			}
			else
				resetEnemyEntryInfo = false;
		}
	}

	// �� ������ �Ϸ�Ǹ� �ʱ�ȭ�ϰ� ��Ȱ���Ѵ�.
	if (resetEnemyEntryInfo)
	{
		for (int i = 0; i < enemyEntryInfo.size(); i++)
		{
			enemyEntryInfo[i].summoned = false;
		}
		enemyEntrytimer = 0.0f;
	}

	// ---�÷��̾�---
	if (player)
	{
		if(!entry && !victory)
		{ 
			if (GetKeyState(VK_LEFT) & 0x0800)
				player->Move(-1, deltaTime);
			if (GetKeyState(VK_RIGHT) & 0x0800)
				player->Move(1, deltaTime);
			if (GetKeyState('X') & 0x0800)
				player->Attack();
		}
		else
		{
			player->Move(1, deltaTime);

			if (entry)
			{
				entryTimer += deltaTime;
				if (entryTimer >= entryTime)
				{
					entry = false;
				}
			}

			if (victory)
			{
				victoryTimer += deltaTime;
				if (victoryTimer >= victoryTime)
				{
					if (currentStage == 0) // ChangeScene�� ������� �ʴ� ������ �⺻Ʋ�� �ִ��� �ٲ��� ��������
					{
						CScene *nextScene = new CGameScene(1, player, score, playerLife);

						if (gScene)
							delete gScene;

						gScene = nextScene;
					}
					else
						ChangeScene("Ending_Victory");

					return;
				}
			}
		}
		player->Update(deltaTime);

		// üũ ����Ʈ ��� & �������� Ŭ��� ���� Ÿ�� üũ
		int tileIndex = player->position.x / gAssetManager->tile_Texture->width;

		if (tileList.size() > tileIndex
			&& tileIndex >= 0)  // Ÿ�ϸ���Ʈ ����� ���� ��츦 ����ó��
		{
			// üũ����Ʈ Ŭ���� �Ӽ��� ���� Ÿ���� ������ üũ����Ʈ�� ������Ʈ�ȴ�
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileInex < tileIndex)
			{
				checkPointTileInex = tileIndex;
				onCheckPointMessage = true;
			}

			// �������� Ŭ���� �Ӽ��� ���� Ÿ���� ������ �������� Ŭ��� ������
			if (!victory && tileEntryInfo[tileIndex].stageEnd)
			{
				victory = true;
				onStageClearMessage = true;
			}
		}

		// ���� ó��
		if (player->isDie)
		{
			//effectList.push_back(new CEffect(player->position, gAssetManager->explodeTexture, 21, 0.05f));

			// ī�޶� Ÿ�� ����
			mainCamera->SetTarget(tileList[checkPointTileInex]);

			delete player;
			player = NULL;

		}
	}
	else
	{
		// ��Ȱ ó��
		rebirthTimer += deltaTime;
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				D3DXVECTOR2 rebirhtPos = tileList[checkPointTileInex]->position + D3DXVECTOR2(128, 0);

				player = new CPlayer(rebirhtPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
			}
			else
			{
				//���� �й�
				ChangeScene("Ending_GameOver");
				return;
			}
		}
	}

	//��
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDie)
		{
			// ����Ʈ
		}

		if ((*it)->isDestroyed || (*it)->isDie)
		{
			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}

	// ����
	for (list<CTrap*>::iterator it = trapList.begin(); it != trapList.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}

	// ������
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isUse && (*it)->index != -1) // �����̳ʴ� ������� �ʵ��� ó��
		{
			delete(*it);
			it = itemList.erase(it);
		}
		else
			++it;
	}

	// --- �Ѿ� ---
	//�� �Ѿ�
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); )
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = enemyBulletList.erase(it);
		}

		else
			++it;
	}

	//�÷��̾� �Ѿ�
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); )
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = playerBulletList.erase(it);
		}

		else
			++it;
	}

	// ����Ʈ
	for (list<CEffect*> ::iterator it = effectList.begin(); it != effectList.end();)
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

	// ---UI---
	// ���ʽ� ����� ó��
	if (score >= 500 * (bonusLifeChecker + 1))
	{
		if (playerLife < 5)
		{
			playerLife++;
		}
		bonusLifeChecker++;
	}

	// ���׷��̵� �����̳� ó��
	if (score >= 1000 * (continerChecker + 1))
	{
		if (!onContinerSpawn)
		{
			onContinerSpawn = true;
		}
		continerChecker++;
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
	}

	for (int i = 0; i < 5; i++)
	{
		playerLifeUI[i].Update(deltaTime);
	}

	if (onUpgradeMessage)
	{
		upgradeMessageTimer += deltaTime;
		if (upgradeMessageTimer >= 2.0f)
		{
			upgradeMessageTimer = 0.0f;
			onUpgradeMessage = false;
		}

		upgradeMessage.Update(deltaTime);
	}

	if (onCheckPointMessage)
	{
		checkPointMessageTimer += deltaTime;
		if (checkPointMessageTimer >= 2.0f)
		{
			checkPointMessageTimer = 0.0f;
			onCheckPointMessage = false;
		}

		checkPointMessage.Update(deltaTime);
	}

	if (onStageClearMessage)
	{
		stageClearMessageTimer += deltaTime;
		if (stageClearMessageTimer >= 2.0f)
		{
			stageClearMessageTimer = 0.0f;
			onStageClearMessage = false;
		}

		stageClearMessage.Update(deltaTime);
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	// �� �׸���
	if (map)
		map->Render(sprite);

	// Ÿ�� �׸���
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}

	// ����
	for (list<CTrap*>::iterator it = trapList.begin(); it != trapList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// �� �Ѿ� �׸���
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	//�� �׸���
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// �÷��̾� �׸���
	if (player)
		player->Render(sprite);

	// ������
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// �÷��̾� �Ѿ� �׸���
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// ����Ʈ �׸���
	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	//UI�׸���
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Draw(sprite, gAssetManager->numberTexture);
	}

	for (int i = 0; i < 5; i++)
	{
		if (playerLife>i)
			playerLifeUI[i].Draw(sprite, gAssetManager->player_1_Texture);
	}

	if (onUpgradeMessage)
		upgradeMessage.Draw(sprite, gAssetManager->upgradeMessage);
	if (onCheckPointMessage)
		checkPointMessage.Draw(sprite, gAssetManager->checkPointMessage);
	if (onStageClearMessage)
		stageClearMessage.Draw(sprite, gAssetManager->stageClearMessage);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
			switch (wParam) {
			case VK_SPACE:
				if (player)
					if (!entry && !victory)
					player->Jump();
				break;
			case VK_F1:
				superPower = !superPower;
				break;
			case VK_F2:
				if (player)
				{
					if (player->upgrade < 2)
						player->upgrade++;
				}
				break;
			case VK_F3:
				if (player)
				{
					if (player->upgrade > 0)
						player->upgrade--;
				}
				break;
			}
	}
}
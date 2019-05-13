#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int inputStage)
	: tileEntryInfo(), currentTileIndex(0), tileList(), cheatinvincible(false),
	playerLife(3), rebirthTime(3), rebirthTimer(0), checkPointIndex(0),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0),
	enemyBulletList(), playerBulletList(), effectList(), objectList(), invincible(false),
	itemTimer(0), itemTime(3), isItem(false), isStageClear(false), stageClearTime(2), stageClearTimer(0),
	isClearAttack(false), clearAttackTimer(0), clearAttackTime(3), clearAttackCount(2), playerImage(new CMatrix),
	miniMap(new CMatrix), playerPoint(new CMatrix), savePoint(new CMatrix), itemMessage(new CMatrix),
	itemCool(new CMatrix), clearCool(new CMatrix), currentStage(inputStage), isEnter(false),
	stageBG(new CMatrix), stageStart(new CMatrix), stageClear(new CMatrix), isStageStart(true), mainUI(new CMatrix),
	conUI(new CMatrix), conBG(new CMatrix), overUI(new CMatrix), isOver(false), isCon(false), isLose(false),
	invincibleTimer(0), tileCount_N(0), tileCount_O(0), randEffect(false), effectTimer(0),
	isHole(false), holeTimer(0), holeTime(0.4f), conAni(NULL), isConAni(false), itemState(new CMatrix)
{
	mainCamera = new CCamera(); // ī�޶� ����
	map = new CMap(0, mainCamera); // �� ���� �������� �ӽ� ����

	mainUI->currentScene = ext_Stage - 1; // ���� ������ Ŀ��Ʈ��

	// Ÿ�� �迭
	TileSet();
	
	// �� �迭
	enemyEntryInfo.push_back(EnemyEntryInfo(1, 2));

	// �������� ���� ���� UI
	stageBG->a = 255;

	stageStart->currentScene = currentStage - 1;
	stageStart->a = 255;

	stageClear->currentScene = currentStage - 1;
	stageClear->a = 0;

	for (int i = 0; i < 6; ++i)
	{
		stageClear_Num[i] = new CMatrix;
		stageClear_Num[i]->position.x = 250 + 48 * i;
		stageClear_Num[i]->position.y = 479;
		stageClear_Num[i]->a = 0;
	}

	// �������� ��Ƽ�� ����
	conUI->a = 0;
	conUI->SetAnimation(1, 10, false);
	conBG->a = 0;
	overUI->a = 0;

	// ������ ����
	itemState->position = D3DXVECTOR2(91, 207);
	itemState->center = D3DXVECTOR2(32, 32);
	itemState->a = 0;

	// ������ �޼��� a 0���� �����α�
	itemMessage->a = 0;

	// ������ ��Ÿ�� UI��ġ
	itemCool->position = D3DXVECTOR2(137, 240);
	itemCool->center = D3DXVECTOR2(8, 64); // �ٴ����� �ص־� ������ �پ����
	itemCool->scale = D3DXVECTOR2(1, 0);
	clearCool->position = D3DXVECTOR2(153, 179);
	clearCool->center = D3DXVECTOR2(0, 8);
	clearCool->scale = D3DXVECTOR2(0, 1);

	// UI ���� & �ʱ�ȭ
	for (int i = 0; i < 3; ++i)
	{
		playerLife_UI[i] = new CMatrix;
		playerLife_UI[i]->position.x = 180 + 84 * i;
		playerLife_UI[i]->position.y = 68;
		playerLife_UI[i]->scale.x = 1.2f;
	}

	for (int i = 0; i < 6; ++i)
	{
		score_UI[i] = new CMatrix;
		score_UI[i]->position.x = 648 + 36 * i;
		score_UI[i]->position.y = 100;
		score_UI[i]->scale = D3DXVECTOR2(0.8f, 0.8f);
	}

	for (int i = 0; i < 2; ++i)
	{
		clearAttackCount_UI[i] = new CMatrix;
		clearAttackCount_UI[i]->position.x = 158 + 52 * i;
		clearAttackCount_UI[i]->position.y = 89;
		clearAttackCount_UI[i]->scale = D3DXVECTOR2(0.6f, 0.6f);
	}

	// Player Image
	playerImage->center = D3DXVECTOR2(64, 64);
	playerImage->position = D3DXVECTOR2(98, 98);
	
	// �̴ϸ� ��ġ
	miniMap->position.y = 768 - 100 + 50;

	savePoint->position.x = 32;
	savePoint->position.y = 768 - 100 - 14 + 50;
	savePoint->center = D3DXVECTOR2(32, 32);

	playerPoint->position.x = 32;
	playerPoint->position.y = 768 - 100 - 14 + 50;
	playerPoint->center = D3DXVECTOR2(32, 32);

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024; // ī�޶� �Ѱ��� ����

	// �÷��̾� ���� �� ����
	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;
	invincible = true; // 2�� ����
	mainCamera->SetTarget(player); // ī�޶� Ÿ�� �÷��̾�� �ٲ��ֱ� 
}

CGameScene::~CGameScene()
{
	// tile List delete
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	// enemy List delete
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	// enemy Bullet List delete
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete (*it);
	enemyBulletList.clear();

	// player Bullet List delete
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

	// Effect delete
	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete (*it);
	effectList.clear();

	// object delete
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (*it)
			delete (*it);
	objectList.clear();

	// UI delete
	for (int i = 0; i < 6; ++i)
	{
		delete  score_UI[i];
		if(i < 3)
			delete playerLife_UI[i];
		if (i < 2)
			delete clearAttackCount_UI[i];
	}
	
	// minimap delete
	delete miniMap;
	delete playerPoint;
	delete savePoint;

	// item state
	delete itemState;
	
	// Stage delete
	delete stageBG;
	delete stageStart;
	delete stageClear;
	for (int i = 0; i < 6; ++i)
		delete stageClear_Num;

	// con ani
	delete conAni;

	// con delete
	delete conUI;
	delete conBG;
	delete overUI;

	// main ui
	delete mainUI;

	// item Message delete
	delete itemMessage;

	// item cool
	delete itemCool;
	delete clearCool;

	// player Image UI
	delete playerImage;

	// player delete
	if (player)
		delete player;

	// camera delete
	if(mainCamera)
		delete mainCamera;

	// map delete
	if(map)
		delete map;
}

void CGameScene::Update(float deltaTime)
{
	switch (ext_Stage)
	{
	case 1:
		gAssetManager->GetSound("Stage2")->Play();
		break;
	case 2:
		gAssetManager->GetSound("Stage2")->Play();
		break;
	default:
		gAssetManager->GetSound("Stage2")->Play();
		break;
	}

	// Camera Update
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// Map Update
	if (map)
		map->Update(deltaTime);

	// �������� ����
	if (isStageStart)
	{
		stageStart->a -= 200 * deltaTime;
		stageBG->a -= 100 * deltaTime;

		if (stageStart->a < 0)
			stageStart->a = 0;

		if (stageBG->a < 0)
		{
			stageBG->a = 0;
			isStageStart = false;
		}

		stageStart->Update(deltaTime);
		stageBG->Update(deltaTime);
	}

	TileUpdate(deltaTime);		// Tile Update
	PlayerUpdate(deltaTime);	// Player Update
	ObjectUpdate(deltaTime);	// Object Update
	EnemyUpdate(deltaTime);		// Enemy Update
	BulletUpdate(deltaTime);	// Bullet Update
	TargetUpdate(deltaTime);	// Target Update
	RectUpdate(deltaTime);		// Rect Update
	EffectUpdate(deltaTime);	// Effect Update
	UIUpdate(deltaTime);		// UI Update
	MiniMapUpdate(deltaTime);	// MiniMap Update

	if (isStageClear || isCon)
	{
		stageClearTimer += deltaTime;
		if (stageClearTime < stageClearTimer)
		{
			// ���������� ���� ���� �������� or ���� ����
			if (isEnter)
			{
				// ��Ƽ���� ����
				if (isCon)
					switch (currentStage)
					{
					case 1:
						ChangeScene("Game_Stage_1");
						break;
					case 2:
						ext_Score = ext_2Stage_Score;
						ChangeScene("Game_Stage_2");
						break;
					}
				else if(isStageClear)
					// �ƴϸ� ����
					switch (currentStage)
					{
					case 1:
						ChangeScene("Game_Stage_2");
						break;
					case 2:
						ChangeScene("Ending_Win");
						break;
					}
			}
		}
	}

	// �й�
	if (isLose)
	{
		ChangeScene("Ending_Lose");
		return;
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	// map Render
	map->Render(sprite);

	// Tile List Render
	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);
	
	// Object Render
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
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
		if((*it)->type == 100)
			(*it)->Render(sprite);

	// Effect Render
	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	// Con Ani
	if (isConAni && conAni)
		conAni->Draw(sprite, gAssetManager->GetTexture("conEffect")); //�����ϱ�

	// MiniMap Render
	miniMap->Draw(sprite, gAssetManager->GetTexture("MiniMap"));
	playerPoint->Draw(sprite, gAssetManager->GetTexture("PlayerPoint"));
	savePoint->Draw(sprite, gAssetManager->GetTexture("SavePoint"));

	// item Message
	itemMessage->Draw(sprite, gAssetManager->GetTexture("ItemMessage"));

	// item Cool
	itemCool->Draw(sprite, gAssetManager->GetTexture("ItemCool"));
	clearCool->Draw(sprite, gAssetManager->GetTexture("ClaerCool"));

	// item state
	itemState->Draw(sprite, gAssetManager->GetTexture("Item"));

	// main ui
	mainUI->Draw(sprite, gAssetManager->GetTexture("MainUI"));

	// UI Render
	for (int i = 0; i < 6; ++i)
	{
		score_UI[i]->Draw(sprite, gAssetManager->GetTexture("Num_B"));

		if (i < playerLife)
			playerLife_UI[i]->Draw(sprite, gAssetManager->GetTexture("PlayerLife"));

		if (i < clearAttackCount)
			clearAttackCount_UI[i]->Draw(sprite, gAssetManager->GetTexture("clearAttackCount")); // �ӽ�
	}

	playerImage->Draw(sprite, gAssetManager->GetTexture("PlayerImage"));

	// ��Ƽ��
	conBG->Draw(sprite, gAssetManager->GetTexture("Black"));
	conUI->Draw(sprite, gAssetManager->GetTexture("Continue"));
	overUI->Draw(sprite, gAssetManager->GetTexture("Over"));

	// Stage Start Clear
	stageBG->Draw(sprite, gAssetManager->GetTexture("Black"));
	stageClear->Draw(sprite, gAssetManager->GetTexture("StageClear_Mes"));
	stageStart->Draw(sprite, gAssetManager->GetTexture("StageStart_Mes"));
	for (int i = 0; i < 6; ++i)
		stageClear_Num[i]->Draw(sprite, gAssetManager->GetTexture("Num_B"));
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE: // Player Jump
			if (player && !isStageClear)
				player->Jump();
			break;

		case VK_F1: // Player ����
			if (player && !isStageClear)
			{
				cheatinvincible = !cheatinvincible;

				if (cheatinvincible)
					player->a = 150;
				else
					player->a = 255;
			}
			break;

		case VK_F2: // Player ���׷��̵�
			if (player && player->upgrade < 2 && !isStageClear)
				player->upgrade++;
			break;

		case VK_F3: // Player ��׷��̵�
			if (player && player->upgrade > 0  && !isStageClear)
				player->upgrade--;
			break;
			
		case VK_RETURN: // �������� Ŭ�������� �� �Ѱ��ֱ�
			if (stageClear || isCon)
				isEnter = true;
			break;

		case 'Q': // Player Die Test
			if (player && !isStageClear)
				if (playerLife < 3)
					playerLife++;
			break;

		case 'P': // Player Die Test
			if (player && !isStageClear)
				player->speed = 3000;
			break;

		case 'W': // Player Speed Test
			if (player && !isStageClear)
				if (clearAttackCount < 2)
					clearAttackCount++;
			break;

		case 'A': // Camera Shake Test
			if (player && !isStageClear)
				player->DoubleJump();
			break;

		case 'S': // Player Die Test
			if (player && !isStageClear)
				player->SpeedUp();
			break;

		case 'D': // Player Die Test
			if (player && !isStageClear)
				player->LongAttack();
			break;

		case 'F': // Player Die Test
			if (player && !isStageClear)
				player->MultiAttack();
			break;

		case 'G': // Player Die Test
			if (player && !isStageClear)
				player->HomingAttack();
			break;

		case 'H': // Player Die Test
			if (player && !isStageClear)
				if (clearAttackCount < 2)
					clearAttackCount++;
			break;

		case 'C': // Player ClearAttack		

			if (player && !isClearAttack && clearAttackCount > 0 && !isStageClear)
			{
				isClearAttack = true;
				clearAttackCount--;
				clearCool->scale.x = 0;
				mainCamera->ShakeCamera(0.7f, 50000);

				// ClearAttack Effect
				effectList.push_back(new CEffect(D3DXVECTOR2(0, 0), 10, mainCamera));
				randEffect = true;

				// enemy List Clear
				for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
					if (*it)
						(*it)->isDie = true;

				// enemy Bullet Clear
				for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
					if (*it)
						(*it)->isDestroyed = true;

				// object Clear
				for (auto it = objectList.begin(); it != objectList.end(); ++it)
					if ((*it)->type == 1 && (*it)->position.x < player->position.x + 1024)
						(*it)->isDestroyed = true;
			}
			break;
		}
		break;
	}
}

// Tile Update
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
					entryPos.y -= 87;
				break;
			default:
				if (t->type == 2)
					entryPos.y += 87;
				break;
			}

			if (tileEntryInfo[currentTileIndex].type == 1)
			{
				tileCount_O++;
				tileCount_N = 0;
			}
			if (tileEntryInfo[currentTileIndex].type == 2)
			{
				tileCount_N++;
				tileCount_O = 0;
			}
		}

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);

		// Ÿ���� �����ϰ�, ������Ʈ Ÿ���� 0���� Ŭ�� ������Ʈ ����
		if (tile->type == 0 && tileEntryInfo[currentTileIndex].objectType > 0)
		{
			// ó�� 3Ÿ�Ͽ� ������Ʈ ���� x
			if (currentTileIndex > 3)
				// ������ ���� �ΰ��ϰ�� �׳� ���� ����
				if (!(tileEntryInfo[currentTileIndex - 1].objectType == 2 && tileEntryInfo[currentTileIndex].objectType == 2))
				{
					D3DXVECTOR2 entryPos = tile->position + D3DXVECTOR2(128, 80);

					if(tileEntryInfo[currentTileIndex].objectType == 100)
						entryPos.y -= 32;

					// ���� �վ��ֱ�
					if (tileEntryInfo[currentTileIndex].objectType == 2)
					{
						tileList[currentTileIndex]->currentScene = 3;
						entryPos.y += 173;
					}

					CObject* object = new CObject(entryPos, tileEntryInfo[currentTileIndex].objectType, mainCamera);
					objectList.push_back(object);
				}
		}

		currentTileIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

// Player Update
void CGameScene::PlayerUpdate(float deltaTime)
{
	// Player Update
	if (player)
	{
		// ���������� Ŭ�������� ��� ���ݰ� �̵��� �ȵǸ� �ڵ� �̵� �� ������ �ɾ���
		if (isStageClear)
		{
			player->position.x += 180 * deltaTime;
			cheatinvincible = true;
		}
		else
		{
			// ���ۿ� ���� ��� �ȵǰ� ����
			if (!isHole && !isConAni)
			{
				// �÷��̾� �̵�
				if (GetKeyState(VK_LEFT) & 0x8000)
					player->Move(-1, deltaTime);
				if (GetKeyState(VK_RIGHT) & 0x8000)
					player->Move(1, deltaTime);
				// �÷��̾� ����
				if (GetKeyState('X') & 0x8000)
					player->Attack();
				else if (GetKeyState('Z') & 0x8000)
					player->Attack_Sky();
			}
			else
				player->velocity_X = 0;
		}

		// �÷��̾� Ÿ�� ��ǥ �޾ƿ���
		int tileIndex = player->position.x / tileWidth;
		// �÷��̾� üũ����Ʈ �ε���
		if (tileIndex >= 0 && tileIndex < tileEntryInfo.size())
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex > checkPointIndex)
				checkPointIndex = tileIndex;

		// clearAttack�� 3�ʿ� �� �� �� �� �� ����
		if (isClearAttack && clearAttackCount > 0)
		{
			clearAttackTimer += deltaTime;

			if (clearAttackTimer > 3)
				clearAttackTimer = 3;

			// ������ ��Ÿ�� UI ������ ���̱�
			if (clearAttackTimer != 0)
			{
				float temp = clearAttackTimer / 3;

				if (temp < 0) temp = 0;
				if (temp > 1) temp = 1;

				clearCool->scale.x = temp;
			}

			// clear Attack ����
			if (clearAttackTimer >= clearAttackTime)
			{
				isClearAttack = false;
				clearAttackTimer = 0;
			}
		}

		// ������ ���ӽð� ó�� & ������ ��Ÿ�� UI ������ ���̱�
		if (isItem)
		{
			itemTimer += deltaTime;
			
			if (itemTimer > 3.5f)
				itemTimer = 3.5f;

			// ������ ��Ÿ�� UI ������ ���̱�
			if (itemTimer != 0)
			{
				float temp = itemTimer / 3.5f;

				if (temp < 0) temp = 0;
				if (temp > 1) temp = 1;

				itemCool->scale.y = 1 - temp;
			}

			// ������ ���ӽð� ó��
			if (itemTime <= itemTimer)
			{
				player->Reset();
				itemState->a = 0;
				itemTimer = 0;
				isItem = false;
			}

		}

		// �÷��̾� ����
		if (invincible || cheatinvincible)
		{
			player->a = 150;
			player->isDie = false;
			if (invincible)
			{
				invincibleTimer += deltaTime;
				if (3 < invincibleTimer)
				{
					invincibleTimer = 0;
					invincible = false;
				}
			}
		}
		else
			player->a = 255;

		// ���ۿ� ������ ���
		if (isHole)
		{
			holeTimer += deltaTime;
			if (holeTimer > holeTime)
			{
				holeTimer = 0;
				isHole = false;
				player->isDie = true;
			}
		}

		// Player Update
		player->Update(deltaTime);

		if (player->isDie)
		{
			gAssetManager->GetSound("Die")->Play();
			effectList.push_back(new CEffect(player->position, 2, mainCamera));

			mainCamera->ShakeCamera(0.2f, 2048);

			mainCamera->SetTarget(NULL);
			invincible = false;
			invincibleTimer = 0;

			playerLife--;

			player = NULL;
			delete player;
		}
	}
	else
	{
		// �÷��̾� ��Ȱ
		rebirthTimer += deltaTime;

		if (rebirthTimer > rebirthTime)
		{
			if (playerLife > 0)
			{
				D3DXVECTOR2 entryPos = tileList[checkPointIndex]->position + D3DXVECTOR2(128, 0);

				player = new CPlayer(entryPos, mainCamera);
				player->parentScene = this;
				invincible = true; // 2�� ����
				mainCamera->SetTarget(player);
				rebirthTimer = 0;
			}
			else
			{
				// ��Ƽ��
				// ��׶��� a
				conBG->a += 200 * deltaTime;
				if (conBG->a > 255)
					conBG->a = 255;

				if (!isOver)
				{
					// ������ �� �����ϴ�...
					overUI->a += 200 * deltaTime;
					if (overUI->a > 255)
					{
						isOver = true;
						overUI->a = 255;
					}
				}
				else
				{
					// �ٿ��ְ�
					overUI->a -= 150 * deltaTime;
					if (overUI->a < 0)
					{
						overUI->a = 0;
						isCon = true;
					}
				}

				if (isCon)
				{
					// ����Ͻðڽ��ϱ�?
					conUI->a += 200 * deltaTime;

					if (conUI->a >= 255)
					{
						conUI->a = 255;

						conUI->Update(deltaTime);

						if (stageClearTime < stageClearTimer)
							if (conUI->isAniEnd)
								isLose = true;
					}
				}
			}
		}
	}
}

void CGameScene::TargetUpdate(float deltaTime)
{
	// enemy Bullet List Update
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (player)
			player->SetTarget1((*it));

	// Enemy
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (player)
			player->SetTarget2((*it));

	// object Update
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (player && (*it)->type == 1 && (*it)->position.x < player->position.x + 800)
			player->SetTarget3((*it));
}

// Enemy Update
void CGameScene::EnemyUpdate(float deltaTime)
{
	enemyEntryTimer += deltaTime;

	// �÷��̾ ���� ���� ����
	while (enemyEntryTimer > enemyEntryInfo[currentEnemyIndex].timer && player)
	{
		// ���� ��ġ
		D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 250 - rand() % 100);
		// ����
		CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
		enemy->parentScene = this;
		enemyList.push_back(enemy);

		// ���� ����
		enemyEntryInfo.push_back(EnemyEntryInfo(rand() % 2 + 1, enemyEntryInfo[currentEnemyIndex].timer + 2.3f + rand() % 1 + ((rand()% 10) / 10)));

		currentEnemyIndex++;
		if (currentEnemyIndex >= enemyEntryInfo.size())
		{
			currentEnemyIndex = 0;
			enemyEntryTimer = 0;
			break;
		}
	}

	// enemy List Update
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDie)
		{
			// Score & effect
			gAssetManager->GetSound("Die")->Play();
			effectList.push_back(new CEffect((*it)->position, 3, mainCamera));
			ext_Score += 70 + rand() % 80;
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
	// enemy Bullet List Update
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			effectList.push_back(new CEffect((*it)->position, 1, mainCamera));
			delete (*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	// player Bullet List Update
	for (auto it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			effectList.push_back(new CEffect((*it)->position, 1, mainCamera));
			delete (*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::RectUpdate(float deltaTime)
{
	// player < enemyBullet enemy obejct
	if (player)
	{
		// enemy
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		{ 
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDie = true;
			}
		}
		// enem Bullet
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
		// object
		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect) && (*it)->isActive)
			{
				// ������ ȿ�� ����
				switch ((*it)->type)
				{
				case 11:
					player->DoubleJump();
					itemState->currentScene = 0;
					break;
				case 12:
					player->SpeedUp();
					itemState->currentScene = 1;
					break;
				case 13:
					player->LongAttack();
					itemState->currentScene = 2;
					break;
				case 14:
					player->MultiAttack();
					itemState->currentScene = 3;
					break;
				case 15:
					player->HomingAttack();
					itemState->currentScene = 4;
					break;
				case 16:
					if(clearAttackCount < 2)
						clearAttackCount++;
					itemState->currentScene = 5;
					break;
				case 100:
					gAssetManager->GetSound("Upgrade")->Play();

					invincible = true; // 2�� ����

					// upgrade
					if(player->upgrade < 2)
						player->upgrade++;

					// life ++
					playerLife = 3;

					// con ani
					conAni = new CMatrix();
					conAni->SetAnimation(0.05f, 20, false); // �����ϱ�
					isConAni = true;

					// �浹 �ȵǰ�
					(*it)->isActive = false;

					break;
				case 777:
					isStageClear = true;
					break;
				}

				// ������ ȹ�� �޼���
				if ((*it)->type > 10 && (*it)->type < 101)
				{
					itemMessage->a = 255;
					switch ((*it)->type)
					{
					case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					case 16:
						itemMessage->currentScene = (*it)->type - 11;
						break;
					case 100:
						itemMessage->currentScene = 6;
						break;
					}
				}

				// �������� ȹ������ �� ó��
				if ((*it)->type > 10 && (*it)->type < 17)
				{
					// ������ ���ӽð�
					if ((*it)->type - 10 != 2 && (*it)->type - 10 != 6)
					{
						isItem = true;
						itemTimer = 0;
					}

					itemCool->scale = D3DXVECTOR2(1, 1);

					// item state
					itemState->a = 255;
				}

				// �浹������Ʈ�� ��쿡�� �÷��̾� ���
				if((*it)->type == 1)
					player->isDie = true;
				
				// ���ۿ� ������ isHole Ʈ��
				if ((*it)->type == 2)
				{
					mainCamera->SetTarget(NULL);
					isHole = true;
				}

				// �����̴� �Ȼ���� ���׷��̵嵵 �������� Ŭ���
				if((*it)->type != 2 && (*it)->type != 100 && (*it)->type != 777)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet > enemy obejct enemyBullet
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// enemy
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect))
			{
				(*it2)->hp--;
				(*it2)->beHit = true;
				(*it)->isDestroyed = true;
			}
		}

		// enemy Bullet
		for (auto it2 = enemyBulletList.begin(); it2 != enemyBulletList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect) && (*it)->type == 100)
			{
				(*it2)->isDestroyed = true;
				(*it)->isDestroyed = true;
			}
		}

		// object
		for (auto it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect) && (*it2)->type == 1)
			{
				(*it2)->hp--;
				(*it)->isDestroyed = true;
			}
		}
	}
}

void CGameScene::EffectUpdate(float deltaTime)
{
	// Effect Update
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

	// ������ǥ ����Ʈ �ѷ��ֱ�
	if (randEffect)
	{
		effectList.push_back(new CEffect(D3DXVECTOR2(rand() % 1024, rand() % 768), 100, mainCamera));

		effectTimer += deltaTime;
		if (effectTimer > 0.8f)
		{
			effectTimer = 0;
			randEffect = false;
		}
	}
}

void CGameScene::ObjectUpdate(float deltaTime)
{
	// object Update
	for (auto it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			if ((*it)->type == 1)
			{
				int ran = rand() % 2 + 1;
				if (ran == 1) 
				{
					D3DXVECTOR2 entryPos = (*it)->position;
					effectList.push_back(new CEffect(entryPos, 2, mainCamera));

					CObject* object = new CObject(entryPos, (rand() % 6 + 11), mainCamera);
					objectList.push_back(object);
				}
			}

			delete (*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::UIUpdate(float deltaTime)
{
	// ���ھ� ������ ź�� ����
	int tempScore = ext_Score;
	for (int i = 5; i >= 0; --i)
	{
		score_UI[i]->currentScene = tempScore % 10;
		tempScore /= 10;
	}

	for (int i = 0; i < 6; ++i)
		score_UI[i]->Update(deltaTime);

	for (int i = 0; i < 3; ++i)
	{
		playerLife_UI[i]->currentScene = playerLife - 1;
		playerLife_UI[i]->Update(deltaTime);
	}

	for (int i = 0; i < 2; ++i)
		clearAttackCount_UI[i]->Update(deltaTime);

	// item state
	itemState->Update(deltaTime);

	// ������ ȹ�� �޼���
	itemMessage->a -= 100 * deltaTime;
	if (itemMessage->a < 0)
		itemMessage->a = 0;

	// ������ ��Ÿ�� ������Ʈ
	itemCool->Update(deltaTime);
	clearCool->Update(deltaTime);

	// �÷��̾� �̹��� ������Ʈ
	if(player)
		playerImage->currentScene = player->upgrade;

	playerImage->Update(deltaTime);

	// �����̳� �ִ� ������Ʈ
	if (isConAni)
	{
		if (conAni->isAniEnd)
			isConAni = false;

		conAni->Update(deltaTime);
	}

	// �������� Ŭ����
	if (isStageClear)
	{
		// �������� Ŭ���� UI����
		stageClear->a += 200 * deltaTime;
		stageBG->a += 200 * deltaTime;

		for (int i = 0; i < 6; ++i)
			stageClear_Num[i]->a += 200 * deltaTime;

		if (stageBG->a > 255)
			stageBG->a = 255;

		if (stageClear->a > 255)
			stageClear->a = 255;

		for (int i = 0; i < 6; ++i)
			if (stageClear_Num[i]->a > 255)
				stageClear_Num[i]->a = 255;

		int tempScore = ext_Score;
		for (int i = 5; i >= 0; --i)
		{
			stageClear_Num[i]->currentScene = tempScore % 10;
			tempScore /= 10;
		}

		stageClear->Update(deltaTime);
		stageBG->Update(deltaTime);
		for (int i = 0; i < 6; ++i)
			stageClear_Num[i]->Update(deltaTime);
	}
}

// �̴ϸ�
void CGameScene::MiniMapUpdate(float deltaTime)
{
	miniMap->Update(deltaTime);

	if (player)
	{
		float temp = player->position.x / (tileEntryInfo.size() * tileWidth);

		if (temp < 0)
			temp = 0;
		if (temp > 1)
			temp = 1;

		playerPoint->position.x = 32 + (964 * temp);
		playerPoint->Update(deltaTime);
	}

	float temp = (tileList[checkPointIndex]->position.x + 128) / (tileEntryInfo.size() * tileWidth);
	savePoint->position.x = 32 + (964 * temp);
	savePoint->Update(deltaTime);
}

// Ÿ�� ���� ����
void CGameScene::TileSet()
{
	for (int i = 0; i < 200; ++i)
	{
		if (i == 195) // �������� Ŭ����
		{
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(0, 777));
			continue;
		}

		if (i % 25 == 0) // �����̳�, üũ����Ʈ
		{
			tileEntryInfo.push_back(TileEntryInfo(0, 100, true));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(0));
			continue;
		}

		if (i > 195) // �������� Ŭ���� �Ŀ� ���� Ÿ�ϸ� ����
		{
			tileEntryInfo.push_back(TileEntryInfo(0));
			continue;
		}

		int ran = rand() % 10 + 1; // ���� ����

		if (ran < 8)
		{
			if(ran == 5) // ������ ���� ����
				tileEntryInfo.push_back(TileEntryInfo(0, rand() % 6 + 11));
			else if(ran == 6) // ��ֹ� ���� ����
				tileEntryInfo.push_back(TileEntryInfo(0, rand() % 2 + 1));
			else if(ran == 7)// ��ֹ� ���� ����
				tileEntryInfo.push_back(TileEntryInfo(0, rand() % 2 + 1));
			else // �Ϲ� Ÿ�� ����
				tileEntryInfo.push_back(TileEntryInfo(0));
		}
		else if(ran == 8 && tileCount_O <= 3) // �������� ����
			tileEntryInfo.push_back(TileEntryInfo(1));
		else if(ran == 9 && tileCount_N <= 3) // �������� ����
			tileEntryInfo.push_back(TileEntryInfo(2));

		if (tileCount_O == 3)
		{
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(2));
			tileEntryInfo.push_back(TileEntryInfo(2));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(2));
			tileEntryInfo.push_back(TileEntryInfo(2));
		}

		if (tileCount_N == 3)
		{
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(1));
			tileEntryInfo.push_back(TileEntryInfo(1));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(1));
			tileEntryInfo.push_back(TileEntryInfo(1));
		}
	}
}
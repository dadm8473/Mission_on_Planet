#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0), enemyEntryInfo(), currentEnemyEntryIndex(0), enemyEntrytimer(0),
	playerLife(3), rebirthTimer(0), rebirthTime(3)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// Ÿ�� ���� ���� + ������Ʈ ����
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, 0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0)); 
	tileEntryInfo.push_back(TileEntryInfo(0, 1));

	// �� ���� ����
	enemyEntryInfo.push_back(EnemyEntryInfo(5, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(10, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(10, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 1));

	// �÷��̾� ������Ʈ ����
	player = new CPlayer(D3DXVECTOR2(100.0f, 384.0f), mainCamera);
	player->parentScene = this; // ���� GameScene�� ���

	// ī�޶� ����
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->tile_Texture->width - 1024.0f;
	// Ÿ������ �÷��̾ ����
	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end();++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	// �Ҹ��ڿ��� �÷��̾� ���������
	if (player)
		delete player;

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	// �浹 üũ �κ� ====================================================================
	// ����� ���÷� �����

	// �÷��̾� �Ѿ� - ������Ʈ
	/* �̰� �Ѿ��� ������ �ȵ��־ ���÷� �ּ����� ����
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// ������Ʈ �� ������ (Type 1)
		for (list<CObject*>::iterator it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;
			
			// Ÿ�� üũ�� �浹 üũ�� ���ÿ�
			if ((*it2)->type == 1 && (&ref, &(*it)->rect, &(*it2)->rect))
			{
				score += 15; // �Ѿ� ���� ����

				// �Ѿ� ����
				(*it)->isDestroyed = true;

				// ���� ������ ����
				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 100; // ���� �ı� ����

					// ���� ����
					(*it2)->isDestroyed = true;
				}
			}
		}
	}
	*/

	// ������Ʈ�� �浹 üũ�κ���
	// ������Ʈ - �÷��̾�
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
				player->isDie = true;
		}
	}

	// ===================================================================================

	// ī�޶�
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// ��
	if (map)
		map->Update(deltaTime);

	// Ÿ��
	float currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;

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
			CTile* t = tileList[currentTileEntryIndex - 1];
			
			entryPos.x = t->position.x + gAssetManager->tile_Texture->width;
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // ������
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
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

		// ������Ʈ ���� �κ� ============================================================
		// ������ Ÿ���϶� �� ������Ʈ�� �����ؾ��� �׷��� �������� �˻���
		if (tileEntryInfo[currentTileEntryIndex].type == 0)
		{
			D3DXVECTOR2 objectEntryPos = tile->position;
			objectList.push_back(new CObject(mainCamera, objectEntryPos, tileEntryInfo[currentTileEntryIndex].objectType));
		}
		// ===============================================================================

		currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Update(deltaTime);
	}

	// �÷��̾� ==========================================================================
	if (player)
	{
		// �¿� Ű�� �޴´�.
		if (GetKeyState(VK_LEFT) & 0x0800)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x0800)
			player->Move(1, deltaTime);
		// ������ �Ʒ� MsgProc �Լ����� ó����

		player->Update(deltaTime);

		// ���� ó��
		if (player->isDie)
		{
			// �÷��̾ ���ﶧ�� �ݵ�� ī�޶��� Ÿ���� NULL�� �ٲ���Ѵ�.
			mainCamera->SetTarget(NULL);

			delete player;
			player = NULL;
		}
	}
	else
	{
		// ��Ȱ ó��
		// ���� ���� ���Ӱ� ���� ����
		rebirthTimer += deltaTime;
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				// ���߿� üũ ����Ʈ ������ ��Ȱ ��ǥ(rebirhtPos)�� ���� ����
				D3DXVECTOR2 rebirhtPos = D3DXVECTOR2(100.0f, 384.0f);

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

	// �� ���� �κ� ======================================================================
	// �� ���� ������ ���� �ð��� ���� �� ��ȯ
	// ���� ����ϰ� ���������� ���� Ÿ�� ���� �ϴ� ������� �ٲ����
	
	if (player && enemyEntryInfo.size() > 0) // �� �����κ��� �÷��̾ ����־�� ������ + �� ���� ���� ����Ʈ�� ũ��(enemyEntryInfo.size)�� 0 �̻�
	{
		enemyEntrytimer += deltaTime; // Ÿ�̸Ӱ� �ö󰡰� enemyEntryInfo ������ �°� �� �����ϴ� ����� ����

		// for������ enemyEntryInfo ����Ʈ ũ�⸸ŭ �Ź� ������ ����� �ƴ϶�
		// while���� currentEnemyEntryIndex �� �̿��ؼ� ���� ó�� �Ź� �˻����� ���� �׸��� �� ª�� ����
		while (enemyEntrytimer >= enemyEntryInfo[currentEnemyEntryIndex].time)
			// ������ �����Ǿ�� �ϴ� ���� ���� �ð��� ���� �ð� ������ ���Ѵ�.
		{
			// �� ���� X�� ��ġ�� ī�޶� �������� �����ʿ��� �����ϵ��� ���ְ� 
			// Y �� ��ġ�� ����� �� �غ��� ������ �ϴ��� �÷��̾ ��� �ִ� ���� Y�� �������� -200 - (0~100) ���̷� �����Ѵ�.
			// rand() % 100 ���� 0 ~ 100 ���̸� �������� ���� �� ����
			// ������ ����� ����Ϸ��� Game.cpp�� Update�κп� srand()�Լ� �߰��ؾ���
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 200 - rand() % 100);

			CEnemy*enemy = new CEnemy(mainCamera, entryPos, enemyEntryInfo[currentEnemyEntryIndex].type);
			enemyList.push_back(enemy);

			// ���� �����ϸ� ���� ���� �����ϱ����� index�� �ϳ� �÷��ش�.
			currentEnemyEntryIndex++;
			// �׸��� �� ���� ����Ʈ�� �ݺ� �����ϱ� ���� ����� �Ѿ�� index�� timer�� 0���� �ʱ�ȭ�Ѵ�.
			if (currentEnemyEntryIndex >= enemyEntryInfo.size())
			{
				currentEnemyEntryIndex = 0;
				enemyEntrytimer = 0.0f;
				break;
			}
		}
	}

	// �� ================================================================================
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

	// ������Ʈ ==========================================================================
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			// ����Ʈ

			delete(*it);
			it = objectList.erase(it);
		}
		else
			++it;
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

	// ������Ʈ �׸���
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// �� �׸���
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// �÷��̾� �׸���
	if (player)
		player->Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	// ���� Ű ó�� ======================================================================
	// ���� Ű ó���� ���⼭ �ϴ� ������
	switch (uMsg) {
	case WM_KEYDOWN: // ���� Ű�� ������ �� �ѹ��� ����ǰ� �ؾ��ؼ���
		switch (wParam) {
		case VK_SPACE:
			if (player)
				player->Jump();
			break;
		}
	}
}
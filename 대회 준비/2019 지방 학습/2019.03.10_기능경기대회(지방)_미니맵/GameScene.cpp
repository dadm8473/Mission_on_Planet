#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0), enemyEntryInfo(), currentEnemyEntryIndex(0), enemyEntrytimer(0), checkPointTileInex(0),
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
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
	tileEntryInfo.push_back(TileEntryInfo(0, 1));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
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

	// UI ================================================================================
	miniMapBar = CMatrix();
	playerIcon = CMatrix();
	checkPointIcon = CMatrix();

	// �̴ϸ� �ٸ� ȭ�鿡 ���� ���� ��������
	miniMapBar.position = D3DXVECTOR2(20.0f, 768.0f - 64.0f);
	miniMapBar.center = D3DXVECTOR2(20.0f, 27.0f);

	// �÷��̾� �������� �̴ϸ� �̹����� �������� ��ġ�ؾ��ϴϱ�
	// �̴ϸ� �� �׸��̶� �÷��̾� ������ �׸��̶� �ߺ��� ��ġ�ϼ�
	// �̴ϸ� �� �׸����� ���� ���۰� ���� ǥ���ϴ� ���� ���� ũ�⸦ �˾ƾ��� �� �׸������� 
	// �̹��� ������ 1024 64���� �������� X 20 Y 27 ������ X 1004 Y 27 �� ǥ�� X ���� 984 �̾ �׷��� ������ ���� �׸����� �� �ٸ��Ŵϱ� �����ؾ���
	// �𸣸� ī���ϼ���
	playerIcon.position = miniMapBar.position;
	playerIcon.center = D3DXVECTOR2(30.0f, 64.0f);
	
	checkPointIcon.position = miniMapBar.position;
	checkPointIcon.center = D3DXVECTOR2(30.0f, 64.0f);
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

		if (tileEntryInfo[currentTileEntryIndex].type == 0)
		{
			D3DXVECTOR2 objectEntryPos = tile->position;
			objectList.push_back(new CObject(mainCamera, objectEntryPos, tileEntryInfo[currentTileEntryIndex].objectType));
		}

		currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;
		currentTileEntryIndex++;
	}

	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Update(deltaTime);
	}

	// �÷��̾�
	if (player)
	{
		if (GetKeyState(VK_LEFT) & 0x0800)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x0800)
			player->Move(1, deltaTime);

		player->Update(deltaTime);

		// üũ ����Ʈ ���
		int tileIndex = player->position.x / gAssetManager->tile_Texture->width;

		if (tileList.size() > tileIndex
			&& tileIndex >= 0) 
		{
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileInex < tileIndex)
				checkPointTileInex = tileIndex;
		}

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
				//���� �й�
				ChangeScene("Ending_GameOver");
				return;
			}
		}
	}

	// ��
	if (player && enemyEntryInfo.size() > 0)
	{
		enemyEntrytimer += deltaTime;

		while (enemyEntrytimer >= enemyEntryInfo[currentEnemyEntryIndex].time)
		{
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 200 - rand() % 100);

			CEnemy*enemy = new CEnemy(mainCamera, entryPos, enemyEntryInfo[currentEnemyEntryIndex].type);
			enemyList.push_back(enemy);

			currentEnemyEntryIndex++;
			if (currentEnemyEntryIndex >= enemyEntryInfo.size())
			{
				currentEnemyEntryIndex = 0;
				enemyEntrytimer = 0.0f;
				break;
			}
		}
	}

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

	// ������Ʈ
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

	// UI ================================================================================
	miniMapBar.Update(deltaTime);

	// �÷��̾� �������� �÷��̾� ���� �˻縦 ���ش�
	if (player)
	{
		// �÷��̾� ������ġ�� �� ��ü ���̷� ������ �÷��̾� ��ġ�� 0 ~ 1 ���̷� ǥ�� ����
		// �� ��ü ���� ���ϴ� �� : tileEntryInfo.size() * gAssetManager->tile_Texture->width
		float temp = player->position.x / (tileEntryInfo.size() * gAssetManager->tile_Texture->width);

		// �÷��̾�� �� �Ѿ� �̵� �����ϱ� ������ �������� ���� �հ� ���� �� ���� �װ� �����������
		if (temp < 0.0f) temp = 0.0f;
		if (temp > 1.0f) temp = 1.0f;

		// ���� �� ���� ������ ���ߴ� �̴ϸ��� ǥ�� ���̿� �����ָ� �̴ϸʿ� ��� �÷��̾ �ִ��� ����
		playerIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		playerIcon.Update(deltaTime);
	}

	// ���� üũ����Ʈ ������ �̹����� ��� �ӽ÷� �÷��̾� �������� ������
	// üũ����Ʈ �ε����� 0�� ���� ���� üũ����Ʈ�� ���� �����Ŷ� �̴ϸʿ� ǥ�ø� ���� ��������
	if (checkPointTileInex != 0)
	{
		// ������ �÷��̾� ��ġ ���� �� ó�� üũ����Ʈ�� ��ġ�� ���ϸ� ��
		// �÷��̾� ��Ȱ �κ��� ���� Ÿ�� ��ġ + D3DXVECTOR2(128.0f, 0.0f) �̷������� ��ġ ������ ���� ������ ���� �־ ����ؾ���
		// X�� ���� ����Ǵϱ� 128.0f�� ������
		float temp = (tileList[checkPointTileInex]->position.x + 128.0f) / (tileEntryInfo.size() * gAssetManager->tile_Texture->width);
	
		checkPointIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		checkPointIcon.Update(deltaTime);
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

	// UI ================================================================================
	miniMapBar.Draw(sprite, gAssetManager->miniMapBar);

	// �÷��̾� �������� �÷��̾� ���� �˻縦 ���ش�
	if (player)
		playerIcon.Draw(sprite, gAssetManager->playerIcon);

	if (checkPointTileInex != 0)
	{
		checkPointIcon.Draw(sprite, gAssetManager->playerIcon);
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_SPACE:
			if (player)
				player->Jump();
			break;
		}
	}
}
#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0), enemyEntryInfo(), currentEnemyEntryIndex(0), enemyEntrytimer(0), checkPointTileInex(0),
	playerLife(3), rebirthTimer(0), rebirthTime(3), score(0)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// 타일 등장 정보 + 오브젝트 정보
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

	// 적 등장 정보
	enemyEntryInfo.push_back(EnemyEntryInfo(5, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(10, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(10, 1));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(15, 1));

	// 플레이어 오브젝트 생성
	player = new CPlayer(D3DXVECTOR2(100.0f, 384.0f), mainCamera);
	player->parentScene = this; // 현재 GameScene을 등록

	// 카메라 설정
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->tile_Texture->width - 1024.0f;
	// 타겟으로 플레이어를 지정
	mainCamera->SetTarget(player);

	// UI
	miniMapBar = CMatrix();
	playerIcon = CMatrix();
	checkPointIcon = CMatrix();

	miniMapBar.position = D3DXVECTOR2(20.0f, 768.0f - 64.0f);
	miniMapBar.center = D3DXVECTOR2(20.0f, 27.0f);

	playerIcon.position = miniMapBar.position;
	playerIcon.center = D3DXVECTOR2(30.0f, 64.0f);
	
	checkPointIcon.position = miniMapBar.position;
	checkPointIcon.center = D3DXVECTOR2(30.0f, 64.0f);

	// 점수
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i] = CMatrix();
		scoreNumUI[i].position.x = 32 + (40 * i);
		scoreNumUI[i].position.y = 32;

		scoreNumUI[i].scale.x = 0.35f;
		scoreNumUI[i].scale.y = 0.35f;
	}
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end();++it)
	{
		if (*it)
			delete(*it);
	}
	tileList.clear();

	// 소멸자에서 플레이어 지워줘야해
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

	// 오브젝트의 충돌 체크부분임
	// 오브젝트 - 플레이어
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
				player->isDie = true;
		}
	}

	// 카메라
	if (mainCamera)
		mainCamera->Update(deltaTime);

	// 맵
	if (map)
		map->Update(deltaTime);

	// 타일
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

	// 플레이어
	if (player)
	{
		if (GetKeyState(VK_LEFT) & 0x0800)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x0800)
		{
			player->Move(1, deltaTime);

			score += 1;
		}

		player->Update(deltaTime);

		// 체크 포인트 등록
		int tileIndex = player->position.x / gAssetManager->tile_Texture->width;

		if (tileList.size() > tileIndex
			&& tileIndex >= 0) 
		{
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileInex < tileIndex)
				checkPointTileInex = tileIndex;
		}

		// 죽음 처리
		if (player->isDie)
		{
			// 플레이어를 지울때는 반드시 카메라의 타겟을 NULL로 바꿔야한다.
			mainCamera->SetTarget(NULL);

			delete player;
			player = NULL;
		}
	}
	else
	{
		// 부활 처리
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
				//게임 패배
				ChangeScene("Ending_GameOver");
				return;
			}
		}
	}

	// 적
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
			// 이펙트
		}

		if ((*it)->isDestroyed || (*it)->isDie)
		{
			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;

	}

	// 오브젝트
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			// 이펙트

			delete(*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}

	// UI
	miniMapBar.Update(deltaTime);

	if (player)
	{
		float temp = player->position.x / (tileEntryInfo.size() * gAssetManager->tile_Texture->width);

		if (temp < 0.0f) temp = 0.0f;
		if (temp > 1.0f) temp = 1.0f;

		playerIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		playerIcon.Update(deltaTime);
	}

	if (checkPointTileInex != 0)
	{
		float temp = (tileList[checkPointTileInex]->position.x + 128.0f) / (tileEntryInfo.size() * gAssetManager->tile_Texture->width);
	
		checkPointIcon.position = miniMapBar.position + D3DXVECTOR2(984 * temp, 0.0f);
		checkPointIcon.Update(deltaTime);
	}

	// 점수
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
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	// 맵 그리기
	if (map)
		map->Render(sprite);

	// 타일 그리기
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Render(sprite);
	}

	// 오브젝트 그리기
	for (list<CObject*>::iterator it = objectList.begin(); it != objectList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// 적 그리기
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		(*it)->Render(sprite);
	}

	// 플레이어 그리기
	if (player)
		player->Render(sprite);

	// UI
	miniMapBar.Draw(sprite, gAssetManager->miniMapBar);

	// 플레이어 아이콘은 플레이어 유무 검사를 해준다
	if (player)
		playerIcon.Draw(sprite, gAssetManager->playerIcon);

	if (checkPointTileInex != 0)
	{
		checkPointIcon.Draw(sprite, gAssetManager->playerIcon);
	}

	// 점수
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Draw(sprite, gAssetManager->numberTexture);
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
		case VK_F1:
			ChangeScene("Ending_Victory", score);
			break;
		}
	}
}
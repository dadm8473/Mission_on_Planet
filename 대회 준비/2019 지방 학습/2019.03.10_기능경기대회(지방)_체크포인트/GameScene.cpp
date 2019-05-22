#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0), enemyEntryInfo(), currentEnemyEntryIndex(0), enemyEntrytimer(0),
	playerLife(3), rebirthTimer(0), rebirthTime(3)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// 타일 등장 정보 + 오브젝트 정보
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
			player->Move(1, deltaTime);

		player->Update(deltaTime);

		// 체크 포인트 등록 ===========================================================
		// 플레이어가 타일을 지날 때 해당 타일이 체크포인트이고 그 타일의 번호가 기존의 체크포인트 보다 앞에 있는 타일이라면 새로운 값으로 변경해주는 코드
		
		// 체크 포인트 등록 & 스테이지 클리어를 위한 타일 체크
		// 이 체크방식은 CPlayer Update에서 GetGround_Y_Pos 함수 호출을 위한 체크와 같은 방식이다.

		int tileIndex = player->position.x / gAssetManager->tile_Texture->width;

		if (tileList.size() > tileIndex
			&& tileIndex >= 0)  // 타일리스트 사이즈를 넘을 경우를 예외처리
		{
			// 체크포인트 클리어 속성을 가졌는지 확인하고 기존 체크포인트 번호보다 앞에 있는지 비교한다.
			if (tileEntryInfo[tileIndex].checkPoint && checkPointTileInex < tileIndex)
			{
				// 조건이 맞는다면 체크포인트 타일의 번호를 새로 업데이트 해준다.
				checkPointTileInex = tileIndex;

				// 이곳에서 체크포인트 등록이라는 이펙트를 띄우면 된다.
			}
		}
		// ============================================================================

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
				// 체크포인트 부활 처리 ===============================================
				// 아주 단순하다 rebirhtPos의 좌표를 체크포인트로 등록된 타일의 위치를 기반으로 초기화하면 된다.
				D3DXVECTOR2 rebirhtPos = tileList[checkPointTileInex]->position + D3DXVECTOR2(128.0f, 0.0f);
				// ====================================================================

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
		case 'A':
			if (player)
				player->isDie = true;
			break;
		}
	}
}
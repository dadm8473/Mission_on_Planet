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

	// 충돌 체크 부분 ====================================================================
	// 여기는 예시로 적어둠

	// 플레이어 총알 - 오브젝트
	/* 이건 총알이 구현이 안되있어서 예시로 주석으로 넣음
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// 오브젝트 중 바위만 (Type 1)
		for (list<CObject*>::iterator it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;
			
			// 타입 체크랑 충돌 체크를 동시에
			if ((*it2)->type == 1 && (&ref, &(*it)->rect, &(*it2)->rect))
			{
				score += 15; // 총알 적중 점수

				// 총알 제거
				(*it)->isDestroyed = true;

				// 바위 데미지 입음
				(*it2)->hp -= (*it)->damage;
				if ((*it2)->hp <= 0)
				{
					score += 100; // 바위 파괴 점수

					// 바위 제거
					(*it2)->isDestroyed = true;
				}
			}
		}
	}
	*/

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

	// ===================================================================================

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

		// 오브젝트 생성 부분 ============================================================
		// 평평한 타일일때 만 오브젝트를 생성해야함 그래서 조건으로 검사함
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

	// 플레이어 ==========================================================================
	if (player)
	{
		// 좌우 키만 받는다.
		if (GetKeyState(VK_LEFT) & 0x0800)
			player->Move(-1, deltaTime);
		if (GetKeyState(VK_RIGHT) & 0x0800)
			player->Move(1, deltaTime);
		// 점프는 아래 MsgProc 함수에서 처리함

		player->Update(deltaTime);

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
		// 기존 수팅 게임과 거의 같음
		rebirthTimer += deltaTime;
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			if (--playerLife >= 0)
			{
				// 나중에 체크 포인트 때문에 부활 좌표(rebirhtPos)를 따로 빼둠
				D3DXVECTOR2 rebirhtPos = D3DXVECTOR2(100.0f, 384.0f);

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

	// 적 생성 부분 ======================================================================
	// 적 등장 정보를 통해 시간에 따라 적 소환
	// 기존 방식하고 유사하지만 위에 타일 생성 하는 방식으로 바뀌었음
	
	if (player && enemyEntryInfo.size() > 0) // 적 생성부분은 플레이어가 살아있어야 동작함 + 적 생성 정보 리스트의 크기(enemyEntryInfo.size)가 0 이상
	{
		enemyEntrytimer += deltaTime; // 타이머가 올라가고 enemyEntryInfo 정보에 맞게 적 생성하는 방식은 같음

		// for문으로 enemyEntryInfo 리스트 크기만큼 매번 돌리는 방식이 아니라
		// while문과 currentEnemyEntryIndex 를 이용해서 위에 처럼 매번 검사하지 않음 그리고 더 짧음 ㅎㅎ
		while (enemyEntrytimer >= enemyEntryInfo[currentEnemyEntryIndex].time)
			// 다음에 생성되어야 하는 적의 등장 시간을 현재 시간 정보와 비교한다.
		{
			// 적 생성 X축 위치는 카메라를 기준으로 오른쪽에서 등장하도록 해주고 
			// Y 축 위치는 고민을 좀 해봐야 하지만 일단은 플레이어가 밟고 있는 땅의 Y축 기준으로 -200 - (0~100) 사이로 생성한다.
			// rand() % 100 으로 0 ~ 100 사이를 랜덤으로 받을 수 있음
			// 랜덤을 제대로 사용하려면 Game.cpp에 Update부분에 srand()함수 추가해야함
			D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 200 - rand() % 100);

			CEnemy*enemy = new CEnemy(mainCamera, entryPos, enemyEntryInfo[currentEnemyEntryIndex].type);
			enemyList.push_back(enemy);

			// 적을 생성하면 다음 적을 생성하기위해 index를 하나 올려준다.
			currentEnemyEntryIndex++;
			// 그리고 적 생성 리스트를 반복 생성하기 위해 사이즈를 넘어가면 index와 timer를 0으로 초기화한다.
			if (currentEnemyEntryIndex >= enemyEntryInfo.size())
			{
				currentEnemyEntryIndex = 0;
				enemyEntrytimer = 0.0f;
				break;
			}
		}
	}

	// 적 ================================================================================
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

	// 오브젝트 ==========================================================================
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

	// 점프 키 처리 ======================================================================
	// 점프 키 처리를 여기서 하는 이유는
	switch (uMsg) {
	case WM_KEYDOWN: // 점프 키를 눌렀을 때 한번만 실행되게 해야해서임
		switch (wParam) {
		case VK_SPACE:
			if (player)
				player->Jump();
			break;
		}
	}
}
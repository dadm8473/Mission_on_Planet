#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage) :
	CScene(), tileEntryInfo(), currentTileEntryIndex(0) 
	// int 같은 변수는 쓰레기 값이 때문에 오류가 생기지않게 초기화를 반드시 해야함
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	// 타일 등장 정보
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	// 카메라의 움직임에 제한값을 설정하는 부분임 이것에 대해 부족한 설명은 그림으로 첨부함
	mainCamera->limitPosition_Max.x = tileEntryInfo.size() * gAssetManager->tile_Texture->width - 1024.0f;
	// 지금은 추적기능이 필요없으니 NULL 넘겼음 
	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
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

	// 카메라
	// 임시 : 테스트를 위해 카메라를 키보드로 이동
	if (mainCamera)
	{
		if (GetKeyState(VK_LEFT) & 0x0800)
			mainCamera->position.x -= 300 * deltaTime;
		if (GetKeyState(VK_RIGHT) & 0x0800)
			mainCamera->position.x += 300 * deltaTime;
		if (GetKeyState(VK_UP) & 0x0800)
			mainCamera->position.y -= 300 * deltaTime;
		if (GetKeyState(VK_DOWN) & 0x0800)
			mainCamera->position.y += 300 * deltaTime;

		mainCamera->Update(deltaTime);
	}

	// 맵
	// 이 게임에서 맵은 뒤에보이는 배경임
	if (map)
		map->Update(deltaTime);

	// 타일 ===================================================================================================================================
	//  - 생성 원리 
	//    화면의 가장 오른쪽(카메라의 위치 + 화면 가로 크기)보다
	//    생성된 타일들의 가로 길이 합이 작을때 새로운 타일을 생성한다.

	// 현재 생성된 타일의 길이 = 생성된 타일 수 * 타일 택스처의 가로길이
	float currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;

	// 화면의 가장 오른쪽 = 현재 카메라의 위치 + 화면의 가로 크기

	// while 반복문으로 현재 화면의 가장 오른쪽 위치가 현재 생성된 타일의 길이보다 큰지 비교
	// 조건에 만족하면 타일 생성 시작

	// 아래는 + 1280으로 지금 설정된 타일 보다 길게 설정되있는데 그것은 화면 길이에 딱 맞게 생성하면 빈공간이 보일까봐 살짝 더 크게 설정한 것
	while (mainCamera->position.x + 1280.0f > currentTileLength)
	{

		// 현재 생성되어야하는 타일의 번호(currentTileEntryIndex)가 타일의 생성 정보(tileEntryInfo)보다 크거나 같을 때는 타일 생성을 멈춰야해
		// 근데 내가 같을 때라고 했네.. >= 가 더 안전함

		// 추가 설명 : 배열의 인덱스는 0부터 시작이기 때문에 배열 길이가 5인 배열에 5번 인덱스로 접근하면 에러남 그래서 그럼 <- 이거 모르겠으면 연락
		if (currentTileEntryIndex == tileEntryInfo.size()) break;

		// entryPos는 타일이 생성될 위치임
		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		// 타일을 생성할때 전에 생성된 타일의 위치 정보를 통해 새로 생성될 타일의 위치를 구해야하는데
		// 0번 즉 처음 생성되는 타일은 이전 정보가 없기에 지정된 위치를 입력한다.
		if (currentTileEntryIndex == 0)
		{
			entryPos.x = 0.0f;
			entryPos.y = 384.0f;
		}
		else
		{
			// 이 부분은 이전 타일의 위치 정보로 현재 생성할 타일의 위치를 계산하는 것

			// 급하게 만드느라 이부분 수정을 안했네
			
			/*
			CTile* t = tileList[currentTileEntryIndex - 1];
			
			entryPos.x = t->position.x + gAssetManager->tile_Texture->width;
			entryPos.y = t->position.y;
			*/

			// 이부분 이렇게 수정하셈
			auto it = tileList.begin();
			std::advance(it, currentTileEntryIndex - 1);

			entryPos.x = (*it)->position.x + gAssetManager->tile_Texture->width;
			entryPos.y = (*it)->position.y;
			// 이 윗줄까지 저거로 수정하세요
			// 수정 이유 : List로 TileList를 만들면 auto를 이용해서 접근해야함
			//			   그런데 Vector<>형으로 만들면 위 수정 내용 처럼 [index]로 배열 같이 접근 가능함


			// 이건 현재 생성되어야 하는 타일의 인덱스 (currentTileEntryIndex)를 통해 
			// 현재 생성되야 하는 타일의 정보(Type : 기울기)를 얻어 그 정보를 이용해 Y축의 위치를 잡는 것 임
			// 0 : 평지
			// 1 : 오르막
			// 2 : 내리막

			switch (tileEntryInfo[currentTileEntryIndex].type)
			{
			case 1: // 오르막

				// 이 조건문을 글로 풀자면
				// 이제 생성할 타일이 오르막인데 이전 타일이 내리막 타일이 아니면 타일의 Y좌표를 위로 기울기 만큼(100) 올린다.
				if (tileEntryInfo[currentTileEntryIndex - 1].type != 2)
					entryPos.y -= 100.0f;
				break;
			default: // 평지 & 내리막

				// 이 조건문을 글로 풀자면
				// 이제 생성할 타일이 내리막 또는 평지인데 이전 타일이 내리막 타일이라면 타일의 Y좌표를 아래로 기울기 만큼(100) 내린다.
				if (tileEntryInfo[currentTileEntryIndex - 1].type == 2)
					entryPos.y += 100.0f;
				break;
			}

			// 이렇게 되는 이유를 이해하기 힘들거라고 생각하는데 추가 설명은 그림으로 첨부함
		}

		// 이렇게 타일이 생성될 위치와 현재 타일의 정보를 전달하면서 생성하면됨
		CTile*tile = new CTile(entryPos, tileEntryInfo[currentTileEntryIndex].type, mainCamera);
		tileList.push_back(tile); // 생성된 타일 관리를 위해 꼭 Push_back


		// 그리고 타일이 새로 생겼으니 현재 생성된 타일의 길이를 업데이트 해줌
		currentTileLength = tileList.size() * gAssetManager->tile_Texture->width;
		// 현재 생성되어야 하는 타일의 인덱스 정보도 업데이트
		currentTileEntryIndex++;
	}
	// 여기까지가 타일 생성

	// 내가 준 코드에는 이것보다 더 길고 뭔가 많이 적혀있는데
	// 그것들은 타일이 생성되면서 동시에 일어나야하는 일들을 전부 여기서 처리하기 때문이야

	// 예를 들자면 구덩이 생성, 바위 생성, 아이템 생성들이 있어 위에 내용을 충분히 숙지해야만 다음을 진행할 수 있음
	// =======================================================================================================================================

	// 생성된 타일 업데이트
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList[i]->Update(deltaTime);
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
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);
}
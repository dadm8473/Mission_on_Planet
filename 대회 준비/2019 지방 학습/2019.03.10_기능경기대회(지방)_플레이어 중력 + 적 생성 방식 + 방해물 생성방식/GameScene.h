#pragma once

class TileEntryInfo
{
public:
	int type;

	// 타일 등장 정보에 오브젝트 생성을 위한 정보가 추가됬음
	int objectType; 
	// 바닥 장애물 종류 (없음 : -1 / 구덩이 : 0 / 바위 : 1)

	TileEntryInfo(int type, int objectType = -1) // 이렇게 생성자에서 미리 값을 넣으면 변수 선언할 때 값 넣지 않아도됨
		: type(type), objectType(objectType)
	{
	}
};

// 적 등장 정보 내가 준 코드랑 조금 달라짐
// 일단 기본은 너희가 구현하던 슈팅이랑 같음
class EnemyEntryInfo
{
public:
	int type;
	float time;
	// bool summoned;
	// 기존 코드는 summoned 변수로 판단했는데 이제는 아님
	// 타일 생성에 사용한 것 같이 바꿈

	EnemyEntryInfo(float time, int type)
		: time(time), type(type)
	{

	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;					
	CMap* map;								

	vector<TileEntryInfo> tileEntryInfo;	
	int currentTileEntryIndex;				

	vector<CTile*> tileList;				
	
	// 플레이어 =============================
	CPlayer*player;

	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	
	//몬스터 등장 정보 ======================
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntrytimer;
	// 원래는 timer만 이용해서 적 생성했는데
	int currentEnemyEntryIndex;
	// 이거 추가됨

	list<CEnemy*>enemyList;
	list<CObject*>objectList;

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
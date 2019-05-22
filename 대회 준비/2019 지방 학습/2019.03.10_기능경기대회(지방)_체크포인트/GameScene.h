#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType; 

	// 체크포인트를 설정하기 위한 변수
	bool checkPoint;

	TileEntryInfo(int type, int objectType = -1, bool checkPoint = false)
		: type(type), objectType(objectType), checkPoint(checkPoint)
	{
	}
};

class EnemyEntryInfo
{
public:
	int type;
	float time;

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
	
	CPlayer*player;

	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntrytimer;
	int currentEnemyEntryIndex;

	list<CEnemy*>enemyList;
	list<CObject*>objectList;

	// 게임 진행 관련 변수
	// 체크포인트 변수
	// 설명 : 체크포인트는 타일 기반으로 구현하였다.
	//		  플레이어가 죽으면 이전에 저장된 체크포인트 타일위에 다시 생성되게 한 것
	
	int checkPointTileInex; // 현재 체크포인트로 설정된 타일의 번호
	// 이 변수는 플레이어가 타일을 지나갈 때 해당 타일의 정보가 체크포인트로 설정되어 있다면
	// checkPointTileInex변수에 타일 번호를 넣어 부활에 사용한다.

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
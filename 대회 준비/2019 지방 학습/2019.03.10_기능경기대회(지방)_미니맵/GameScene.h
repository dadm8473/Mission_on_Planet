#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType; 

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

	int checkPointTileInex;

	// UI
	CMatrix miniMapBar;
	CMatrix playerIcon;
	CMatrix checkPointIcon;

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
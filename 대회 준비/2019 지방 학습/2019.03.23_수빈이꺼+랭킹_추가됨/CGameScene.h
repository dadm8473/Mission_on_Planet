#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType;
	// 장애물 없음 -1, 구덩이 0, 바위 1, 컨테이너 100 777
	/*
	10 핵
	11 유도
	12 점프
	13 사거리
	14 이속
	15 3방향
	*/
	bool checkPoint;
	bool Clear;
	// 0 - 평지 1 - 오르막 2 - 내리막
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
	//bool summoned;

	EnemyEntryInfo(float time, int type)
		: time(time), type(type)
	{

	}
};

class CGameScene : public CScene
{
public:
	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileEntryIndex;
	vector<CTile*> tileList;

	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntryTimer;
	int currentEnemyEntryIndex;
	list<CEnemy*> enemyList;

	// Object
	list<CObject*> objectList;

	// Bullet
	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

	// Effect
	list<CEffect*> effectList;

	// player
	CPlayer* player;
	CMatrix* playerDie;
	bool isPlayerDie;

	int playerLife;
	int bonusLifeCounter;
	bool invincible;

	float rebirthTimer;
	float rebirthTime;

	int checkPointTileIndex;

	CMatrix* clearAttack;
	int clearAttackCount;
	bool isClearAttack;

	bool isWin;
	bool isLose;

	// Camera
	CCamera* mainCamera;

	// Map
	CMap* map;

	// UI
	CMatrix* ui;

	CMatrix* isItem;
	CMatrix* itemMessage;
	float isItemTimer;
	CMatrix scoreNumUI[6];
	CMatrix playerLifeUI[6];
	CMatrix clearAttackUI[2];

	CMatrix miniMapBar;
	CMatrix playerIcon;
	CMatrix checkPointIcon;

public:
	CGameScene(int stage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void ClearAttack();

	void SetTile();

	void TileUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);
	void ObjectUpdate(float deltaTime);
	void BulletUpdate(float deltaTime);
	void PlayerUpdate(float deltaTime);
	void UIUpdate(float deltaTime);

	void RectUpdate(float deltaTime);
};

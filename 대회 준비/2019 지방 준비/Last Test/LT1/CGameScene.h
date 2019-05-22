#pragma once

class TileEntryInfo
{
public:
	int type;
	bool checkPoint;

	TileEntryInfo(int type, bool checkPoint = false)
		: type(type), checkPoint(checkPoint)
	{

	}
};

class EnemyEntryInfo
{
public:
	int type;
	float timer;

	EnemyEntryInfo(int type, float timer)
		: type(type), timer(timer)
	{

	}
};

class CGameScene : public CScene
{
public:
	// Camera & Map
	CCameara* mainCamera;
	CMap* map;

public:
	// Tile ≥Ù¿Ã 105
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;

public:
	// Bullet
	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

public:
	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

public:
	// Player
	CPlayer* player;
	int playerLife;
	
	int checkPointIndex; // Player checkPoint

	// player rebirth
	float rebirthTimer;
	float rebirthTime;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void TileUpdate(float deltaTime);
	void PlayerUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);

public:
	void BulletUpdate(float deltaTime);
	void RectUpdate(float deltaTime);
};


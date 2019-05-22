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
	// Camera
	CCamera* mainCamera;
	// Map
	CMap* map;

	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;
	float tileWidth;

	// Player
	CPlayer* player;
	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	int checkPointIndex;
	
	// Enemy
	vector<EnemyEntryInfo> enemyEntryIinfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

	// Bullet
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

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
	void BulletUpdate(float deltaTime);
	void RectUpdate(float deltaTime);
};


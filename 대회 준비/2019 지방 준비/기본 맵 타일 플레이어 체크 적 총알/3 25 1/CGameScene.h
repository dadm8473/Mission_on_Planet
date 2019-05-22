#pragma once

class TileEntryInfo
{
public:
	int type;
	bool checkPoint;

	TileEntryInfo(int type, bool checkPoint = false)
		:type(type), checkPoint(checkPoint)
	{
	}
};

class EnemyEntryInfo
{
public:
	int type;
	float time;

	EnemyEntryInfo(int type, float time)
		: type(type), time(time)
	{

	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;

	CMap* map;

	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileindex;
	vector<CTile*> tileList;
	int tileWidth;

	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

	// Player
	CPlayer* player;
	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	int checkRebirthIndex;

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
};


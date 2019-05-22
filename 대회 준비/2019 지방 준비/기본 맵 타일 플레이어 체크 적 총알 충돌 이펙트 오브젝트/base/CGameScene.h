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
		:type(type), timer(timer)
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
	int currentTileIndex;
	vector<CTile*> tileList;
	int tileWidth;

	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyindex;
	list<CEnemy*> enemyList;
	float enemyEnterTimer;

	// Player
	CPlayer* player;
	int playerLife;

	float rebirthTime;
	float rebirthTimer;
	int checkPointIndex;

	// Bullet
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

	// Effect
	list<CEffect*> effectList;

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
	void EffectUpdate(float deltaTime);
};


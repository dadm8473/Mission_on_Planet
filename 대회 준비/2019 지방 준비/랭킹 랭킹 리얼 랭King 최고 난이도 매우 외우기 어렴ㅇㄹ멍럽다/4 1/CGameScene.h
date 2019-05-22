#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType;
	bool checkPoint;

	TileEntryInfo(int type, int objectType = -1, bool checkPoint = false)
		: type(type), checkPoint(checkPoint), objectType(objectType)
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
	CCamera* mainCamera;
	CMap* map;

public:
	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;

public:
	// Effect
	list<CEffect*> effectList;

public:
	// Object
	list<CObject*> objectList;

public:
	// Bullet
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

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

	float rebirthTimer;
	float rebirthTime;
	int checkPointIndex;

public:
	// ClearAttack
	CClearAttack* clearAttack;
	bool isClearAttack;

public:
	// GameScene
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
	void EffectUpdate(float deltaTime);

public:
	void ObjectUpdate(float deltaTime);
};


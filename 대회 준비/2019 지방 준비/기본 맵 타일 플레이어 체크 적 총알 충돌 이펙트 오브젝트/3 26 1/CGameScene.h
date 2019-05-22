#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType;
	bool checkPoint;

	TileEntryInfo(int type, int obeectType = -1 ,bool checkPoint = false)
		: type(type), objectType(obeectType),checkPoint(checkPoint)
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

	// ClearAttack;
	CMatrix* clearAttack;
	bool isClearAttack;

	// Object;
	list<CObject*> objectList;

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
	void ObjectUpdate(float deltaTime);
	void ClearAttack();
};


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

class CGameScene : public  CScene
{
public:
	// Camera
	CCamera* mainCamera;
	// Map
	CMap* map;

	// Tile
	vector<TileEntryInfo> tileEntryinfo;
	int currentTileIndex;
	vector<CTile*> tileList;

	// Effect
	list<CEffect*> effectList;

	//Bullet
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

	// Object
	list<CObject*> objectList;

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
	int currentCheckIndex;

	// ClearAttack
	CMatrix* clearAttack;
	bool isClearAttack;
	int clearAttackCount;

	// UI
	CMatrix scoreUI[6];
	CMatrix playerLifeUI[3];
	CMatrix clearAttackUI[2];

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
	void BulletUpdaet(float deltaTime);
	void ObjectUpdate(float deltaTime);

public:
	void RectUpdate(float deltaTime);
	void ClearAttack();
	void UIUpdate(float deltaTime);
};


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
	//bool summoned;

	EnemyEntryInfo(float time, int type)
		: time(time), type(type)
	{

	}
};

class CGameScene : public CScene
{
public:
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileEntryIndex;
	vector<CTile*> tileList;

	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntryTimer;
	int currentEnemyEntryIndex;
	list<CEnemy*> enemyList;

	list<CObject*> objectList;

	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

	CMatrix* isItem;
	float isItemTimer;
	CMatrix scoreNumUI[6];
	CMatrix playerLifeUI[6];

	CPlayer* player;

	int playerLife;
	bool invincible;

	float rebirthTimer;
	float rebirthTime;

	int checkPointTileInex;

	CCamera* mainCamera;
	CMap* map;

public:
	CGameScene(int stage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

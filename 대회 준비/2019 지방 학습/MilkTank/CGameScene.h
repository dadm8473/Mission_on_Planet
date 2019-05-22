#pragma once
class TileEntryInfo;
class EnemyEntryInfo;
class CGameScene : public CScene
{
public:
	int currentStage;

	CCamera* mainCamera;
	CMap* map;

	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntryTimer;
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileEntryIndex;

	vector<CTile*> tileList;
	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

	list <CEnemy*> enemyList;
	list<CTrap*> trapList;
	list<CItem*> itemList;

	list<CEffect*> effectList;

	CPlayer* player;
	int playerLife;

	// 플레이 관련
	int checkPointTileIndex;

	float rebirthTimer;
	float rebirthTime;

	bool entry;
	float entryTimer;
	float entryTime;

	bool victory;
	float victoryTimer;
	float victoryTime;

	int score;
	int bonusLifeChecker;

	bool onContinerSpawn;
	int continerChecker;

	// UI
	CMatrix scoreNumUI[6];
	CMatrix playerLifeUI[5];

	CMatrix stageClearMessage;
	CMatrix upgradeMessage;
	CMatrix checkPointMessage;

	bool onStageClearMessage;
	bool onUpgradeMessage;
	bool onCheckPointMessage;

	float stageClearMessageTimer;
	float upgradeMessageTimer;
	float checkPointMessageTimer;

	bool superPower = false;

public:
	CGameScene(int stage, CPlayer* player = NULL, int score = 0, int life = 3);
	virtual ~CGameScene();
	virtual void Update(float detlaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class TileEntryInfo
{
public:
	int type;
	int objectType;
	bool checkPoint;

	bool stageEnd;

	TileEntryInfo(int type, int objectType = -1, bool checkPoint = false, bool stageEnd = false)
		:type(type), objectType(objectType), checkPoint(checkPoint), stageEnd(stageEnd)
	{

	}
};

class EnenmyEntryInfo
{
public:
	int type;
	float time;
	bool summoned;

	EnenmyEntryInfo(float time, int type)
		:time(time), type(type), summoned(false)
	{

	}
};
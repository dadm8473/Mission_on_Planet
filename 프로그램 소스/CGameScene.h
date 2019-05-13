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
	// camera & map
	CCamera* mainCamera;
	CMap* map;

public:
	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;
	int tileCount_N;
	int tileCount_O;

public:
	// Bullet
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

public:
	// Effect
	list<CEffect*> effectList;

	bool randEffect;
	float effectTimer;

public:
	// Object
	list<CObject*> objectList;
	bool isStageClear;

	float stageClearTimer;
	float stageClearTime;

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

	// 무적
	bool invincible;
	bool cheatinvincible;
	float invincibleTimer;

	// 부활
	float rebirthTimer;
	float rebirthTime;
	int checkPointIndex;

	// 아이템 지속시간
	bool isItem;
	float itemTimer;
	float itemTime;

public:
	// ClearAttack;
	bool isClearAttack;
	int clearAttackCount;

	float clearAttackTimer;
	float clearAttackTime;

public:
	// 구멍에 빠졌을 경우
	bool isHole;
	float holeTimer;
	float holeTime;

public:
	CMatrix* itemState;

public:
	// 컨테이너 애니메이션 생성해서 사용
	CMatrix* conAni;
	bool isConAni;

public:
	// UI
	CMatrix* playerLife_UI[3];
	CMatrix* clearAttackCount_UI[2];
	CMatrix* score_UI[6];

	// Mini Map
	CMatrix* miniMap;
	CMatrix* playerPoint;
	CMatrix* savePoint;

	// item Message
	CMatrix* itemMessage;

	// item Cool Time
	CMatrix* itemCool;
	CMatrix* clearCool;

	// Stage
	CMatrix* stageBG;
	CMatrix* stageStart;
	CMatrix* stageClear;
	CMatrix* stageClear_Num[6];

	// Continue
	CMatrix* conBG;
	CMatrix* conUI;
	CMatrix* overUI;
	bool isOver;
	bool isCon;
	bool isStageStart;
	
	// player
	CMatrix* mainUI;
	CMatrix* playerImage;

public:
	CGameScene(int inputStage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int currentStage;
	bool isEnter;
	bool isLose;

public:
	void TileUpdate(float deltaTime);
	void PlayerUpdate(float deltaTime);
	void TargetUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);

public:
	void BulletUpdate(float deltaTime);
	void RectUpdate(float deltaTime);
	void EffectUpdate(float deltaTime);
	void ObjectUpdate(float deltaTime);

public:
	void UIUpdate(float deltaTime);
	void MiniMapUpdate(float deltaTime);
	void TileSet();
};


#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType;
	// ��ֹ� ���� -1, ������ 0, ���� 1, �����̳� 100 777
	/*
	10 ��
	11 ����
	12 ����
	13 ��Ÿ�
	14 �̼�
	15 3����
	*/
	bool checkPoint;
	bool Clear;
	// 0 - ���� 1 - ������ 2 - ������
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
	// Tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileEntryIndex;
	vector<CTile*> tileList;

	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntryTimer;
	int currentEnemyEntryIndex;
	list<CEnemy*> enemyList;

	// Object
	list<CObject*> objectList;

	// Bullet
	list<CBullet*> playerBulletList;
	list<CBullet*> enemyBulletList;

	// Effect
	list<CEffect*> effectList;

	// player
	CPlayer* player;
	CMatrix* playerDie;
	bool isPlayerDie;

	int playerLife;
	int bonusLifeCounter;
	bool invincible;

	float rebirthTimer;
	float rebirthTime;

	int checkPointTileIndex;

	CMatrix* clearAttack;
	int clearAttackCount;
	bool isClearAttack;

	bool isWin;
	bool isLose;

	// Camera
	CCamera* mainCamera;

	// Map
	CMap* map;

	// UI
	CMatrix* ui;

	CMatrix* isItem;
	CMatrix* itemMessage;
	float isItemTimer;
	CMatrix scoreNumUI[6];
	CMatrix playerLifeUI[6];
	CMatrix clearAttackUI[2];

	CMatrix miniMapBar;
	CMatrix playerIcon;
	CMatrix checkPointIcon;

public:
	CGameScene(int stage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void ClearAttack();

	void SetTile();

	void TileUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);
	void ObjectUpdate(float deltaTime);
	void BulletUpdate(float deltaTime);
	void PlayerUpdate(float deltaTime);
	void UIUpdate(float deltaTime);

	void RectUpdate(float deltaTime);
};

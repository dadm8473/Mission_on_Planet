#pragma once

class TileEntryInfo
{
public:
	int type; // Ÿ�� ����
	int objectType; // �ٴ� ��ֹ� ���� -1 : ���� 0 : ������, 1 : ����
	bool checkPoint;

	bool stageEnd;

	TileEntryInfo(int type, int objectType = -1, bool checkPoint = false, bool stageEnd = false)
		: type(type), objectType(objectType), checkPoint(checkPoint), stageEnd(stageEnd)
	{

	}
};

class EnemyEntryInfo
{
public:
	int type;
	float time;
	bool summoned;

	EnemyEntryInfo(float time, int type)
		: time(time), type(type), summoned(false)
	{

	}
};

class CGameScene : public CScene
{
public:
	int currentStage;

	CCamera* mainCamera;
	CMap* map;

	vector<EnemyEntryInfo> enemyEntryInfo; //���� ���� ����
	float enemyEntrytimer;
	vector<TileEntryInfo> tileEntryInfo; //Ÿ�� ���� ����
	int currentTileEntryIndex;

	vector<CTile*> tileList;
	list<CBullet*>playerBulletList;
	list<CBullet*>enemyBulletList;

	list<CEnemy*>enemyList;
	list<CTrap*>trapList;
	list<CItem*>itemList;

	list<CEffect*> effectList;

	CPlayer*player;
	int playerLife;

	//�÷��� ����
	int checkPointTileInex;

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

	/*UI*/
	//����
	CMatrix scoreNumUI[6];
	//�÷��̾� ����
	CMatrix playerLifeUI[5];

	//�޼���
	CMatrix stageClearMessage;
	CMatrix upgradeMessage;
	CMatrix checkPointMessage;

	bool onStageClearMessage;
	bool onUpgradeMessage;
	bool onCheckPointMessage;

	float stageClearMessageTimer;
	float upgradeMessageTimer;
	float checkPointMessageTimer;

	// ġƮ ����
	bool superPower = false;

	CGameScene(int stage, CPlayer* player = NULL, int score = 0.0f, int life = 3);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
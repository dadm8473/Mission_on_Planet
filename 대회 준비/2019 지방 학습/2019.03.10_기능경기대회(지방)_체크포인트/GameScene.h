#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType; 

	// üũ����Ʈ�� �����ϱ� ���� ����
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

	EnemyEntryInfo(float time, int type)
		: time(time), type(type)
	{

	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;					
	CMap* map;								

	vector<TileEntryInfo> tileEntryInfo;	
	int currentTileEntryIndex;				

	vector<CTile*> tileList;				
	
	CPlayer*player;

	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntrytimer;
	int currentEnemyEntryIndex;

	list<CEnemy*>enemyList;
	list<CObject*>objectList;

	// ���� ���� ���� ����
	// üũ����Ʈ ����
	// ���� : üũ����Ʈ�� Ÿ�� ������� �����Ͽ���.
	//		  �÷��̾ ������ ������ ����� üũ����Ʈ Ÿ������ �ٽ� �����ǰ� �� ��
	
	int checkPointTileInex; // ���� üũ����Ʈ�� ������ Ÿ���� ��ȣ
	// �� ������ �÷��̾ Ÿ���� ������ �� �ش� Ÿ���� ������ üũ����Ʈ�� �����Ǿ� �ִٸ�
	// checkPointTileInex������ Ÿ�� ��ȣ�� �־� ��Ȱ�� ����Ѵ�.

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
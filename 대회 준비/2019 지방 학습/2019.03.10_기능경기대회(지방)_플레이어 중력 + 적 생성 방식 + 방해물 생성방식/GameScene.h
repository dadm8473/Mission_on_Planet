#pragma once

class TileEntryInfo
{
public:
	int type;

	// Ÿ�� ���� ������ ������Ʈ ������ ���� ������ �߰�����
	int objectType; 
	// �ٴ� ��ֹ� ���� (���� : -1 / ������ : 0 / ���� : 1)

	TileEntryInfo(int type, int objectType = -1) // �̷��� �����ڿ��� �̸� ���� ������ ���� ������ �� �� ���� �ʾƵ���
		: type(type), objectType(objectType)
	{
	}
};

// �� ���� ���� ���� �� �ڵ�� ���� �޶���
// �ϴ� �⺻�� ���� �����ϴ� �����̶� ����
class EnemyEntryInfo
{
public:
	int type;
	float time;
	// bool summoned;
	// ���� �ڵ�� summoned ������ �Ǵ��ߴµ� ������ �ƴ�
	// Ÿ�� ������ ����� �� ���� �ٲ�

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
	
	// �÷��̾� =============================
	CPlayer*player;

	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	
	//���� ���� ���� ======================
	vector<EnemyEntryInfo> enemyEntryInfo;
	float enemyEntrytimer;
	// ������ timer�� �̿��ؼ� �� �����ߴµ�
	int currentEnemyEntryIndex;
	// �̰� �߰���

	list<CEnemy*>enemyList;
	list<CObject*>objectList;

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
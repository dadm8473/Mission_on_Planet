#pragma once

class TileEntryInfo
{
public:
	int type; // Ÿ�� ����

	TileEntryInfo(int type)
		: type(type)
	{
	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;					// ī�޶�
	CMap* map;								// �� ���

	vector<TileEntryInfo> tileEntryInfo;	// Ÿ�� ���� ����(�� ����)
	int currentTileEntryIndex;				// ���� �����Ǿ�� �ϴ� Ÿ���� �ε��� ���� 

	vector<CTile*> tileList;				// �� ������ ���� ������� Ÿ�ϵ��� ����Ǵ� ��
											// �����̳� ����Ʈ, �Ѿ�ó�� List�� ������� ���� ���� []�� �迭 ó�� �ε����� �����ϱ� ������

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
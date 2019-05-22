#pragma once

class TileEntryInfo
{
public:
	int type;
	bool checkPoint;

	TileEntryInfo(int type, bool checkPoint = false)
		:type(type), checkPoint(checkPoint)
	{
	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;

	CMap* map;

	vector<TileEntryInfo> tileEntryInfo;
	int currentTileindex;
	vector<CTile*> tileList;
	int tileWidth;

	CPlayer* player;
	int playerLife;

	float rebirthTimer;
	float rebirthTime;
	int checkRebirthIndex;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void TileUpdate(float deltaTime);
};


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

	// tile
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;
	int tileWidht;
	
	// player
	CPlayer* player;
	int playerLife;

	float rebrithTime;
	float rebrithTimer;
	int checkPointTileIndex;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void TileUpdate(float deltaTime);
};


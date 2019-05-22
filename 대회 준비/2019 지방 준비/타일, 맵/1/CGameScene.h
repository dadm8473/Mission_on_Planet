#pragma once

class TileEntryInfo
{
public:
	int type;

	TileEntryInfo(int type)
		: type(type)
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
	float tileWidth;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void TileUpdate(float deltaTime);
};


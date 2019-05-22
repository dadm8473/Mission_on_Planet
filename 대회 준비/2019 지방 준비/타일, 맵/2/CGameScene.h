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

	vector<TileEntryInfo> titleEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;
	int tileWidth;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void TileUpdate(float deltaTime);
};


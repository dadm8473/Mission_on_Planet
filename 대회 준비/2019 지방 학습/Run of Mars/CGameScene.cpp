#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: tileEntryInfo(), currentTileEntryIndex(0)
{
	mainCamera = new CCamera();
	map = new CMap(0, mainCamera);

	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(1));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(2));
	tileEntryInfo.push_back(TileEntryInfo(0));

	mainCamera->limitPos_Max.x = tileEntryInfo.size() * gAssetManager->GetTexture("Tile")->width - 1024;
	mainCamera->SetTarget(NULL);
}

CGameScene::~CGameScene()
{
	for (vector<CTile*>::iterator it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete(*it);
	tileList.clear();

	if (map)
		delete map;

	if (mainCamera)
		delete mainCamera;
}

void CGameScene::Update(float deltaTime)
{

}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPara)
{
}

#pragma once

class TileEntryInfo
{
public:
	int type; // 타일 종류

	TileEntryInfo(int type)
		: type(type)
	{
	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;					// 카메라
	CMap* map;								// 뒷 배경

	vector<TileEntryInfo> tileEntryInfo;	// 타일 등장 정보(맵 정보)
	int currentTileEntryIndex;				// 현재 생성되어야 하는 타일의 인덱스 정보 

	vector<CTile*> tileList;				// 위 정보를 통해 만들어진 타일들이 저장되는 곳
											// 적들이나 이펙트, 총알처럼 List를 사용하지 않은 것은 []로 배열 처럼 인덱스로 접근하기 위함임

	CGameScene(int stage);	//Init
	virtual ~CGameScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
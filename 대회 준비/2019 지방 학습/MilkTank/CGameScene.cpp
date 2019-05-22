#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage, CPlayer * player, int score, int life)
	: CScene(), currentStage(stage), enemyEntryInfo(), tileEntryInfo(), enemyEntryTimer(0), currentTileEntryIndex(0)
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F7:
			ChangeScene(2);
			break;
		case VK_F8:
			ChangeScene(3);
			break;
		}
		break;
	}
}

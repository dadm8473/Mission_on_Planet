#include "DXUT.h"
#include "Header.h"


CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

void CGameScene::Update(float deltaTime)
{
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

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

#include "DXUT.h"
#include "Header.h"
#include <ctime>

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

void ChagneScene(string sceneName)
{
	if (gScene)
		delete gScene;

	if (sceneName == "Title")
		gScene = new CTitleScene();
	else if (sceneName == "Game_Stage_1")
		gScene = new CGameScene();
	else if (sceneName == "Game_Stage_2")
		gScene = new CGameScene();
	else if (sceneName == "Ending_Win")
		gScene = new CEndingScene();
	else if (sceneName == "Ending_Lose")
		gScene = new CEndingScene();
}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	gAssetManager = new AssetManager;
	gAssetManager->LoadAssets();

	gScene = new CTitleScene();
}

void Term()
{
	gAssetManager->ReleaseAssets();

	if (gSprite)
		gSprite->Release();

	if (gScene)
		delete gScene;
}

void Reset()
{
	if (gSprite)
		gSprite->OnResetDevice();
}

void Lost()
{
	if (gSprite)
		gSprite->OnLostDevice();
}

void Update(float deltaTime)
{
	srand((unsigned int)time(0));

	if (gScene)
		gScene->Update(deltaTime);
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (gScene)
		gScene->Render(gSprite);

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (uMsg)
		{
		case VK_F4:
			ChagneScene("Title");
			break;
		case VK_F5:
			ChagneScene("Game_Stage_1");
			break;
		case VK_F6:
			ChagneScene("Game_Stage_2");
			break;
		case VK_F7:
			ChagneScene("Ending_Win");
			break;
		case VK_F8:
			ChagneScene("Ending_Lose");
			break;
		}
		break;
	}
}

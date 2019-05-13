#include "DXUT.h"
#include "Header.h"
#include <ctime>

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

int tileWidth = 0;
int ext_Score = 0;
int ext_Stage = 1;
int ext_2Stage_Score = 0;

void ChangeScene(string sceneName)
{
	if (gScene)
		delete gScene;

	gAssetManager->GetSound("Main")->Stop();
	gAssetManager->GetSound("Lose")->Stop();
	gAssetManager->GetSound("Stage1")->Stop();
	gAssetManager->GetSound("Stage2")->Stop();
	gAssetManager->GetSound("Win")->Stop();

	gAssetManager->GetSound("Main")->Reset();
	gAssetManager->GetSound("Lose")->Reset();
	gAssetManager->GetSound("Stage1")->Reset();
	gAssetManager->GetSound("Stage2")->Reset();
	gAssetManager->GetSound("Win")->Reset();

	if (sceneName == "Title")
		gScene = new CTitleScene();
	else if (sceneName == "Game_Stage_1")
	{
		ext_Stage = 1;
		ext_Score = 0;
		gScene = new CGameScene(ext_Stage);
	}
	else if (sceneName == "Game_Stage_2")
	{
		ext_Stage = 2;
		ext_2Stage_Score = ext_Score;
		gScene = new CGameScene(ext_Stage);
	}
	else if (sceneName == "Ending_Win")
		gScene = new CEndingScene(true);
	else if (sceneName == "Ending_Lose")
		gScene = new CEndingScene(false);
}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	gAssetManager = new AssetManager;
	gAssetManager->LoadAssets();

	gScoreManager = new ScoreManager;

	tileWidth = gAssetManager->GetTexture("Tile")->width;

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

void Update(float deltaTime)
{
	srand(GetTickCount());

	if (ext_Score > 999999)
		ext_Score = 999999;

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
		switch (wParam)
		{
		case VK_F4:
			ChangeScene("Title");
			break;
		case VK_F5:
			ChangeScene("Game_Stage_1");
			break;
		case VK_F6:
			ChangeScene("Game_Stage_2");
			break;
		case VK_F7:
			ChangeScene("Ending_Win");
			break;
		case VK_F8:
			ChangeScene("Ending_Lose");
			break;
		}
		break;
	}
}

float GetAngle(float x, float y)
{
	return D3DXToDegree(atan2(y, x)) + 90;
}

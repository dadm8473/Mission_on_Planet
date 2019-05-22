#include "DXUT.h"
#include "Header.h"
#include <ctime>

LPD3DXSPRITE gSprite = NULL;
CScene*gScene = NULL;

void ChangeScene(string sceneName)
{
	if (gScene)
		delete gScene;

	if (sceneName == "Title")
	{
		gScene = new CTitleScene();
	}
	else if (sceneName == "Game_Stage")
	{
		gScene = new CGameScene(0);
	}
	else if (sceneName == "Ending_Victory")
	{
		gScene = new CEndingScene(true);
	}
	else if (sceneName == "Ending_GameOver")
	{
		gScene = new CEndingScene(false);
	}
}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	gAssetManager = new CAssetManager();
	gAssetManager->InitAssets();

	gScene = new CTitleScene();
}

void Term()
{
	gAssetManager->TermAssets();

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
}

float GetAngle(float x, float y)
{
	return D3DXToDegree(atan2(y, x)) + 90;
}
#include "DXUT.h"
#include "Header.h"

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

bool changeScene = true;
int changeSceneNum = 0;

CMatrix* loadImage;
bool isLoading = true;
float loadTime = 0.2f, loadTimer = 0;
bool isStartLoading;
bool isFadingOut;
float fadeInTime = 1, fadeInTimer = 0;

void ChangeScene(int sceneNum)
{
	changeSceneNum = sceneNum;
	
	isStartLoading = true;
	isFadingOut = true;
}

void _ChangeScene(int sceneNum)
{
	if (gScene)
	{
		delete gScene;
		gScene = NULL;
	}

	switch (sceneNum)
	{
	case 0:
		// Title Scene
		gScene = new CTitleScene();
		break;
	case 1:
		// Gamse Scene
		gScene = new CGameScene();
		break;
	case 2:
		// Ending Win
		gScene = new CEndingScene(true);
		break;
	case 3:
		// Ending Lose
		gScene = new CEndingScene(false);
		break;
	}
}

void Init()
{
	loadImage = new CMatrix();

	gAssetManager = new AssetManager();
	gAssetManager->LoadTexture("Load", L"images/Main/loading00", L"png", 1);

	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	ChangeScene(0);
}

void Term()
{
	gAssetManager->ReleaseAssets();
	delete gAssetManager;

	gSprite->Release();
	
	if (gScene)
	{
		delete gScene;
		gScene = NULL;
	}
}

void Lost()
{
	gSprite->OnLostDevice();
}

void Reset()
{
	gSprite->OnResetDevice();
}

void Update(float deltaTime)
{
	if (gScene)
		gScene->Update(deltaTime);

	if (isStartLoading)
	{
		if (isFadingOut)
		{
			loadImage->a += (int)(255 * deltaTime);
			if (loadImage->a >= 255)
			{
				loadImage->a = 255;

				fadeInTimer += deltaTime;
				if (fadeInTimer > fadeInTime)
				{
					fadeInTimer = 0;
					isFadingOut = false;
					_ChangeScene(changeSceneNum);
				}
			}
		}
		else
		{
			loadImage->a -= (int)(255 * deltaTime);
			if (loadImage->a <= 0)
			{
				loadImage->a = 0;
				isStartLoading = false;
			}
		}
	}
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (gScene)
		gScene->Render(gSprite);

	loadImage->Draw(gSprite, gAssetManager->GetTexture("Load"));

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);
}

void LoadingUpdate(float deltaTime)
{
	loadImage->Update(deltaTime);

	loadTimer += deltaTime;
	if (loadTimer >= loadTime)
	{
		gAssetManager->LoadAssets();
		isLoading = false;
	}
}

void LoadingRender()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);
	loadImage->Draw(gSprite, gAssetManager->GetTexture("Load"));
	gSprite->End();
}

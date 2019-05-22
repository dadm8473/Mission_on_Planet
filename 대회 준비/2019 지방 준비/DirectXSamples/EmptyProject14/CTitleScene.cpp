#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false)
{
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
	delete rankImage;
}

void CTitleScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (isHowTo)
		howToImage->Update(deltaTime);
	else if (isRank)
		rankImage->Update(deltaTime);
	else
		titleImage->Update(deltaTime);
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (isHowTo)
		howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
	else if (isRank)
		rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));
	else
		titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (isHowTo || isRank)
				return;
			else if (titleImage->currentScene < 0)
				titleImage->currentScene = 3;
			else
				titleImage->currentScene--;
			break;
		case VK_DOWN:
			if (isHowTo || isRank)
				return;
			else if (titleImage->currentScene > 3)
				titleImage->currentScene = 0;
			else
				titleImage->currentScene++;
			break;
		case VK_RETURN:
			switch (titleImage->currentScene)
			{
			case 0:
				ChangeScene("Game_Stage_1");
				break;
			case 1:
				isHowTo = !isHowTo;
				break;
			case 2:
				isRank = !isRank;
				break;
			case 3:
				PostQuitMessage(0);
				break;
			}
			break;
		}
		break;
	}
}

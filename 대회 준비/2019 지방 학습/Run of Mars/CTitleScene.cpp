#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix), kreditImage(new CMatrix),
	isHowTo(false), isRank(false), isKredit(false)
{
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
	delete rankImage;
	delete kreditImage;
}

void CTitleScene::Update(float deltaTime)
{
	if (isHowTo)
		howToImage->Update(deltaTime);
	else if (isRank)
		rankImage->Update(deltaTime);
	else if (isKredit)
		kreditImage->Update(deltaTime);
	else
		titleImage->Update(deltaTime);
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	if (isHowTo)
		howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
	else if (isRank)
		rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));
	else if (isKredit)
		kreditImage->Draw(sprite, gAssetManager->GetTexture("Kredit"));
	else
		titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPara)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (isHowTo || isRank || isKredit)
				return;
			else if (titleImage->currentScene > 0)
				titleImage->currentScene--;
			else
				titleImage->currentScene = 4;
			break;
		case VK_DOWN:
			if (isHowTo || isRank || isKredit)
				return;
			else if (titleImage->currentScene < 4)
				titleImage->currentScene++;
			else
				titleImage->currentScene = 0;
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
				isKredit = !isKredit;
				break;
			case 4:
				PostQuitMessage(0);
				break;
			}
			break;
		}
		break;
	}
}

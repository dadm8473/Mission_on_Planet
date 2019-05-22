#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleimage(new CMatrix), howToimage(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false)
{
}

CTitleScene::~CTitleScene()
{
	delete titleimage;
	delete howToimage;
	delete rankImage;
}

void CTitleScene::Update(float deltaTime)
{
	if (isHowTo)
		howToimage->Update(deltaTime);
	else if (isRank)
		rankImage->Update(deltaTime);
	else
		titleimage->Update(deltaTime);
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	if (isHowTo)
		howToimage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
	else if (isRank)
		rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));
	else
		titleimage->Draw(sprite, gAssetManager->GetTexture("Title"));
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (isHowTo || isRank)
				return;
			else if (titleimage->currentScene > 0)
				titleimage->currentScene--;
			else
				titleimage->currentScene = 3;
			break;
		case VK_DOWN:
			if (isHowTo || isRank)
				return;
			else if (titleimage->currentScene < 3)
				titleimage->currentScene++;
			else
				titleimage->currentScene = 0;
			break;
		case VK_RETURN:
			switch (titleimage->currentScene)
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

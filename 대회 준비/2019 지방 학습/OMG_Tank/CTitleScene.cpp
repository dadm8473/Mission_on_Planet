#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(), titleImage(new CMatrix()), backGroundImage(new CMatrix), tankImage(new CMatrix), kreditImage(new CMatrix),
	howToImage(new CMatrix()), rankImage(new CMatrix()), introImage(new CMatrix), isRank(false), isHowTo(false), intro(true), isKredit(false)
{
	tankImage->SetAnimation(0.03f, 20, true);
	introImage->SetAnimation(0.04f, 40, false);
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete backGroundImage;
	delete tankImage;

	delete howToImage;
	delete rankImage;
	delete introImage;
}

void CTitleScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	backGroundImage->Update(deltaTime);

	if (intro)
	{
		introImage->Update(deltaTime);
		if (introImage->isAniEnd)
			intro = false;
	}
	else
	{
		if (isHowTo)
			howToImage->Update(deltaTime);
		else if (isRank)
			rankImage->Update(deltaTime);
		else if (isKredit)
			kreditImage->Update(deltaTime);
		else
		{
			titleImage->Update(deltaTime);
			tankImage->Update(deltaTime);
		}
	}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	backGroundImage->Draw(sprite, gAssetManager->GetTexture("TitleBG"));

	if (intro)
		introImage->Draw(sprite, gAssetManager->GetTexture("Intro"));
	else
	{
		if (isHowTo)
			howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
		else if (isRank)
			rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));
		else if (isKredit)
			kreditImage->Draw(sprite, gAssetManager->GetTexture("Kredit"));
		else
		{
			tankImage->Draw(sprite, gAssetManager->GetTexture("Tank"));
			titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
		}
	}
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (!intro)
			switch (wParam)
			{
			case VK_UP:
				if (isHowTo || isRank)
					return;
				else if (titleImage->currentScene > 0)
					titleImage->currentScene--;
				else
					titleImage->currentScene = 4;
				break;
			case VK_DOWN:
				if (isHowTo || isRank)
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

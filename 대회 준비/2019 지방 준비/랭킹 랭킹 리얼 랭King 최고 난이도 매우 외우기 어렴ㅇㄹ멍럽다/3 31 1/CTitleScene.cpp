#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			num[i][j] = new CMatrix;
			num[i][j]->position.x = 100 + j * 32;
			num[i][j]->position.y = 100 + 100 * i;
		}

		for (int j = 0; j < 3; ++j)
		{
			initial[i][j] = new CMatrix;
			initial[i][j]->position.x = (100 + 6 * 32) + (32 * j);
			initial[i][j]->position.y = 100 + 100 * i;
		}		
	}

	gScoreManager->Load();
}


CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
	delete rankImage;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
			delete num[i][j];

		for (int j = 0; j < 3; ++j)
			delete initial[i][j];
	}
}

void CTitleScene::Update(float deltaTime)
{
	if (isHowTo)
		howToImage->Update(deltaTime);
	else if (isRank)
		rankImage->Update(deltaTime);
	else
		titleImage->Update(deltaTime);

	if (isRank)
		for (int i = 0; i < 3; ++i)
		{
			int tempScore = gScoreManager->scoreData[i].score;
			for (int j = 5; j >= 0; --j)
			{
				num[i][j]->currentScene = tempScore % 10;
				tempScore /= 10;
			}

			for (int j = 0; j < 6; ++j)
				num[i][j]->Update(deltaTime);

			for (int j = 0; j < 3; ++j)
			{
				initial[i][j]->currentScene = gScoreManager->scoreData[i].initial[j];
				initial[i][j]->Update(deltaTime);
			}
		}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	if (isHowTo)
		howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
	else if (isRank)
		rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));
	else
		titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));

	if (isRank)
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 6; ++j)
				num[i][j]->Draw(sprite, gAssetManager->GetTexture("Num"));

			for (int j = 0; j < 3; ++j)
				initial[i][j]->Draw(sprite, gAssetManager->GetTexture("Apb"));
		}
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
			else if (titleImage->currentScene > 0)
				titleImage->currentScene--;
			else
				titleImage->currentScene = 3;
			break;
		case VK_DOWN:
			if (isHowTo || isRank)
				return;
			else if (titleImage->currentScene < 3)
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
				PostQuitMessage(0);
				break;
			}
			break;
		}
		break;
	}
}

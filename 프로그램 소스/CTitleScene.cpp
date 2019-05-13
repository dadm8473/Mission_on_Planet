#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false), BGImage(new CMatrix),
	introImage(new CMatrix), iuImage(new CMatrix), kreditImage(new CMatrix), isIntro(true), isIu(false), isKredit(false), mainAni(new CMatrix)
{
	introImage->SetAnimation(0.06f, 60, false);
	mainAni->SetAnimation(0.06f, 20, true);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			num[i][j] = new CMatrix;
			num[i][j]->position.x = (283 + 48 * 6) + (48 * j);
			num[i][j]->position.y = 189 + 182 * i;
			num[i][j]->scale = D3DXVECTOR2(1.5f, 1.5f);
		}

		for (int j = 0; j < 3; ++j)
		{
			initial[i][j] = new CMatrix;
			initial[i][j]->position.x = 283 + 48 * j;
			initial[i][j]->position.y = 189 + 182 * i;
			initial[i][j]->scale = D3DXVECTOR2(1.5f, 1.5f);
		}
	}

	gScoreManager->Load();
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
	delete rankImage;

	delete introImage;
	delete iuImage;
	delete kreditImage;

	delete BGImage;
	delete mainAni;

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
	gAssetManager->GetSound("Main")->Play();
	BGImage->Update(deltaTime);

	if (isIntro)
	{
		introImage->Update(deltaTime);
		if (introImage->isAniEnd)
			isIntro = false;
	}
	else
	{
		mainAni->Update(deltaTime);

		if (isHowTo)
			howToImage->Update(deltaTime);
		else if (isRank)
		{
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

			rankImage->Update(deltaTime);
		}
		else if (isIu)
			iuImage->Update(deltaTime);
		else if (isKredit)
			kreditImage->Update(deltaTime);
		else
			titleImage->Update(deltaTime);
	}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	BGImage->Draw(sprite, gAssetManager->GetTexture("Sky"));

	if (isIntro)
		introImage->Draw(sprite, gAssetManager->GetTexture("Intro"));
	else
	{
		mainAni->Draw(sprite, gAssetManager->GetTexture("mainAni"));

		if (isHowTo)
			howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
		else if (isRank)
		{
			rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 6; ++j)
					num[i][j]->Draw(sprite, gAssetManager->GetTexture("Num"));

				for (int j = 0; j < 3; ++j)
					initial[i][j]->Draw(sprite, gAssetManager->GetTexture("Apb"));
			}
		}
		else if (isIu)
			iuImage->Draw(sprite, gAssetManager->GetTexture("iu"));
		else if (isKredit)
			kreditImage->Draw(sprite, gAssetManager->GetTexture("Kredit"));
		else
			titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
	}
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (!isIntro)
			switch (wParam)
			{
			case VK_UP:
				if (isHowTo || isRank || isIu || isKredit)
					return;
				else if (titleImage->currentScene > 0)
					titleImage->currentScene--;
				else
					titleImage->currentScene = 5;
				break;
			case VK_DOWN:
				if (isHowTo || isRank || isIu || isKredit)
					return;
				else if (titleImage->currentScene < 5)
					titleImage->currentScene++;
				else
					titleImage->currentScene = 0;
				break;
			case VK_LEFT:
				if (isHowTo)
				{
					if (howToImage->currentScene > 0)
						howToImage->currentScene--;
				}
				break;
			case VK_RIGHT:
				if (isHowTo)
				{
					if (howToImage->currentScene < 2)
						howToImage->currentScene++;
				}
				break;
			case VK_RETURN:
				switch (titleImage->currentScene)
				{
				case 0:
					isIu = !isIu;
					break;
				case 1:
					isHowTo = !isHowTo;
					break;
				case 2:
					ChangeScene("Game_Stage_1");
					break;
				case 3:
					isRank = !isRank;
					break;
				case 4:
					isKredit = !isKredit;
					break;
				case 5:
					PostQuitMessage(0);
					break;
				}
				break;
			}
		break;
	}
}

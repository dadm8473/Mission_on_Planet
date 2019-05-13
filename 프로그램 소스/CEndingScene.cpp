#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	: winImage(new CMatrix), loseImage(new CMatrix), isWin(isWin), black(new CMatrix), rankImage(new CMatrix),
	isEnter(false), isRank(false), currentInputindex(0), blinkTimer(0), noRankMessage(new CMatrix), bgImage(new CMatrix)
{
	winImage->SetAnimation(0.05f, 20, true);
	loseImage->SetAnimation(0.05f, 20, true);

	for (int i = 0; i < 3; ++i)
	{
		initial[i] = new CMatrix;
		initial[i]->position.x = 390 + 122 * i;
		initial[i]->position.y = 609;
		initial[i]->center = D3DXVECTOR2(16, 16);
		initial[i]->scale = D3DXVECTOR2(2, 2);
	}
	
	for (int i = 0; i < 6; ++i)
	{
		num[i] = new CMatrix;
		num[i]->position.x = (385 + 32 * i) + (16 * i);
		num[i]->position.y = 414;
		num[i]->center = D3DXVECTOR2(16, 16);
		num[i]->scale = D3DXVECTOR2(2, 2);
	}

	gScoreManager->Load();
	//if (gScoreManager->scoreData[2].score < ext_Score)
	{
		isRank = true;

		ScoreInfo myData;
		myData.score = ext_Score;

		gScoreManager->scoreData.push_back(myData);
	}
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseImage;
	delete bgImage;

	for (int i = 0; i < 3; ++i)
		delete initial[i];

	for (int i = 0; i < 6; ++i)
		delete num[i];
}

void CEndingScene::Update(float deltaTime)
{
	bgImage->Update(deltaTime);

	if (isWin)
	{
		gAssetManager->GetSound("Win")->Play();
		rankImage->currentScene = 0;
		winImage->Update(deltaTime);
	}
	else
	{
		gAssetManager->GetSound("Lose")->Play();
		rankImage->currentScene = 1;
		loseImage->Update(deltaTime);
	}

	black->a -=  200 * deltaTime;

	if (black->a < 0)
		black->a = 0;

	black->Update(deltaTime);

	if (isRank)
	{
		rankImage->Update(deltaTime);

		int tempScore = ext_Score;
		for (int i = 5; i >= 0; --i)
		{
			num[i]->currentScene = tempScore % 10;
			tempScore /= 10;
		}

		for (int i = 0; i < 6; ++i)
			num[i]->Update(deltaTime);

		blinkTimer += deltaTime * 3;

		for (int i = 0; i < 3; ++i)
		{
			initial[i]->currentScene = gScoreManager->scoreData[3].initial[i];
			initial[i]->Update(deltaTime);
		}
	}
	else
		noRankMessage->Update(deltaTime);

	if (isEnter)
	{
		gScoreManager->Save();
		ChangeScene("Title");
		return;
	}
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	bgImage->Draw(sprite, gAssetManager->GetTexture("Sky"));

	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));

	if (isRank)
	{
		rankImage->Draw(sprite, gAssetManager->GetTexture("Rank_end"));

		for (int i = 0; i < 6; ++i)
			num[i]->Draw(sprite, gAssetManager->GetTexture("Num"));

		for (int i = 0; i < 3; ++i)
			if (currentInputindex >= i)
				if (currentInputindex != i || (currentInputindex == i && (int)blinkTimer % 2 == 0))
					initial[i]->Draw(sprite, gAssetManager->GetTexture("Apb"));
	}
	else
		noRankMessage->Draw(sprite, gAssetManager->GetTexture("Rank_end"));

	black->Draw(sprite, gAssetManager->GetTexture("Black_E"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (isRank)
			if (currentInputindex < 4)
				if (wParam >= 65 && wParam <= 95)
					gScoreManager->scoreData[3].initial[currentInputindex] = wParam - 65;


		switch (wParam)
		{
		case VK_RETURN:
			currentInputindex++;
			if (currentInputindex >= 4 || !isRank)
				isEnter = true;
			break;
		}
		break;
	}
}

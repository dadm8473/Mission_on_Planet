#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	:CScene(), winImage(new CMatrix), loseImage(new CMatrix), isWin(false), isEnter(false)
{
	this->isWin = isWin;

	// ���� �߰��� �κ�================================================= //
	isRanking = false; // ��ŷ �Է� ���´� �⺻������ false

	curInputindex = 0;
	blinkTimer = 0.0f;

	// ��ġ �������ִ� �κ�
	for (int i = 0; i < 6; i++)
	{
		Num[i] = new CMatrix();

		Num[i]->position.x = 100.0f + 32.0f * i;
		Num[i]->position.y = 384.0f;
	}

	for (int i = 0; i < 3; i++)
	{
		Initial[i] = new CMatrix();

		Initial[i]->position.x = (100.0f + 32.0f * 6) + (32.0f * i);
		Initial[i]->position.y = 384.0f;
	}

	// ��ġ �������ִ� �κ�
	noRankingMessage = new CMatrix();
	noRankingMessage->position.x = 0.0f;
	noRankingMessage->position.y = 0.0f;

	// ���� : EndingScene���� �� ���� ������ ��ŷ�� ������ ������ ���ؼ� ��ŷ �Է� ������ �����ؾ��ϱ� ������
	// SocreManager�� Load�ؼ� ���� �����͵��� �ҷ��;��Ѵ�.
	gScoreManager->Load();
	
	// ���� �� ���� ������ 3���� ������ ���غ���.
	if (gScoreManager->scoreDatas[2].score < score)
	{
		// 3 ��� ���ؼ� �� ������ ���Ƽ� ��ŷ����� �Ѵ�.
		isRanking = true;

		// ��ŷ �� �κп� �� ���� �־��ش�.
		ScoreInfo myData;
		myData.score = score;

		gScoreManager->scoreDatas.push_back(myData);
	}
	// ================================================================ //
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseImage;

	for (int i = 0; i < 6; i++)
	{
		delete Num[i];
	}

	for (int i = 0; i < 3; i++)
	{
		delete Initial[i];
	}

	delete noRankingMessage;
}

void CEndingScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (isWin)
		winImage->Update(deltaTime);
	else
		loseImage->Update(deltaTime);

	// ���� �߰��� �κ� ================================================ //
	if (isRanking) // ��ŷ �Է� ������ ��
	{
		// ���ھ� Update
		// ���ڸ� CurrentScene���� ��ȯ�ϴ� �κ�
		int tempScore = score;
		for (int i = 5; i >= 0; i--)
		{
			Num[i]->currentScene = tempScore % 10;
			tempScore /= 10;
		}

		for (int i = 0; i < 6; i++)
		{
			Num[i]->Update(deltaTime);
		}

		// �̴ϼ� Update
		blinkTimer += deltaTime * 3; // �̴ϼ��� �����̰��ϱ� ���� ���� (*3�� �����̴� �ӵ��� ������ �Ϸ���)
		for (int i = 0; i < 3; i++)
		{
			Initial[i]->currentScene = gScoreManager->scoreDatas[3].initial[i]; // ���� �� ������ �̴ϼ��� EndingScene���� �������� scoreDatas �ǵ� ���⼭�� 3���� ����Ǿ�����
			Initial[i]->Update(deltaTime);
		}
	}
	else // ��ŷ �Է��� �ƴ� ��
	{
		noRankingMessage->Update(deltaTime);
	}

	// ���� ������ �κ� ================================================ //
	if (isEnter)
	{
		// Ÿ��Ʋ�� �Ѿ�� ������ ScoreData�� ���İ� ������ ���ش�.
		gScoreManager->Save(); // ������ Save() �Լ� �ȿ��� �ڵ����� �ϰ� �����.
		ChangeScene("Title");

		return;
	}
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));

	// ���� �߰��� �κ� ================================================ //
	if (isRanking)
	{
		for (int i = 0; i < 6; i++)
		{
			Num[i]->Draw(sprite, gAssetManager->GetTexture("Num"));
		}

		for (int i = 0; i < 3; i++)
		{
			if (i <= curInputindex) // �̴ϼ� �迭�� ���� �ʰ� ó��
			{
				if (i != curInputindex || (i == curInputindex && (int)blinkTimer % 2 == 0)) // �̰� �����̰� �ϱ� ���� ���ǹ�
				{
					Initial[i]->Draw(sprite, gAssetManager->GetTexture("Alphabet"));
				}
			}
		}
	}
	else // ��ŷ �Է��� �ƴ� �� �ٸ� �׸��� �������� ��
	{
		noRankingMessage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
	}
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (isRanking)
		{
			// �̴ϼ� �迭�� �����ʰ� 
			if (curInputindex < 3)
			{
				// ���Ĺ� ����
				if (wParam >= 65 && wParam <= 90) // ���� : ���Ĺ� ������ �� ����ϵ���
				{
					gScoreManager->scoreDatas[3].initial[curInputindex] = wParam-65; // ���� : -65�� �� ������� 
				}
			}
		}

		switch (wParam)
		{
		case VK_RETURN: // ���͸� ������ ���� �̴ϼ��� �Է��� �� �ֵ��� ó��
			curInputindex++;
			if (curInputindex == 4 || !isRanking) // ���� 4��° ������ �� or ��ŷ ȭ���� �ƴҶ� �ٷ�
				isEnter = true;

			break;
		}
		break;
	}
}

#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isVictory, int score)
	:CScene(), isVictory(isVictory), ending(), inputCount(0), noRanking(false)
{
	// ���� ������ �ҷ��´�.
	gScoreManager->Load();
	gScoreManager->Sort();

	if (gScoreManager->scoreDatas[2].score > score) // 3 ��� ���ؼ� �� ������ ������ ��ŷ �Է� X
		noRanking = true;
	else
	{
		ScoreInfo newData;
		newData.score = score;

		gScoreManager->scoreDatas.push_back(newData);

		// ����
		for (int i = 0; i < 6; i++)
		{
			scoreNum[i] = CMatrix();
			scoreNum[i].position.x = 512.0f - (113 * 6 / 2) + 113 * i;
			scoreNum[i].position.y = 384.0f + 64; 
		}

		// �̴ϼ�
		for (int i = 0; i < 3; i++)
		{
			initial[i] = CMatrix();
			initial[i].position.x = 512.0f - (64 * 3 / 2) + (64 * i);
			initial[i].position.y = 384.0f;
		}
	}
}
CEndingScene:: ~CEndingScene()
{

}
void CEndingScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	ending.Update(deltaTime);

	if (!noRanking)
	{
		// ����
		int tempScore = gScoreManager->scoreDatas[3].score;
		for (int i = 5; i >= 0; i--)
		{
			scoreNum[i].currentScene = tempScore % 10;
			tempScore /= 10;
		}

		for (int i = 0; i < 6; i++)
		{
			scoreNum[i].Update(deltaTime);
		}

		// �̴ϼ�
		for (int i = 0; i < 3; i++)
		{
			initial[i].currentScene = gScoreManager->scoreDatas[3].initial[i];
			initial[i].Update(deltaTime);
		}
	}
}
void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);
	if (isVictory)
		ending.Draw(sprite, gAssetManager->victoryTexture); //���� ���� �׸�
	else
		ending.Draw(sprite, gAssetManager->gameoverTexture); //���� ���� �׸�

	if (!noRanking)
	{
		// ����
		for (int i = 0; i < 6; i++)
		{
			scoreNum[i].Draw(sprite, gAssetManager->numberTexture);
		}

		// �̴ϼ�
		for (int i = 0; i < 3; i++)
		{
			if (i <= inputCount)
				initial[i].Draw(sprite, gAssetManager->alphabetTexture);
		}
	}
}
void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			inputCount++;
			if (inputCount >= 4 || noRanking)
			{
				gScoreManager->Save();
				ChangeScene("Title");
			}
		}
		else
		{
			// ���ĺ� ���� �˻�
			if (!noRanking && inputCount < 3
				&& wParam >= 65 && wParam <= 90)
				gScoreManager->scoreDatas[3].initial[inputCount] = (int)wParam - 65;
		}
		break;
	}
}
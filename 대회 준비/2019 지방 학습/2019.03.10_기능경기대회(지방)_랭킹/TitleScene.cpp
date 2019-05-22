#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(),scene(), howtoplay(), ranking(), activeHowtoplay(false), activeRanking(false)
{
	// i = ��� j = �� Matrix�� index
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			scoreNum[i][j] = CMatrix();
			scoreNum[i][j].position.x = 100.0f + 113 * j;
			scoreNum[i][j].position.y = 384.0f - 150.0f + 100.0f * i;
		}

		// �̴ϼ�
		for (int j = 0; j < 3; j++)
		{
			initial[i][j] = CMatrix();
			initial[i][j].position.x = 100.0f + (113 * 6) + (64 * j);
			initial[i][j].position.y = 384.0f - 150.0f + 100.0f * i;
		}
	}
}
CTitleScene::~CTitleScene()
{

}
void CTitleScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	scene.Update(deltaTime);
	howtoplay.Update(deltaTime);
	ranking.Update(deltaTime);

	// ��ŷ �׸���
	if (activeRanking)
	{
		for (int i = 0; i < 3; i++)
		{
			// ����
			int tempScore = gScoreManager->scoreDatas[i].score;
			for (int j = 5; j >= 0; j--)
			{
				scoreNum[i][j].currentScene = tempScore % 10;
				tempScore /= 10;
			}

			for (int j = 0; j < 6; j++)
			{
				scoreNum[i][j].Update(deltaTime);
			}

			// �̴ϼ�
			for (int j = 0; j < 3; j++)
			{
				initial[i][j].currentScene = gScoreManager->scoreDatas[i].initial[j];
				initial[i][j].Update(deltaTime);
			}
		}
	}
}
void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	scene.Draw(sprite,gAssetManager->titleTexture);

	if(activeHowtoplay)
		howtoplay.Draw(sprite, gAssetManager->howtoTexture);

	// ��ŷ �׸���
	if (activeRanking)
	{
		ranking.Draw(sprite, gAssetManager->rankingBackgroundTexture);

		for (int i = 0; i < 3; i++)
		{
			// ����
			for (int j = 0; j < 6; j++)
			{
				scoreNum[i][j].Draw(sprite, gAssetManager->numberTexture);
			}

			// �̴ϼ�
			for (int j = 0; j < 3; j++)
			{
				initial[i][j].Draw(sprite, gAssetManager->alphabetTexture);
			}
		}
	}
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
			if (!activeHowtoplay && !activeRanking) // ���� �ٲ�
			{
				scene.currentScene--;
				if (scene.currentScene < 0)
					scene.currentScene = 0;
			}
			break;
		case VK_DOWN:
			if (!activeHowtoplay && !activeRanking) // ���� �ٲ�
			{
				scene.currentScene++;
				if (scene.currentScene > 3)
					scene.currentScene = 3;
			}
			break;
		case VK_RETURN:
			if (scene.currentScene == 0)
			{
				ChangeScene("Game_Stage");
			}
			else if (scene.currentScene == 1)
			{
				activeHowtoplay = !activeHowtoplay;
			}
			else if (scene.currentScene == 2)
			{
				// ��ŷ ȭ�� ��ȯ �κ�
				activeRanking = !activeRanking;

				// ��ŷ ȭ������ ��ȯ�Ǹ� ����� �����͸� ȣ���Ѵ�.
				if (activeRanking)
					gScoreManager->Load();
			}
			else if (scene.currentScene == 3)
			{
				PostQuitMessage(0);
			}
			break;

		}
		break;
	}
}
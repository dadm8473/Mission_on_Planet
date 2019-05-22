#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(),scene(), howtoplay(), ranking(), activeHowtoplay(false), activeRanking(false)
{
	// i = 등수 j = 각 Matrix의 index
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			scoreNum[i][j] = CMatrix();
			scoreNum[i][j].position.x = 100.0f + 113 * j;
			scoreNum[i][j].position.y = 384.0f - 150.0f + 100.0f * i;
		}

		// 이니셜
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

	// 랭킹 그리기
	if (activeRanking)
	{
		for (int i = 0; i < 3; i++)
		{
			// 점수
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

			// 이니셜
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

	// 랭킹 그리기
	if (activeRanking)
	{
		ranking.Draw(sprite, gAssetManager->rankingBackgroundTexture);

		for (int i = 0; i < 3; i++)
		{
			// 점수
			for (int j = 0; j < 6; j++)
			{
				scoreNum[i][j].Draw(sprite, gAssetManager->numberTexture);
			}

			// 이니셜
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
			if (!activeHowtoplay && !activeRanking) // 조건 바뀜
			{
				scene.currentScene--;
				if (scene.currentScene < 0)
					scene.currentScene = 0;
			}
			break;
		case VK_DOWN:
			if (!activeHowtoplay && !activeRanking) // 조건 바뀜
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
				// 랭킹 화면 전환 부분
				activeRanking = !activeRanking;

				// 랭킹 화면으로 전환되면 저장된 데이터를 호출한다.
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
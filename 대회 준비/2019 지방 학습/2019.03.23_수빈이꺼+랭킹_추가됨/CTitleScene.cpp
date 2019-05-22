#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(), titleImage(new CMatrix()), backGroundImage(new CMatrix), tankImage(new CMatrix), kreditImage(new CMatrix),
	howToImage(new CMatrix()), rankImage(new CMatrix()), introImage(new CMatrix), isRank(false), isHowTo(false), intro(true), isKredit(false)
{
	tankImage->SetAnimation(0.03f, 20, true);
	introImage->SetAnimation(0.04f, 40, false);

	// ���� �߰��� �κ� ================================================ //
	for (int i = 0; i < 3; i++)
	{
		// ���ڿ� ��ġ �����ϱ�
		for (int j = 0 ; j < 6 ; j++)
		{
			scoreNum[i][j] = CMatrix();
			scoreNum[i][j].position.x = 100.0f + 32 * j;
			scoreNum[i][j].position.y = 100.0f + 100 * i;
		}

		// �̴ϼ� ��ġ �����ϱ�
		for (int j = 0; j < 3; j++)
		{
			initial[i][j] = CMatrix();
			initial[i][j].position.x = (100.0f + 32 * 6) + 64 * j;
			initial[i][j].position.y = 100.0f + 100 * i;
		}
	}
	// ================================================================ //
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
		{
			rankImage->Update(deltaTime);

			// ��ŷ ������ �� �߰��� �κ�=========================================//

			// ���� : 2���� �迭�� �� �����ؼ� �ڵ��ϵ���
			// i = ��ŷ ����
			// j = �� �׸��� index��
			for (int i = 0; i < 3; i++)
			{
				// ���ھ� �κ�
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
			// ================================================================ //
		}
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
		{
			rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));

			// ��ŷ ������ �� �߰��� �κ�=========================================//
			for (int i = 0; i < 3; i++)
			{
				// ����
				for (int j = 0; j < 6; j++)
				{
					scoreNum[i][j].Draw(sprite, gAssetManager->GetTexture("Num"));
				}

				// �̴ϼ�
				for (int j = 0; j < 3; j++)
				{
					initial[i][j].Draw(sprite, gAssetManager->GetTexture("Alphabet"));
				}
			}
			// ================================================================ //
		}
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
					if (isRank)
					{
						gScoreManager->Load();
					}
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

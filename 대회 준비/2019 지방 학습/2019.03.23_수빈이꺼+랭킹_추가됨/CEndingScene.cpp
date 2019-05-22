#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	:CScene(), winImage(new CMatrix), loseImage(new CMatrix), isWin(false), isEnter(false)
{
	this->isWin = isWin;

	// 새로 추가된 부분================================================= //
	isRanking = false; // 랭킹 입력 상태는 기본적으로 false

	curInputindex = 0;
	blinkTimer = 0.0f;

	// 위치 지정해주는 부분
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

	// 위치 지정해주는 부분
	noRankingMessage = new CMatrix();
	noRankingMessage->position.x = 0.0f;
	noRankingMessage->position.y = 0.0f;

	// 주의 : EndingScene에서 내 최종 점수와 랭킹의 최하위 점수와 비교해서 랭킹 입력 유무를 결정해야하기 때문에
	// SocreManager를 Load해서 이전 데이터들을 불러와야한다.
	gScoreManager->Load();
	
	// 현재 내 최종 점수와 3등의 점수를 비교해본다.
	if (gScoreManager->scoreDatas[2].score < score)
	{
		// 3 등과 비교해서 내 점수가 높아서 랭킹등록을 한다.
		isRanking = true;

		// 랭킹 끝 부분에 내 점수 넣어준다.
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

	// 새로 추가된 부분 ================================================ //
	if (isRanking) // 랭킹 입력 상태일 때
	{
		// 스코어 Update
		// 숫자를 CurrentScene으로 변환하는 부분
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

		// 이니셜 Update
		blinkTimer += deltaTime * 3; // 이니셜을 깜빡이게하기 위한 변수 (*3은 깜빡이는 속도를 빠르게 하려고)
		for (int i = 0; i < 3; i++)
		{
			Initial[i]->currentScene = gScoreManager->scoreDatas[3].initial[i]; // 현재 내 점수와 이니셜은 EndingScene진입 시점에서 scoreDatas 맨뒤 여기서는 3번에 저장되어있음
			Initial[i]->Update(deltaTime);
		}
	}
	else // 랭킹 입력이 아닐 때
	{
		noRankingMessage->Update(deltaTime);
	}

	// 조금 수정된 부분 ================================================ //
	if (isEnter)
	{
		// 타이틀을 넘어가는 시점에 ScoreData를 정렬과 저장을 해준다.
		gScoreManager->Save(); // 정렬은 Save() 함수 안에서 자동으로 하게 해줬다.
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

	// 새로 추가된 부분 ================================================ //
	if (isRanking)
	{
		for (int i = 0; i < 6; i++)
		{
			Num[i]->Draw(sprite, gAssetManager->GetTexture("Num"));
		}

		for (int i = 0; i < 3; i++)
		{
			if (i <= curInputindex) // 이니셜 배열이 넘지 않게 처리
			{
				if (i != curInputindex || (i == curInputindex && (int)blinkTimer % 2 == 0)) // 이건 깜빡이게 하기 위한 조건문
				{
					Initial[i]->Draw(sprite, gAssetManager->GetTexture("Alphabet"));
				}
			}
		}
	}
	else // 랭킹 입력이 아닐 때 다른 그림이 나오도록 함
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
			// 이니셜 배열이 넘지않게 
			if (curInputindex < 3)
			{
				// 알파뱃 영역
				if (wParam >= 65 && wParam <= 90) // 주의 : 알파뱃 영역을 잘 기억하도록
				{
					gScoreManager->scoreDatas[3].initial[curInputindex] = wParam-65; // 주의 : -65를 꼭 해줘야함 
				}
			}
		}

		switch (wParam)
		{
		case VK_RETURN: // 엔터를 눌러서 다음 이니셜을 입력할 수 있도록 처리
			curInputindex++;
			if (curInputindex == 4 || !isRanking) // 엔터 4번째 눌렀을 때 or 랭킹 화면이 아닐때 바로
				isEnter = true;

			break;
		}
		break;
	}
}

#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(),scene(), howtoplay(), activeHowtoplay(false)
{
	
}
CTitleScene::~CTitleScene()
{

}
void CTitleScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	scene.Update(deltaTime);
	howtoplay.Update(deltaTime);
}
void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	scene.Draw(sprite,gAssetManager->titleTexture);

	if(activeHowtoplay)
		howtoplay.Draw(sprite, gAssetManager->howtoTexture);
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
			if (!activeHowtoplay)
			{
				scene.currentScene--;
				if (scene.currentScene < 0)
					scene.currentScene = 0;
			}
			break;
		case VK_DOWN:
			if (!activeHowtoplay)
			{
				scene.currentScene++;
				if (scene.currentScene > 3)
					scene.currentScene = 3;
			}
			break;
		case VK_RETURN:
			if (scene.currentScene == 0)			//메인화면 -> 게임화면으로 이동
			{
				ChangeScene("Game_Stage_1");
			}
			else if (scene.currentScene == 1)		//메인화면 -> 게임조작법 보기
			{
				/*if (!activeHowtoplay)
					activeHowtoplay = true;
				else
					activeHowtoplay = false;*/		// 이 구문을 한줄로 바꾼것이 밑에 구문

				activeHowtoplay = !activeHowtoplay;
			}
			else if (scene.currentScene == 2)		//메인화면 -> 랭킹
			{

			}
			else if (scene.currentScene == 3)		//메인화면 -> 게임 종료
			{
				PostQuitMessage(0);
			}
			break;

		}

		break;
	}
}
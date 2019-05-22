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
			if (scene.currentScene == 0)			//����ȭ�� -> ����ȭ������ �̵�
			{
				ChangeScene("Game_Stage_1");
			}
			else if (scene.currentScene == 1)		//����ȭ�� -> �������۹� ����
			{
				/*if (!activeHowtoplay)
					activeHowtoplay = true;
				else
					activeHowtoplay = false;*/		// �� ������ ���ٷ� �ٲ۰��� �ؿ� ����

				activeHowtoplay = !activeHowtoplay;
			}
			else if (scene.currentScene == 2)		//����ȭ�� -> ��ŷ
			{

			}
			else if (scene.currentScene == 3)		//����ȭ�� -> ���� ����
			{
				PostQuitMessage(0);
			}
			break;

		}

		break;
	}
}
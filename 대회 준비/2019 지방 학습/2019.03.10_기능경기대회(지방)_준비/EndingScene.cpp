#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isVictory)
	:CScene(),isVictory(isVictory),ending()
{

}
CEndingScene:: ~CEndingScene()
{

}
void CEndingScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	ending.Update(deltaTime);
}
void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);
	if (isVictory)
		ending.Draw(sprite, gAssetManager->victoryTexture); //성공 관련 그림
	else
		ending.Draw(sprite, gAssetManager->gameoverTexture); //실패 관련 그림
}
void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:

		if (wParam == VK_RETURN)
		{
			ChangeScene("Title");
		}

		break;
	}
}
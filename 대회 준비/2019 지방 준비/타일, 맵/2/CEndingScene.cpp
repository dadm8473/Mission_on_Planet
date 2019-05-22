#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	: winImage(new CMatrix), loseimage(new CMatrix), isWin(isWin)
{
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseimage;
}

void CEndingScene::Update(float deltaTime)
{
	if (isWin)
		winImage->Update(deltaTime);
	else
		loseimage->Update(deltaTime);
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseimage->Draw(sprite, gAssetManager->GetTexture("Lose"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			ChangeScene("Title");
			break;
		}
		break;
	}
}

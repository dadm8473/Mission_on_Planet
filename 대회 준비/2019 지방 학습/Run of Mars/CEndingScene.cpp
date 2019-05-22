#include "DXUT.h"
#include "Header.h"


CEndingScene::CEndingScene(bool isWin)
	: winIamge(new CMatrix), loseImage(new CMatrix), isWin(isWin)
{
}

CEndingScene::~CEndingScene()
{
	delete winIamge;
	delete loseImage;
}

void CEndingScene::Update(float deltaTime)
{
	if (isWin)
		winIamge->Update(deltaTime);
	else
		loseImage->Update(deltaTime);
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	if (isWin)
		winIamge->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPara)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			ChangeScene("TItle");
			break;
		}
		break;
	}
}

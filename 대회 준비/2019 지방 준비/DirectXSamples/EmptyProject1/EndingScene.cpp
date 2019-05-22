#include "DXUT.h"
#include "Header.h"
#include "EndingScene.h"

CEndingScene::CEndingScene(bool isWin)
	:CScene(), winImage(new CMatrix), loseImage(new CMatrix), isWin(false), isEnter(false)
{
	this->isWin = isWin;
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseImage;
}

void CEndingScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (isWin)
		winImage->Update(deltaTime);
	else
		loseImage->Update(deltaTime);

	if (isEnter)
	{
		ChangeScene(0);
	}
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		isEnter = true;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			isEnter = true;
		}
		break;
	}
}

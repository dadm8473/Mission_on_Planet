#pragma once
class CEndingScene : public CScene
{
public:
	CMatrix* winIamge;
	CMatrix* loseImage;

	bool isWin;

public:
	CEndingScene(bool iswin);
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPara);
};


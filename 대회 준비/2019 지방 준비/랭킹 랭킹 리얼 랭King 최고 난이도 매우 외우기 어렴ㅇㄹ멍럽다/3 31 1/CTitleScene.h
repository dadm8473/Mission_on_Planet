#pragma once
class CTitleScene : public  CScene
{
public:
	CMatrix* titleImage;
	CMatrix* howToImage;
	CMatrix* rankImage;

	bool isHowTo;
	bool isRank;

	CMatrix* num[3][6];
	CMatrix* initial[3][3];

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


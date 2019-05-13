#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* titleImage;
	CMatrix* howToImage;
	CMatrix* rankImage;
	CMatrix* introImage;
	CMatrix* iuImage;
	CMatrix* kreditImage;

	CMatrix* BGImage;
	CMatrix* mainAni;

	bool isHowTo;
	bool isRank;
	bool isIntro;
	bool isIu;
	bool isKredit;

public:
	CMatrix* num[3][6];
	CMatrix* initial[3][3];

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


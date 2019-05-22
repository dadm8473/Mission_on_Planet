#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* titleImage;
	CMatrix* backGroundImage;
	CMatrix* tankImage;

	CMatrix* howToImage;
	CMatrix* rankImage;
	CMatrix* kreditImage;

	CMatrix* introImage;

	bool isHowTo;
	bool isRank;
	bool isKredit;

	bool intro;

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


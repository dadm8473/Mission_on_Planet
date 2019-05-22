#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* titleImage;
	CMatrix* howToImage;
	CMatrix* rankImage;
	CMatrix* kreditImage;

	bool isHowTo;
	bool isRank;
	bool isKredit;

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPara);
};


#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* titleimage;
	CMatrix* howToimage;
	CMatrix* rankImage;

	bool isHowTo;
	bool isRank;

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


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

	// ���� �߰��� �κ� ================================================ //
	CMatrix scoreNum[3][6];
	CMatrix initial[3][3];
	// ================================================================ //

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


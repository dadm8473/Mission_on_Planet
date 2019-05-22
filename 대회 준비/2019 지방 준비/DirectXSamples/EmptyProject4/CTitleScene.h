#pragma once
class CTitleScene : public CScene
{
public:
	CTitleScene();
	~CTitleScene();
	virtual void Updaet(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


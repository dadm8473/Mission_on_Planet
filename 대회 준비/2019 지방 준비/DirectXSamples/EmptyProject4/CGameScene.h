#pragma once
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();
	virtual void Updaet(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


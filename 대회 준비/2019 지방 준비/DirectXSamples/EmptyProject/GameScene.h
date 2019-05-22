#pragma once
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();
public:
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


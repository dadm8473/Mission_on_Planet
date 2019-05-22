#pragma once
class CGameScene : public CScene
{
public:
	CGameScene(int stage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#pragma once
class CScene
{
public:
	CScene();
	~CScene();
	virtual void Updaet(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


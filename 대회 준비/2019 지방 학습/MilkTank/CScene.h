#pragma once
class CScene
{
public:
	CScene();
	~CScene();
	virtual void Update(float detlaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


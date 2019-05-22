#pragma once
class CEndingScene : public CScene
{
public:
	CEndingScene();
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lPamam);
};


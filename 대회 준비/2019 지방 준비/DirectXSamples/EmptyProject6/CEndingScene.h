#pragma once
class CEndingScene : public Scene
{
public:
	CEndingScene();
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXVECTOR2 sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


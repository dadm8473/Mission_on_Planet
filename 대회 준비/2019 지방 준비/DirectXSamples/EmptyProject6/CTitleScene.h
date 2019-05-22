#pragma once
class CTitleScene : public Scene
{
public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXVECTOR2 sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


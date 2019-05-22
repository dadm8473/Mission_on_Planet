#pragma once

class CTitleScene :public CScene
{
public:

	CMatrix scene;	//화면을 표시할 메트릭스
	CMatrix howtoplay;

	bool activeHowtoplay;

	CTitleScene(); //Init
	virtual ~CTitleScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
#pragma once

class CTitleScene :public CScene
{
public:

	CMatrix scene;	//ȭ���� ǥ���� ��Ʈ����
	CMatrix howtoplay;

	bool activeHowtoplay;

	CTitleScene(); //Init
	virtual ~CTitleScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
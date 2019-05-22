#pragma once

class CTitleScene :public CScene
{
public:

	CMatrix scene;
	CMatrix howtoplay;

	bool activeHowtoplay;

	// ���� �߰��� �κ�
	bool activeRanking;

	// 1~3�� ���� ������ �̴ϼ��� ������ ��
	CMatrix ranking; // ��ŷ ȭ��
	CMatrix scoreNum[3][6];
	CMatrix initial[3][3];

	CTitleScene(); //Init
	virtual ~CTitleScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
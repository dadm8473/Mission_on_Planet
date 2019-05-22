#pragma once

class CTitleScene :public CScene
{
public:

	CMatrix scene;
	CMatrix howtoplay;

	bool activeHowtoplay;

	// 새로 추가된 부분
	bool activeRanking;

	// 1~3위 까지 점수와 이니셜을 보여줄 것
	CMatrix ranking; // 랭킹 화면
	CMatrix scoreNum[3][6];
	CMatrix initial[3][3];

	CTitleScene(); //Init
	virtual ~CTitleScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
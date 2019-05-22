#pragma once

class CEndingScene : public CScene
{
public:
	CMatrix ending;
	
	bool isVictory;
	
	// 새로 추가된 부분
	CMatrix scoreNum[6];
	CMatrix initial[3];
	
	// 랭킹 입력 변수
	bool noRanking;
	int inputCount;

	CEndingScene(bool isVictory, int score);	//Init
	virtual ~CEndingScene();					//Termn
	virtual void Update(float deltaTime);		//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
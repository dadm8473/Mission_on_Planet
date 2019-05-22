#pragma once

class CEndingScene : public CScene
{
public:
	/*
	엔딩(성공 혹은 실패) 그림이 뜨고, 엔터키를 누르면 메인화면으로 이동합니다.
	*/

	CMatrix ending;

	bool isVictory;

	CEndingScene(bool isVictory); //Init
	virtual ~CEndingScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
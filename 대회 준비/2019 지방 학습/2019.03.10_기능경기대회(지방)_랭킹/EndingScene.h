#pragma once

class CEndingScene : public CScene
{
public:
	CMatrix ending;
	
	bool isVictory;
	
	// ���� �߰��� �κ�
	CMatrix scoreNum[6];
	CMatrix initial[3];
	
	// ��ŷ �Է� ����
	bool noRanking;
	int inputCount;

	CEndingScene(bool isVictory, int score);	//Init
	virtual ~CEndingScene();					//Termn
	virtual void Update(float deltaTime);		//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
#pragma once

class CEndingScene : public CScene
{
public:
	/*
	����(���� Ȥ�� ����) �׸��� �߰�, ����Ű�� ������ ����ȭ������ �̵��մϴ�.
	*/

	CMatrix ending;

	bool isVictory;

	CEndingScene(bool isVictory); //Init
	virtual ~CEndingScene();	//Termn
	virtual void Update(float deltaTime);	//Update
	virtual void Render(LPD3DXSPRITE sprite);	//Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	//MsgProc
};
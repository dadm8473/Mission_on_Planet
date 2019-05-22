#pragma once
class CEndingScene : public CScene
{
public:
	CMatrix* winImage;
	CMatrix* loseImage;
	bool isWin;

	// ���� �߰��� �κ� ================================================ //
	bool isEnter;
	bool isRanking; // �� : ��ŷ ���̴°� / ���� : ������ ���� 

	int curInputindex; // �Է� ������� ���ڸ� index�� ����

	float blinkTimer; // �����̴� Ÿ�̹�

	CMatrix* Num[6];
	CMatrix* Initial[3];
	CMatrix* noRankingMessage;
	// ================================================================ //
public:
	CEndingScene(bool isWin);
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};


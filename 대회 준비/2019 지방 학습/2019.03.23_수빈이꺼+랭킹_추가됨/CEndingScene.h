#pragma once
class CEndingScene : public CScene
{
public:
	CMatrix* winImage;
	CMatrix* loseImage;
	bool isWin;

	// 새로 추가된 부분 ================================================ //
	bool isEnter;
	bool isRanking; // 참 : 랭킹 보이는거 / 거짓 : 순위에 들지 

	int curInputindex; // 입력 대기중인 문자를 index로 관리

	float blinkTimer; // 깜빡이는 타이밍

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


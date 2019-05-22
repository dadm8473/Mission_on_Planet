#pragma once

// 세이브 데이터 구조체
// 이 구조체를 파일로 저장하고 불러온다.
struct ScoreInfo
{
public :
	int score = 0;
	int initial[3] = { 0, };
};

// 스코어 
class CScoreManager
{
public : 
	// 1~3위 그리고 현재 자신의 점수가 들어갈 Vector
	vector<ScoreInfo> scoreDatas;

	void Save();
	void Load();

	// sort는 저장과 동시에 작동하게 해도 됨
	void Sort();
};

// 주의 : Game.cpp에서 Init()안에다 gScoreManager 초기화 해주기
extern CScoreManager*gScoreManager;

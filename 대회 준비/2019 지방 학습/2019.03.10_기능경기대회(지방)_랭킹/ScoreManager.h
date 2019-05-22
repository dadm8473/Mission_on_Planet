#pragma once

// 세이브 데이터 구조체
struct ScoreInfo
{
public :
	int score = 0;
	int initial[3] = { 0, };
};

class CScoreManager
{
public:
	vector<ScoreInfo> scoreDatas;

	void Save();
	void Load();

	void Sort();
};
extern CScoreManager*gScoreManager;
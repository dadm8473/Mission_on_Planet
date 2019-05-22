#pragma once

struct ScoreInfo
{
public:
	int score = 0;
	int initial[3] = { 0, };
};

class CScoreManager
{
public:
	vector<ScoreInfo> scoreData;

public:
	void Save();
	void Load();
	void Sort();
};

extern CScoreManager* gScoreManager;